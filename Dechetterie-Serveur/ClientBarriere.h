#pragma once
#include "Client.h"
#include "Enum.h"
#include "Logger.h"
#include "Protocole\Protocole.h"


using namespace System;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic;

ref class ClientBarriere : public Client
{
protected:
	int _pos;

	void fctThread() override 
	{
		while (true)
		{
			if (_clientSocket != nullptr)
			{
				try
				{
					if (_clientSocket->Connected)
					{
						array<Byte>^ data = gcnew array<Byte>(1024);
						_clientSocket->Receive(data);
						ProtocolMsg^ pm = protocole->translateReceive(data);

						if (pm->type == protocole->GetTypeProtocoleByID("AllPing"))
						{
							this->Send(protocole->RetourPing());
							Logger::PrintLog("PING", "Demande de ping de " + _ip->ToString() + "( " + _groupe.ToString() + " " + _type.ToString() + " )");
						}
						else
						{
							if (pm->type == protocole->GetTypeProtocoleByID("brRDPos"))
							{
								_pos = pm->getData1Int();
								Logger::PrintLog("");
							}
							else
							{
								bufferRecv = data;
							}
						}
					}
					else
					{
						this->Disconnect();
					}
				}
				catch (Exception^e)
				{

					//Console::WriteLine("[ Client ][ Thread Receive ]" + e);

				}
			}
			Thread::Sleep(100);
		}
	}
	void startReceive() override
	{
		_thread = gcnew Thread(gcnew ThreadStart(this, &ClientBarriere::fctThread));
		_thread->Name = "Client IP " + _ip->ToString();
		_thread->Start();
	}

public:
	int getPosition(){ return _pos; }
	ClientBarriere(id_groupe groupe, IPAddress^ip) : Client(groupe, id_client::ClientBarrière, ip)
	{

	}
	void OuvrirBarriere()
	{
		this->Send(protocole->OuvrirBarriere());
	}
	void FermerBarriere()
	{
		this->Send(protocole->FermerBarriere());
	}
};

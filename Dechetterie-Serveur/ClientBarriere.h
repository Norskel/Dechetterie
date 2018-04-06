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
private:
	int _pos;

	void fctThread()
	{
		Protocole^ p = Protocole::getProtocole();

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
						ProtocolMsg^ pm = p->translateReceive(data);
						if (pm->type == p->GetTypeProtocoleByID("AllPing"))
						{
							this->Send(p->RetourPing());
							Logger::PrintLog("PING", "Demande de ping de " + _ip->ToString() + "( " + id_groupe(_groupe).ToString() + " " + id_client(_type).ToString() + " )");
						}
						else
						{
							if (pm->type == p->GetTypeProtocoleByID("brRDPos"))
							{
								_pos = pm->getData1Int();
								Logger::PrintLog("", "Demande de ping de " + _ip->ToString() + "( " + id_groupe(_groupe).ToString() + " " + id_client(_type).ToString() + " )");
							}
							else
							{

							}
						}
					}
					else
					{
						Console::WriteLine("[ Serveur " + id_groupe(_groupe).ToString() + " ] " + id_client(_type).ToString() + " viens de ce déconnectée");
						_isConnected = false;
						_clientSocket->Close();
					}
				}
				catch (Exception^e)
				{

					//Console::WriteLine("[ Client ][ Thread Receive ]" + e);

				}
			}
			Thread::Sleep(1000);
		}
	}
public:
	int getPosition()
	{
		return _pos;
	}
	ClientBarriere(int groupe, IPAddress^ip) : Client(groupe, 2, ip)
	{

	}
};

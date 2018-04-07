#pragma once
#include "Client.h"
#define TIMEOUT_GET_POIDS 15

ref class ClientBalance : public Client
{

private:
	int _poids = 0;

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
							if (pm->type == protocole->GetTypeProtocoleByID("baRDPoids"))
							{
								_poids = pm->getData1Int();
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
		_thread = gcnew Thread(gcnew ThreadStart(this, &ClientBalance::fctThread));
		_thread->Name = "Client IP " + _ip->ToString();
		_thread->Start();
	}
public:

	int getPoids()
	{
		this->Send(protocole->GetBalancePoids());
		int timeout = 0;
		int r;
		while (_poids == 0 && timeout < TIMEOUT_GET_POIDS)
		{
			Thread::Sleep(500);
			timeout++;
		}
		if (timeout >= TIMEOUT_GET_POIDS)
		{
			throw gcnew Exception("Timeout Get Poids");
		}
		else
		{
			r = _poids;
			_poids = 0;
			return r;
		}

	}
	ClientBalance(id_groupe groupe, IPAddress^ip) : Client(groupe, id_client::ClientBalance, ip)
	{
		
	}



};


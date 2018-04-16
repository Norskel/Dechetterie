#pragma once
#include "Client.h"
#define TIMEOUT_GET_POIDS 15

ref class ClientBalance : public Client
{

protected:
	int _poids = 0;
	void fonctionReceive(ProtocolMsg^ pm, array<Byte>^ data) override
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
	ClientBalance(id_groupe groupe, IPAddress^ip) : Client(groupe, id_client::ClientBalance, ip){}



};


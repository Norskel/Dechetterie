#pragma once
#include "Client.h"
#define TIMEOUT_GET_POIDS 15

ref class ClientBalance : public Client
{

protected:
	float _poids = 0;
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
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
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	float getPoids()
	{
		this->Send(protocole->GetBalancePoids());
		int timeout = 0;
		float r;
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
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	ClientBalance(id_groupe groupe, IPAddress^ip) : Client(groupe, id_client::ClientBalance, ip){}



};


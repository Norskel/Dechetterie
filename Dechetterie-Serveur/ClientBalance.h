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
	Nom          : getPoids
	Description  : Permet la récuperation du poids
	Arguments    :
	Valeur renvoyée : le poids en kg : float
	-----------------------------------------------------------------*/
	float getPoids()
	{
		this->Send(protocole->GetBalancePoids()); // on fait une demande de poids a la balance
		int timeout = 0; 
		float r;
		while (_poids == 0 && timeout < TIMEOUT_GET_POIDS) // on attend que le thread recois la valeur et qu'il modifie la variable poids
		{
			Thread::Sleep(500);
			timeout++;
		}
		if (timeout >= TIMEOUT_GET_POIDS) // si on attend trop longtemps le timeout prend le relais et crée une execption
		{
			throw gcnew Exception("Timeout Get Poids");
		}
		else // sinon on recupere le poids qu'on a eu et on remet la valeur à 0
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
	~ClientBalance()
	{
		Disconnect();
		_thread->Abort();
	}


};


#pragma once
#include "Client.h"
#include "Enum.h"
#include "Logger.h"
#include "Protocole\Protocole.h"

ref class Client;
ref class ClientBarriere : public Client
{
protected:
	int _pos;
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	void fonctionReceive(ProtocolMsg^ pm, array<Byte>^ data) override
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

public:
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	int getPosition(){ return _pos; }
	/*---------------------------------------------------------------
	Nom          :  
	Description  :  
	Arguments    :  
	Valeur renvoyée : 
	-----------------------------------------------------------------*/
	ClientBarriere(id_groupe groupe, IPAddress^ip) : Client(groupe, id_client::ClientBarrière, ip)
	{

	}
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	void OuvrirBarriere()
	{
		this->Send(protocole->OuvrirBarriere());
	}
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	void FermerBarriere()
	{
		this->Send(protocole->FermerBarriere());
	}
};

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
	Valeur renvoy�e :
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
	Valeur renvoy�e :
	-----------------------------------------------------------------*/
	int getPosition(){ return _pos; }
	/*---------------------------------------------------------------
	Nom          :  
	Description  :  
	Arguments    :  
	Valeur renvoy�e : 
	-----------------------------------------------------------------*/
	ClientBarriere(id_groupe groupe, IPAddress^ip) : Client(groupe, id_client::ClientBarri�re, ip)
	{

	}
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoy�e :
	-----------------------------------------------------------------*/
	void OuvrirBarriere()
	{
		this->Send(protocole->OuvrirBarriere());
	}
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoy�e :
	-----------------------------------------------------------------*/
	void FermerBarriere()
	{
		this->Send(protocole->FermerBarriere());
	}
};

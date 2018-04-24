#pragma once
#define TEMPO_BARRIERE 20000

#include "Serveur.h"
#include "StructGroupeClient.h"
#include "DataBddProxy.h"

using namespace System;

ref class Groupe
{
protected:
	GroupeClient^ _listClient;
	Serveur^ _srv;
	virtual void AccesDemandEvent(String^ rfid) {}
	DataBddProxy^ _bdd;
	Protocole^ protocole;
	id_groupe _idGroupe;
public:
	Groupe(id_groupe id, IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid)
	{
		Logger::PrintLog(id.ToString(), "Interface d'écoute : " + listenip + " Port d'écoute : " + listenPort);
		_listClient = gcnew GroupeClient();
		_listClient->ClientBarriere = gcnew ClientBarriere(id, ipBarriere);
		_listClient->ClientBalance = gcnew ClientBalance(id, ipBalance);
		_listClient->ClientRFID = gcnew ClientRFID(id, ipRfid);

		_srv = gcnew Serveur(listenip, listenPort, id, _listClient);
		_srv->Start();

		_idGroupe = id;

		this->_listClient->ClientRFID->AccesDemand += gcnew AccesDemandDelegate(this, &Groupe::AccesDemandEvent);

		_bdd = DataBddProxy::getDataBddProxy();
		protocole = Protocole::getProtocole();

	}

	/*---------------------------------------------------------------
	Nom          : OuvrirBarriere
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	void OuvrirBarriere()
	{
		if (_listClient->ClientBarriere->getState())
		{
			_listClient->ClientBarriere->OuvrirBarriere();
		}

	}

	/*---------------------------------------------------------------
	Nom          : FermerBarriere
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	void FermerBarriere()
	{
		if (_listClient->ClientBarriere->getState())
		{
			_listClient->ClientBarriere->FermerBarriere();
		}
	}

	/*---------------------------------------------------------------
	Nom          : GetPositionBarriere
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	int GetPositionBarriere()
	{
		if (_listClient->ClientBarriere->getState())
		{
			return _listClient->ClientBarriere->getPosition();
		}
		else
		{
			return -1;
		}

	}

	/*---------------------------------------------------------------
	Nom          : AllClientConnected
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	Boolean AllClientConnected()
	{
		//return	_listClient->ClientBalance->getState() && _listClient->ClientBarriere->getState() && _listClient->ClientRFID->getState();
		return true;
	}

	/*---------------------------------------------------------------
	Nom          : TestRfidID
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	Boolean TestRfidID(String^ rfid)
	{
		try
		{
			DataUser^ user = _bdd->getUserByIdRFID(rfid);
			return true;
		}
		catch (Exception^ e)
		{

			if (e->Message != "ID_RFID Introuvable")
			{
				Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), "[ TestRfidID ]" + e->ToString());
			}

			return false;
		}

	}

	/*---------------------------------------------------------------
	Nom          : GetStateAllClient
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	String^ GetStateAllClient()
	{
		String^ r = "";
		if (_listClient->ClientBarriere->getState()) { r += 1; }
		else { r += 0; }
		if (_listClient->ClientBalance->getState()) { r += 1; }
		else { r += 0; }
		if (_listClient->ClientRFID->getState()) { r += 1; }
		else { r += 0; }
		return r;

	}

};


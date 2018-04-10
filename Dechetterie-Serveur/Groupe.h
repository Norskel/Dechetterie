#pragma once
#include "Serveur.h"
#include "StructGroupeClient.h"
#include "DataBddProxy.h"

using namespace System;

ref class Groupe
{
protected:
	GroupeClient^ _listClient;
	Serveur^ _srv;
	virtual void AccesDemandEvent(String^ rfid);
	DataBddProxy^ _bdd;
	Protocole^ protocole;
	id_groupe _idGroupe;
public:
	Groupe(id_groupe id,IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid);
	void OuvrirBarriere();
	void FermerBarriere();
	int GetPositionBarriere();
	Boolean AllClientConnected();
	Boolean TestRfidID(String^ rfid);
	String^ GetStateAllClient();

};


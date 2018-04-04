#pragma once
#include "Serveur.h"
#include "DataBddProxy.h"
#include "Dechetterie.h"
#include "Protocole\Protocole.h"


using namespace System;
using namespace System::Threading;
using namespace System::Text;


ref class Entree
{
private:
	Serveur^ _srv;
	Thread^ _tEntree;
	void ThreadEntree();
	array<Byte>^ ReceptionPhoto(Client ^ cl);
	String ^ WaitAccesDemand(Client ^ cl);
	int WaitDechetType(Client ^ cl);
	void WaitAllConnection();
	DataBddProxy^ _bdd;

	Protocole^ protocole;

	Client^ _ClientBarrière;
	Client^ _ClientBalance;
	Client^ _ClientRFID;
	int getPoids(Client ^ cl);
	void getClientFromList(List<Client^>^ l);

public:
	Entree(IPAddress ^ listenip, int listenPort);

};


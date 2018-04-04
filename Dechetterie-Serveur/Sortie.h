#pragma once
#include "Serveur.h"
#include "DataBddProxy.h"
#include "Dechetterie.h"
#include "Protocole\Protocole.h"



using namespace System;
using namespace System::Threading;
using namespace System::Text;

ref class Sortie
{
private:
	Protocole^ protocole;

	DataBddProxy^ _bdd;
	Serveur^ _srv;

	Thread^ _tSortie;
	
	Client^ _ClientBarrière;
	Client^ _ClientBalance;
	Client^ _ClientRFID;
	
	int getPoids(Client ^ cl);
	void getClientFromList(List<Client^>^ l);
	String ^ WaitAccesDemand(Client ^ cl);
	void ThreadSortie();
public:
	Sortie(IPAddress ^ listenip, int listenPort);
};


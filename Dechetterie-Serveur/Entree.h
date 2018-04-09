#pragma once
#include "Serveur.h"
#include "DataBddProxy.h"
#include "Dechetterie.h"
#include "Protocole\Protocole.h"
#include "ClientBalance.h"
#include "Groupe.h"


using namespace System;
using namespace System::Threading;
using namespace System::Text;

 
ref class Entree : public Groupe
{
protected:
	void AccesDemandEvent(String^ rfid) override; 
public:
	Entree(IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid);

};


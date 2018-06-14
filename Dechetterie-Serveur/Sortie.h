#pragma once
#include "Groupe.h"
#include "Serveur.h"
#include "DataBddProxy.h"
#include "Protocole\Protocole.h"
#include "Dechetterie.h"

using namespace System;
using namespace System::Text;

ref class Sortie : public Groupe
{
protected:
	void AccesDemandEvent(String^ rfid) override;
public:
	Sortie(IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid);
	~Sortie();
};


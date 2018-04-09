#pragma once
#include "Client.h"
#include "ClientBarriere.h"
#include "ClientBalance.h"
#include "ClientRFID.h"
#include "Enum.h"
#include "StructGroupeClient.h"

using namespace System;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic;

ref class Serveur
{
protected:
	IPAddress^ _interface = IPAddress::Any;
	int _port;
	Socket^ _socketServeur;
	Boolean _isRunning = false;
	Thread^ _tWaitClient;
	GroupeClient^ _listClient;
	id_groupe _groupe;
public:
	Serveur(IPAddress ^ listenip, int listenPort, id_groupe groupe);
	Serveur(IPAddress^ listenip, int listenPort, id_groupe groupe, GroupeClient^ %l);

	Boolean Start();
	void WaitClient();
};


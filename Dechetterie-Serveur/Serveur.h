#pragma once
#include "Client.h"
#include "ClientBarriere.h"
#include "ClientBalance.h"
#include "ClientRFID.h"
#include "Enum.h"

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
	Boolean _isRunning;
	Thread^ _tWaitClient;
	List<Client^>^ _listClient;
	int _groupe = 0;
public:
	Serveur(IPAddress^ listenip, int listenPort,int groupe);
	Serveur(IPAddress^ listenip, int listenPort, int groupe,ClientBalance %cba,ClientBarriere %cbr,ClientRFID %cr);
	Boolean Start();
	void WaitClient();
	List<Client^>^ getClientList();
};


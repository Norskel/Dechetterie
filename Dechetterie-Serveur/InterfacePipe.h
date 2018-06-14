#pragma once
#include "Dechetterie.h"
#include "Entree.h"
#include "Sortie.h"
#include "Protocole\Protocole.h"

#define PIPE_NAME_INTER_SERV_IN "InterfaceServeur"
#define PIPE_NAME_INTER_SERV_OUT "ServeurInterface"

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::IO::Pipes;
using namespace System::Xml::Serialization;
using namespace System::Threading;
using namespace System::Diagnostics;

ref class Entree;
ref class Sortie;
ref class Dechetterie;

ref class InterfacePipe
{
private:
	Thread^ _threadRecev;
	NamedPipeServerStream^ _pipeOutServerInterface;
	NamedPipeServerStream^ _pipeInServerInterface;
	void fctThreadRecev();
	Entree^ _entree;
	Sortie^ _sortie;
	Dechetterie^ _dechetterie;
	String^ getState();
	Protocole^ protocole;
	void OuvrirBarriere(int i);
	void FermerBarriere(int i);
	int PositionBarriere(int i);
	String^ nameServeur;
	Boolean Connect();
	void start();
	Boolean _isConnectedIn = false;
	Boolean _isConnectedOut = false;
	static InterfacePipe^ _interfacePipe;


	InterfacePipe(Entree^ %e, Sortie^ %s, Dechetterie^ const %d);
public:
	static InterfacePipe^ getInterfacePipe();
	static InterfacePipe^ getInterfacePipe(Entree^ %e, Sortie^ %s,  Dechetterie^ const %d);
	void updateListClient();
	void updateClientState();
	~InterfacePipe();
};


#pragma once
#include "Dechetterie.h"
#include "Entree.h"
#include "Sortie.h"
#include "Protocole\Protocole.h"

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

ref class Interface
{
private:
	Thread^ _threadRecev;
	NamedPipeServerStream^ _pipeServerInterface;
	void fctThreadRecev();
	Entree^ _entree;
	Sortie^ _sortie;
	String^ getState();
	Protocole^ protocole;
	void OuvrirBarriere(int i);
	void FermerBarriere(int i);
	int PositionBarriere(int i);

public:
	Interface(String^ name_serveur, Entree^ %e, Sortie^ %s);
};


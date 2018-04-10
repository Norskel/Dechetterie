#pragma once
#include "Protocole\Protocole.h"
#define PIPE_NAME_SERV "PipeInterServ"

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::IO::Pipes;
using namespace System::Xml::Serialization;
using namespace System::Threading;
using namespace System::Diagnostics;

static public enum class id_groupe : int { TOUS, ENTREE, SORTIE };

ref class PipeServeur
{
	PipeServeur();
	static PipeServeur^ _pipeServeur = nullptr;
	Boolean _isConnected = false;
	NamedPipeClientStream^ _pipeClientInterface;
	Boolean Connect();
	Protocole^ protocole;
public:
	static PipeServeur^ GetPipeServeur();

	array<Byte>^ getState();
	array<Byte>^ getPositionBarriere(id_groupe id);
	void ouvrirBarriere(id_groupe id);
	void fermerBarriere(id_groupe id);

};


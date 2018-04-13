#pragma once
#include "Protocole\Protocole.h"
#define PIPE_NAME_INTER_SERV_OUT "InterfaceServeur"
#define PIPE_NAME_INTER_SERV_IN "ServeurInterface"
#define TIMEOUT_GET_STATE 10
#define TIMEOUT_GET_POS 30
#include "Logger.h"

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
ref struct pos {
	int posBarriereEntree = 0;
	int posBarriereSortie = 0;
};

ref class PipeServeur
{
	PipeServeur();
	static PipeServeur^ _pipeServeur = nullptr;
	Boolean _isConnected = false;
	NamedPipeClientStream^ _pipeInClientInterface;
	NamedPipeClientStream^ _pipeOutClientInterface;
	Boolean Connect();
	Protocole^ protocole;
	void fctThread();
	array<Byte>^ _state = nullptr;
	Thread^ _thread;
	void startReceive();
	pos _positionBarriere;
	void disconnect();

public:
	static PipeServeur^ GetPipeServeur();
	event EventHandler<int>^ UpdateClientList;
	array<Byte>^ getState();
	int getPositionBarriere(id_groupe id);
	void ouvrirBarriere(id_groupe id);
	void fermerBarriere(id_groupe id);

};


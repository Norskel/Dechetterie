#pragma once

#include "Enum.h"
#include "Utilisateur.h"
#include "DataBddProxy.h"
#include "Entree.h"
#include "Sortie.h"
#include "Protocole\Protocole.h"
#include "Protocole\StructProtocolMsg.h"
#include "Protocole\StructTypeMessage.h"
#include "StructDataConfigServeur.h"
#include "Logger.h"
#include "Interface.h"

#define PIPE_NAME_INTER_SERV "InterServeur"
#define PIPE_NAME_USER_INFOS_SERV "UserServeur"
#define INTERFACE_PROCESS_NAME "Dechetterie-Interface"  

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::IO::Pipes;
using namespace System::Xml::Serialization;
using namespace System::Threading;
using namespace System::Diagnostics;

delegate void EventUpdateClientStateDelegate();

ref class Entree;
ref class Sortie;
ref class Interface;

ref class Dechetterie
{
private:
	static List<Utilisateur^>^ _listUtilisateur = gcnew List<Utilisateur^>;
	DataBddProxy^ _bdd;
	DataConfigServeur^ _config;
	Sortie^ _sortie;
	Entree^ _entree;

	static Interface^ servInter;

	static List<Client^>^ _listClient = gcnew List<Client^>;

	NamedPipeServerStream^ _pipeServerState;
	NamedPipeServerStream^ _pipeServerUser;

	Thread^ _tServerStateMsg;
	Thread^ _tServerUserMsg;

public:

	static event EventUpdateClientStateDelegate^ EventUpdateClientState;
	static Boolean Debug = false;
	static void UpdateClientState();


	Dechetterie(String^ configFile);
	~Dechetterie();

	Boolean loadConfigFile(String^ file);

	//================ Utilisateur =================================
	static void addUtilisateur(String ^ id_rfid, int tDechet, int poids, array<Byte>^ photo);
	static void deleteUtilisateur(String ^ id_rfid);
	static List<Utilisateur^>^ GetListUtilisateur();
	static void updateUserFile();



};


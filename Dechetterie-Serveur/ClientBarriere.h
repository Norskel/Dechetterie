#pragma once
#include "Client.h"
#include "Enum.h"
#include "Logger.h"
#include "Protocole\Protocole.h"


using namespace System;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic;

ref class ClientBarriere : public Client
{
protected:
	int _pos;

	void fonctionReceive(ProtocolMsg^ pm, array<Byte>^ data) override
	{
		if (pm->type == protocole->GetTypeProtocoleByID("brRDPos"))
		{
			_pos = pm->getData1Int();
			Logger::PrintLog("");
		}
		else
		{
			bufferRecv = data;
		}
	}

public:
	int getPosition(){ return _pos; }
	ClientBarriere(id_groupe groupe, IPAddress^ip) : Client(groupe, id_client::ClientBarrière, ip)
	{

	}
	void OuvrirBarriere()
	{
		this->Send(protocole->OuvrirBarriere());
	}
	void FermerBarriere()
	{
		this->Send(protocole->FermerBarriere());
	}
};

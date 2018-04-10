#include "stdafx.h"
#include "PipeServeur.h"


PipeServeur::PipeServeur()
{
	_pipeClientInterface = gcnew NamedPipeClientStream(".", PIPE_NAME_SERV, PipeDirection::InOut);
	protocole = Protocole::getProtocole();
	
}

Boolean PipeServeur::Connect()
{
	if (!_pipeClientInterface->IsConnected)
	{
		try
		{
			_pipeClientInterface->Connect(30000);
		}
		catch (...)
		{

		}
	}
	_isConnected = _pipeClientInterface->IsConnected;
	return _pipeClientInterface->IsConnected;
}

PipeServeur ^ PipeServeur::GetPipeServeur()
{
	if (_pipeServeur == nullptr)
	{
		_pipeServeur = gcnew PipeServeur();
	}
	return _pipeServeur;
}

array<Byte>^ PipeServeur::getState()
{
	if (Connect())
	{
		array<Byte>^ send = protocole->InterfaceGetEtatClients();
		_pipeClientInterface->Write(send, 0, send->Length);
	}
	array<Byte>^ retour = gcnew array<Byte>(10);
	return retour;


}

array<Byte>^ PipeServeur::getPositionBarriere(id_groupe id)
{
	if (Connect())
	{
		array<Byte>^ send = protocole->InterfaceGetPositionBarriere(Convert::ToInt16(id));
		_pipeClientInterface->Write(send, 0, send->Length);
	}
	array<Byte>^ retour = gcnew array<Byte>(10);
	return retour;
}

void PipeServeur::ouvrirBarriere(id_groupe id)
{
	if (Connect())
	{
		array<Byte>^ send = protocole->InterfaceOuvrirBarriere(Convert::ToInt16(id));
		_pipeClientInterface->Write(send, 0, send->Length);
	}

}

void PipeServeur::fermerBarriere(id_groupe id)
{
	if (Connect())
	{
		array<Byte>^ send = protocole->InterfaceFermerBarriere(Convert::ToInt16(id));
		_pipeClientInterface->Write(send, 0, send->Length);
	}

}

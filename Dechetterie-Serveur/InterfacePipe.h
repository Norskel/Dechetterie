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

ref class InterfacePipe
{
private:
	Thread^ _threadRecev;
	NamedPipeServerStream^ _pipeOutServerInterface;
	NamedPipeServerStream^ _pipeInServerInterface;
	void fctThreadRecev()
	{

		while (true)
		{
			try
			{
				if (!Connect())
				{

					Logger::PrintLog(EnteteCode::INTERFACE, " Interface Erreur ");

				}
				else
				{

					Logger::PrintLog(EnteteCode::DEBUG, "Attents reception");
					Encoding^ encoder = Encoding::ASCII;

					//array<Byte>^ data = encoder->GetBytes(_sr->ReadLine());
					array<Byte>^ data = gcnew array<Byte>(256);
					_pipeInServerInterface->Read(data, 0, 256);
					//Logger::PrintLog(EnteteCode::DEBUG, encoder->GetString(data));
					ProtocolMsg^ pm = protocole->translateReceive(data);
					Logger::PrintLog(EnteteCode::DEBUG, "Type :" + pm->type);




					if (pm->type == protocole->GetTypeProtocoleByID("inEtatClient"))
					{
						Logger::PrintLog(EnteteCode::INTERFACE, " Demande de l'etat des clients ");
						array<Byte>^ send = protocole->InterfaceRetourGetEtatClients(this->getState());
						_pipeOutServerInterface->Write(send, 0, send->Length);

					}
					else
					{
						if (pm->type == protocole->GetTypeProtocoleByID("inOuvre"))
						{
							Logger::PrintLog(EnteteCode::INTERFACE, " Ouvrir Barriere " + pm->getData1Int());
							OuvrirBarriere(pm->getData1Int());
						}
						else
						{
							if (pm->type == protocole->GetTypeProtocoleByID("inFerme"))
							{
								Logger::PrintLog(EnteteCode::INTERFACE, " Fermer Barriere " + pm->getData1Int());
								FermerBarriere(pm->getData1Int());
							}
							else
							{
								if (pm->type == protocole->GetTypeProtocoleByID("inDPos"))
								{
									Logger::PrintLog(EnteteCode::INTERFACE, " Demande de la position de " + pm->getData1Int() + " : " + PositionBarriere(pm->getData1Int()));
									array<Byte>^ send = protocole->InterfaceRetourGetPositionBarriere(pm->getData1Int(), PositionBarriere(pm->getData1Int()));
									_pipeOutServerInterface->Write(send, 0, send->Length);
								}
								else
								{


								}
							}
						}
					}
				}
			}
			catch (Exception^e)
			{

				Console::WriteLine("[ Client ][ Thread Receive ]" + e);

			}
			Thread::Sleep(100);

		}
	}
	Entree^ _entree;
	Sortie^ _sortie;
	Protocole^ protocole;
	String^ nameServeur;
	Boolean Connect()
	{
		if (_isConnectedIn && !_pipeInServerInterface->IsConnected)
		{
			try
			{
				_pipeInServerInterface->Close();
				_pipeInServerInterface = gcnew NamedPipeServerStream(PIPE_NAME_INTER_SERV_IN, PipeDirection::InOut, 1);
				_isConnectedIn = false;
			}
			catch (Exception^ e)
			{
				Logger::PrintLog(EnteteCode::ERROR, e->ToString());
			}
		}
		if (_isConnectedOut && !_pipeOutServerInterface->IsConnected)
		{
			try
			{
				_pipeOutServerInterface->Close();
				_pipeOutServerInterface = gcnew NamedPipeServerStream(PIPE_NAME_INTER_SERV_OUT, PipeDirection::InOut, 1);
				_isConnectedOut = false;
			}
			catch (Exception^ e)
			{
				Logger::PrintLog(EnteteCode::ERROR, e->ToString());
			}
		}
		if (!_isConnectedIn && !_pipeInServerInterface->IsConnected)
		{
			try
			{
				Logger::PrintLog(EnteteCode::INTERFACE, " Attente de l'interface");
				_pipeInServerInterface->WaitForConnection();
				Logger::PrintLog(EnteteCode::INTERFACE, " Interface connecte ");
				_isConnectedIn = true;
			}
			catch (Exception^ e)
			{
				Logger::PrintLog(EnteteCode::ERROR, e->ToString());
			}
		}
		if (!_isConnectedOut && !_pipeOutServerInterface->IsConnected)
		{
			try
			{
				Logger::PrintLog(EnteteCode::INTERFACE, " Attente de l'interface");
				_pipeOutServerInterface->WaitForConnection();
				Logger::PrintLog(EnteteCode::INTERFACE, " Interface connecte ");
				_isConnectedOut = true;
			}
			catch (Exception^ e)
			{
				Logger::PrintLog(EnteteCode::ERROR, e->ToString());
			}
		}

		return _pipeOutServerInterface->IsConnected && _pipeInServerInterface->IsConnected;


	}
	void start()
	{
		if (!_isConnectedIn && !_pipeInServerInterface->IsConnected)
		{
			try
			{
				Logger::PrintLog(EnteteCode::INTERFACE, " Attente de l'interface");
				_pipeInServerInterface->WaitForConnection();
				Logger::PrintLog(EnteteCode::INTERFACE, " Interface connecte ");
				_isConnectedIn = true;
			}
			catch (Exception^ e)
			{
				Logger::PrintLog(EnteteCode::ERROR, e->ToString());
			}
		}
		if (!_isConnectedOut && !_pipeOutServerInterface->IsConnected)
		{
			try
			{
				Logger::PrintLog(EnteteCode::INTERFACE, " Attente de l'interface");
				_pipeOutServerInterface->WaitForConnection();
				Logger::PrintLog(EnteteCode::INTERFACE, " Interface connecte ");
				_isConnectedOut = true;
			}
			catch (Exception^ e)
			{
				Logger::PrintLog(EnteteCode::ERROR, e->ToString());
			}
		}


	}
	Boolean _isConnectedIn = false;
	Boolean _isConnectedOut = false;
	static InterfacePipe^ _interfacePipe;

	InterfacePipe(Entree^ %e, Sortie^ %s)
	{
		_entree = e;
		_sortie = s;
		protocole = Protocole::getProtocole();

		_pipeOutServerInterface = gcnew NamedPipeServerStream(PIPE_NAME_INTER_SERV_OUT, PipeDirection::InOut, 1);
		_pipeInServerInterface = gcnew NamedPipeServerStream(PIPE_NAME_INTER_SERV_IN, PipeDirection::InOut, 1);
		_threadRecev = gcnew Thread(gcnew ThreadStart(this, &InterfacePipe::fctThreadRecev));
		_threadRecev->Name = "Thread Wait connection server";
		_threadRecev->Start();

	}

	String^ getState()
	{
		String^ r = "";
		r += _entree->GetStateAllClient();
		r += _sortie->GetStateAllClient();
		return r;
	}
	void OuvrirBarriere(int i)
	{
		switch (i)
		{
		case 0:
			_entree->OuvrirBarriere();
			_sortie->OuvrirBarriere();
			break;
		case 1:
			_entree->OuvrirBarriere();
			break;
		case 2:
			_sortie->OuvrirBarriere();
			break;
		}
	}
	void FermerBarriere(int i)
	{
		switch (i)
		{
		case 0:
			_entree->FermerBarriere();
			_sortie->FermerBarriere();
			break;
		case 1:
			_entree->FermerBarriere();
			break;
		case 2:
			_sortie->FermerBarriere();
			break;
		}
	}
	int PositionBarriere(int i)
	{
		switch (i)
		{
		case 1:
			return _entree->GetPositionBarriere();
			break;
		case 2:
			return _sortie->GetPositionBarriere();
			break;
		}
	}

public:
	static InterfacePipe^ getInterfacePipe()
	{
		if (_interfacePipe == nullptr)
		{
			throw gcnew System::NotImplementedException();
		}
		return _interfacePipe;
	}
	static InterfacePipe^ getInterfacePipe(Entree^ %e, Sortie^ %s)
	{
		if (_interfacePipe == nullptr)
		{
			_interfacePipe = gcnew InterfacePipe(e, s);
		}
		return _interfacePipe;
	}
	void updateListClient()
	{
		try
		{
			array<Byte>^ send = protocole->InterfaceUpdateListClient();
			_pipeOutServerInterface->Write(send, 0, send->Length);
		}
		catch (...)
		{

		}

	}
	void updateClientState()
	{
		Logger::PrintLog(EnteteCode::INTERFACE, " Update etat des clients ");
		array<Byte>^ send = protocole->InterfaceRetourGetEtatClients(this->getState());
		_pipeOutServerInterface->Write(send, 0, send->Length);
	}
};


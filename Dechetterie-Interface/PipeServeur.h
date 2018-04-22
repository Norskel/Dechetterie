#pragma once
#define SRV_PROCESS_NAME "Dechetterie-Serveur"
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
	static PipeServeur^ _pipeServeur = nullptr;
	Boolean _isConnected = false;
	NamedPipeClientStream^ _pipeInClientInterface;
	NamedPipeClientStream^ _pipeOutClientInterface;
	Protocole^ protocole;
	array<Byte>^ _state = nullptr;
	pos _positionBarriere;
	Thread^ _thread;

	PipeServeur()
	{
		_pipeInClientInterface = gcnew NamedPipeClientStream(".", PIPE_NAME_INTER_SERV_IN, PipeDirection::InOut);
		_pipeOutClientInterface = gcnew NamedPipeClientStream(".", PIPE_NAME_INTER_SERV_OUT, PipeDirection::InOut);
		protocole = Protocole::getProtocole();
		startReceive();
	}

	Boolean Connect()
	{
		if (_isConnected == true && !_pipeInClientInterface->IsConnected)
		{
			_pipeInClientInterface->Close();
			_pipeOutClientInterface->Close();

		}

		if (!_pipeInClientInterface->IsConnected)
		{
			try
			{
				_pipeInClientInterface->Connect(30000);
				_pipeOutClientInterface->Connect(30000);

			}
			catch (...)
			{

			}
		}

		_isConnected = _pipeInClientInterface->IsConnected && _pipeOutClientInterface->IsConnected;

		return _isConnected;
	}
	void fctThread()
	{
		while (true)
		{
			try
			{
				if (getServeurState())
				{


					if (Connect())
					{

						Encoding^ encoder = Encoding::ASCII;
						array<Byte>^ data = gcnew array<Byte>(256);
						_pipeInClientInterface->Read(data, 0, 256);

						ProtocolMsg^ pm = protocole->translateReceive(data);


						Logger::PrintLog(EnteteCode::DEBUG, encoder->GetString(data));
						Logger::PrintLog(EnteteCode::DEBUG, "Type :" + pm->type);

						if (pm->type == protocole->GetTypeProtocoleByID("inREtatClient"))
						{
							Logger::PrintLog(EnteteCode::DEBUG, "Reception etats");
							_state = pm->data1;
						}
						else
						{
							if (pm->type == protocole->GetTypeProtocoleByID("inRDPos"))
							{

							}
							else
							{
								if (pm->type == protocole->GetTypeProtocoleByID("inUpdateClient"))
								{
									UpdateClientList(this, 0);
								}
								else
								{

								}
							}
						}
					}
					else
					{

					}
				}
				else
				{
					Thread::Sleep(2000);
				}
			}
			catch (Exception^e)
			{
				disconnect();
				Console::WriteLine("[ Client ][ Thread Receive ]" + e);

			}
		}
		Thread::Sleep(100);
	}
	void startReceive()
	{
		_thread = gcnew Thread(gcnew ThreadStart(this, &PipeServeur::fctThread));
		_thread->Name = "Thread pipe";
		_thread->Start();
	}
	void disconnect()
	{
		_pipeInClientInterface->Close();
		_pipeOutClientInterface->Close();

	}

public:
	event EventHandler<int>^ UpdateClientList;

	static PipeServeur^ GetPipeServeur()
	{
		if (_pipeServeur == nullptr)
		{
			_pipeServeur = gcnew PipeServeur();
		}
		return _pipeServeur;
	}
	array<Byte>^ getClientState()
	{
		try
		{
			if (getServeurState())
			{
				while (!Connect())
				{

				}
				Console::WriteLine(_pipeOutClientInterface->IsConnected);
				array<Byte>^ retour = gcnew array<Byte>(6);
				array<Byte>^ send = protocole->InterfaceGetEtatClients();
				Encoding^ encoder = Encoding::ASCII;
				Logger::PrintLog(EnteteCode::DEBUG, encoder->GetString(send));
				String^ cmd = encoder->GetString(send);

				_pipeOutClientInterface->Write(send, 0, send->Length);

				Logger::PrintLog("flush");
				Logger::PrintLog(EnteteCode::DEBUG, "");

				int timeout = 0;

				while (_state == nullptr && timeout < TIMEOUT_GET_STATE)
				{
					Thread::Sleep(500);
					timeout++;
				}
				if (timeout >= TIMEOUT_GET_STATE)
				{
					throw gcnew Exception("Timeout Get State");
				}
				else
				{
					retour = _state;
					_state = nullptr;
					return retour;
				}
			}

		}
		catch (Exception^ e)
		{
			Console::WriteLine("dkjsfkgild");
			Logger::PrintLog(EnteteCode::ERROR, " no state " + e->ToString());
			return nullptr;
		}

	}
	Boolean getServeurState()
	{
		array<Process^>^ listProcess = Process::GetProcessesByName(SRV_PROCESS_NAME);

		for each (Process^ var in listProcess)
		{
			if (var->ToString() == "System.Diagnostics.Process (" + SRV_PROCESS_NAME + ")")
			{
				return true;
				break;
			}
			else
			{
				return false;
			}

		}
		if (listProcess->Length == 0)
		{
			return false;
		}
	}
	int getPositionBarriere(id_groupe id)
	{
		try
		{
			int retour = 0;
			array<Byte>^ send = protocole->InterfaceGetPositionBarriere(Convert::ToInt16(id));
			_pipeOutClientInterface->Write(send, 0, send->Length);
			int timeout = 0;

			while (retour == 0 && timeout < TIMEOUT_GET_POS)
			{
				Thread::Sleep(500);
				if (id == id_groupe::ENTREE)
				{
					retour = _positionBarriere.posBarriereEntree;
				}
				else
				{
					retour = _positionBarriere.posBarriereSortie;
				}
				timeout++;
			}
			if (timeout >= TIMEOUT_GET_POS)
			{
				throw gcnew Exception("Timeout Get Positon");
			}
			else
			{
				if (id == id_groupe::ENTREE)
				{
					_positionBarriere.posBarriereEntree = 0;
				}
				else
				{
					_positionBarriere.posBarriereSortie = 0;
				}
				return retour;
			}
		}
		catch (...)
		{

		}

	}
	void ouvrirBarriere(id_groupe id)
	{
		try
		{
			if (_isConnected)
			{
				Logger::PrintLog("Ouvrir barriere " + id.ToString());
				array<Byte>^ send = protocole->InterfaceOuvrirBarriere(Convert::ToInt16(id));
				Encoding^ encoder = Encoding::ASCII;
				Logger::PrintLog(EnteteCode::INTERFACE, encoder->GetString(send));
				_pipeOutClientInterface->Write(send, 0, send->Length);
			}
		}
		catch (...)
		{

		}

	}
	void fermerBarriere(id_groupe id)
	{
		try
		{
			if (_isConnected)
			{
				array<Byte>^ send = protocole->InterfaceFermerBarriere(Convert::ToInt16(id));
				_pipeOutClientInterface->Write(send, 0, send->Length);
			}
		}
		catch (...)
		{

		}
	}
	void stopServeur()
	{
		array<Byte>^ send = protocole->InterfaceStopServeur();
		_pipeOutClientInterface->Write(send, 0, send->Length);
	}

};


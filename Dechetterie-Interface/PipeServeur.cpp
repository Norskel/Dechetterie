#include "stdafx.h"
#include "PipeServeur.h"


PipeServeur::PipeServeur()
{
	_pipeInClientInterface = gcnew NamedPipeClientStream(".", PIPE_NAME_INTER_SERV_IN , PipeDirection::InOut);
	_pipeOutClientInterface = gcnew NamedPipeClientStream(".", PIPE_NAME_INTER_SERV_OUT, PipeDirection::InOut);
	protocole = Protocole::getProtocole();
	startReceive();
}

Boolean PipeServeur::Connect()
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

void PipeServeur::fctThread()
{
	while (true)
	{
		try
		{
			if (Connect())
			{
					
				Encoding^ encoder = Encoding::ASCII;
				array<Byte>^ data = gcnew array<Byte>(256);
				_pipeInClientInterface->Read(data, 0, 256);
				
				ProtocolMsg^ pm = protocole->translateReceive(data);

				
				Logger::PrintLog(EnteteCode::DEBUG, encoder->GetString(data));
				Logger::PrintLog(EnteteCode::DEBUG,"Type :" + pm->type);

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
								UpdateClientList(this,0);
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
			catch (Exception^e)
			{
				disconnect();
				Console::WriteLine("[ Client ][ Thread Receive ]" + e);

			}
		}
		Thread::Sleep(100);
}

void PipeServeur::startReceive()
{
	_thread = gcnew Thread(gcnew ThreadStart(this, &PipeServeur::fctThread));
	_thread->Name = "Thread pipe";
	_thread->Start();
}

void PipeServeur::disconnect()
{
	_pipeInClientInterface->Close();
	_pipeOutClientInterface->Close();

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
	try
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
		Logger::PrintLog(EnteteCode::DEBUG,"");

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
	catch (Exception^ e)
	{
		Console::WriteLine("dkjsfkgild");
		Logger::PrintLog(EnteteCode::ERROR, " no state " + e->ToString());
		return nullptr;
	}

}

int PipeServeur::getPositionBarriere(id_groupe id)
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

void PipeServeur::ouvrirBarriere(id_groupe id)
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

void PipeServeur::fermerBarriere(id_groupe id)
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

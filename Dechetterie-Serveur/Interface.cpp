#include "Interface.h"

Interface::Interface(String ^ name_serveur, Entree ^% e, Sortie ^% s)
{
	protocole = Protocole::getProtocole();
	_pipeServerInterface = gcnew NamedPipeServerStream(name_serveur, PipeDirection::InOut, 1);
	_threadRecev = gcnew Thread(gcnew ThreadStart(this, &Interface::fctThreadRecev));
	_threadRecev->Name = "Thread Wait connection server User";
	_threadRecev->Start();
}


void Interface::fctThreadRecev()
{
	while (true)
	{
		try
		{
			if (!_pipeServerInterface->IsConnected)
			{
				try
				{
					Logger::PrintLog(EnteteCode::INTERFACE, " Attente de l'interface");
					_pipeServerInterface->WaitForConnection();
					Logger::PrintLog(EnteteCode::INTERFACE, " Interface connecte ");

				}
				catch (...)
				{

				}
			}
			else
			{
				array<Byte>^ data = gcnew array<Byte>(1024);
				_pipeServerInterface->Read(data, 0, 1024);

				ProtocolMsg^ pm = protocole->translateReceive(data);

				Encoding^ encoder = Encoding::ASCII;

				if (pm->type == protocole->GetTypeProtocoleByID("inEtatClient"))
				{
					Logger::PrintLog(EnteteCode::INTERFACE, " Demande de l'etat des clients ");
					array<Byte>^ send = protocole->InterfaceRetourGetEtatClients(this->getState());
					_pipeServerInterface->Write(send, 0, send->Length);
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
								_pipeServerInterface->Write(send, 0, send->Length);
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

String ^ Interface::getState()
{
	String^ r = "";
	r += _entree->GetStateAllClient();
	r += _sortie->GetStateAllClient();
	return r;
}

void Interface::OuvrirBarriere(int i)
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

void Interface::FermerBarriere(int i)
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

int Interface::PositionBarriere(int i)
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


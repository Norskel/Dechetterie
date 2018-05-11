#include "Serveur.h"
#include "InterfacePipe.h"

Serveur::Serveur(IPAddress^ listenip, int listenPort, id_groupe groupe, GroupeClient^ %l)
{
	_interface = listenip;
	_port = listenPort;
	_groupe = groupe;

	_socketServeur = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
	IPEndPoint^ local = gcnew IPEndPoint(listenip, listenPort);
	_socketServeur->Bind(local);
	_listClient = l;
}

Boolean Serveur::Start()
{
	//try
	//{
	Logger::PrintLog(EnteteCode::SERVEUR, _groupe.ToString(), "Démarage du serveur TCP " + _groupe.ToString() + " qui ecoute sur le port " + _port + " et l'interface " + _interface->ToString() + "  ");
	this->_socketServeur->Listen(1);
	this->_isRunning = true;
	this->_tWaitClient = gcnew Thread(gcnew ThreadStart(this, &Serveur::WaitClient));
	this->_tWaitClient->Name = "Thread TCP SERVEUR PORT " + _port;
	this->_tWaitClient->Start();
	//}
	//catch (Exception^ e)
	//{
	//		Logger::PrintLog(EnteteCode::ERROR, EnteteCode::SERVEUR, _groupe.ToString(), "[ Start ] "+ e);
	//}
	return true;
}

void Serveur::WaitClient()
{
	while (_isRunning)
	{
		try
		{
			Socket^ cliSocket;
			cliSocket = _socketServeur->Accept();

			IPAddress^ ipAdresseClient = (IPAddress^)(((IPEndPoint^)cliSocket->RemoteEndPoint)->Address);

			if (_listClient->ClientBalance->getIP()->ToString() == ipAdresseClient->ToString())
			{
				_listClient->ClientBalance->setSocket(cliSocket);
				_listClient->ClientBalance->setState(true);
				Logger::PrintLog(EnteteCode::SERVEUR, _groupe.ToString(), id_client::ClientBalance.ToString() + " viens de ce connectée");
				(InterfacePipe::getInterfacePipe())->updateClientState();
			}
			else
			{
				if (_listClient->ClientBarriere->getIP()->ToString() == ipAdresseClient->ToString())
				{
					_listClient->ClientBarriere->setSocket(cliSocket);
					_listClient->ClientBarriere->setState(true);
					Logger::PrintLog(EnteteCode::SERVEUR, _groupe.ToString(), id_client::ClientBarrière.ToString() + " viens de ce connectée");
					(InterfacePipe::getInterfacePipe())->updateClientState();
				}
				else
				{
					if (_listClient->ClientRFID->getIP()->ToString() == ipAdresseClient->ToString())
					{
						_listClient->ClientRFID->setSocket(cliSocket);
						_listClient->ClientRFID->setState(true);
						Logger::PrintLog(EnteteCode::SERVEUR, _groupe.ToString(), id_client::ClientRFID.ToString() + " viens de ce connectée");
						(InterfacePipe::getInterfacePipe())->updateClientState();
					}
					else
					{
						Logger::PrintLog(EnteteCode::SERVEUR, _groupe.ToString(), "Un Client avec l'ip " + ipAdresseClient->ToString() + " a essayé de ce connectée");
						cliSocket->Close();
					}
				}

			}

		}
		catch (Exception^ e)
		{
			Logger::PrintLog(EnteteCode::ERROR, EnteteCode::SERVEUR, _groupe.ToString(), "[ WaitClient ] " + e);

		}

	}
}


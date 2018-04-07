#include "Serveur.h"
#include "Dechetterie.h"



Serveur::Serveur(IPAddress ^ listenip, int listenPort, id_groupe groupe)
{
	_interface = listenip;
	_port = listenPort;
	_groupe = groupe;

	_socketServeur = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
	IPEndPoint^ local = gcnew IPEndPoint(listenip, listenPort);
	_socketServeur->Bind(local);
}

Serveur::Serveur(IPAddress ^ listenip, int listenPort, id_groupe groupe, List<Client^>^% l)
{
	Serveur(listenip, listenPort, groupe);
	_listClient = l;
}


Boolean Serveur::Start()
{
	try
	{
		Logger::PrintLog(EnteteCode::SERVEUR, _groupe.ToString(), "Démarage du serveur TCP " + _groupe.ToString() + " qui ecoute sur le port " + _port + " et l'interface " + _interface->ToString() + "  ");
		this->_socketServeur->Listen(1);
		this->_isRunning = true;
		this->_tWaitClient = gcnew Thread(gcnew ThreadStart(this, &Serveur::WaitClient));
		this->_tWaitClient->Name = "Thread TCP SERVEUR PORT " + _port;
		this->_tWaitClient->Start();
	}
	catch (Exception^ e)
	{
		Logger::PrintLog(EnteteCode::ERROR, EnteteCode::SERVEUR, _groupe.ToString(), "[ Start ] "+ e);
	}
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
			int i;

			IPAddress^ ipAdresseClient = (IPAddress^)(((IPEndPoint^)cliSocket->RemoteEndPoint)->Address);

			for (i = 0; i < _listClient->Count; i++)

			{
				IPAddress^ IPAdresseList = _listClient[i]->getIP();
				id_groupe idGroupe = _listClient[i]->getGroupe();



				if (ipAdresseClient->ToString() == IPAdresseList->ToString() && idGroupe == _groupe)
				{
					_listClient[i]->setSocket(cliSocket);
					_listClient[i]->setState(true);
					Logger::PrintLog(EnteteCode::SERVEUR, _groupe.ToString(), _listClient[i]->getType().ToString() + " viens de ce connectée");
					break;

				}
			}

			if (i == _listClient->Count)
			{
				Logger::PrintLog(EnteteCode::SERVEUR,_groupe.ToString(), "Un Client avec l'ip "+ipAdresseClient->ToString()+" a essayé de ce connectée");
				cliSocket->Close();
			}
			


		}
		catch (Exception^ e)
		{
			Logger::PrintLog(EnteteCode::ERROR, EnteteCode::SERVEUR, _groupe.ToString(), "[ WaitClient ] " + e);

		}

	}
}

List<Client^>^ Serveur::getClientList()
{
	return _listClient;
}

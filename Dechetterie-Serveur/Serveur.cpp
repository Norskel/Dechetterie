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
	while (_isRunning) // si le serveur est en marche
	{
		try
		{
			Socket^ cliSocket; // on defini un socket
			cliSocket = _socketServeur->Accept(); //on attend les demande de connexion et quand il y a une on met le socket de cliSocket

			IPAddress^ ipAdresseClient = (IPAddress^)(((IPEndPoint^)cliSocket->RemoteEndPoint)->Address); // on recupere l'ip du client qui demande une connexion
			 
			if (_listClient->ClientBalance->getIP()->ToString() == ipAdresseClient->ToString()) // si l'ip est la meme que celle defini pour le client balance
			{
				_listClient->ClientBalance->setSocket(cliSocket); // on defini le socket du client balance avec le socket du client qui demande la connection
				_listClient->ClientBalance->setState(true); // on dit que le client balance est connecté
				Logger::PrintLog(EnteteCode::SERVEUR, _groupe.ToString(), id_client::ClientBalance.ToString() + " viens de ce connectée");
				(InterfacePipe::getInterfacePipe())->updateClientState(); // on envois une  update a l'interface pour dire qu'un client c'est connecté
			}
			else
			{
				if (_listClient->ClientBarriere->getIP()->ToString() == ipAdresseClient->ToString())// si l'ip est la meme que celle defini pour le client barriere
				{
					_listClient->ClientBarriere->setSocket(cliSocket);// on defini le socket du client barriere avec le socket du client qui demande la connection
					_listClient->ClientBarriere->setState(true); // on dit que le client barriere est connecté
					Logger::PrintLog(EnteteCode::SERVEUR, _groupe.ToString(), id_client::ClientBarrière.ToString() + " viens de ce connectée");
					(InterfacePipe::getInterfacePipe())->updateClientState();// on envois une  update a l'interface pour dire qu'un client c'est connecté
				}
				else
				{
					if (_listClient->ClientRFID->getIP()->ToString() == ipAdresseClient->ToString())// si l'ip est la meme que celle defini pour le client RFID
					{
						_listClient->ClientRFID->setSocket(cliSocket);// on defini le socket du client RFID avec le socket du client qui demande la connection
						_listClient->ClientRFID->setState(true); // on dit que le client RFID est connecté
						Logger::PrintLog(EnteteCode::SERVEUR, _groupe.ToString(), id_client::ClientRFID.ToString() + " viens de ce connectée");
						(InterfacePipe::getInterfacePipe())->updateClientState();// on envois une  update a l'interface pour dire qu'un client c'est connecté
					}
					else // sinon on force le client qui demande a ce deconnecter
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


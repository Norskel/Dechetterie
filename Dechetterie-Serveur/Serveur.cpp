#include "Serveur.h"
#include "Dechetterie.h"



Serveur::Serveur(IPAddress ^ listenip, int listenPort,int groupe)
{
	_interface = listenip;
	_port = listenPort;
	_groupe = groupe;

	_socketServeur = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
	IPEndPoint^ local = gcnew IPEndPoint(listenip, listenPort);
	_socketServeur->Bind(local);
}
Boolean Serveur::Start()
{
	try
	{
		Console::WriteLine("[ Serveur " + id_groupe(_groupe).ToString() + " ] Démarage du serveur TCP " + id_groupe(_groupe).ToString() + " qui ecoute sur le port " + _port + " et l'interface " + _interface->ToString() + "  ");
		this->_socketServeur->Listen(1);
		this->_isRunning = true;
		this->_tWaitClient = gcnew Thread(gcnew ThreadStart(this, &Serveur::WaitClient));
		this->_tWaitClient->Name = "Thread TCP SERVEUR PORT " + _port;
		this->_tWaitClient->Start();
	}
	catch (Exception^ e)
	{
		if (Dechetterie::Debug)
		{
			Console::WriteLine("[ ERROR ][ Serveur " + id_groupe(_groupe).ToString() + " ][Start] ===============================================  ");
			Console::WriteLine(e);

		}
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


			_listClient = Dechetterie::GetListClient();
			IPAddress^ ipAdresseClient = (IPAddress^)(((IPEndPoint^)cliSocket->RemoteEndPoint)->Address);
			for (i = 0; i < _listClient->Count; i++)

			{
				IPAddress^ IPAdresseList = _listClient[i]->getIP();
				int idGroupe = _listClient[i]->getGroupe();
				if (Dechetterie::Debug)
				{
					Console::Write("List : " + _listClient[i]->getIP());
					Console::WriteLine("Address : " + ipAdresseClient);
				}


				if (ipAdresseClient->ToString() == IPAdresseList->ToString() && idGroupe == _groupe)
				{
					_listClient[i]->setSocket(cliSocket);
					_listClient[i]->setState(true);
					Console::WriteLine("[ Serveur "+id_groupe(_groupe).ToString() +" ] "+id_client(_listClient[i]->getType()).ToString() +" viens de ce connectée" );
					Dechetterie::SetListClient(_listClient);
					break;

				}
			}

			if (i == _listClient->Count)
			{
				Console::WriteLine("[ Serveur " + id_groupe(_groupe).ToString() + " ] Un Client avec l'ip "+ipAdresseClient->ToString()+" a essayé de ce connectée");
				cliSocket->Close();
			}
			


		}
		catch (Exception^ e)
		{
			if (Dechetterie::Debug)
			{
				Console::WriteLine("[ ERROR ][ Serveur " + id_groupe(_groupe).ToString() + " ][WaitClient] ===============================================  ");
				Console::WriteLine(e);

			}

		}

	}
}
List<Client^>^ Serveur::getClientList()
{
	return _listClient;
}

#include "Entree.h"



Entree::Entree(IPAddress ^ listenip, int listenPort)
{
	Logger::PrintLogCode(3, "Interface d'écoute : " + listenip + " Port d'écoute : " + listenPort);
	_srv = gcnew Serveur(listenip, listenPort,1);
	_srv->Start();
	_tEntree = gcnew Thread(gcnew ThreadStart(this, &Entree::ThreadEntree));
	_tEntree->Name = "Thread Entree";
	_tEntree->Start();
	_bdd = DataBddProxy::getDataBddProxy();
	protocole = Protocole::getProtocole();

}

void Entree::ThreadEntree()
{
	Boolean connected = false;
	Boolean logstate = false;
	do
	{	
		if (!logstate)
		{
			Logger::PrintLogCode(3, "Attente de la connection de tous les client");
			logstate = true;
		}

		Thread::Sleep(500);
		getClientFromList(Dechetterie::GetListClient());
		//connected = _ClientBalance->getState() && _ClientBarrière->getState() && _ClientRFID->getState();
		connected = _ClientRFID->getState();
		//connected = _ClientBalance->getState();
		
	}
	while (!connected);
	Logger::PrintLogCode(3, "Tous les client sont connectés");
	logstate = false;


	while (true)
	{
		getClientFromList(Dechetterie::GetListClient());
		try
		{
			//===================================== Attente de Demande d'accès ========================================================================
			String^ rfid_id = WaitAccesDemand(_ClientRFID);
			Logger::PrintLogCode(3, "[ RFID ] Demande d'accès avec l'id RFID " + rfid_id);
			
			//===================================== Demande d'accès ====================================================================================
			try
			{
				//Console::WriteLine("[Entree] Demande d'accès avec l'id RFID " + Encoding::Default->GetString(msgRev->data1));
				DataUser^ user = _bdd->getUserByIdRFID(rfid_id);
				Logger::PrintLogCode(3, "[ RFID ] Accès autorisé");
				_ClientRFID->Send(protocole->RetourRFIDAccesDemand(true));

				int dechet_type = WaitDechetType(_ClientRFID);
				int poids = 2500;
				//int poids = getPoids(_ClientBalance);
			
				//array<Byte>^ photo = ReceptionPhoto(_ClientRFID);
				//Dechetterie::addUtilisateur(rfid_id, dechet_type, poids, photo);

				_ClientBarrière->Send(protocole->OuvrirBarriere());
				Thread::Sleep(20000);
				_ClientBarrière->Send(protocole->FermerBarriere());
				
				
			}
			catch (Exception^ e)
			{
				
				Logger::PrintLogCode(2, "[ Entree ] " + e->Message);
				
				if (e->Message == "ID_RFID Introuvable")
				{
					Logger::PrintLogCode(3, "[ RFID ] Accès Refusé");
					_ClientRFID->Send(protocole->RetourRFIDAccesDemand(false));
				}
				
				
			}


		}
		catch (...)
		{
			
		}
		Console::WriteLine("[Entree] Fin de procédure");
	}
}

array<Byte>^ Entree::ReceptionPhoto(Client^ cl)
{
	cl->Send(protocole->GetPhoto());

	ProtocolMsg^ msgRev = gcnew ProtocolMsg();
	do
	{
		msgRev = protocole->translateReceive(_ClientRFID->Receive());
		Console::WriteLine("Type = " + msgRev->type);

	} while (msgRev->type != protocole->GetTypeProtocoleByID("RfPhotoInit"));

	int nbPacket = msgRev->getData1Int();
	Console::WriteLine("[ Reception Photo ] Initialisation de la reception de la Photo ");
	Console::WriteLine("[ Reception Photo ] Nombre de packet à recevoir : " + nbPacket);

	array<Byte>^ photo = gcnew array<Byte>(1024 * nbPacket);

	int iPhoto = 0;
	ProtocolMsg^ receptionMsg;
	do
	{
		receptionMsg = protocole->translateReceive(cl->Receive());
		if (receptionMsg->type == protocole->GetTypeProtocoleByID("RfPhotoSend"))
		{
			for (int i = 0; i < receptionMsg->data2->Length; i++)
			{


				photo[iPhoto] = receptionMsg->data2[i];
				iPhoto++;



			}
			if (receptionMsg->getData1Int() == nbPacket)
			{
				break;
			}
		}


	} while (receptionMsg->type != protocole->GetTypeProtocoleByID("RfPhotoEnd"));

	Console::WriteLine("[ Reception Photo ] Fin de transmission ");
	Console::WriteLine("[ Reception Photo ] Taille de la photo recu en octet (Byte) : " + iPhoto);

	return photo;
}
String^ Entree::WaitAccesDemand(Client^ cl)
{
	ProtocolMsg^ msgRev = gcnew ProtocolMsg();
	do
	{

		msgRev = protocole->translateReceive(cl->Receive());
		Console::WriteLine("Type = " + msgRev->type);

	} while (msgRev->type != protocole->GetTypeProtocoleByID("RfDAcces"));

	return msgRev->getData1String();
}
int Entree::WaitDechetType(Client^ cl)
{
	ProtocolMsg^ msgRev = gcnew ProtocolMsg();
	do
	{
		msgRev = protocole->translateReceive(cl->Receive());
		Console::WriteLine("Type = " + msgRev->type);

	} while (msgRev->type != protocole->GetTypeProtocoleByID("RfDechet"));

	return msgRev->getData1Int();
}
int Entree::getPoids(Client^ cl)
{
	cl->Send(protocole->GetBalancePoids());
	ProtocolMsg^ msgRev = gcnew ProtocolMsg();
	do
	{

		msgRev = protocole->translateReceive(cl->Receive());
		Console::WriteLine("Type = " + msgRev->type);
	


	} while (msgRev->type != protocole->GetTypeProtocoleByID("baRDPoids"));
	return msgRev->getData1Int();
}
void Entree::getClientFromList(List<Client^>^ l)
{
	for each (Client^ var in l)
	{
		if (var->getGroupe() == 1)
		{
			if (var->getType() == 1)
			{
				_ClientBarrière = var;
			}
			else
			{
				if (var->getType() == 2)
				{
					_ClientBalance = var;
				}
				else
				{
					if (var->getType() == 3)
					{
						_ClientRFID = var;
					}
				}
			}
		}
	}
}

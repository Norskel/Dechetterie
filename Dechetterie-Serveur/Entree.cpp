#include "Entree.h"


Entree::Entree(IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid)
{
	Logger::PrintLog(EnteteCode::ENTREE, "Interface d'�coute : " + listenip + " Port d'�coute : " + listenPort);
	
	_listClient[0] = gcnew ClientBarriere(id_groupe::Entr�e, ipBarriere);
	_listClient[1] = gcnew ClientBalance(id_groupe::Entr�e, ipBalance);
	_listClient[2] = gcnew ClientRFID(id_groupe::Entr�e, ipRfid);
	_srv = gcnew Serveur(listenip, listenPort, id_groupe::Entr�e,_listClient);
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
			Logger::PrintLog(3, "Attente de la connection de tous les client");
			logstate = true;
		}

		Thread::Sleep(500);
		getClientFromList(Dechetterie::GetListClient());
		//connected = _ClientBalance->getState() && _ClientBarri�re->getState() && _ClientRFID->getState();
		connected = _ClientRFID->getState();
		//connected = _ClientBalance->getState();
		
	}
	while (!connected);
	Logger::PrintLog(3, "Tous les client sont connect�s");
	logstate = false;


	while (true)
	{
		getClientFromList(Dechetterie::GetListClient());
		try
		{
			//===================================== Attente de Demande d'acc�s ========================================================================
			String^ rfid_id = WaitAccesDemand(_ClientRFID);
			Logger::PrintLog(3, "[ RFID ] Demande d'acc�s avec l'id RFID " + rfid_id);
			
			//===================================== Demande d'acc�s ====================================================================================
			try
			{
				//Console::WriteLine("[Entree] Demande d'acc�s avec l'id RFID " + Encoding::Default->GetString(msgRev->data1));
				DataUser^ user = _bdd->getUserByIdRFID(rfid_id);
				Logger::PrintLog(3, "[ RFID ] Acc�s autoris�");
				_ClientRFID->Send(protocole->RetourRFIDAccesDemand(true));

				int dechet_type = WaitDechetType(_ClientRFID);
				int poids = 2500;
				//int poids = getPoids(_ClientBalance);
			
				//array<Byte>^ photo = ReceptionPhoto(_ClientRFID);
				//Dechetterie::addUtilisateur(rfid_id, dechet_type, poids, photo);

				_ClientBarri�re->Send(protocole->OuvrirBarriere());
				Thread::Sleep(20000);
				_ClientBarri�re->Send(protocole->FermerBarriere());
				
				
			}
			catch (Exception^ e)
			{
				
				Logger::PrintLog(2, "[ Entree ] " + e->Message);
				
				if (e->Message == "ID_RFID Introuvable")
				{
					Logger::PrintLog(3, "[ RFID ] Acc�s Refus�");
					_ClientRFID->Send(protocole->RetourRFIDAccesDemand(false));
				}
				
				
			}


		}
		catch (...)
		{
			
		}
		Console::WriteLine("[Entree] Fin de proc�dure");
	}
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
				_ClientBarri�re = var;
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

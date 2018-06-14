#include "Sortie.h"
#include "ClientRFID.h"

#define TEMPO_BARRIERE 2000


Sortie::Sortie(IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid) : Groupe(id_groupe::SORTIE, listenip, listenPort, ipBarriere, ipBalance, ipRfid){}
Sortie::~Sortie()
{
	_srv->~Serveur();
	delete _listClient;
}
/*---------------------------------------------------------------
Nom          : AccesDemandEvent
Description  : Lorsqu'on a une demande d'acces � la sortie
Arguments    : rfid : Id rfid de la demande d'acc�s
Valeur renvoy�e :
-----------------------------------------------------------------*/
void Sortie::AccesDemandEvent(String ^ rfid)
{
	Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Demande d'acc�s avec l'id RFID " + rfid);
	while (!AllClientConnected()) {}// on attend que tous les clients soient connect�es
	if (_bdd->TestRfidID(rfid))//Si l'id rfid existe dans la BDD
	{
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Acc�s autoris�");
		_listClient->ClientRFID->retourAccesDemand(true);// on envoie le retour de demande d'acces 
		try
		{
			float poids = _listClient->ClientBalance->getPoids();// on demande le poids du v�hicule � la balance
			Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Poids du vehicule : " + poids);
			Dechetterie::deleteUtilisateur(rfid,poids);
			_listClient->ClientBarriere->OuvrirBarriere();// on ouvre la barriere
			Thread::Sleep(TEMPO_BARRIERE);
			_listClient->ClientBarriere->FermerBarriere();// on ferme la barriere
		}
		catch (Exception^ e)
		{
			if (e->Message == "Timeout Get Poids")// si on recois pas le poids
			{
				Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), "Pas de poids");
			}
			else
			{
				Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), "[ AccesDemandEvent ]" + e->ToString());
			}

		}

	}
	else // si l'id rfid n'existe pas dans la bdd
	{
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Acc�s Refus�");
		_listClient->ClientRFID->retourAccesDemand(false);// on envoie le retour de demande d'acces 
	}
	Logger::PrintLog(_idGroupe.ToString(), "Fin de procedure !");
}




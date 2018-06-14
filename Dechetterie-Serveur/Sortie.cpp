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
Description  : Lorsqu'on a une demande d'acces à la sortie
Arguments    : rfid : Id rfid de la demande d'accès
Valeur renvoyée :
-----------------------------------------------------------------*/
void Sortie::AccesDemandEvent(String ^ rfid)
{
	Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Demande d'accès avec l'id RFID " + rfid);
	while (!AllClientConnected()) {}// on attend que tous les clients soient connectées
	if (_bdd->TestRfidID(rfid))//Si l'id rfid existe dans la BDD
	{
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Accès autorisé");
		_listClient->ClientRFID->retourAccesDemand(true);// on envoie le retour de demande d'acces 
		try
		{
			float poids = _listClient->ClientBalance->getPoids();// on demande le poids du véhicule à la balance
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
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Accès Refusé");
		_listClient->ClientRFID->retourAccesDemand(false);// on envoie le retour de demande d'acces 
	}
	Logger::PrintLog(_idGroupe.ToString(), "Fin de procedure !");
}




#include "Sortie.h"
#include "ClientRFID.h"

#define TEMPO_BARRIERE 20000


Sortie::Sortie(IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid) : Groupe(id_groupe::SORTIE, listenip, listenPort, ipBarriere, ipBalance, ipRfid){}
/*---------------------------------------------------------------
Nom          : AccesDemandEvent
Description  : Lorsqu'on a une demande d'acces à la sortie
Arguments    : rfid : Id rfid de la demande d'accès
Valeur renvoyée :
-----------------------------------------------------------------*/
void Sortie::AccesDemandEvent(String ^ rfid)
{
	Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Demande d'accès avec l'id RFID " + rfid);
	while (!AllClientConnected()) {}
	if (_bdd->TestRfidID(rfid))
	{
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Accès autorisé");
		_listClient->ClientRFID->retourAccesDemand(true);
		try
		{
			float poids = _listClient->ClientBalance->getPoids();
			Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Poids du vehicule : " + poids);


			Dechetterie::deleteUtilisateur(rfid,poids);

			_listClient->ClientBarriere->OuvrirBarriere();
			Thread::Sleep(TEMPO_BARRIERE);
			_listClient->ClientBarriere->FermerBarriere();
		}
		catch (Exception^ e)
		{
			if (e->Message == "Timeout Get Poids")
			{
				Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), "Pas de poids");
			}
			else
			{
				Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), "[ AccesDemandEvent ]" + e->ToString());
			}

		}

	}
	else
	{
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Accès Refusé");
		_listClient->ClientRFID->retourAccesDemand(false);
	}
	Logger::PrintLog(_idGroupe.ToString(), "Fin de procedure !");
}




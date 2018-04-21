#include "Sortie.h"
#include "ClientRFID.h"
#define TEMPO_BARRIERE 20000




Sortie::Sortie(IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid) : Groupe(id_groupe::SORTIE, listenip, listenPort, ipBarriere, ipBalance, ipRfid)
{

}
/*---------------------------------------------------------------
Nom          :
Description  :
Arguments    :
Valeur renvoy�e :
-----------------------------------------------------------------*/
void Sortie::AccesDemandEvent(String ^ rfid)
{
	Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Demande d'acc�s avec l'id RFID " + rfid);
	while (!AllClientConnected()) {}
	if (TestRfidID(rfid))
	{
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Acc�s autoris�");
		_listClient->ClientRFID->retourAccesDemand(true);
		try
		{
			int poids = 2000;
			//int poids = _listClient->ClientBalance->getPoids();
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
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Acc�s Refus�");
		_listClient->ClientRFID->retourAccesDemand(false);
	}
	Logger::PrintLog(_idGroupe.ToString(), "Fin de procedure !");
}



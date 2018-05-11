#include "Entree.h"
#include "ClientRFID.h"
#define TEMPO_BARRIERE 20000


Entree::Entree(IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid) : Groupe(id_groupe::ENTREE, listenip, listenPort, ipBarriere, ipBalance, ipRfid){}

/*---------------------------------------------------------------
Nom          : AccesDemandEvent
Description  : Lorsqu'on a une demande d'acces à l'entree
Arguments    : rfid : Id rfid de la demande d'accès
Valeur renvoyée :
-----------------------------------------------------------------*/
void Entree::AccesDemandEvent(String ^ rfid)
{
	Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Demande d'accès avec l'id RFID " + rfid);
	while (!AllClientConnected()) {}
	if (_bdd->TestRfidID(rfid))
	{
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Accès autorisé");
		_listClient->ClientRFID->retourAccesDemand(true);
		try
		{
			int dechet_type = _listClient->ClientRFID->getTypeDechet();
			Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Type de dechet selectionner : " + dechet_type);
			float poids = 2500;
			//int poids = _listClient->ClientBalance->getPoids();
			Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Poids du vehicule : " + poids);

			array<Byte>^ photo = _listClient->ClientRFID->getPhoto();

			Dechetterie::addUtilisateur(rfid, dechet_type, poids, photo);

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
				if (e->Message == "Timeout Get Dechet")
				{
					Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), " Pas de type de dechet");
				}
				else
				{
					if (e->Message == "Timeout Get Photo")
					{
						Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), " Pas de photo");
					}
					else
					{
						Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), "[ AccesDemandEvent ]" + e->ToString());
					}
				}


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






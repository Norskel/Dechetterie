#include "Entree.h"
#include "ClientRFID.h"
#define TEMPO_BARRIERE 2000


Entree::Entree(IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid) : Groupe(id_groupe::ENTREE, listenip, listenPort, ipBarriere, ipBalance, ipRfid){}

Entree::~Entree()
{
	_srv->~Serveur();
	delete _listClient;
}

/*---------------------------------------------------------------
Nom          : AccesDemandEvent
Description  : Lorsqu'on a une demande d'acces à l'entree
Arguments    : rfid : Id rfid de la demande d'accès
Valeur renvoyée :
-----------------------------------------------------------------*/
void Entree::AccesDemandEvent(String ^ rfid)
{
	Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Demande d'accès avec l'id RFID " + rfid);
	while (!AllClientConnected()) {} // on attend que tous les clients soient connectées
	if (_bdd->TestRfidID(rfid))//Si l'id rfid existe dans la BDD
	{
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Accès autorisé");
		_listClient->ClientRFID->retourAccesDemand(true); // on envoie le retour de demande d'acces 
		try
		{
			int dechet_type = _listClient->ClientRFID->getTypeDechet(); // on attend le type de dechet selectionnée
			Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Type de dechet selectionner : " + dechet_type);
			//float poids = 2500;
			float poids = _listClient->ClientBalance->getPoids(); // on demande le poids du véhicule à la balance
			Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Poids du vehicule : " + poids);

			array<Byte>^ photo = _listClient->ClientRFID->getPhoto(); // on demande l'envoie de la photo

			Dechetterie::addUtilisateur(rfid, dechet_type, poids, photo); // on ajoute un utilisateur dans le dechetterie

			_listClient->ClientBarriere->OuvrirBarriere(); // on ouvre la barriere
			Thread::Sleep(TEMPO_BARRIERE);
			_listClient->ClientBarriere->FermerBarriere(); // on ferme la barriere
		}
		catch (Exception^ e)
		{
			if (e->Message == "Timeout Get Poids") // si on recois pas le poids
			{
				Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), "Pas de poids");
			}
			else
			{
				if (e->Message == "Timeout Get Dechet") //si on recois pas le type de dechet
				{
					Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), " Pas de type de dechet");
				}
				else
				{
					if (e->Message == "Timeout Get Photo") //si on recois recois pas la photo
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
	else // si l'id rfid n'existe pas dans la bdd
	{
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Accès Refusé");
		_listClient->ClientRFID->retourAccesDemand(false);// on envoie le retour de demande d'acces 
	}
	Logger::PrintLog(_idGroupe.ToString(), "Fin de procedure !");
}






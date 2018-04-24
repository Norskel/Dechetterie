#pragma once
#include "Serveur.h"
#include "DataBddProxy.h"
#include "Dechetterie.h"
#include "Protocole\Protocole.h"
#include "ClientBalance.h"
#include "Groupe.h"


using namespace System;
using namespace System::Threading;
using namespace System::Text;

 
ref class Entree : public Groupe
{
protected:
	void AccesDemandEvent(String^ rfid) override
	{
		Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Demande d'accès avec l'id RFID " + rfid);
		while (!AllClientConnected()) {}
		if (TestRfidID(rfid))
		{
			Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Accès autorisé");
			_listClient->ClientRFID->retourAccesDemand(true);
			try
			{
				int dechet_type = _listClient->ClientRFID->getTypeDechet();
				Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Type de dechet selectionner : " + dechet_type);
				int poids = 2500;
				//int poids = _listClient->ClientBalance->getPoids();
				Logger::PrintLog(_idGroupe.ToString(), "[ RFID ] Poids du vehicule : " + poids);

				array<Byte>^ photo = _listClient->ClientRFID->getPhoto();

				//				Dechetterie::addUtilisateur(rfid, dechet_type, poids, photo);

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
public:
	Entree(IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid) : Groupe(id_groupe::ENTREE, listenip, listenPort, ipBarriere, ipBalance, ipRfid)
	{

	}

};


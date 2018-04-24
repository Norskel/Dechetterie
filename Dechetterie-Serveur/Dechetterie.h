#pragma once

#include "Enum.h"
#include "Utilisateur.h"
#include "DataBddProxy.h"
#include "Entree.h"
#include "Sortie.h"
#include "Protocole\Protocole.h"
#include "Protocole\StructProtocolMsg.h"
#include "Protocole\StructTypeMessage.h"
#include "StructDataConfigServeur.h"
#include "Logger.h"
#include "InterfacePipe.h"

#define PIPE_NAME_INTER_SERV "InterServeur"
#define PIPE_NAME_USER_INFOS_SERV "UserServeur"
#define INTERFACE_PROCESS_NAME "Dechetterie-Interface"  
#define FILE_NAME_USER "user.xml" // nom du fichier de sauvegarde des utilisateur dans la dechetterie

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::IO::Pipes;
using namespace System::Xml::Serialization;
using namespace System::Threading;
using namespace System::Diagnostics;

delegate void EventUpdateClientStateDelegate();

ref class Entree;
ref class Sortie;
ref class InterfacePipe;

ref class Dechetterie
{
private:
	static List<Utilisateur^>^ _listUtilisateur = gcnew List<Utilisateur^>;
	DataBddProxy^ _bdd;
	DataConfigServeur^ _config;
	Sortie^ _sortie;
	Entree^ _entree;

	InterfacePipe^ servInter;

	static List<Client^>^ _listClient = gcnew List<Client^>;

	NamedPipeServerStream^ _pipeServerState;
	NamedPipeServerStream^ _pipeServerUser;

	Thread^ _tServerStateMsg;
	Thread^ _tServerUserMsg;

public:

	static event EventUpdateClientStateDelegate^ EventUpdateClientState;
	static Boolean Debug = false;



	Dechetterie(String^ configFile)
	{
		if (loadConfigFile(configFile)) // Si on arrive a charger les configurations 
		{

			_bdd = DataBddProxy::getDataBddProxy(_config->IPBDD, _config->PortBDD.ToString(), _config->NomBDD, _config->UsernameBDD, _config->PasswordBDD); // on instancie le proxy de la BDD

			_entree = gcnew Entree(IPAddress::Parse(_config->Entree->Interface), _config->Entree->portServeur, IPAddress::Parse(_config->Entree->IPBarriere), IPAddress::Parse(_config->Entree->IPBalance), IPAddress::Parse(_config->Entree->IPRFID)); //Instanciation du groupe Entree
			_sortie = gcnew Sortie(IPAddress::Parse(_config->Sortie->Interface), _config->Sortie->portServeur, IPAddress::Parse(_config->Sortie->IPBarriere), IPAddress::Parse(_config->Sortie->IPBalance), IPAddress::Parse(_config->Sortie->IPRFID)); //Instanciation du groupe Sortie
			servInter = InterfacePipe::getInterfacePipe(_entree, _sortie); //première instanciation
		}
		else //si on arrive pas a charger le fichier de configutation
		{
			Logger::PrintLog(EnteteCode::ERROR, "[ Dechetterie ] Impossible de démarrer ");
			Thread::Sleep(2000);
			this->~Dechetterie(); // on arrete l'application
		}


	}
	~Dechetterie()
	{
		Logger::PrintLog("Dechetterie", "Arret");

	}
	/*---------------------------------------------------------------
	Nom          :  loadConfigFile
	Description  :  Charge le fichier de configuration
	Arguments    :  file: nom du fichier de configuration
	Valeur renvoyée : Boolean : resultat
	-----------------------------------------------------------------*/
	Boolean loadConfigFile(String^ file)
	{
		if (System::IO::File::Exists(file))
		{
			FileStream^ fs;
			bool fileOpened = false;
			do
			{
				try
				{
					fileOpened = false;
					fs = File::Open(file, System::IO::FileMode::Open);

				}
				catch (...)
				{
					Logger::PrintLog("[ Configuration ] Erreur à l'ouverture de " + file);
					fileOpened = true;
				}
			} while (!fileOpened);
			XmlSerializer^ serializer = gcnew XmlSerializer(DataConfigServeur::typeid);
			_config = (DataConfigServeur^)serializer->Deserialize(fs);
			fs->Close();
			Logger::PrintLog(EnteteCode::INFO, "[ Configuration ] Fichier de configuration bien chargée");
			return true;
		}
		else
		{
			Logger::PrintLog(EnteteCode::ERROR, "[ Configuration ] Fichier de configuration " + file + " est manquant. Démarer l'interface au moins une fois pour faire la configuration");
			return false;
		}
	}

	//================ Utilisateur =================================

	/*---------------------------------------------------------------
	Nom          : addUtilisateur
	Description  : Ajoute un utilisateur dans la liste des utilisateurs et rajoute une entrée a la table entree
	Arguments    : id_rfid : son id RFID, tDechet : type de dechey selectionne, poids : poids du vehicule à l'éntrée, photo : la photo
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	static void addUtilisateur(String ^ id_rfid, int tDechet, int poids, array<Byte>^ photo)
	{
		DataBddProxy^ bdd = DataBddProxy::getDataBddProxy();
		try
		{
			DataUser^ du = bdd->getUserByIdRFID(id_rfid); // On recupere les info de la personne grace a son id rfid

			_listUtilisateur->Add(gcnew Utilisateur(du->Nom, du->Prenom, tDechet, id_rfid, poids, photo)); // on rajoute la personne dans le tableau utilisateur de toutes les personne  qui sont dans la dechetterie

			DataEntree^ de = gcnew DataEntree();
			de->ID_Dechet = tDechet;
			de->ID_User = bdd->getUserByIdRFID(id_rfid)->ID;
			de->Poids = poids;
			de->dt = DateTime::Now;
			bdd->addEntree(de); //on ajoute dans la BDD Entree l'entree

			Logger::PrintLog(EnteteCode::INFO, EnteteCode::UTILISATEUR, "Nouvelle utilisateur dans la dechetterie : " + du->Nom + " " + du->Prenom + " ID_RFID = " + id_rfid);
		}
		catch (Exception^e)
		{
			if (e->Message == "ID_RFID Introuvable")
			{
				Logger::PrintLog(EnteteCode::ERROR, EnteteCode::UTILISATEUR, "Utilisateur avec id RFID " + id_rfid + " Inconnu ");
			}
			else
			{
				Logger::PrintLog(EnteteCode::ERROR, EnteteCode::UTILISATEUR, "addUtilisateur", e->ToString());
			}
		}
		try
		{
			Dechetterie::updateUserFile();
			(InterfacePipe::getInterfacePipe())->updateListClient();
		}
		catch (Exception^e)
		{
			Logger::PrintLog(EnteteCode::ERROR, EnteteCode::UTILISATEUR, "addUtilisateur", e->ToString());
		}

	}

	/*---------------------------------------------------------------
	Nom          : deleteUtilisateur
	Description  : Supprime l'utilisateur et supprime l'entre de la table entree  créé a l'entree dans la dechetterie
	fait le calcul du poids et cree une entrée dans la table historique
	Arguments    : id_rfid : id rfid de l'utilisateur, poidsSortie : poids à la sortie du véhicule
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	static void deleteUtilisateur(String ^ id_rfid, int poidsSortie)
	{
		try
		{
			DataBddProxy^ bdd = DataBddProxy::getDataBddProxy();
			Utilisateur^user = getUtilisateurByIdRFID(id_rfid);

			DataHistorique^ dh = gcnew DataHistorique();
			dh->Poids = (user->_poidsEntree - poidsSortie);
			dh->ID_Dechet = user->_typeDechet;
			dh->ID_User = user->ID_User;
			dh->dt = DateTime::Now;
			bdd->addHistorique(dh);

			Logger::PrintLog(EnteteCode::INFO, "[ Utilisateur ] L'utilisateur quitte la dechetterie : " + user->getNom() + " " + user->getPrenom() + " ID_RFID = " + id_rfid);

			int idEntree = bdd->getEntreeByUserID(user->ID_User)->ID;
			bdd->deleteEntreeByID(idEntree);
			_listUtilisateur->Remove(user);

			Dechetterie::updateUserFile();
			(InterfacePipe::getInterfacePipe())->updateListClient();
		}
		catch (Exception^ e)
		{
			if (e->Message == "Timeout Get Poids")
			{

			}
		}



	}

	/*---------------------------------------------------------------
	Nom          : getUtilisateurByIdRFID
	Description  : Renvoie l'utilisateur qui a l'id rfid indiqué
	Arguments    :	id_rfid : id rfid de l'utilisateur
	Valeur renvoyée : renvoie l'utilisateur qui porte cette id rfid ,  si il n'existe pas renvoie une excption "Utilisateur_existe_pas"
	-----------------------------------------------------------------*/
	static Utilisateur^ getUtilisateurByIdRFID(String ^ id_rfid)
	{
		for (int i = 0; i < _listUtilisateur->Count; i++)
		{
			if (_listUtilisateur[i]->getRFIDID() == id_rfid)
			{

				return _listUtilisateur[i];
				break;
			}
		}

		throw gcnew Exception("Utilisateur_existe_pas");
	}

	/*---------------------------------------------------------------
	Nom          :  getListUtilisateur
	Description  :  Retour la liste des utilisateur qui sont dans la dechetterie
	Arguments    :
	Valeur renvoyée : Liste d'utilisateur
	-----------------------------------------------------------------*/
	static List<Utilisateur^>^ getListUtilisateur()
	{
		return _listUtilisateur;
	}

	/*---------------------------------------------------------------
	Nom          : updateUserFile
	Description  : Mets à jour le fichier user.xml
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	static void updateUserFile()
	{
		FileStream^ fs;

		if (System::IO::File::Exists(FILE_NAME_USER))
		{
			bool fileOpened = false;
			do
			{
				try
				{
					fileOpened = false;
					System::IO::File::WriteAllText(FILE_NAME_USER, String::Empty);
					fs = File::Open(FILE_NAME_USER, System::IO::FileMode::Open);
				}
				catch (...)
				{
					Console::WriteLine("[ Configuration ] Erreur à l'ouverture de " + FILE_NAME_USER);
					fileOpened = true;
				}
			} while (fileOpened);

		}
		else
		{
			fs = File::Create(FILE_NAME_USER);

		}
		if (Dechetterie::getListUtilisateur()->Count > 0)
		{
			XmlSerializer^ serializer = gcnew XmlSerializer(List<Utilisateur^>::typeid);
			serializer->Serialize(fs, Dechetterie::getListUtilisateur());
			Console::WriteLine("[ Send User Msg ] Envoie");
		}
		fs->Close();
		Thread::Sleep(2000);
	}



};


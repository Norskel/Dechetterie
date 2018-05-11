#include "Dechetterie.h"
#define FILE_NAME_USER "user.xml" // nom du fichier de sauvegarde des utilisateur dans la dechetterie


Dechetterie::Dechetterie(String^ configFile)
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
		Logger::PrintLog(EnteteCode::ERROR,"[ Dechetterie ] Impossible de démarrer ");
		Thread::Sleep(2000);
		this->~Dechetterie(); // on arrete l'application
	}


}
Dechetterie::~Dechetterie()
{
	Logger::PrintLog("Dechetterie","Arret");

}
/*---------------------------------------------------------------
Nom          :  loadConfigFile
Description  :  Charge le fichier de configuration
Arguments    :  file: nom du fichier de configuration
Valeur renvoyée : Boolean : resultat
-----------------------------------------------------------------*/
Boolean Dechetterie::loadConfigFile(String ^ file)
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
		Logger::PrintLog(EnteteCode::INFO,"[ Configuration ] Fichier de configuration bien chargée");
		return true;
	}
	else
	{
		Logger::PrintLog(EnteteCode::ERROR, "[ Configuration ] Fichier de configuration " + file + " est manquant. Démarer l'interface au moins une fois pour faire la configuration");
		return false;
	}
}
/*---------------------------------------------------------------
Nom          :  getListUtilisateur
Description  :  Retour la liste des utilisateur qui sont dans la dechetterie
Arguments    : 
Valeur renvoyée : Liste d'utilisateur 
-----------------------------------------------------------------*/
List<Utilisateur^>^ Dechetterie::getListUtilisateur()
{
	return _listUtilisateur;
}
/*---------------------------------------------------------------
Nom          : updateUserFile
Description  : Mets à jour le fichier user.xml
Arguments    :
Valeur renvoyée :
-----------------------------------------------------------------*/
void Dechetterie::updateUserFile()
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
	//if (Dechetterie::getListUtilisateur()->Count > 0)
	//{
		XmlSerializer^ serializer = gcnew XmlSerializer(List<Utilisateur^>::typeid);
		serializer->Serialize(fs, Dechetterie::getListUtilisateur());
		Console::WriteLine("[ Send User Msg ] Envoie");
	//}
	fs->Close();
		Thread::Sleep(2000);
}
/*---------------------------------------------------------------
Nom          : addUtilisateur
Description  : Ajoute un utilisateur dans la liste des utilisateurs et rajoute une entrée a la table entree
Arguments    : id_rfid : son id RFID, tDechet : type de dechey selectionne, poids : poids du vehicule à l'éntrée, photo : la photo
Valeur renvoyée :
-----------------------------------------------------------------*/
void Dechetterie::addUtilisateur(String ^ id_rfid, int tDechet, float poids, array<Byte>^ photo)
{
	DataBddProxy^ bdd = DataBddProxy::getDataBddProxy();
	try
	{
		DataUser^ du = bdd->getUserByIdRFID(id_rfid); // On recupere les info de la personne grace a son id rfid

		_listUtilisateur->Add(gcnew Utilisateur(du->Nom, du->Prenom, tDechet, id_rfid,poids,photo)); // on rajoute la personne dans le tableau utilisateur de toutes les personne  qui sont dans la dechetterie
		
		bdd->EntrerUtilisateur(id_rfid, tDechet, poids);

		Logger::PrintLog(EnteteCode::INFO,EnteteCode::UTILISATEUR,"Nouvelle utilisateur dans la dechetterie : " + du->Nom +" "+ du->Prenom + " ID_RFID = " + id_rfid);
	}
	catch (Exception^e)
	{
		if (e->Message == "ID_RFID Introuvable")
		{
			Logger::PrintLog(EnteteCode::ERROR, EnteteCode::UTILISATEUR, "Utilisateur avec id RFID " + id_rfid + " Inconnu ");
		}
		else
		{
			Logger::PrintLog(EnteteCode::ERROR, EnteteCode::UTILISATEUR,"addUtilisateur",e->ToString());
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
Nom          : getUtilisateurByIdRFID
Description  : Renvoie l'utilisateur qui a l'id rfid indiqué
Arguments    :	id_rfid : id rfid de l'utilisateur
Valeur renvoyée : renvoie l'utilisateur qui porte cette id rfid ,  si il n'existe pas renvoie une excption "Utilisateur_existe_pas"
-----------------------------------------------------------------*/
Utilisateur^ Dechetterie::getUtilisateurByIdRFID(String ^ id_rfid)
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
Nom          : deleteUtilisateur
Description  : Supprime l'utilisateur et supprime l'entre de la table entree  créé a l'entree dans la dechetterie
				fait le calcul du poids et cree une entrée dans la table historique
Arguments    : id_rfid : id rfid de l'utilisateur, poidsSortie : poids à la sortie du véhicule
Valeur renvoyée :
-----------------------------------------------------------------*/
void Dechetterie::deleteUtilisateur(String ^ id_rfid,float poidsSortie)
{
	try
	{
		Console::WriteLine(_listUtilisateur->Count);
		DataBddProxy^ bdd = DataBddProxy::getDataBddProxy();
		Utilisateur^user = getUtilisateurByIdRFID(id_rfid);

		bdd->SortieUtilisateur(id_rfid, poidsSortie);


		Logger::PrintLog(EnteteCode::INFO, "[ Utilisateur ] L'utilisateur quitte la dechetterie : " + user->getNom() + " " + user->getPrenom() + " ID_RFID = " + id_rfid);
		_listUtilisateur->Remove(user);

		Dechetterie::updateUserFile();
		(InterfacePipe::getInterfacePipe())->updateListClient();
		Console::WriteLine(_listUtilisateur->Count);

	}
	catch (Exception^ e)
	{
		if (e->Message == "Timeout Get Poids")
		{
			
		}
	}


	
}



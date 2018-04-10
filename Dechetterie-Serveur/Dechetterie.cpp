#include "Dechetterie.h"
#define FILE_NAME_USER "user.xml"


Dechetterie::Dechetterie(String^ configFile)
{
	if (loadConfigFile(configFile))
	{

		_bdd = DataBddProxy::getDataBddProxy(_config->IPBDD, _config->PortBDD.ToString(), _config->NomBDD, _config->UsernameBDD, _config->PasswordBDD);

		_entree = gcnew Entree(IPAddress::Parse(_config->Entree->Interface), _config->Entree->portServeur, IPAddress::Parse(_config->Entree->IPBarriere), IPAddress::Parse(_config->Entree->IPBalance), IPAddress::Parse(_config->Entree->IPRFID));
		_sortie = gcnew Sortie(IPAddress::Parse(_config->Sortie->Interface), _config->Sortie->portServeur, IPAddress::Parse(_config->Sortie->IPBarriere), IPAddress::Parse(_config->Sortie->IPBalance), IPAddress::Parse(_config->Sortie->IPRFID));
		servInter = gcnew Interface(PIPE_NAME_INTER_SERV, _entree, _sortie);
	}
	else
	{
		Logger::PrintLog(EnteteCode::ERROR,"[ Dechetterie ] Impossible de démarrer ");
		Thread::Sleep(2000);
		this->~Dechetterie();
	}


}
Dechetterie::~Dechetterie()
{
	Logger::PrintLog("Dechetterie","Arret");

}
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
		} while (fileOpened);
		XmlSerializer^ serializer = gcnew XmlSerializer(DataConfigServeur::typeid);
		_config = (DataConfigServeur^)serializer->Deserialize(fs);
		fs->Close();
		Logger::PrintLog(0,"[ Configuration ] Fichier de configuration bien chargée");
		return true;
	}
	else
	{
		Logger::PrintLog(1, "[ Configuration ] Fichier de configuration " + file + " est manquant. Démarer l'interface au moins une fois pour faire la configuration");
		return false;
	}
}



List<Utilisateur^>^ Dechetterie::GetListUtilisateur()
{
	return _listUtilisateur;
}
void Dechetterie::addUtilisateur(String ^ id_rfid, int tDechet, int poids, array<Byte>^ photo)
{
	DataBddProxy^ bdd = DataBddProxy::getDataBddProxy();
	try
	{
		DataUser^ du = bdd->getUserByIdRFID(id_rfid); // On recupere les info de la personne grace a son id rfid

		_listUtilisateur->Add(gcnew Utilisateur(du->Nom, du->Prenom, tDechet, id_rfid,poids,photo)); // on rajoute la personne dans le tableau utilisateur de toutes les personne  qui sont dans la dechetterie
		
		DataEntree^ de = gcnew DataEntree(); 
		de->ID_Dechet = tDechet;
		de->ID_User = bdd->getUserByIdRFID(id_rfid)->ID;
		de->Poids = poids;
		de->dt = DateTime::Now;
		bdd->addEntree(de); //on ajoute dans la BDD Entree l'entree

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
	//
}
void Dechetterie::deleteUtilisateur(String ^ id_rfid)
{
	DataBddProxy^ bdd = DataBddProxy::getDataBddProxy();
	
	for (int i = 0; i < _listUtilisateur->Count; i++)
	{
		if (_listUtilisateur[i]->getRFIDID() == id_rfid)
		{
			Logger::PrintLog(0, "[ Utilisateur ] L'utilisateur quitte la dechetterie : " + _listUtilisateur[i]->getNom() + " " + _listUtilisateur[i]->getPrenom() + " ID_RFID = " + id_rfid);
			_listUtilisateur->RemoveAt(i);
			Console::WriteLine(_listUtilisateur->Count);

			break;
		}
	}
	try
	{
		int iduser = bdd->getUserByIdRFID(id_rfid)->ID;
		int idEntree = bdd->getEntreeByUserID(iduser)->ID;
		bdd->deleteEntreeByID(idEntree);
	}
	catch (Exception^ e)
	{
		Logger::PrintLog(2, e->ToString());
	}


}

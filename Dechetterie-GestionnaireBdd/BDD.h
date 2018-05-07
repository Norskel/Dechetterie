#pragma once
#include "StructDataConfigGestionnaire.h"
#include "StructDataDechet.h"
#include "StructDataEntree.h"
#include "StructDataHistorique.h"
#include "StructDataUser.h"
#include "StructDataFacture.h"

#define FILE_CONFIG "Config.xml"


using namespace System;
using namespace System::IO;
using namespace System::Xml::Serialization;
using namespace MySql::Data::MySqlClient;
using namespace System::Collections::Generic;

ref class BDD
{
private:
	BDD()
	{
		loadConfig();
		_infoConnection = "SERVER=" + _config->IPBDD + "; DATABASE=" + _config->NomBDD + "; PORT=" + Convert::ToString(_config->PortBDD) + "; UID=" + _config->UsernameBDD + "; PASSWORD=" + _config->PasswordBDD + "";
		_con = gcnew MySqlConnection(_infoConnection);
	}
	~BDD()
	{
		_con->Close();
	}
	static BDD^ _bdd = nullptr;
	MySqlConnection^ _con;
	DataConfigGestionnaire^ _config;
	String^ _infoConnection;
	void loadConfig()
	{
		FileStream^ fs;
		bool fileOpened = false;
		do
		{
			try
			{
				fileOpened = false;
				fs = File::Open((String^)FILE_CONFIG, System::IO::FileMode::Open);

			}
			catch (...)
			{
				Console::WriteLine("[ Configuration ] Erreur à l'ouverture de " + FILE_CONFIG);
				fileOpened = true;
			}
		} while (fileOpened);
		XmlSerializer^ serializer = gcnew XmlSerializer(DataConfigGestionnaire::typeid);
		_config = (DataConfigGestionnaire^)serializer->Deserialize(fs);
		fs->Close();


	}

public:

	static BDD^ getBdd()
	{
		if (_bdd == nullptr)
		{
			_bdd = gcnew BDD();
		}
		return _bdd;
	}
	void connect()
	{
		try
		{
			_con->Open();
		}
		catch (...)
		{

		}
	}

	Boolean ping()
	{
		return _con->Ping();
	}
	List<DataEntree^>^ getTableEntree() 
	{
		if (ping())
		{
			List<DataEntree^>^ t = gcnew List<DataEntree^>;
			MySqlCommand^ request = gcnew MySqlCommand("SELECT * FROM Entree;", _con);
			MySqlDataReader^ DR = request->ExecuteReader();

			while (DR->Read())
			{
				DataEntree^ et = gcnew DataEntree();
				et->ID = Convert::ToInt64(DR["ID"]);
				et->ID_User = Convert::ToInt64(DR["Utilisateur_ID"]);
				et->ID_Dechet = Convert::ToInt64(DR["TypeDechet_ID"]);
				et->Poids = Convert::ToInt64(DR["Poids"]);
				et->dt = DateTime::Parse(Convert::ToString(DR["DateTime"]));

				t->Add(et);

			}
			DR->Close();
			return t;
		}

	}
	List<DataUser^>^ getTableUser(String^ search) 
	{
		Console::WriteLine("co " + _infoConnection);

		Console::WriteLine("search " + search);
		Console::WriteLine("ping " + ping());
		if (ping())
		{
			
			List<DataUser^>^ t = gcnew List<DataUser^>;
			MySqlCommand^ request = gcnew MySqlCommand("call Dechetterie.RechercheUtilisateur(@search);", _con);
			request->Parameters->AddWithValue("@search", search);
			MySqlDataReader^ DR = request->ExecuteReader();
			while (DR->Read())
			{
				Console::WriteLine("HEY");
				DataUser^ ut = gcnew DataUser();
				ut->ID = Convert::ToInt64(DR["ID"]);
				ut->Prenom = Convert::ToString(DR["Prenom"]);
				ut->Nom = Convert::ToString(DR["Nom"]);
				ut->ID_RFID = Convert::ToString(DR["ID_RFID"]);
				ut->Ville = Convert::ToString(DR["Ville"]);
				ut->Adresse = Convert::ToString(DR["Adresse"]);
				ut->numero = Convert::ToInt64(DR["Numero"]);
				ut->Code_Postal = Convert::ToInt64(DR["Code_Postal"]);

				t->Add(ut);

			}
			DR->Close();

			return t;
		}
	}
	List<DataDechet^>^ getTableDechet() 
	{
		if (ping())
		{
			List<DataDechet^>^ t = gcnew List<DataDechet^>;
			MySqlCommand^ request = gcnew MySqlCommand("SELECT * FROM TypeDechet;", _con);

			MySqlDataReader^ DR = request->ExecuteReader();
			while (DR->Read())
			{
				DataDechet^ dt = gcnew DataDechet();
				dt->ID = Convert::ToInt64(DR["ID"]);
				dt->Nom = Convert::ToString(DR["Nom_Dechet"]);
				dt->Prix = Convert::ToDouble(DR["Prix"]);
				t->Add(dt);
				//t->Add(gcnew User((int)DR["ID"], (String^)DR["Nom"],(String^)DR["Prenom"], (String^)DR["ID_RFID"]));

			}
			DR->Close();

			return t;

		}

	}
	List<DataHistorique^>^ getTableHistorique()
	{
		if (ping())
		{
			List<DataHistorique^>^ t = gcnew List<DataHistorique^>;
			MySqlCommand^ request = gcnew MySqlCommand("SELECT * FROM Historique;", _con);

			MySqlDataReader^ DR = request->ExecuteReader();
			while (DR->Read())
			{
				DataHistorique^ dt = gcnew DataHistorique();
				dt->ID = Convert::ToInt64(DR["ID"]);
				dt->ID_Dechet = Convert::ToInt64(DR["ID_Dechet"]);
				dt->ID_User = Convert::ToInt64(DR["ID_User"]);
				dt->Poids = Convert::ToInt64(DR["Poids"]);
				dt->dt = DateTime::Parse(Convert::ToString(DR["DateTime"]));
				dt->temps = TimeSpan::Parse((DR["Temps"]->ToString()));
				t->Add(dt);
				

			}
			DR->Close();

			return t;

		}

	}

	List<DataHistorique^>^ getTableHistoriqueByIdUser(int id_User)
	{
		if (ping())
		{
			List<DataHistorique^>^ t = gcnew List<DataHistorique^>;
			MySqlCommand^ request = gcnew MySqlCommand("call Dechetterie.HistoriqueUtilisateur(@idUser);", _con);
			request->Parameters->AddWithValue("@idUser", id_User);

			MySqlDataReader^ DR = request->ExecuteReader();
			while (DR->Read())
			{
				DataHistorique^ dt = gcnew DataHistorique();
				dt->ID = Convert::ToInt64(DR["ID"]);
				dt->ID_Dechet = Convert::ToInt64(DR["TypeDechet_ID"]);
				dt->ID_User = Convert::ToInt64(DR["Utilisateur_ID"]);
				dt->Poids = Convert::ToInt64(DR["Poids"]);
				dt->dt = DateTime::Parse(Convert::ToString(DR["DateTime"]));

				//dt->temps = TimeSpan::Parse((DR["Temps"]->ToString()));
				t->Add(dt);


			}
			DR->Close();

			return t;

		}

	}

	DataUser^ getUserByID(int id)
	{
		for each (DataUser^ var in this->getTableUser(""))
		{
			if (var->ID == id)
			{
				return var;
			}
		}

		throw gcnew System::MissingMemberException();

	}
	DataDechet^ getDechetByID(int id)
	{
		for each (DataDechet^ var in this->getTableDechet())
		{
			if (var->ID == id)
			{
				return var;
			}
		}

		throw gcnew System::MissingMemberException();
	}

	void addUser(DataUser^ e) override
	{
		if (ping())
		{
			MySqlCommand^ request = gcnew MySqlCommand("call Dechetterie.NouvelleUtilisateur(@nom, @prenom, @ID_RFID, @ville, @adresse, @numero, @codePostal);", _con);
			request->Parameters->AddWithValue("@ID_RFID", e->ID_RFID);
			request->Parameters->AddWithValue("@nom", e->Nom);
			request->Parameters->AddWithValue("@prenom", e->Prenom);
			request->Parameters->AddWithValue("@adresse", e->Adresse);
			request->Parameters->AddWithValue("@ville", e->Ville);
			request->Parameters->AddWithValue("@numero", e->numero);
			request->Parameters->AddWithValue("@codePostal", e->Code_Postal);
			request->ExecuteNonQuery();
		}
	}
	void updateUser(DataUser^ e) override
	{
		if (ping())
		{
			
			MySqlCommand^ request = gcnew MySqlCommand("call Dechetterie.EditUtilisateur(@ID,@nom, @prenom, @ID_RFID, @ville, @adresse, @numero, @codePostal);", _con);


			request->Parameters->AddWithValue("@ID", e->ID);
			request->Parameters->AddWithValue("@ID_RFID", e->ID_RFID);
			request->Parameters->AddWithValue("@nom", e->Nom);
			request->Parameters->AddWithValue("@prenom", e->Prenom);
			request->Parameters->AddWithValue("@adresse", e->Adresse);
			request->Parameters->AddWithValue("@ville", e->Ville);
			request->Parameters->AddWithValue("@numero", e->numero);
			request->Parameters->AddWithValue("@codePostal", e->Code_Postal);
			request->ExecuteNonQuery();
		}
	}

	void deleteUserByID(int id) override
	{
		if (ping())
		{
			MySqlCommand^ request = gcnew MySqlCommand("call Dechetterie.SupprimerUtilisateur(@ID);", _con);
			request->Parameters->AddWithValue("@ID", id);
			request->ExecuteNonQuery();
		}
	}

	List<DataFacture^>^ getFacture(int id_user)
	{
		List<DataFacture^>^ dfL = gcnew List<DataFacture^>;
		List<DataHistorique^>^ dhL = getTableHistoriqueByIdUser(id_user);
		DataUser^ du = getUserByID(id_user);
		DataFacture^ df = gcnew DataFacture();
		if (dhL->Count > 0)
		{
			df->dt = dhL[0]->dt; //recupere la dernier date

			for each (DataHistorique^ var in dhL)
			{
				if (var->dt->Month < df->dt->Month || var->dt->Year < df->dt->Year) //si c'est un autre mois
				{
					df->utilisateur = du;
					dfL->Add(df);
					df = gcnew DataFacture();
					df->dt = var->dt;
				}

				df->listHistorique->Add(var);

			}
		}

		

		return dfL;
	}
};


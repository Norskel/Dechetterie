#include "DataBddProxy.h"


void DataBddProxy::_pingServeur()
{
	MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
	try
	{
		TcpClient^ tc = gcnew TcpClient();
		tc->SendTimeout = 20;
		tc->Connect(_ip, _port);
		tc->Close();
		_serveurPresent = true;
		if (_serveurPresent)
		{
			con->Open();
			if (_tableTask->Count > 0)
			{
				for each (BddTask^ var in _tableTask)
				{
					Console::WriteLine(var->table);
					MySqlCommand^ request = gcnew MySqlCommand(var->table, con);
					request->ExecuteNonQuery();
				}
				_tableTask->Clear();

			}
			Console::WriteLine("[ BDD ] Connection OK");
		}
					
	}
	catch (...)
	{
		_serveurPresent = false;
		Console::WriteLine("[ BDD ] Problème de connection");

	}
	con->Close();
}
bool DataBddProxy::getStateServeur()
{
	return _serveurPresent;
}

DataBddProxy::DataBddProxy(String^ ip, String^ port, String^ db, String^ user, String^ password)
{
	Console::WriteLine("[ BDD ] Première instanciation");
	_ip = ip;
	if (port == "")
	{
		_infoConnection = "SERVER=" + ip + "; DATABASE=" + db + "; UID=" + user + "; PASSWORD=" + password + "";
		_port = 3306;
	}
	else
	{
		_infoConnection = "SERVER=" + ip + "; DATABASE=" + db + "; PORT=" + port + "; UID=" + user + "; PASSWORD=" + password + "";
		_port = Convert::ToInt32(port);
	}
	Console::WriteLine(_infoConnection);
	_pingServeur();
}
DataBddProxy^ DataBddProxy::getDataBddProxy(String^ ip, String^ port, String^ db, String^ user, String^ password)
{
	if (_DataBddProxy == nullptr)
	{
		_DataBddProxy = gcnew DataBddProxy(ip,port,db,user,password);
	}
	return _DataBddProxy;
}

DataBddProxy ^ DataBddProxy::getDataBddProxy()
{
	if (_DataBddProxy == nullptr)
	{
		throw gcnew System::NotImplementedException();
	}
	return _DataBddProxy;
	
}

// ========================================= GET ===========================================
List<DataEntree^>^ DataBddProxy::getTableEntree()
{
	_pingServeur();
	if (_serveurPresent)
	{
		List<DataEntree^>^ t = gcnew List<DataEntree^>;
		MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
		con->Open();
		MySqlCommand^ request = gcnew MySqlCommand("SELECT * FROM Entree;", con);
		MySqlDataReader^ DR = request->ExecuteReader();

		while (DR->Read())
		{
			DataEntree^ dt = gcnew DataEntree();
			dt->ID =  Convert::ToInt64(DR["ID"]);
			dt->ID_User = Convert::ToInt64(DR["Utilisateur_ID"]);
			dt->ID_Dechet = Convert::ToInt64(DR["TypeDechet_ID"]);
			dt->Poids = Convert::ToInt64(DR["Poids"]);
			dt->dt = DateTime::Parse(Convert::ToString(DR["DateTime"]));

			t->Add(dt);

		}
		con->Close();
		_dataBdd->setTableEntree(t);
	}
	return _dataBdd->getTableEntree();
}
List<DataUser^>^ DataBddProxy::getTableUser()
{
	_pingServeur();
	if (_serveurPresent)
	{
		List<DataUser^>^ t = gcnew List<DataUser^>;
		MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
		con->Open();
		MySqlCommand^ request = gcnew MySqlCommand("SELECT * FROM Utilisateur;", con);
		MySqlDataReader^ DR = request->ExecuteReader();
		while (DR->Read())
		{
			DataUser^ et = gcnew DataUser();
			et->ID = Convert::ToInt64(DR["ID"]);
			et->Prenom = Convert::ToString(DR["Prenom"]);
			et->Nom = Convert::ToString(DR["Nom"]);
			et->ID_RFID = Convert::ToString(DR["ID_RFID"]);
			t->Add(et);

		}
		con->Close();
		_dataBdd->setTableUser(t);
	}
	return _dataBdd->getTableUser();
}
List<DataDechet^>^ DataBddProxy::getTableDechet()
{
	_pingServeur();
	if (_serveurPresent)
	{
		List<DataDechet^>^ t = gcnew List<DataDechet^>;
		MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
		con->Open();
		MySqlCommand^ request = gcnew MySqlCommand("SELECT * FROM TypeDechet;", con);


		MySqlDataReader^ DR = request->ExecuteReader();
		while (DR->Read())
		{
			DataDechet^ et = gcnew DataDechet();
			et->ID = Convert::ToInt64(DR["ID"]);
			et->Nom = Convert::ToString(DR["Nom_Dechet"]);
			t->Add(et);
			//t->Add(gcnew User((int)DR["ID"], (String^)DR["Nom"],(String^)DR["Prenom"], (String^)DR["ID_RFID"]));

		}
		con->Close();
		_dataBdd->setTableDechet(t);
	}
	return _dataBdd->getTableDechet();
}

DataUser ^ DataBddProxy::getUserByIdRFID(String^ id_Rfid)
{
	for each (DataUser^ var in this->getTableUser())
	{
		if (var->ID_RFID == id_Rfid)
		{
			return var;
		}
	}

	throw gcnew	Exception("ID_RFID Introuvable");

}

DataUser ^ DataBddProxy::getUserByID(int id)
{
	for each (DataUser^ var in this->getTableUser())
	{ 
		if (var->ID == id)
		{
			return var;
		}
	}	

	throw gcnew System::MissingMemberException();

}
DataDechet ^ DataBddProxy::getDechetByID(int id)
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
DataEntree ^ DataBddProxy::getEntreeByID(int id)
{
	for each (DataEntree^ var in this->getTableEntree())
	{
		if (var->ID == id)
		{
			return var;
		}
	}

	throw gcnew System::MissingMemberException();
}
DataEntree ^ DataBddProxy::getEntreeByUserID(int id)
{
	for each (DataEntree^ var in this->getTableEntree())
	{
		if (var->ID_User == id)
		{
			return var;
		}
	}

	throw gcnew System::MissingMemberException();
}
// ========================================= INSERT ===========================================
void DataBddProxy::addEntree(DataEntree ^ e)
{
	_pingServeur();
	if (_serveurPresent)
	{
		MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
		con->Open();
		MySqlCommand^ request = gcnew MySqlCommand("INSERT INTO `Dechetterie`.`Entree` (`Utilisateur_ID`, `Poids`, `TypeDechet_ID`, `DateTime`) VALUES (@ID_user, @poids, @ID_Dechet, @Dt);", con);
		request->Parameters->AddWithValue("@ID_user", e->ID_User);
		request->Parameters->AddWithValue("@poids", e->Poids);
		request->Parameters->AddWithValue("@ID_Dechet", e->ID_Dechet);
		request->Parameters->AddWithValue("@Dt", e->dt->ToString("yyyy-MM-dd HH:mm:ss"));

		request->ExecuteNonQuery();
		con->Close();
	}
	else
	{
		BddTask^ bt = gcnew BddTask();
		bt->type = 1;
		bt->table = "INSERT INTO `Dechetterie`.`Entree` (`Utilisateur_ID`, `Poids`, `TypeDechet_ID`, `DateTime`) VALUES ('"+e->ID_User+"', '" + e->Poids + "', '" + e->ID_Dechet + "', '" + e->dt->ToString("yyyy-MM-dd HH:mm:ss") + "');";
		_tableTask->Add(bt);
	}
	_dataBdd->addEntree(e);
}
void DataBddProxy::addUser(DataUser ^ e)
{
	_pingServeur();
	if (_serveurPresent)
	{
		MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
		con->Open();
		MySqlCommand^ request = gcnew MySqlCommand("INSERT INTO `Dechetterie`.`Utilisateur` (`Nom`, `Prenom`, `ID_RFID`) VALUES (@nom, @prenom, @ID_RFID);", con);
		request->Parameters->AddWithValue("@ID_RFID", e->ID_RFID);
		request->Parameters->AddWithValue("@nom", e->Nom);
		request->Parameters->AddWithValue("@prenom", e->Prenom);
		request->ExecuteNonQuery();
		con->Close();
	}
	else
	{
		BddTask^ bt = gcnew BddTask();
		bt->type = 1;
		bt->table = "INSERT INTO `Dechetterie`.`Utilisateur` (`Nom`, `Prenom`, `ID_RFID`) VALUES (`" + e->Nom + "`, `" + e->Prenom + "`, `" + e->ID_RFID + "`);";
		_tableTask->Add(bt);
	}
	_dataBdd->addUser(e);
}
void DataBddProxy::addDechet(DataDechet ^ e)
{
	_pingServeur();
	if (_serveurPresent)
	{
		MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
		con->Open();
		MySqlCommand^ request = gcnew MySqlCommand("INSERT INTO `Dechetterie`.`TypeDechet` (`Nom_Dechet`) VALUES (@nom);", con);
		request->Parameters->AddWithValue("@nom", e->Nom);
		request->ExecuteNonQuery();
		con->Close();
	}
	else
	{
		BddTask^ bt = gcnew BddTask();
		bt->type = 1;
		bt->table = "INSERT INTO `Dechetterie`.`TypeDechet` (`Nom_Dechet`) VALUES ('"+e->Nom+"');";
		_tableTask->Add(bt);
	}
	_dataBdd->addDechet(e);
}
void DataBddProxy::addHistorique(DataHistorique ^ e)
{
	_pingServeur();
	if (_serveurPresent)
	{
		MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
		con->Open();
		MySqlCommand^ request = gcnew MySqlCommand("INSERT INTO `Dechetterie`.`Historique` (`Utilisateur_ID`, `Poids`, `TypeDechet_ID`, `DateTime`) VALUES (@ID_user, @poids, @ID_Dechet, @Dt);", con);
		request->Parameters->AddWithValue("@ID_user", e->ID_User);
		request->Parameters->AddWithValue("@poids", e->Poids);
		request->Parameters->AddWithValue("@ID_Dechet", e->ID_Dechet);
		request->Parameters->AddWithValue("@Dt", e->dt->ToString("yyyy-MM-dd HH:mm:ss"));

		request->ExecuteNonQuery();
		con->Close();
	}
	else
	{
		BddTask^ bt = gcnew BddTask();
		bt->type = 1;
		bt->table = "INSERT INTO `Dechetterie`.`Historique` (`Utilisateur_ID`, `Poids`, `TypeDechet_ID`, `DateTime`) VALUES ('" + e->ID_User + "', '" + e->Poids + "', '" + e->ID_Dechet + "', '" + e->dt->ToString("yyyy-MM-dd HH:mm:ss") + "');";
		_tableTask->Add(bt);
	}
}
// ========================================= DELETE ===========================================
void DataBddProxy::deleteEntreeByID(int id)
{
	_pingServeur();
	if (_serveurPresent)
	{
		MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
		con->Open();
		MySqlCommand^ request = gcnew MySqlCommand("DELETE FROM `Dechetterie`.`Entree` WHERE `ID`=@ID;", con);
		request->Parameters->AddWithValue("@ID", id);
		request->ExecuteNonQuery();
		con->Close();
	}
	else
	{
		BddTask^ bt = gcnew BddTask();
		bt->type = 2;
		bt->table = "DELETE FROM `Dechetterie`.`Entree` WHERE `ID`=`"+id+"`;";
		_tableTask->Add(bt);
	}
	_dataBdd->deleteEntreeByID(id);
}
void DataBddProxy::deleteUserByID(int id)
{
	_pingServeur();
	if (_serveurPresent)
	{
		MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
		con->Open();
		MySqlCommand^ request = gcnew MySqlCommand("DELETE FROM `Dechetterie`.`Utilisateur` WHERE `ID`=@ID;", con);
		request->Parameters->AddWithValue("@ID", id);
		request->ExecuteNonQuery();
		con->Close();
	}
	else
	{
		BddTask^ bt = gcnew BddTask();
		bt->type = 2;
		bt->table = "DELETE FROM `Dechetterie`.`Utilisateur` WHERE `ID`=`" + id + "`;";
		_tableTask->Add(bt);
	}
	_dataBdd->deleteEntreeByID(id);
}
void DataBddProxy::deleteDechetByID(int id)
{
	_pingServeur();
	if (_serveurPresent)
	{
		MySqlConnection^ con = gcnew MySqlConnection(_infoConnection);
		con->Open();
		MySqlCommand^ request = gcnew MySqlCommand("DELETE FROM `Dechetterie`.`TypeDechet` WHERE `ID`=@ID;", con);
		request->Parameters->AddWithValue("@ID", id);
		request->ExecuteNonQuery();
		con->Close();
	}
	else
	{
		BddTask^ bt = gcnew BddTask();
		bt->type = 2;
		bt->table = "DELETE FROM `Dechetterie`.`TypeDechet` WHERE `ID`=" + id + ";";
		_tableTask->Add(bt);
	}
	_dataBdd->deleteEntreeByID(id);
}


 
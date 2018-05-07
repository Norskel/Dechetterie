#pragma once
#include "StructDataConfigServeur.h"
#include "Logger.h"

using namespace System;
using namespace System::Xml::Serialization;


ref class Config
{

private:
	static Config^ _config = nullptr;
	String^ _file = "";
	Config(){}
	DataConfigServeur^ _dataConfig = nullptr;
	/*---------------------------------------------------------------
	Nom          :  loadConfig
	Description  :  Charge les configs si le fichier existe d�j�
	Arguments    :  .
	Valeur renvoy�e : .
	-----------------------------------------------------------------*/
	void loadConfig()
	{
		if (System::IO::File::Exists(_file)) // Si le fichier existe d�j�
		{
			FileStream^ fs;
			bool fileOpened = false;
			do
			{
				try
				{
					fileOpened = false;
					fs = File::Open(_file, System::IO::FileMode::Open);
				}
				catch (...)
				{
					Logger::PrintLog(EnteteCode::CONFIG, " Erreur � l'ouverture de " + _file);
					fileOpened = true;
				}
			} while (!fileOpened);
			XmlSerializer^ serializer = gcnew XmlSerializer(DataConfigServeur::typeid);
			_dataConfig = (DataConfigServeur^)serializer->Deserialize(fs);
			fs->Close();
		}
	}

	/*---------------------------------------------------------------
	Nom          :  saveConfig
	Description  :  Sauvegarde les configs dans le fichier
	Arguments    :  .
	Valeur renvoy�e : .
	-----------------------------------------------------------------*/
	void saveConfig()
	{
		FileStream^ fs;
		XmlSerializer^ serializer = gcnew XmlSerializer(DataConfigServeur::typeid);

		if (System::IO::File::Exists(_file))
		{
			bool fileOpened = false;
			do
			{
				try
				{
					fileOpened = false;
					System::IO::File::WriteAllText(_file, String::Empty);
					fs = File::Open(_file, System::IO::FileMode::Open);
				}
				catch (...)
				{
					Logger::PrintLog(EnteteCode::CONFIG, " Erreur � l'ouverture de " + _file);
					fileOpened = true;
				}
			} while (fileOpened);

		}
		else // Si le fichier n'existe pas d�j�
		{
			fs = File::Create(_file); // on le cree

		}
		if (_config != nullptr)
		{
			serializer->Serialize(fs, _dataConfig);
		}
		fs->Close();
	}




public:

	static Config^ GetConfig()
	{
		if (_config == nullptr)
		{
			_config = gcnew Config();
		}
		return _config;
	}
	/*---------------------------------------------------------------
	Nom          :  getDataConfig
	Description  :  Retourne les donn�e de configuration du serveur
	Arguments    :  .
	Valeur renvoy�e : DataConfigServeur^ : les donn�e de configuration du serveur
	-----------------------------------------------------------------*/
	DataConfigServeur^ getDataConfig()
	{
		loadConfig();
		return _dataConfig;
	}

	/*---------------------------------------------------------------
	Nom          :  setDataConfig
	Description  :  Set les donn�e de configuration du serveur
	Arguments    :  DataConfigServeur^ : les donn�e de configuration du serveur
	Valeur renvoy�e : .
	-----------------------------------------------------------------*/
	void setDataConfig(DataConfigServeur^ dataconfigserveur)
	{
		_dataConfig = dataconfigserveur;
		saveConfig();
	}

	/*---------------------------------------------------------------
	Nom          :  getFileName
	Description  :  Retourne le noms et le chemin du fichier
	Arguments    :  .
	Valeur renvoy�e : String^ : noms et le chemin du fichier
	-----------------------------------------------------------------*/
	String^ getFileName()
	{
		return _file;
	}

	/*---------------------------------------------------------------
	Nom          :  getFileName
	Description  :  Set le noms et le chemin du fichier
	Arguments    :  String^ : noms et le chemin du fichier
	Valeur renvoy�e : .
	-----------------------------------------------------------------*/
	void setFileName(String^ file)
	{
		_file = file;
	}
};


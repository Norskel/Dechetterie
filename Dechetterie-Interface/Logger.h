#pragma once
#define NAME_LOG_FILE  "logInterface.txt"
using namespace System;
using namespace System::Text;
using namespace System::IO;


static public enum class EnteteCode : char { INFO, ERROR, DEBUG, ENTREE, SORTIE, INTERFACE, SERVEUR, CLIENT, UTILISATEUR,CONFIG };

static ref class Logger
{
public:
	static void print(String^ t)
	{
		FileStream ^fs;
		StreamWriter^ sw;
		String^ msg = "";
		msg += DateTime::Now.ToString("dd-MM-yyyy HH:mm:ss");

		if (!System::IO::File::Exists(NAME_LOG_FILE))
		{
			fs = File::Create(NAME_LOG_FILE);
			fs->Close();
		}

		bool fileOpened = false;
		do
		{
			try
			{
				fileOpened = false;
				sw = gcnew StreamWriter(NAME_LOG_FILE, true, Encoding::ASCII);

			}
			catch (...)
			{
				Console::WriteLine("[ Configuration ] Erreur à l'ouverture de " + NAME_LOG_FILE);
				fileOpened = true;
			}
		} while (fileOpened);
		msg += t;
		sw->WriteLine(msg);
		sw->Close();



		Console::WriteLine(t);
	}

	String^ nameFile = "log.txt";

	static void PrintLog(String^ text)
	{
		print("[ " + Convert::ToString(EnteteCode::INFO) + " ] " + text);
	}
	static void PrintLog(String^ entete,String^ text)
	{
		print("[ " + entete + " ] " + text);

	}
	static void PrintLog(EnteteCode entete, String^ text)
	{
		print("[ " + Convert::ToString(entete) + " ] " + text);
	}
	static void PrintLog(EnteteCode entete, String^ entete2, String^ text)
	{
		print("[ " + Convert::ToString(entete) + " ][ " + entete2 + " ] " + text);
	}
	static void PrintLog(EnteteCode entete, EnteteCode entete2, String^ text)
	{
		print("[ " + Convert::ToString(entete) + " ][ " + Convert::ToString(entete2) + " ] " + text);
	}
	static void PrintLog(EnteteCode entete, EnteteCode entete2, String^ entete3, String^ text)
	{
		print("[ " + Convert::ToString(entete) + " ][ " + Convert::ToString(entete2) + " ][ " + entete3 + " ] " + text);
	}
	Logger()
	{

	}
};



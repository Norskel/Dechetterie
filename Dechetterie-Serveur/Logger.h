#pragma once
#define NAME_LOG_FILE  "log.txt"
using namespace System;
using namespace System::Text;
using namespace System::IO;


static public enum class EnteteCode : char { INFO, ERROR, DEBUG, ENTREE, SORTIE, INTERFACE,SERVEUR,CLIENT };

static ref class Logger
{
public:
	static void print(String^ t);

	String^ nameFile = "log.txt";
	static void PrintLog(String^ text);
	static void PrintLog(String^ entete,String^ text);
	static void PrintLog(int entete,String^ text);
	static void PrintLog(EnteteCode entete, String^ text);
	static void PrintLog(EnteteCode entete, String^ entete2, String^ text);
	static void PrintLog(EnteteCode entete, EnteteCode entete2, String^ text);
	static void PrintLog(EnteteCode entete, EnteteCode entete2, String^ entete3, String^ text);
	Logger();
};


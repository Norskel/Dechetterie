#pragma once
#define NAME_LOG_FILE  "log.txt"
using namespace System;
using namespace System::Text;
using namespace System::IO;


static public enum class EnteteCode : char { INFO, ERROR, DEBUG, ENTREE, SORTIE , INTERFACE };

static ref class Logger
{
public:
	static void print(String^ t);

	String^ nameFile = "log.txt";
	static void PrintLog(String^ text);
	static void PrintLog(String^ entete,String^ text);
	static void PrintLogCode(int entete,String^ text);
	static void PrintLogCode(EnteteCode entete, String^ text);
	static void PrintLogCode(int entete, int t);



	Logger();
};


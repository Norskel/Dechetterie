#include "Logger.h"


void Logger::print(String ^ t)
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
					sw = gcnew StreamWriter(NAME_LOG_FILE, true,Encoding::ASCII);

				}
				catch (...)
				{
					Console::WriteLine("[ Configuration ] Erreur � l'ouverture de " + NAME_LOG_FILE);
					fileOpened = true;
				}
			} while (fileOpened);
			msg += t;
			sw->WriteLine(msg);
			sw->Close();
		

	
	Console::WriteLine(t);
}

void Logger::PrintLog(String ^ text)
{
	print("[ " + Convert::ToString(EnteteCode::INFO) + " ] " + text);
}

void Logger::PrintLog(String ^ entete, String ^ text)
{
	print("[ " + entete + " ] " + text);

}

void Logger::PrintLogCode(int entete, String ^ text)
{
	print("[ " + Convert::ToString(EnteteCode(entete)) + " ] " + text);
}

void Logger::PrintLogCode(int entete, int t)
{
	throw gcnew System::NotImplementedException();
}

Logger::Logger()
{
}
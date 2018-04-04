#include "Dechetterie.h"
#include "Entree.h"
#include "StructDataConfigServeur.h"

#define FILE_CONFIG "ConfigServeur.xml"
#define PIPE_NAME_STATE_SERV "StateServeur"
#define PIPE_NAME_USER_INFOS_SERV "StateServeur"
#define INTERFACE_PROCESS_NAME "Dechetterie-Interface"

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Xml::Serialization;
using namespace System::Threading;
using namespace System::Diagnostics;
using namespace System::Drawing;


int main(array<System::String ^> ^args)
{

	//Entree^ r;
	//List<Client^>^ listClient = gcnew List<Client^>;
	//listClient->Add(gcnew Client(1, 1, IPAddress::Parse("192.168.245.128")));// 1 barriere 2 balance 3 rfid	
	////listClient->Add(gcnew Client(1, 2, IPAddress::Parse("192.168.245.130")));
	//listClient->Add(gcnew Client(1, 2, IPAddress::Parse("192.168.0.5")));

	////listClient->Add(gcnew Client(1, 3, IPAddress::Parse("192.168.245.130")));
	//listClient->Add(gcnew Client(1, 3, IPAddress::Parse("127.0.0.1")));

	//listClient->Add(gcnew Client(2, 1, IPAddress::Parse("192.168.245.128")));// 1 barriere 2 balance 3 rfid	
	//																		 //listClient->Add(gcnew Client(1, 2, IPAddress::Parse("192.168.245.130")));
	//listClient->Add(gcnew Client(2, 2, IPAddress::Parse("192.168.0.5")));

	////listClient->Add(gcnew Client(1, 3, IPAddress::Parse("192.168.245.130")));
	//listClient->Add(gcnew Client(2, 3, IPAddress::Parse("127.0.0.1")));


	Dechetterie^ d = gcnew Dechetterie(FILE_CONFIG);

	Bitmap^ i = gcnew Bitmap("test.jpeg");
	ImageConverter^ converter = gcnew ImageConverter();

	array<Byte>^ rt = (array<Byte>^)converter->ConvertTo(i, array<Byte>::typeid);
	Dechetterie::addUtilisateur("02006D7223", 1, 2500, rt);
	Thread::Sleep(10000);
	Dechetterie::deleteUtilisateur("02006D7223");

	return 0;
}

//String^ convertDateTimeFormat()
//{
//
//}
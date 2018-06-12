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

	Dechetterie^ d = gcnew Dechetterie(FILE_CONFIG);

	return 0;
}

//String^ convertDateTimeFormat()
//{
//
//}
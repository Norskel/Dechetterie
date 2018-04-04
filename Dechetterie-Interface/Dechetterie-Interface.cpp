#define FILE_CONFIG "ConfigServeur.xml"
#define SRV_PROCESS_NAME "Dechetterie-Serveur"
#define PIPE_NAME_STATE_SERV "StateServeur"
#define PIPE_NAME_USER_INFOS_SERV "UserServeur"

#include "MainForm.h"
#include "ConfigForm.h"
#include "stdafx.h"

using namespace System;
using namespace System::Windows::Forms;

int Main(array<System::String ^> ^args)
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);


	MainForm mainForm;

	Application::Run(%mainForm);
	Console::WriteLine(L"Hello World");
	return 0;
}

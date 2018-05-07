// Dechetterie-Gestionnaire.cpp : fichier projet principal.

#include "MainForm.h"
#include "stdafx.h"
#include "ConfigBddForm.h"

using namespace System;
using namespace System::Windows::Forms;

int Main(array<System::String ^> ^args)
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MainForm mainnForm;
	//ConfigBddForm mainnForm;

	Application::Run(%mainnForm);
	Console::WriteLine(L"Hello World");
	return 0;
}
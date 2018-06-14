#pragma once
#include "StructDataHistorique.h"
#include "StructDataUser.h"
//#include "BDD.h"
using namespace System;
using namespace System::Collections::Generic;

ref class DataFacture
{
public:

	int ID;
	int ID_Utilisateur;
	DateTime^ dt;
	Boolean^ state;
	
};
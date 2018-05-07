#pragma once
#include "StructDataHistorique.h"
#include "StructDataUser.h"
//#include "BDD.h"
using namespace System;
using namespace System::Collections::Generic;

ref class DataFacture
{
public:


	List<DataHistorique^>^ listHistorique = gcnew List<DataHistorique^>;
	DataUser^ utilisateur;
	DateTime^ dt;
	
};
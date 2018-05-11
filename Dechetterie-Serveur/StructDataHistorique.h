#pragma once
using namespace System;

ref struct DataHistorique
{
	int ID;
	DateTime^ dt;
	int Poids;
	int ID_User;
	int ID_Dechet;
	int temps;
};
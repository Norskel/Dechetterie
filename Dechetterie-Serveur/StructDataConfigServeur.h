#pragma once
using namespace System;

public ref struct DataGroupe
{

	int portServeur = 0;
	String^ Interface = "0.0.0.0";
	String^ IPBalance = "0.0.0.0";
	String^ IPBarriere = "0.0.0.0";
	String^ IPRFID = "0.0.0.0";


};

public ref struct DataConfigServeur
{
	DataGroupe^ Entree= gcnew DataGroupe();
	DataGroupe^ Sortie = gcnew DataGroupe();
	String^ NomBDD = "Dechetterie";
	String^ IPBDD = "0.0.0.0";
	int PortBDD = 0;
	String^ UsernameBDD = "";
	String^ PasswordBDD = "";


};



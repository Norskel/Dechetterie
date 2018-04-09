#pragma once
using namespace System;

ref class TypeMessage
{
public:
	TypeMessage(){}
	TypeMessage(String^ id,int Type, int s, String^ nom, String^ data1, String^ typeData1, int nbBData1, String^ data2, String^ typeData2, int nbBData2)
	{
		ID = id;
		type = Type;
		Sender = s;
		Nom = nom;
		Data1 = data1;
		TypeData1 = typeData1;
		NbBData1 = nbBData1;
		Data2 = data2;
		TypeData2 = typeData2;
		NbBData2 = nbBData2;
	}
	TypeMessage(String^ id, int Type, int s, String^ nom, String^ data1, String^ typeData1, int nbBData1)
	{
		ID = id;
		type = Type;
		Sender = s;
		Nom = nom;
		Data1 = data1;
		TypeData1 = typeData1;
		NbBData1 = nbBData1;
	}
	TypeMessage(String^ id, int Type, int s, String^ nom)
	{
		ID = id;
		type = Type;
		Sender = s;
		Nom = nom;
	}

	String^ ID = ""; 
	int type;
	int Sender;
	String^ Nom;

	String^ Data1 = "";
	int NbBData1 = 0;
	String^ TypeData1 = "";

	String^ Data2 = "";
	int NbBData2 = 0;
	String^ TypeData2 = "";

	String^ ToString() override
	{
		return Nom;
	}
};
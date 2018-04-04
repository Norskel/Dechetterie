#pragma once

using namespace System;


public ref class Utilisateur
{
public:
	String^ _prenom = "";
	String^ _nom = "";
	array<Byte>^ _photo = gcnew array<Byte>(25);
	int _typeDechet;
	String^ _RFID_Card;
	DateTime _dtArrivee;
	int ID_User;
	int _poidsEntree;


	Utilisateur() {}
	Utilisateur(String^ nom, String^prenom, int tdechet, String^  rfid, int poids, array<Byte>^p)
	{
		_nom = nom;
		_prenom = prenom;
		_typeDechet = tdechet;
		_RFID_Card = rfid;
		_poidsEntree = poids;
		_dtArrivee = DateTime::Now;
		_photo = p;
	}

	TimeSpan getDuree()
	{
		DateTime d = DateTime::Now;
		return d.Subtract(_dtArrivee);
	}

	DateTime getArrivee()
	{
		return _dtArrivee;
	}

	String^ getRFIDID()
	{
		return _RFID_Card;
	}

	String^ getNom()
	{
		return _nom;
	}

	String^ getPrenom()
	{
		return _prenom;
	}

	int getTypeDechet()
	{
		return _typeDechet;
	}

	array<Byte>^ getPhoto()
	{
		return _photo;
	}




};


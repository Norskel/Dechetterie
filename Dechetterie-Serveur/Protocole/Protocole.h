#pragma once
#include "StructProtocolMsg.h"
#include "StructTypeMessage.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;

ref class Protocole
{
private:
	static Protocole^  _proto = nullptr;
	int _nbByteTaille = 4;
	int _nbByteType = 2;
	int _tailleBuffer = 1024;
	Encoding^ encoder = Encoding::ASCII;

	List<TypeMessage^>^ _listTypeMsg = gcnew List<TypeMessage^>;

	Protocole()
	{
		//====Type Message = ID | Nb Type | Sender | Nom | Nom Data1 | Type Data1 | Nb Octet Data1 | Nom Data2 | Type Data2 | Nb Octet Data2 
		_listTypeMsg->Add(gcnew TypeMessage("baDPoids",21, 1, "Demande du poids"));
		_listTypeMsg->Add(gcnew TypeMessage("baRDPoids",22, 2, "Retour du poids", "Poids", "int", 6));

		_listTypeMsg->Add(gcnew TypeMessage("brOuvre",31, 1, "Ouvrir Barrière"));
		_listTypeMsg->Add(gcnew TypeMessage("brFerme",32, 1, "Fermé Barrière"));
		_listTypeMsg->Add(gcnew TypeMessage("brDEtat",33, 1, "Demande de l'état de la barrière"));
		_listTypeMsg->Add(gcnew TypeMessage("brRDEtat",34, 3, "Retour de l'état de la barrière", "Etat", "bool", 1));

		_listTypeMsg->Add(gcnew TypeMessage("RfDAcces",41, 4, "Demande d'accès", "ID RFID", "string", 10));
		_listTypeMsg->Add(gcnew TypeMessage("RfRDAcces",42, 1, "Retour demande d'accès", "Autorisation", "bool", 1));
		_listTypeMsg->Add(gcnew TypeMessage("RfDechet",43, 4, "Envoie des infos dechet", "Type de dechet", "int", 1));
		_listTypeMsg->Add(gcnew TypeMessage("RfPhotoGet", 44, 1, "Demande photo véhicule"));
		_listTypeMsg->Add(gcnew TypeMessage("RfPhotoInit",45, 4, "Initialisation envoie photo", "nombre de packet", "int", 5));
		_listTypeMsg->Add(gcnew TypeMessage("RfPhotoSend",46, 4, "Envoie photo", "Numéro de packet", "int", 5, "Data photo", "byte", _tailleBuffer - _nbByteTaille + _nbByteType + 5));
		_listTypeMsg->Add(gcnew TypeMessage("RfPhotoEnd",47, 4, "Fin Envoie photo"));

		_listTypeMsg->Add(gcnew TypeMessage("AllPing",10, 0, "Ping"));
		_listTypeMsg->Add(gcnew TypeMessage("AllRPing",11, 0, "Retour Ping"));
	}

	//copie le tableau b dans le tableau a à partir de ai
	void cpyTableByte(array<Byte>^ %a, int ai, array<Byte>^b) 
	{
		//Console::WriteLine("ta " + a->Length + " tb " + b->Length + " AI " + ai);

		for (int i = 0; i < b->Length; i++)
		{
			//Console::WriteLine("i " + i + "  ai+i " + (ai + i));

			a[ai + i] = b[i];
		}
	}
	//copie le tableau b dans le tableau a à partir de ai mais dans le sens inverse 
	void cpyTableByteI(array<Byte>^ %a, int ai, array<Byte>^b)
	{
		for (int i = 0; i < b->Length; i++)
		{
			a[ai - b->Length + i + 1] = b[i];
		}
	}
	// permet d'extraire le tableau b du tableau a à partir de ai
	void cpyTableByteRI(array<Byte>^ a, int ai, array<Byte>^%b)
	{
		//Console::WriteLine("ta " + a->Length + " tb " + b->Length + " AI " + ai);
		for (int i = 0; i < b->Length; i++)
		{
			//Console::WriteLine("i " + i + "  ai+i " + (ai + i));
			b[i] = a[ai + i];
		}
	}


public:
	// Récupration de l'obejet protocole etant donnée que c'est un singleton
	static Protocole^ getProtocole()
	{
		if (_proto == nullptr)
		{
			_proto = gcnew Protocole();
		}
		return _proto;
	}

	// Traduit les messages a envoyé en tableau de Byte
	array<Byte>^ translate(int type, String^ data)
	{
		int taille = encoder->GetByteCount(data) + _nbByteTaille + _nbByteType; // calcule la taille du packet a envoyé pour la premier partie du protocole
		array<Byte>^buffer = gcnew array<Byte>(taille); // création du tableau de sortie avec la bonne taille
		for (int i = 0; i < buffer->Length; i++) //remplissage du tableau de 0;
		{
			buffer[i] = '0';
		}
		cpyTableByteI(buffer, _nbByteTaille - 1, encoder->GetBytes(Convert::ToString(taille))); // copie la taille dans le tableau final ici c'est 4 byte pour la taille
		cpyTableByteI(buffer, _nbByteTaille + _nbByteType - 1, encoder->GetBytes(Convert::ToString(type))); // copie le type dans le tableau final ici c'est 2 byte pour la taille
		cpyTableByte(buffer, _nbByteTaille + _nbByteType, encoder->GetBytes(Convert::ToString(data))); //copie le message dans le tableau de final

		return buffer;
	}
	array<Byte>^ translate(int type, array<Byte>^ data)
	{
		Encoding^ encoder = Encoding::ASCII;
		//Console::WriteLine("tL " + data->Length + " taille " + _nbByteTaille + " type " + _nbByteType);
		int taille = (data->Length + _nbByteTaille + _nbByteType);
		array<Byte>^buffer = gcnew array<Byte>(taille);
		for (int i = 0; i < buffer->Length; i++)
		{
			buffer[i] = '0';
		}
		cpyTableByteI(buffer, _nbByteTaille - 1, encoder->GetBytes(Convert::ToString(taille)));
		cpyTableByteI(buffer, _nbByteTaille + _nbByteType - 1, encoder->GetBytes(Convert::ToString(type)));
		cpyTableByte(buffer, _nbByteTaille + _nbByteType, data);

		return buffer;
	}

	array<Byte>^ GetBalancePoids()
	{
		return translate(GetTypeProtocoleByID("baDPoids"), "");
	}
	array<Byte>^ RetourGetBalancePoids(int poids)
	{
		TypeMessage^ tTM = getTypeMessageByType(GetTypeProtocoleByID("baRDPoids"));
		array<Byte>^ t = gcnew array<Byte>(tTM->NbBData1);
		for (int i = 0; i < t->Length; i++)
		{
			t[i] = '0';
		}
		cpyTableByteI(t, tTM->NbBData1 - 1, encoder->GetBytes(Convert::ToString(poids)));

		return translate(GetTypeProtocoleByID("baRDPoids"), t);
	}

	array<Byte>^ OuvrirBarriere()
	{
		return translate(GetTypeProtocoleByID("brOuvre"), "");
	}
	array<Byte>^ FermerBarriere()
	{
		return translate(GetTypeProtocoleByID("brFerme"), "");
	}
	array<Byte>^ GetEtatBarriere()
	{
		return translate(GetTypeProtocoleByID("brDEtat"), "");
	}
	array<Byte>^ RetourGetEtatBarriere(Boolean state)
	{
		if (state)
		{
			return translate(GetTypeProtocoleByID("brRDEtat"), "1");

		}
		else
		{
			return translate(GetTypeProtocoleByID("brRDEtat"), "0");
		}
	}

	array<Byte>^ RFIDAccesDemand(String^ RFID_ID)
	{
		return translate(GetTypeProtocoleByID("RfDAcces"), RFID_ID);
	}
	array<Byte>^ RetourRFIDAccesDemand(Boolean state)
	{
		if (state)
		{
			return translate(GetTypeProtocoleByID("RfRDAcces"), "1");
		}
		else
		{
			return translate(GetTypeProtocoleByID("RfRDAcces"), "0");
		}
	}
	array<Byte>^ EnvoieTypeDechet(int tdechet)
	{
		return translate(GetTypeProtocoleByID("RfDechet"), Convert::ToString(tdechet));
	}
	array<Byte>^ GetPhoto()
	{
		return translate(GetTypeProtocoleByID("RfPhotoGet"), "");
	}
	array<Byte>^ InitEnvoiePhoto(int nbPacket)
	{
		TypeMessage^ tTM = getTypeMessageByType(GetTypeProtocoleByID("RfPhotoInit"));
		array<Byte>^ t = gcnew array<Byte>(tTM->NbBData1);
		for (int i = 0; i < t->Length; i++)
		{
			t[i] = '0';
		}
		cpyTableByteI(t, tTM->NbBData1 - 1, encoder->GetBytes(Convert::ToString(nbPacket)));

		return translate(GetTypeProtocoleByID("RfPhotoInit"), t);
	}
	array<Byte>^ EnvoiePhoto(int nPacket, array<Byte>^ data)
	{
		TypeMessage^ tTM = getTypeMessageByType(GetTypeProtocoleByID("RfPhotoSend"));
		array<Byte>^ t = gcnew array<Byte>(tTM->NbBData1 + data->Length);
		for (int i = 0; i < t->Length; i++)
		{
			t[i] = '0';
		}
		cpyTableByteI(t, tTM->NbBData1 - 1, encoder->GetBytes(Convert::ToString(nPacket)));
		cpyTableByteI(t, t->Length - 1, data);

		return translate(GetTypeProtocoleByID("RfPhotoSend"), t);
	}
	array<Byte>^ EndEnvoiePhoto()
	{
		return translate(GetTypeProtocoleByID("RfPhotoEnd"), "");
	}

	array<Byte>^ Ping()
	{
		return translate(GetTypeProtocoleByID("AllPing"), "");
	}
	array<Byte>^ RetourPing()
	{
		return translate(GetTypeProtocoleByID("AllRPing"), "");
	}

	List<TypeMessage^>^  GetListTypeMessage()
	{
		return _listTypeMsg;
	}

	ProtocolMsg^ translateReceive(array<Byte>^t)
	{

		//Console::WriteLine(" ");
		ProtocolMsg^ tPM = gcnew ProtocolMsg();

		array<Byte>^ ttaille = gcnew array<Byte>(_nbByteTaille);
		array<Byte>^ ttype = gcnew array<Byte>(_nbByteType);

		cpyTableByteRI(t, 0, ttaille);
		cpyTableByteRI(t, _nbByteTaille, ttype);


		tPM->lenght = Convert::ToInt16(encoder->GetString(ttaille));
		tPM->type = Convert::ToInt16(encoder->GetString(ttype));

		TypeMessage^ tTM = getTypeMessageByType(tPM->type);

		if (tTM->NbBData1 != 0)
		{
			array<Byte>^ tt1 = gcnew array<Byte>(tTM->NbBData1);
			cpyTableByteRI(t, _nbByteTaille + _nbByteType, tt1);
			tPM->data1 = tt1;

			if (tTM->NbBData2 != 0)
			{
				array<Byte>^ tt2 = gcnew array<Byte>(tPM->lenght - (_nbByteTaille + _nbByteType + tTM->NbBData1));
				cpyTableByteRI(t, _nbByteTaille + _nbByteType + tTM->NbBData1, tt2);
				tPM->data2 = tt2;
			}
		}
		tPM->raw = t;
		return tPM;
	}
	array<Byte>^ translateByID(int id, Boolean state, String^ txt, int n)
	{
		switch (id)
		{
		case 1:
			return GetBalancePoids();
			break;
		case 2:
			return RetourGetBalancePoids(n);
			break;
		case 3:
			return OuvrirBarriere();
			break;
		case 4:
			return FermerBarriere();
			break;
		case 5:
			return GetEtatBarriere();
			break;
		case 6:
			return RetourGetEtatBarriere(state);
			break;
		case 7:
			return RFIDAccesDemand(txt);
			break;
		case 8:
			return RetourRFIDAccesDemand(state);
			break;
		case 50:
			return Ping();
			break;
		case 51:
			return RetourPing();
			break;
		default:
			break;
		}
	}

	TypeMessage^ getTypeMessageByType(int type)
	{
		for each (TypeMessage^ var in _listTypeMsg)
		{
			if (var->type == type)
			{
				return var;
				break;
			}
		}
	}
	int GetTypeProtocoleByID(String^ id)
	{
		for each (TypeMessage^ var in _listTypeMsg)
		{
			if (var->ID == id)
			{
				return var->type;
				break;
			}
		}
	}


};

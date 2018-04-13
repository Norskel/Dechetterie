#include "Groupe.h"


Groupe::Groupe(id_groupe id,IPAddress ^ listenip, int listenPort, IPAddress ^ ipBarriere, IPAddress ^ ipBalance, IPAddress ^ ipRfid)
{
	Logger::PrintLog(id.ToString(), "Interface d'écoute : " + listenip + " Port d'écoute : " + listenPort);
	_listClient = gcnew GroupeClient();
	_listClient->ClientBarriere = gcnew ClientBarriere(id, ipBarriere);
	_listClient->ClientBalance = gcnew ClientBalance(id, ipBalance);
	_listClient->ClientRFID = gcnew ClientRFID(id, ipRfid);

	_srv = gcnew Serveur(listenip, listenPort, id, _listClient);
	_srv->Start();

	_idGroupe = id;

	this->_listClient->ClientRFID->AccesDemand += gcnew AccesDemandDelegate(this, &Groupe::AccesDemandEvent);

	_bdd = DataBddProxy::getDataBddProxy();
	protocole = Protocole::getProtocole();

}

void Groupe::AccesDemandEvent(String ^ rfid)
{
	Console::WriteLine("FAILLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL");
}


void Groupe::OuvrirBarriere()
{
	if (_listClient->ClientBarriere->getState())
	{
		_listClient->ClientBarriere->OuvrirBarriere();
	}

}

void Groupe::FermerBarriere()
{
	if (_listClient->ClientBarriere->getState())
	{
		_listClient->ClientBarriere->FermerBarriere();
	}
}

int Groupe::GetPositionBarriere()
{
	if (_listClient->ClientBarriere->getState())
	{
		return _listClient->ClientBarriere->getPosition();
	}
	else
	{
		return -1;
	}
	
}

Boolean Groupe::AllClientConnected()
{
	//return	_listClient->ClientBalance->getState() && _listClient->ClientBarriere->getState() && _listClient->ClientRFID->getState();
	return true;
}

Boolean Groupe::TestRfidID(String ^ rfid)
{
	try
	{
		DataUser^ user = _bdd->getUserByIdRFID(rfid);
		return true;
	}
	catch (Exception^ e)
	{

		if (e->Message != "ID_RFID Introuvable")
		{
			Logger::PrintLog(EnteteCode::ERROR, _idGroupe.ToString(), "[ TestRfidID ]" + e->ToString());
		}

		return false;
	}

}

String ^ Groupe::GetStateAllClient()
{
	String^ r = "";
	if (_listClient->ClientBarriere->getState()) { r += 1; } else { r += 0; }
	if (_listClient->ClientBalance->getState()) { r += 1; } else { r += 0; }
	if (_listClient->ClientRFID->getState()) { r += 1; } else { r += 0; }
	return r;

}

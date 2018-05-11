#include "Groupe.h"
#include "InterfacePipe.h"

/*---------------------------------------------------------------
Nom          :
Description  :
Arguments    :
Valeur renvoyée :
-----------------------------------------------------------------*/
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

	_listClient->ClientBalance->disconnection += gcnew DisconnectionDelegate(this, &Groupe::ClientDisconnectionEvent);
	_listClient->ClientBarriere->disconnection += gcnew DisconnectionDelegate(this, &Groupe::ClientDisconnectionEvent);
	_listClient->ClientRFID->disconnection += gcnew DisconnectionDelegate(this, &Groupe::ClientDisconnectionEvent);


}
/*---------------------------------------------------------------
Nom          :
Description  :
Arguments    :
Valeur renvoyée :
-----------------------------------------------------------------*/
void Groupe::AccesDemandEvent(String ^ rfid)
{
}

void Groupe::ClientDisconnectionEvent()
{
	(InterfacePipe::getInterfacePipe())->updateClientState();
}

/*---------------------------------------------------------------
Nom          :
Description  :
Arguments    :
Valeur renvoyée :
-----------------------------------------------------------------*/
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
/*---------------------------------------------------------------
Nom          :
Description  :
Arguments    :
Valeur renvoyée :
-----------------------------------------------------------------*/
Boolean Groupe::AllClientConnected()
{
	//return	_listClient->ClientBalance->getState() && _listClient->ClientBarriere->getState() && _listClient->ClientRFID->getState();
	return true;
}

/*---------------------------------------------------------------
Nom          : GetStateAllClient
Description  :
Arguments    :
Valeur renvoyée :
-----------------------------------------------------------------*/
String ^ Groupe::GetStateAllClient()
{
	String^ r = "";
	if (_listClient->ClientBarriere->getState()) { r += 1; } else { r += 0; }
	if (_listClient->ClientBalance->getState()) { r += 1; } else { r += 0; }
	if (_listClient->ClientRFID->getState()) { r += 1; } else { r += 0; }
	return r;

}



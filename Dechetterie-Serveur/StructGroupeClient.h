#pragma once
#include "Client.h"
#include "ClientBarriere.h"
#include "ClientBalance.h"
#include "ClientRFID.h"

ref struct GroupeClient
{
	ClientBalance^ ClientBalance = nullptr;
	ClientBarriere^ ClientBarriere = nullptr;
	ClientRFID^ ClientRFID = nullptr;
};

#pragma once
#include "Client.h"
#include "ClientBarriere.h"
#include "ClientBalance.h"
#include "ClientRFID.h"

ref class GroupeClient
{
public:
	ClientBalance^ ClientBalance = nullptr;
	ClientBarriere^ ClientBarriere = nullptr;
	ClientRFID^ ClientRFID = nullptr;

	~GroupeClient()
	{
		if (ClientBarriere != nullptr)
		{
			ClientBarriere->~ClientBarriere();
		}
		if (ClientBalance != nullptr)
		{
			ClientBalance->~ClientBalance();
		}
		if (ClientRFID != nullptr)
		{
			ClientRFID->~ClientRFID();
		}
	}
};

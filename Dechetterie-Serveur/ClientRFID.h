#pragma once
#include "Client.h"
ref class ClientRFID : public Client
{
public:
	ClientRFID(int groupe, IPAddress^ip) : Client(groupe, 3, ip)
	{

	}
};


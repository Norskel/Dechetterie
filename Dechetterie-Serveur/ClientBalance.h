#pragma once
#include "Client.h"

ref class ClientBalance : public Client
{
public:
	ClientBalance(int groupe, IPAddress^ip) : Client(groupe, 3, ip)
	{

	}



};


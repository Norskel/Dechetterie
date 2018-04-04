#pragma once
#include "StructDataEntree.h"
#include "StructDataUser.h"
#include "StructDataDechet.h"

using namespace System;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic;
using namespace MySql::Data::MySqlClient;

ref class IDataBdd abstract
{
public:
	// ========================================= GET ===========================================
	virtual List<DataEntree^>^ getTableEntree() = 0;
	virtual List<DataUser^>^ getTableUser() = 0;
	virtual List<DataDechet^>^ getTableDechet() = 0;
	// -------------------------------
	virtual DataUser^ getUserByID(int id) = 0;
	virtual DataDechet^ getDechetByID(int id) = 0;
	virtual DataEntree^ getEntreeByID(int id) = 0;
	virtual DataEntree^ getEntreeByUserID(int id) = 0;
	// ========================================= INSERT ===========================================
	virtual void addEntree(DataEntree^ e) = 0;
	virtual void addUser(DataUser^ e) = 0;
	virtual void addDechet(DataDechet^ e) = 0;
	// ========================================= DELETE ===========================================
	virtual void deleteEntreeByID(int id) = 0;
	virtual void deleteUserByID(int id) = 0;
	virtual void deleteDechetByID(int id) = 0;

};
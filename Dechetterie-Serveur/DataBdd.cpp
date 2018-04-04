#include "DataBdd.h"



// ========================================= GET ===========================================
List<DataEntree^>^ DataBdd::getTableEntree()
{
	return tableEntree;
}
List<DataUser^>^ DataBdd::getTableUser()
{
	return tableUser;
}
List<DataDechet^>^ DataBdd::getTableDechet()
{
	return tableDechet;
}

DataUser ^ DataBdd::getUserByID(int id)
{
	for each (DataUser^ var in tableUser)
	{
		if (var->ID == id)
		{
			return var;
		}
	}
}
DataDechet ^ DataBdd::getDechetByID(int id)
{
	for each (DataDechet^ var in tableDechet)
	{
		if (var->ID == id)
		{
			return var;
		}
	}
}
DataEntree ^ DataBdd::getEntreeByID(int id)
{
	for each (DataEntree^ var in tableEntree)
	{
		if (var->ID == id)
		{
			return var;
		}
	}
}
DataEntree ^ DataBdd::getEntreeByUserID(int id)
{
	for each (DataEntree^ var in tableEntree)
	{
		if (var->ID_User == id)
		{
			return var;
		}
	}
}
// ========================================= SET ===========================================
void DataBdd::setTableEntree(List<DataEntree^>^ t)
{
	tableEntree = t;
}
void DataBdd::setTableUser(List<DataUser^>^ t)
{
	tableUser = t;
}
void DataBdd::setTableDechet(List<DataDechet^>^ t)
{
	tableDechet = t;
}
// ========================================= INSERT ===========================================
void DataBdd::addEntree(DataEntree ^ e)
{
	tableEntree->Add(e);
}
void DataBdd::addUser(DataUser ^ e)
{
	tableUser->Add(e);
}
void DataBdd::addDechet(DataDechet ^ e)
{
	tableDechet->Add(e);
}
// ========================================= DELETE ===========================================
void DataBdd::deleteEntreeByID(int id)
{
	for (int i = 0; i < tableEntree->Count; i++)
	{
		if (tableEntree[i]->ID == id)
		{
			tableEntree->RemoveAt(i);
			break;
		}
	}
}
void DataBdd::deleteUserByID(int id)
{
	for (int i = 0; i < tableUser->Count; i++)
	{
		if (tableUser[i]->ID == id)
		{
			tableUser->RemoveAt(i);
			break;
		}
	}
}
void DataBdd::deleteDechetByID(int id)
{
	for (int i = 0; i < tableDechet->Count; i++)
	{
		if (tableDechet[i]->ID == id)
		{
			tableDechet->RemoveAt(i);
			break;
		}
	}
}



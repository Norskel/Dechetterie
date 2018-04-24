#pragma once
#include "IDataBdd.h"

using namespace System::Collections::Generic;

ref class DataBdd : public IDataBdd
{
private:
	List<DataEntree^>^ tableEntree = gcnew List<DataEntree^>;
	List<DataUser^>^ tableUser = gcnew List<DataUser^>;
	List<DataDechet^>^ tableDechet = gcnew List<DataDechet^>;

public:

	// ========================================= GET ===========================================
	List<DataEntree^>^ getTableEntree() override
	{
		return tableEntree;
	}
	List<DataUser^>^ getTableUser() override
	{
		return tableUser;
	}
	List<DataDechet^>^ getTableDechet() override
	{
		return tableDechet;
	}
	// -------------------------------
	DataUser^ getUserByID(int id) override
	{
		for each (DataUser^ var in tableUser)
		{
			if (var->ID == id)
			{
				return var;
			}
		}
	}
	DataDechet^ getDechetByID(int id) override
	{
		for each (DataDechet^ var in tableDechet)
		{
			if (var->ID == id)
			{
				return var;
			}
		}
	}
	DataEntree^ getEntreeByID(int id) override
	{
		for each (DataEntree^ var in tableEntree)
		{
			if (var->ID == id)
			{
				return var;
			}
		}
	}
	DataEntree^ getEntreeByUserID(int id) override
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
	void setTableEntree(List<DataEntree^>^ t)
	{
		tableEntree = t;
	}
	void setTableUser(List<DataUser^>^ t)
	{
		tableUser = t;
	}
	void setTableDechet(List<DataDechet^>^ t)
	{
		tableDechet = t;
	}
	// ========================================= INSERT ===========================================
	void addEntree(DataEntree^ e) override
	{
		tableEntree->Add(e);
	}
	void addUser(DataUser^ e) override
	{
		tableUser->Add(e);
	}
	void addDechet(DataDechet^ e) override
	{
		tableDechet->Add(e);
	}
	// ========================================= DELETE ===========================================
	void deleteEntreeByID(int id) override
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
	void deleteUserByID(int id) override
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
	void deleteDechetByID(int id) override
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

};


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
	List<DataEntree^>^ getTableEntree() override;
	List<DataUser^>^ getTableUser() override;
	List<DataDechet^>^ getTableDechet() override;
	// -------------------------------
	DataUser^ getUserByID(int id) override;
	DataDechet^ getDechetByID(int id) override;
	DataEntree^ getEntreeByID(int id) override;
	DataEntree^ getEntreeByUserID(int id) override;
	// ========================================= SET ===========================================
	void setTableEntree(List<DataEntree^>^ t);
	void setTableUser(List<DataUser^>^ t);
	void setTableDechet(List<DataDechet^>^ t);
	// ========================================= INSERT ===========================================
	void addEntree(DataEntree^ e) override;
	void addUser(DataUser^ e) override;
	void addDechet(DataDechet^ e) override;
	// ========================================= DELETE ===========================================
	void deleteEntreeByID(int id) override;
	void deleteUserByID(int id) override;
	void deleteDechetByID(int id) override;

};


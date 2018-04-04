#pragma once
#include "IDataBdd.h"
#include "DataBdd.h"
#include "StructDataHistorique.h"
#include "StructBddTask.h"


ref class DataBddProxy : public IDataBdd
{
private:
	static DataBddProxy^ _DataBddProxy = nullptr;
	DataBdd^ _dataBdd = gcnew DataBdd();
	String^ _infoConnection;
	int _port;
	String^ _ip;
	Boolean _serveurPresent = false;
	void _pingServeur();
	List<BddTask^>^ _tableTask = gcnew List<BddTask^>;
	DataBddProxy(String^ ip, String^ port, String^ db, String^ user, String^ password);
public: 
	static DataBddProxy^ getDataBddProxy(String^ ip, String^ port, String^ db, String^ user, String^ password);
	static DataBddProxy^ getDataBddProxy();

	bool getStateServeur();

	// ========================================= GET ===========================================
	List<DataEntree^>^ getTableEntree() override;
	List<DataUser^>^ getTableUser() override;
	List<DataDechet^>^ getTableDechet() override;
	// -------------------------------
	DataUser^ getUserByID(int id) override;
	DataUser^ getUserByIdRFID(String^ id_Rfid);
	DataDechet^ getDechetByID(int id) override;
	DataEntree^ getEntreeByID(int id) override;
	DataEntree^ getEntreeByUserID(int id) override;
	// ========================================= INSERT ===========================================
	void addEntree(DataEntree^ e) override;
	void addUser(DataUser^ e) override;
	void addDechet(DataDechet^ e) override;
	void addHistorique(DataHistorique^ e);
	// ========================================= DELETE ===========================================
	void deleteEntreeByID(int id) override;
	void deleteUserByID(int id) override;
	void deleteDechetByID(int id) override;



};


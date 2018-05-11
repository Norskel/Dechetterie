#pragma once
#include "Protocole\Protocole.h"
#include "Client.h"

#define TIMEOUT_GET_DECHET 60 //*0.5s
#define TIMEOUT_GET_PHOTO 120 //*0.5s

using namespace System::Windows::Forms;

delegate void AccesDemandDelegate(String^);

ref class ClientRFID : public Client
{
protected:
	array<Byte>^ _photo = nullptr;
	String^ _RFID = nullptr;
	int _dechet = 0;

	Thread^ accesDemandThread;


	void fonctionReceive(ProtocolMsg^ pm, array<Byte>^ data) override
	{
		if (pm->type == protocole->GetTypeProtocoleByID("RfDAcces"))
		{
			_RFID = pm->getData1String();
			accesDemandThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &ClientRFID::AccesDemandEvent));
			accesDemandThread->Name = "Thread Acces Demand";
			accesDemandThread->Start(_RFID);

			Logger::PrintLog("Sortie de l'event");
		}
		else
		{
			if (pm->type == protocole->GetTypeProtocoleByID("RfPhotoInit"))
			{
				int nbPacket = pm->getData1Int();
				ReceptionPhoto(nbPacket);
			}
			else
			{
				if (pm->type == protocole->GetTypeProtocoleByID("RfDechet"))
				{
					//m->WaitOne();
					Logger::PrintLog(EnteteCode::DEBUG, "dechet :" + pm->getData1Int());
					this->_dechet = pm->getData1Int();
					//m->ReleaseMutex();

				}
				else
				{

					bufferRecv = data;
				}
			}
		}
	}
	void ReceptionPhoto(int nbPacket)
	{

		Console::WriteLine("[ Reception Photo ] Initialisation de la reception de la Photo ");
		Console::WriteLine("[ Reception Photo ] Nombre de packet à recevoir : " + nbPacket);

		array<Byte>^ photo = gcnew array<Byte>(1024 * nbPacket);

		int iPhoto = 0;
		ProtocolMsg^ receptionMsg;
		do
		{
			array<Byte>^ data = gcnew array<Byte>(1024);
			_clientSocket->Receive(data);
			receptionMsg = protocole->translateReceive(data);
			if (receptionMsg->type == protocole->GetTypeProtocoleByID("RfPhotoSend"))
			{
				for (int i = 0; i < receptionMsg->data2->Length; i++)
				{


					photo[iPhoto] = receptionMsg->data2[i];
					iPhoto++;



				}
				if (receptionMsg->getData1Int() == nbPacket)
				{
					break;
				}
			}


		} while (receptionMsg->type != protocole->GetTypeProtocoleByID("RfPhotoEnd"));

		Console::WriteLine("[ Reception Photo ] Fin de transmission ");
		Console::WriteLine("[ Reception Photo ] Taille de la photo recu en octet (Byte) : " + iPhoto);

		_photo = photo;
	}
	void AccesDemandEvent(Object^ o)
	{
		AccesDemand((String^)o);
		Console::WriteLine("Sortie de l'event acces");
		accesDemandThread->Abort();
		//accesDemandThread->Join();
		Console::WriteLine("event acces" + accesDemandThread->IsAlive);
		
	}

public:
	event AccesDemandDelegate^ AccesDemand;
	ClientRFID(id_groupe groupe, IPAddress^ip) : Client(groupe, id_client::ClientRFID, ip)
	{

	}

	//String^ getAccesDemand()
	//{
	//	String^ r;
	//	while (_RFID == nullptr)
	//	{
	//		Thread::Sleep(500);
	//	}
	//	r = _RFID;
	//	_RFID = nullptr;
	//	return r;
	//	
	//}
	void retourAccesDemand(Boolean autorisation)
	{
		this->Send(protocole->RetourRFIDAccesDemand(autorisation));
	}
	int getTypeDechet()
	{
		int timeout = 0;
		int r;
		while (_dechet == 0 && timeout < TIMEOUT_GET_DECHET)
		{
			Thread::Sleep(500);
			timeout++;
		}
		if (timeout >= TIMEOUT_GET_DECHET)
		{
			throw gcnew Exception("Timeout Get Dechet");
		}
		else
		{
			r = _dechet;
			_dechet = 0;
			return r;
		}
		
	}
	array<Byte>^ getPhoto() 
	{ 
		this->Send(protocole->GetPhoto());

		int timeout = 0;
		array<Byte>^ r;
		while (_photo == nullptr && timeout < TIMEOUT_GET_PHOTO)
		{
			Thread::Sleep(500);
			timeout++;
		}
		if (timeout >= TIMEOUT_GET_PHOTO)
		{
			throw gcnew Exception("Timeout Get Photo");
		}
		else
		{
			r = _photo;
			_photo = nullptr;
			return r;
		}

		return _photo; 

	}

	
};


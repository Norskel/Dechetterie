#pragma once
#include "Protocole\Protocole.h"
#include "Client.h"
ref class ClientRFID : public Client
{
private:
	array<Byte>^ _photo = nullptr;
	String^ _RFID = nullptr;
	int _dechet = 0;

	void fctThread() override
	{
		while (true)
		{
			if (_clientSocket != nullptr)
			{
				try
				{
					if (_clientSocket->Connected)
					{
						array<Byte>^ data = gcnew array<Byte>(1024);
						_clientSocket->Receive(data);
						ProtocolMsg^ pm = protocole->translateReceive(data);

						if (pm->type == protocole->GetTypeProtocoleByID("AllPing"))
						{
							this->Send(protocole->RetourPing());
							Logger::PrintLog("PING", "Demande de ping de " + _ip->ToString() + "( " + _groupe.ToString() + " " + _type.ToString() + " )");
						}
						else
						{
							if (pm->type == protocole->GetTypeProtocoleByID("RfDAcces"))
							{
								_RFID = pm->getData1String();
								Logger::PrintLog("");
							}
							else
							{
								bufferRecv = data;
							}
						}
					}
					else
					{
						this->Disconnect();
					}
				}
				catch (Exception^e)
				{

					//Console::WriteLine("[ Client ][ Thread Receive ]" + e);

				}
			}
			Thread::Sleep(100);
		}
	}
	void startReceive() override
	{
		_thread = gcnew Thread(gcnew ThreadStart(this, &ClientRFID::fctThread));
		_thread->Name = "Client IP " + _ip->ToString();
		_thread->Start();
	}
public:




	ClientRFID(id_groupe groupe, IPAddress^ip) : Client(groupe, id_client::ClientRFID, ip)
	{

	}

	String^ getRfid()
	{
		String^ r;
		while (_RFID == nullptr)
		{
			Thread::Sleep(500);
			
		}
	
		r = _RFID;
		_RFID = nullptr;
		return r;
		
	}
	array<Byte>^ ReceptionPhoto(Client^ cl)
	{
		cl->Send(protocole->GetPhoto());

		ProtocolMsg^ msgRev = gcnew ProtocolMsg();
		do
		{
			msgRev = protocole->translateReceive(_ClientRFID->Receive());
			Console::WriteLine("Type = " + msgRev->type);

		} while (msgRev->type != protocole->GetTypeProtocoleByID("RfPhotoInit"));

		int nbPacket = msgRev->getData1Int();
		Console::WriteLine("[ Reception Photo ] Initialisation de la reception de la Photo ");
		Console::WriteLine("[ Reception Photo ] Nombre de packet à recevoir : " + nbPacket);

		array<Byte>^ photo = gcnew array<Byte>(1024 * nbPacket);

		int iPhoto = 0;
		ProtocolMsg^ receptionMsg;
		do
		{
			receptionMsg = protocole->translateReceive(cl->Receive());
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

		return photo;
	}
	array<Byte>^ getPhoto() { return _photo; }
};


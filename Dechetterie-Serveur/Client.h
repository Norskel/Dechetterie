#pragma once
#include "Enum.h"
#include "Logger.h"
#include "Protocole\Protocole.h"


using namespace System;
using namespace System::Threading;
using namespace System::Threading::Tasks;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic;

delegate void SetIntDelegate(int);

ref class Client
{
protected:

	Protocole^ protocole = Protocole::getProtocole();
	id_groupe _groupe;
	id_client _type;
	IPAddress^ _ip;
	Boolean _isConnected = false;
	Socket^ _clientSocket = nullptr;
	Thread^ _thread;
	array<Byte>^ bufferRecv = nullptr;

	virtual void fctThread()
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
							Logger::PrintLog(EnteteCode::CLIENT, "Ping", "Demande de ping de " + _ip->ToString() + "( " + id_groupe(_groupe).ToString() + " " + id_client(_type).ToString() + " )");
						}
						else
						{
							bufferRecv = data;
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
	virtual void startReceive()
	{
		_thread = gcnew Thread(gcnew ThreadStart(this, &Client::fctThread));
		_thread->Name = "Client IP " + _ip->ToString();
		_thread->Start();
	}

public:
	Client(id_groupe groupe, id_client type, IPAddress^ip)
	{ 
		_groupe = groupe;
		_type = type; 
		_ip = ip; 
		startReceive();
	}


	~Client()
	{
		_thread->Abort();
	}
	id_groupe getGroupe() { return _groupe; }
	id_client getType() { return _type; }
	IPAddress^ getIP() { return _ip; }
	Boolean getState() { return _isConnected; }
	Socket^ getSocket() { return _clientSocket; }

	void setGroupe(id_groupe i) { _groupe = i; }
	void setType(id_client i) { _type = i; }
	void setIP(IPAddress^ i) { _ip = i; }
	void setState(Boolean i) { _isConnected = i; }
	void setSocket(Socket^ s) { _clientSocket = s; }

	void Disconnect()
	{
		try
		{
			_clientSocket->Disconnect(true);
			_isConnected = false;
			Logger::PrintLog(EnteteCode::CLIENT, _groupe.ToString(), _type.ToString() + " viens de ce déconnectée");
			
		}
		catch (Exception^ e)
		{
			Logger::PrintLog(EnteteCode::ERROR, EnteteCode::CLIENT, " Problème lors de la deconnexion de " + _ip->ToString());
			Logger::PrintLog(EnteteCode::DEBUG, EnteteCode::ERROR,e->ToString());
		}
		

	}

	Boolean Send(array<Byte>^ data)
	{
		try
		{
			if (_clientSocket->Connected)
			{
				_clientSocket->Send(data);
				return true;
			}
			else
			{
				this->Disconnect();
				return false;
			}

		}
		catch (Exception^e)
		{
			Logger::PrintLog(EnteteCode::ERROR, EnteteCode::CLIENT, _groupe.ToString(), "[ Send ] " + e->ToString());
			return false;
		}
	}

	array<Byte>^ Receive()
	{
		array<Byte>^ data = gcnew array<Byte>(1024);
		try
		{
			while (bufferRecv == nullptr)
			{
				Thread::Sleep(100);
			}
			data = bufferRecv;
			bufferRecv = nullptr;
			return data;

		}
		catch (Exception^e)
		{
				//Console::WriteLine("[ Client ][ Receive ]" + e);
		}
	}
	


};
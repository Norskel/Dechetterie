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

	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	void fctThreadReceive()
	{
		while (true)
		{
			if (_clientSocket != nullptr)
			{
				try
				{
					if (verifyConnected())
					{
						
						if (_clientSocket->Available != 0)
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
								fonctionReceive(pm, data);
							}
							_isConnected = true;
						}

					}
					else
					{
						if (_isConnected)
						{
							this->Disconnect();
							_isConnected = false;
						}
					}

				}
				catch (System::Net::Sockets::SocketException^ e)
				{
					if (_isConnected)
					{
						this->Disconnect();
						_isConnected = false;
					}
				}
				catch (Exception^e)
				{
				
					//Console::WriteLine("[ Client ][ Thread Receive ]" + e);

				}
			}
			else
			{
				Thread::Sleep(100);
			}
			
		}
	}
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	virtual void fonctionReceive(ProtocolMsg^ pm, array<Byte>^ data)
	{
		bufferRecv = data;
	}

public:
	Client(id_groupe groupe, id_client type, IPAddress^ip)
	{ 
		_groupe = groupe;
		_type = type; 
		_ip = ip; 
		_thread = gcnew Thread(gcnew ThreadStart(this, &Client::fctThreadReceive));
		_thread->Name = "[ "+_groupe.ToString()+" ] Client "+_type.ToString()+" IP :" + _ip->ToString();
		_thread->Start();
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

	/*---------------------------------------------------------------
	Nom          :  
	Description  :  
	Arguments    :  
	Valeur renvoyée : 
	-----------------------------------------------------------------*/
	void Disconnect()
	{
		if (_clientSocket != nullptr)
		{
			Monitor::Enter(_clientSocket);
			try
			{
				_clientSocket->Disconnect(true);
				_isConnected = false;
				Logger::PrintLog(EnteteCode::CLIENT, _groupe.ToString(), _type.ToString() + " viens de ce déconnectée");
				_clientSocket = nullptr;
				
			
			}
			catch (Exception^ e)
			{
				Logger::PrintLog(EnteteCode::ERROR, EnteteCode::CLIENT, " Problème lors de la deconnexion de " + _ip->ToString());
				Logger::PrintLog(EnteteCode::DEBUG, EnteteCode::ERROR,e->ToString());
			}
			finally
			{
				Monitor::Exit(_clientSocket);
			}
			//(InterfacePipe::getInterfacePipe())->updateClientState();
		}

	}
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
	Boolean verifyConnected()
	{
		Boolean read = _clientSocket->Poll(5, SelectMode::SelectRead);
		Boolean connected = (_clientSocket->Available != 0 && read) || !read;
		return connected;
	}
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
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
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoyée :
	-----------------------------------------------------------------*/
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
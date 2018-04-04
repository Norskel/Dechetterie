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

ref class Client
{
private:
	int _groupe; // 1 entree 2 sortie
	int _type; // 1 barriere 2 balance 3 rfid	
	IPAddress^ _ip;
	Boolean _isConnected = false;
	Socket^ _clientSocket = nullptr;
	Thread^ _thread;
	array<Byte>^ bufferRecv = nullptr;
	void fctThread()
	{
		Protocole^ p = Protocole::getProtocole();
		
		while (true)
		{
			if (_clientSocket != nullptr)
			{
				_clientSocket->ReceiveTimeout = 120;

			
			try
			{
				if (_clientSocket->Connected)
				{
					array<Byte>^ data = gcnew array<Byte>(1024);
					_clientSocket->Receive(data);
					ProtocolMsg^ pm = p->translateReceive(data);
					if (pm->type == p->GetTypeProtocoleByID("AllPing"))
					{
						this->Send(p->RetourPing());
						Logger::PrintLog("Ping", "Demande de ping de "+ _ip->ToString()+ "( "+id_groupe(_groupe).ToString() +" "+id_client(_type).ToString()+" )");
					}
					else
					{
						bufferRecv = data;
					}
				}
				else
				{
					Console::WriteLine("[ Serveur " + id_groupe(_groupe).ToString() + " ] " + id_client(_type).ToString() + " viens de ce déconnectée");
					_isConnected = false;
					_clientSocket->Close();
				}
			}
			catch (Exception^e)
			{

				//Console::WriteLine("[ Client ][ Thread Receive ]" + e);

			}
			}
			Thread::Sleep(1000);
		}
	}
public:
	Client(int groupe, int type, IPAddress^ip) 
	{ 
		_groupe = groupe;
		_type = type; 
		_ip = ip; 
		_thread = gcnew Thread(gcnew ThreadStart(this,&Client::fctThread));
		_thread->Name = "Client IP "+ _ip->ToString();
		_thread->Start();
	}

	~Client()
	{
		_thread->Abort();
	}
	int getGroupe() { return _groupe; }
	int getType() { return _type; }
	IPAddress^ getIP() { return _ip; }
	Boolean getState() { return _isConnected; }
	Socket^ getSocket() { return _clientSocket; }

	void setGroupe(int i) { _groupe = i; }
	void setType(int i) { _type = i; }
	void setIP(IPAddress^ i) { _ip = i; }
	void setState(Boolean i) { _isConnected = i; }
	void setSocket(Socket^ s) { _clientSocket = s; }

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
				Console::WriteLine("[ Serveur " + id_groupe(_groupe).ToString() + " ] " + id_client(_type).ToString() + " viens de ce déconnectée");
				_isConnected = false;
				_clientSocket->Close();
				return false;
			}

		}
		catch (Exception^e)
		{

				//Console::WriteLine("[ Client ][ Send ]" + e);
			
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
			//if (_clientSocket->Connected)
			//{
			//	_clientSocket->Receive(data);
			//	return data;
			//}
			//else
			//{
			//	Console::WriteLine("[ Serveur " + id_groupe(_groupe).ToString() + " ] " + id_client(_type).ToString() + " viens de ce déconnectée");
			//	_isConnected = false;
			//	_clientSocket->Close();
			//}
		}
		catch (Exception^e)
		{

				//Console::WriteLine("[ Client ][ Receive ]" + e);
			
		}
	}
	


};
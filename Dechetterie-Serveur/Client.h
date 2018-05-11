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
delegate void DisconnectionDelegate();


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
	Nom          :fctThreadReceive
	Description  :Fonction qui attend la reception d'un message du client.
	Arguments    :
	Valeur renvoy�e :
	-----------------------------------------------------------------*/
	void fctThreadReceive()
	{
		while (true)
		{
			if (_clientSocket != nullptr)  //Si le client est connect�
			{
				try
				{
					if (verifyConnected()) //  On verifie qu'il est bien encore connect�
					{
						
						if (_clientSocket->Available != 0) // Si on a recu quelque chose
						{
							array<Byte>^ data = gcnew array<Byte>(1024);
							_clientSocket->Receive(data);
							ProtocolMsg^ pm = protocole->translateReceive(data);  //On traduit ce qu'on recoi avec le protocole
							if (pm->type == protocole->GetTypeProtocoleByID("AllPing")) // Si le type de message est un ping
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
					else // si il est plus connect�e
					{
						if (_isConnected)  // Si la deconnexion n'a pas encore �tait faite
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
					Logger::PrintLog(EnteteCode::ERROR, EnteteCode::CLIENT, "[ Receive ]" + e->ToString());
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
	Nom          :fonctionReceive
	Description  :C'est une fonction virtuel qui permet d'�tre redefini par les class fille pour d'autre reception
	Arguments    : ProtocolMsg^; le message traduit,array<Byte>^ data:  les donn�e brut
	Valeur renvoy�e :
	-----------------------------------------------------------------*/
	virtual void fonctionReceive(ProtocolMsg^ pm, array<Byte>^ data)
	{
		bufferRecv = data;
	}

public:
	event DisconnectionDelegate^ disconnection;

	/*---------------------------------------------------------------
	Nom          :Client
	Description  :Constructeur du client
	Arguments    : groupe : le groupe au quelle il appartient , type : le type de client, ip : l'ip du client 
	Valeur renvoy�e :
	-----------------------------------------------------------------*/
	Client(id_groupe groupe, id_client type, IPAddress^ip)
	{ 
		_groupe = groupe;
		_type = type; 
		_ip = ip; 
		_thread = gcnew Thread(gcnew ThreadStart(this, &Client::fctThreadReceive));
		_thread->Name = "[ "+_groupe.ToString()+" ] Client "+_type.ToString()+" IP :" + _ip->ToString();
		_thread->Start();
	}

	/*---------------------------------------------------------------
	Nom          :~Client
	Description  :Destructeur du client
	Arguments    :
	Valeur renvoy�e :
	-----------------------------------------------------------------*/
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
	void setSocket(Socket^ s) { _clientSocket = s; }

	/*---------------------------------------------------------------
	Nom          :  Disconnect
	Description  :  Permet de deconnect� le client
	Arguments    :  
	Valeur renvoy�e : 
	-----------------------------------------------------------------*/
	void Disconnect()
	{
		if (_clientSocket != nullptr)
		{
			//Monitor::Enter(_clientSocket);
			try
			{
				_clientSocket->Disconnect(true);
				_isConnected = false;
				Logger::PrintLog(EnteteCode::CLIENT, _groupe.ToString(), _type.ToString() + " viens de ce d�connect�e");
				_clientSocket = nullptr;
				disconnection();
			
			}
			catch (Exception^ e)
			{
				Logger::PrintLog(EnteteCode::ERROR, EnteteCode::CLIENT, " Probl�me lors de la deconnexion de " + _ip->ToString());
				Logger::PrintLog(EnteteCode::DEBUG, EnteteCode::ERROR,e->ToString());
			}
			//finally
			//{
			//	Monitor::Exit(_clientSocket);
			//}
//			(InterfacePipe::getInterfacePipe())->updateClientState();
		}

	}
	/*---------------------------------------------------------------
	Nom          :
	Description  :
	Arguments    :
	Valeur renvoy�e :
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
	Valeur renvoy�e :
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
	Valeur renvoy�e :
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
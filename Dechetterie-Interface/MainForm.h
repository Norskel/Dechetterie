#pragma once

#define FILE_CONFIG "ConfigServeur.xml"
#define FILE_NAME_USER "user.xml"

#define SRV_PROCESS_NAME "Dechetterie-Serveur"
#define PIPE_NAME_STATE_SERV "StateServeur"
#define PIPE_NAME_USER_INFOS_SERV "UserServeur"

#include "Utilisateur.h"
#include "ConfigForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace System::Threading;
using namespace System::IO::Pipes;
using namespace System::Xml::Serialization;

delegate void DelegateUser(List<Utilisateur^>^ list, int h, int w);

/// <summary>
/// Description r�sum�e de MainForm
/// </summary>
public ref class MainForm : public System::Windows::Forms::Form
{
public:
	MainForm(void)
	{

		Screen^ s = Screen::PrimaryScreen;
		InitializeComponent();
		this->Width = s->WorkingArea.Width;
		this->Height = s->WorkingArea.Height;
	

		_thWaitServerMsg = gcnew Thread(gcnew ThreadStart(this, &MainForm::fctWaitClientListFromServer));
		_thWaitServerMsg->Name = "ThreadWaitMsgUserFromSrv";
		//_thWaitServerMsg->Start();


		//
		//TODO: ajoutez ici le code du constructeur
		//

		
		Bitmap^ i = gcnew Bitmap("test.jpeg");
		ImageConverter^ converter = gcnew ImageConverter();

		array<Byte>^ rt = (array<Byte>^)converter->ConvertTo(i, array<Byte>::typeid);

		list->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
		//_listUser->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
		//_listUser->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
		//_listUser->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
		//_listUser->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
		//_listUser->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));

		AfficherControlUser(list, 200, 300);
		//AfficherControlUser(_listUser, 150, 50, 300, 400);
		this->timerUpdate->Enabled = true;

		//controlUtilisateur1->prenom = u1->getPrenom();
		//controlUtilisateur1->nom = u1->getNom();
		//controlUtilisateur1->typeDechet = u1->getTypeDechet();
		//controlUtilisateur1->temp = u1->getDuree();


		//Image^ image = (Image^)converter->ConvertFrom(u1->getPhoto());
		//controlUtilisateur1->photo = gcnew Bitmap(image);

		//			Console::WriteLine("H = " + controlUtilisateur1->Size.Height + " W = " + controlUtilisateur1->Size.Width);





		//pictureBox1->Image = img;

	}

protected:
	List<Utilisateur^>^ list = gcnew List<Utilisateur^>();
	/// <summary>
	/// Nettoyage des ressources utilis�es.
	/// </summary>
	~MainForm()
	{
		if (components)
		{
			delete components;
		}
	}

private: System::ComponentModel::IContainer^  components;
		 List<ControlInterface::ControlUtilisateur^>^_listControlUser = gcnew List<ControlInterface::ControlUtilisateur^>();
		 Thread^ _thWaitServerMsg;
		 NamedPipeClientStream^ _pipeClient;
		 DelegateUser^ _DAfficherControlUser = gcnew DelegateUser(this, &MainForm::AfficherControlUser);
		 ConfigForm^ configForm = gcnew ConfigForm();
		 int nbUser = 0;


private:
	/// <summary>
	/// Variable n�cessaire au concepteur.
	/// </summary>



private: ControlInterface::ControlEtat^  controlEtat1;
private: System::Windows::Forms::Timer^  timerUpdate;
private: System::Windows::Forms::MenuStrip^  menuStrip1;
private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;
private: System::Windows::Forms::FlowLayoutPanel^  PhotoClientLayout;
private: System::Windows::Forms::Button^  button1;



private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem1;





#pragma region Windows Form Designer generated code
		 /// <summary>
		 /// M�thode requise pour la prise en charge du concepteur - ne modifiez pas
		 /// le contenu de cette m�thode avec l'�diteur de code.
		 /// </summary>
		 void InitializeComponent(void)
		 {
			 this->components = (gcnew System::ComponentModel::Container());
			 this->controlEtat1 = (gcnew ControlInterface::ControlEtat());
			 this->timerUpdate = (gcnew System::Windows::Forms::Timer(this->components));
			 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			 this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			 this->optionToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			 this->PhotoClientLayout = (gcnew System::Windows::Forms::FlowLayoutPanel());
			 this->button1 = (gcnew System::Windows::Forms::Button());
			 this->menuStrip1->SuspendLayout();
			 this->SuspendLayout();
			 // 
			 // controlEtat1
			 // 
			 this->controlEtat1->BackColor = System::Drawing::Color::Red;
			 this->controlEtat1->colorFalse = System::Drawing::Color::Red;
			 this->controlEtat1->colorTexte = System::Drawing::Color::White;
			 this->controlEtat1->colorTrue = System::Drawing::Color::Lime;
			 this->controlEtat1->Location = System::Drawing::Point(25, 66);
			 this->controlEtat1->Name = L"controlEtat1";
			 this->controlEtat1->Size = System::Drawing::Size(75, 51);
			 this->controlEtat1->state = false;
			 this->controlEtat1->TabIndex = 1;
			 this->controlEtat1->texteSize = 15;
			 this->controlEtat1->textFalse = L"OFF";
			 this->controlEtat1->textTrue = L"ON";
			 // 
			 // timerUpdate
			 // 
			 this->timerUpdate->Interval = 10000;
			 this->timerUpdate->Tick += gcnew System::EventHandler(this, &MainForm::timerUpdate_Tick);
			 // 
			 // menuStrip1
			 // 
			 this->menuStrip1->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->optionToolStripMenuItem });
			 this->menuStrip1->Location = System::Drawing::Point(0, 0);
			 this->menuStrip1->Name = L"menuStrip1";
			 this->menuStrip1->Size = System::Drawing::Size(1362, 24);
			 this->menuStrip1->TabIndex = 2;
			 this->menuStrip1->Text = L"menuStrip1";
			 // 
			 // optionToolStripMenuItem
			 // 
			 this->optionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->optionToolStripMenuItem1 });
			 this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
			 this->optionToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			 this->optionToolStripMenuItem->Text = L"Option";
			 // 
			 // optionToolStripMenuItem1
			 // 
			 this->optionToolStripMenuItem1->Name = L"optionToolStripMenuItem1";
			 this->optionToolStripMenuItem1->Size = System::Drawing::Size(111, 22);
			 this->optionToolStripMenuItem1->Text = L"Option";
			 this->optionToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::optionToolStripMenuItem1_Click);
			 // 
			 // PhotoClientLayout
			 // 
			 this->PhotoClientLayout->Location = System::Drawing::Point(168, 27);
			 this->PhotoClientLayout->Name = L"PhotoClientLayout";
			 this->PhotoClientLayout->Size = System::Drawing::Size(1194, 716);
			 this->PhotoClientLayout->TabIndex = 3;
			 // 
			 // button1
			 // 
			 this->button1->Location = System::Drawing::Point(25, 28);
			 this->button1->Name = L"button1";
			 this->button1->Size = System::Drawing::Size(75, 23);
			 this->button1->TabIndex = 4;
			 this->button1->Text = L"button1";
			 this->button1->UseVisualStyleBackColor = true;
			 this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			 // 
			 // MainForm
			 // 
			 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			 this->ClientSize = System::Drawing::Size(1362, 741);
			 this->Controls->Add(this->button1);
			 this->Controls->Add(this->controlEtat1);
			 this->Controls->Add(this->PhotoClientLayout);
			 this->Controls->Add(this->menuStrip1);
			 this->MainMenuStrip = this->menuStrip1;
			 this->Name = L"MainForm";
			 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			 this->Text = L" ";
			 this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			 this->menuStrip1->ResumeLayout(false);
			 this->menuStrip1->PerformLayout();
			 this->ResumeLayout(false);
			 this->PerformLayout();

		 }
#pragma endregion



private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: void AfficherControlUser(List<Utilisateur^>^ list, int h, int w)
{
	if (list->Count != nbUser)
	{

		nbUser = list->Count;
		for (int i = 0; i < _listControlUser->Count; i++)
		{
			delete _listControlUser[i];
		}

		ImageConverter^ converter = gcnew ImageConverter();

		for (int i = 0; i < list->Count; i++)
		{

			_listControlUser->Add(gcnew ControlInterface::ControlUtilisateur());

			Image^ image = (Image^)converter->ConvertFrom(list[i]->getPhoto());

			_listControlUser[_listControlUser->Count - 1]->BackColor = System::Drawing::SystemColors::ActiveBorder;
			//_listControlUser[_listControlUser->Count - 1]->Location = System::Drawing::Point(x, y);
			_listControlUser[_listControlUser->Count - 1]->Name = L"controlUtilisateur" + i;
			_listControlUser[_listControlUser->Count - 1]->nom = list[i]->getNom();
			_listControlUser[_listControlUser->Count - 1]->photo = gcnew Bitmap(image);
			_listControlUser[_listControlUser->Count - 1]->prenom = list[i]->getPrenom();
			_listControlUser[_listControlUser->Count - 1]->Size = System::Drawing::Size(w, h);
			_listControlUser[_listControlUser->Count - 1]->temp = list[i]->getArrivee();
			_listControlUser[_listControlUser->Count - 1]->typeDechet = 0;
			this->PhotoClientLayout->Controls->Add(this->_listControlUser[_listControlUser->Count - 1]);
			//this->Controls->Add(_listControlUser[_listControlUser->Count - 1]);

		}
		this->Refresh();
	}
}
private: System::Void timerUpdate_Tick(System::Object^  sender, System::EventArgs^  e) {


	array<Process^>^ listProcess = Process::GetProcessesByName(SRV_PROCESS_NAME);

	for each (Process^ var in listProcess)
	{
		if (var->ToString() == "System.Diagnostics.Process (" + SRV_PROCESS_NAME + ")")
		{

			controlEtat1->state = true;
			break;
		}
		else
		{
			controlEtat1->state = false;
		}

	}
	if (listProcess->Length == 0)
	{
		controlEtat1->state = false;
	}

	//Thread::Sleep(10000);
	//Console::ReadKey();

	//AfficherControlUser(_listUser, 150, 50, 300, 400);


}
private: void fctWaitClientListFromServer()
{

	while (true)
	{
		if (System::IO::File::Exists(FILE_NAME_USER))
		{
			FileStream^ fs;
			bool fileOpened = false;
			do
			{
				try
				{
					fileOpened = false;
					fs = File::Open(FILE_NAME_USER, System::IO::FileMode::Open);

				}
				catch (...)
				{
					Console::WriteLine("[ Configuration ] Erreur � l'ouverture de " + FILE_NAME_USER);
					fileOpened = true;
				}
			} while (fileOpened);

			XmlSerializer^ serializer = gcnew XmlSerializer(List<Utilisateur^>::typeid);
			List<Utilisateur^>^ t = (List<Utilisateur^>^)serializer->Deserialize(fs);
			//array<Byte>^ buffer = gcnew array<Byte>(6);
			//_pipeClient->Read(buffer, 0, 6);

			Console::WriteLine("[ Client User Srv ] Reception ");
			this->Invoke(_DAfficherControlUser, t, 150, 50, 300, 400);
			fs->Close();

		}
		else
		{

		}
		Thread::Sleep(2000);
	}
	//bool serverStart = false;
	//do
	//{
	//	array<Process^>^ listProcess = Process::GetProcessesByName(SRV_PROCESS_NAME);
	//	for each (Process^ var in listProcess)
	//	{
	//		Console::WriteLine(var->ToString());
	//		if (var->ToString() == "System.Diagnostics.Process (" + SRV_PROCESS_NAME + ")")
	//		{
	//			_pipeClient = gcnew NamedPipeClientStream(".", PIPE_NAME_USER_INFOS_SERV, PipeDirection::In);
	//			try
	//				//Console::WriteLine(_pipeClient->IsConnected);
	//			{
	//				_pipeClient->Connect();
	//				serverStart = true;
	//				Console::WriteLine("[ Client User Srv ] Connection ");


	//			}
	//			catch (...)
	//			{

	//			}
	//			break;
	//		}

	//	}
	//} while (!serverStart);

	//while (true)
	//{
	//	//Console::WriteLine(_pipeClient->IsConnected);
	//	if (_pipeClient->IsConnected)
	//	{

	//		XmlSerializer^ serializer = gcnew XmlSerializer(List<Utilisateur^>::typeid);
	//		List<Utilisateur^>^ t = (List<Utilisateur^>^)serializer->Deserialize(_pipeClient);
	//		//array<Byte>^ buffer = gcnew array<Byte>(6);
	//		//_pipeClient->Read(buffer, 0, 6);
	//		Console::WriteLine("[ Client User Srv ] Reception ");
	//		this->Invoke(_DAfficherControlUser, t, 150, 50, 300, 400);

	//	}
	//	else
	//	{
	//		_pipeClient->Close();
	//		Console::WriteLine("[ Client User Srv ] Connexion interrompu");

	//		try
	//		{
	//			_pipeClient->Connect();
	//			Console::WriteLine("[ Client User Srv ] Reconnexion");
	//		}
	//		catch (...)
	//		{
	//			Thread::Sleep(500);
	//		}

	//	}
	//}
}

private: System::Void optionToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {


	configForm->Show();
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	

	Bitmap^ i = gcnew Bitmap("test.jpeg");
	ImageConverter^ converter = gcnew ImageConverter();

	array<Byte>^ rt = (array<Byte>^)converter->ConvertTo(i, array<Byte>::typeid);

	list->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
	//_listUser->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
	//_listUser->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
	//_listUser->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
	//_listUser->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
	//_listUser->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));

	AfficherControlUser(list, 200, 300);
}
};

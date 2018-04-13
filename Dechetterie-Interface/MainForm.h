#pragma once

#define FILE_CONFIG "ConfigServeur.xml"
#define FILE_NAME_USER "user.xml"

#define SRV_PROCESS_NAME "Dechetterie-Serveur"
#define PIPE_NAME_STATE_SERV "StateServeur"
#define PIPE_NAME_USER_INFOS_SERV "UserServeur"

#include "Utilisateur.h"
#include "ConfigForm.h"
#include "PipeServeur.h"

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
delegate void DelegateUpdate();

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
		pipeServeur->UpdateClientList += gcnew System::EventHandler<int>(this, &MainForm::OnUpdateClientList);
		UpdateAffClient();
		//_thWaitServerMsg = gcnew Thread(gcnew ThreadStart(this, &MainForm::fctWaitClientListFromServer));
		//_thWaitServerMsg->Name = "ThreadWaitMsgUserFromSrv";
		//_thWaitServerMsg->Start();
		
		//Bitmap^ i = gcnew Bitmap("test2.jpeg");
		//ImageConverter^ converter = gcnew ImageConverter();

		//array<Byte>^ rt = (array<Byte>^)converter->ConvertTo(i, array<Byte>::typeid);
		
	

		//list->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
		//AfficherControlUser(list, 200, 300);
		this->timerUpdate->Enabled = true;
		this->timerUpdateState->Enabled = true;
		
	}
private: System::Windows::Forms::Button^  btServeurStart;
private: System::Windows::Forms::Button^  btServeurStop;
private: System::Windows::Forms::Button^  button4;
private: System::Windows::Forms::GroupBox^  gb1;
private: ControlInterface::ControlEtat^  ceEnBr;
private: ControlInterface::ControlEtat^  ceEnRf;
private: ControlInterface::ControlEtat^  ceEnBa;
private: System::Windows::Forms::GroupBox^  groupBox1;
private: ControlInterface::ControlEtat^  ceSoBr;
private: ControlInterface::ControlEtat^  ceSoBa;
private: ControlInterface::ControlEtat^  ceSoRf;
private: System::Windows::Forms::Timer^  timerUpdateState;
private: System::Windows::Forms::Button^  btEntreeOuvrirBarriere;

private: System::Windows::Forms::Button^  btEntreeFermerBarriere;

private: System::Windows::Forms::Button^  btSortieFermerBarriere;
private: System::Windows::Forms::Button^  btSortieOuvrirBarriere;




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
		 DelegateUser^ _DAfficherControlUser = gcnew DelegateUser(this, &MainForm::AfficherControlUser);
		 DelegateUpdate^ _DUpdateAffClient = gcnew DelegateUpdate(this, &MainForm::UpdateAffClient);
		 ConfigForm^ configForm = gcnew ConfigForm();
		 int nbUser = 0;
		 PipeServeur^ pipeServeur = PipeServeur::GetPipeServeur();
		


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
			 this->btServeurStart = (gcnew System::Windows::Forms::Button());
			 this->btServeurStop = (gcnew System::Windows::Forms::Button());
			 this->button4 = (gcnew System::Windows::Forms::Button());
			 this->gb1 = (gcnew System::Windows::Forms::GroupBox());
			 this->btEntreeFermerBarriere = (gcnew System::Windows::Forms::Button());
			 this->btEntreeOuvrirBarriere = (gcnew System::Windows::Forms::Button());
			 this->ceEnBr = (gcnew ControlInterface::ControlEtat());
			 this->ceEnBa = (gcnew ControlInterface::ControlEtat());
			 this->ceEnRf = (gcnew ControlInterface::ControlEtat());
			 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			 this->btSortieFermerBarriere = (gcnew System::Windows::Forms::Button());
			 this->btSortieOuvrirBarriere = (gcnew System::Windows::Forms::Button());
			 this->ceSoBr = (gcnew ControlInterface::ControlEtat());
			 this->ceSoBa = (gcnew ControlInterface::ControlEtat());
			 this->ceSoRf = (gcnew ControlInterface::ControlEtat());
			 this->timerUpdateState = (gcnew System::Windows::Forms::Timer(this->components));
			 this->menuStrip1->SuspendLayout();
			 this->gb1->SuspendLayout();
			 this->groupBox1->SuspendLayout();
			 this->SuspendLayout();
			 // 
			 // controlEtat1
			 // 
			 this->controlEtat1->BackColor = System::Drawing::Color::Red;
			 this->controlEtat1->colorFalse = System::Drawing::Color::Red;
			 this->controlEtat1->colorTexte = System::Drawing::Color::White;
			 this->controlEtat1->colorTrue = System::Drawing::Color::Lime;
			 this->controlEtat1->Location = System::Drawing::Point(9, 30);
			 this->controlEtat1->Name = L"controlEtat1";
			 this->controlEtat1->Size = System::Drawing::Size(119, 28);
			 this->controlEtat1->state = false;
			 this->controlEtat1->TabIndex = 1;
			 this->controlEtat1->texteSize = 12;
			 this->controlEtat1->textFalse = L"Serveur OFF";
			 this->controlEtat1->textTrue = L"Serveur ON";
			 // 
			 // timerUpdate
			 // 
			 this->timerUpdate->Interval = 1000;
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
			 this->PhotoClientLayout->BackColor = System::Drawing::SystemColors::ButtonShadow;
			 this->PhotoClientLayout->Location = System::Drawing::Point(137, 22);
			 this->PhotoClientLayout->Name = L"PhotoClientLayout";
			 this->PhotoClientLayout->Size = System::Drawing::Size(1225, 723);
			 this->PhotoClientLayout->TabIndex = 3;
			 // 
			 // button1
			 // 
			 this->button1->Location = System::Drawing::Point(189, 0);
			 this->button1->Name = L"button1";
			 this->button1->Size = System::Drawing::Size(108, 23);
			 this->button1->TabIndex = 4;
			 this->button1->Text = L"button1";
			 this->button1->UseVisualStyleBackColor = true;
			 this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			 // 
			 // btServeurStart
			 // 
			 this->btServeurStart->Location = System::Drawing::Point(9, 65);
			 this->btServeurStart->Name = L"btServeurStart";
			 this->btServeurStart->Size = System::Drawing::Size(119, 23);
			 this->btServeurStart->TabIndex = 5;
			 this->btServeurStart->Text = L"Start Serveur";
			 this->btServeurStart->UseVisualStyleBackColor = true;
			 // 
			 // btServeurStop
			 // 
			 this->btServeurStop->Location = System::Drawing::Point(9, 94);
			 this->btServeurStop->Name = L"btServeurStop";
			 this->btServeurStop->Size = System::Drawing::Size(119, 23);
			 this->btServeurStop->TabIndex = 6;
			 this->btServeurStop->Text = L"Stop Serveur";
			 this->btServeurStop->UseVisualStyleBackColor = true;
			 // 
			 // button4
			 // 
			 this->button4->Location = System::Drawing::Point(9, 123);
			 this->button4->Name = L"button4";
			 this->button4->Size = System::Drawing::Size(119, 23);
			 this->button4->TabIndex = 7;
			 this->button4->Text = L"button4";
			 this->button4->UseVisualStyleBackColor = true;
			 // 
			 // gb1
			 // 
			 this->gb1->BackColor = System::Drawing::SystemColors::ControlLight;
			 this->gb1->Controls->Add(this->btEntreeFermerBarriere);
			 this->gb1->Controls->Add(this->btEntreeOuvrirBarriere);
			 this->gb1->Controls->Add(this->ceEnBr);
			 this->gb1->Controls->Add(this->ceEnBa);
			 this->gb1->Controls->Add(this->ceEnRf);
			 this->gb1->Location = System::Drawing::Point(3, 156);
			 this->gb1->Name = L"gb1";
			 this->gb1->Size = System::Drawing::Size(131, 175);
			 this->gb1->TabIndex = 8;
			 this->gb1->TabStop = false;
			 this->gb1->Text = L"Entrée";
			 // 
			 // btEntreeFermerBarriere
			 // 
			 this->btEntreeFermerBarriere->Location = System::Drawing::Point(5, 79);
			 this->btEntreeFermerBarriere->Name = L"btEntreeFermerBarriere";
			 this->btEntreeFermerBarriere->Size = System::Drawing::Size(119, 23);
			 this->btEntreeFermerBarriere->TabIndex = 14;
			 this->btEntreeFermerBarriere->Text = L"Fermer";
			 this->btEntreeFermerBarriere->UseVisualStyleBackColor = true;
			 this->btEntreeFermerBarriere->Click += gcnew System::EventHandler(this, &MainForm::btEntreeFermerBarriere_Click);
			 // 
			 // btEntreeOuvrirBarriere
			 // 
			 this->btEntreeOuvrirBarriere->Location = System::Drawing::Point(5, 50);
			 this->btEntreeOuvrirBarriere->Name = L"btEntreeOuvrirBarriere";
			 this->btEntreeOuvrirBarriere->Size = System::Drawing::Size(119, 23);
			 this->btEntreeOuvrirBarriere->TabIndex = 13;
			 this->btEntreeOuvrirBarriere->Text = L"Ouvrir";
			 this->btEntreeOuvrirBarriere->UseVisualStyleBackColor = true;
			 this->btEntreeOuvrirBarriere->Click += gcnew System::EventHandler(this, &MainForm::btEntreeOuvrirBarriere_Click);
			 // 
			 // ceEnBr
			 // 
			 this->ceEnBr->BackColor = System::Drawing::Color::Red;
			 this->ceEnBr->colorFalse = System::Drawing::Color::Red;
			 this->ceEnBr->colorTexte = System::Drawing::Color::White;
			 this->ceEnBr->colorTrue = System::Drawing::Color::Lime;
			 this->ceEnBr->Location = System::Drawing::Point(5, 20);
			 this->ceEnBr->Margin = System::Windows::Forms::Padding(4);
			 this->ceEnBr->Name = L"ceEnBr";
			 this->ceEnBr->Size = System::Drawing::Size(119, 23);
			 this->ceEnBr->state = false;
			 this->ceEnBr->TabIndex = 9;
			 this->ceEnBr->texteSize = 12;
			 this->ceEnBr->textFalse = L"Barrière";
			 this->ceEnBr->textTrue = L"Barrière";
			 // 
			 // ceEnBa
			 // 
			 this->ceEnBa->BackColor = System::Drawing::Color::Red;
			 this->ceEnBa->colorFalse = System::Drawing::Color::Red;
			 this->ceEnBa->colorTexte = System::Drawing::Color::White;
			 this->ceEnBa->colorTrue = System::Drawing::Color::Lime;
			 this->ceEnBa->Location = System::Drawing::Point(5, 115);
			 this->ceEnBa->Margin = System::Windows::Forms::Padding(4);
			 this->ceEnBa->Name = L"ceEnBa";
			 this->ceEnBa->Size = System::Drawing::Size(119, 23);
			 this->ceEnBa->state = false;
			 this->ceEnBa->TabIndex = 11;
			 this->ceEnBa->texteSize = 12;
			 this->ceEnBa->textFalse = L"Balance";
			 this->ceEnBa->textTrue = L"Balance";
			 // 
			 // ceEnRf
			 // 
			 this->ceEnRf->BackColor = System::Drawing::Color::Red;
			 this->ceEnRf->colorFalse = System::Drawing::Color::Red;
			 this->ceEnRf->colorTexte = System::Drawing::Color::White;
			 this->ceEnRf->colorTrue = System::Drawing::Color::Lime;
			 this->ceEnRf->Location = System::Drawing::Point(5, 146);
			 this->ceEnRf->Margin = System::Windows::Forms::Padding(4);
			 this->ceEnRf->Name = L"ceEnRf";
			 this->ceEnRf->Size = System::Drawing::Size(119, 23);
			 this->ceEnRf->state = false;
			 this->ceEnRf->TabIndex = 10;
			 this->ceEnRf->texteSize = 12;
			 this->ceEnRf->textFalse = L"RFID";
			 this->ceEnRf->textTrue = L"RFID";
			 // 
			 // groupBox1
			 // 
			 this->groupBox1->BackColor = System::Drawing::SystemColors::ControlLight;
			 this->groupBox1->Controls->Add(this->btSortieFermerBarriere);
			 this->groupBox1->Controls->Add(this->btSortieOuvrirBarriere);
			 this->groupBox1->Controls->Add(this->ceSoBr);
			 this->groupBox1->Controls->Add(this->ceSoBa);
			 this->groupBox1->Controls->Add(this->ceSoRf);
			 this->groupBox1->Location = System::Drawing::Point(3, 337);
			 this->groupBox1->Name = L"groupBox1";
			 this->groupBox1->Size = System::Drawing::Size(131, 203);
			 this->groupBox1->TabIndex = 12;
			 this->groupBox1->TabStop = false;
			 this->groupBox1->Text = L"Sortir";
			 // 
			 // btSortieFermerBarriere
			 // 
			 this->btSortieFermerBarriere->Location = System::Drawing::Point(6, 79);
			 this->btSortieFermerBarriere->Name = L"btSortieFermerBarriere";
			 this->btSortieFermerBarriere->Size = System::Drawing::Size(119, 23);
			 this->btSortieFermerBarriere->TabIndex = 16;
			 this->btSortieFermerBarriere->Text = L"Fermer";
			 this->btSortieFermerBarriere->UseVisualStyleBackColor = true;
			 this->btSortieFermerBarriere->Click += gcnew System::EventHandler(this, &MainForm::btSortieFermerBarriere_Click);
			 // 
			 // btSortieOuvrirBarriere
			 // 
			 this->btSortieOuvrirBarriere->Location = System::Drawing::Point(5, 50);
			 this->btSortieOuvrirBarriere->Name = L"btSortieOuvrirBarriere";
			 this->btSortieOuvrirBarriere->Size = System::Drawing::Size(119, 23);
			 this->btSortieOuvrirBarriere->TabIndex = 15;
			 this->btSortieOuvrirBarriere->Text = L"Ouvrir";
			 this->btSortieOuvrirBarriere->UseVisualStyleBackColor = true;
			 this->btSortieOuvrirBarriere->Click += gcnew System::EventHandler(this, &MainForm::btSortieOuvrirBarriere_Click);
			 // 
			 // ceSoBr
			 // 
			 this->ceSoBr->BackColor = System::Drawing::Color::Red;
			 this->ceSoBr->colorFalse = System::Drawing::Color::Red;
			 this->ceSoBr->colorTexte = System::Drawing::Color::White;
			 this->ceSoBr->colorTrue = System::Drawing::Color::Lime;
			 this->ceSoBr->Location = System::Drawing::Point(5, 20);
			 this->ceSoBr->Margin = System::Windows::Forms::Padding(4);
			 this->ceSoBr->Name = L"ceSoBr";
			 this->ceSoBr->Size = System::Drawing::Size(119, 23);
			 this->ceSoBr->state = false;
			 this->ceSoBr->TabIndex = 9;
			 this->ceSoBr->texteSize = 12;
			 this->ceSoBr->textFalse = L"Barrière";
			 this->ceSoBr->textTrue = L"Barrière";
			 // 
			 // ceSoBa
			 // 
			 this->ceSoBa->BackColor = System::Drawing::Color::Red;
			 this->ceSoBa->colorFalse = System::Drawing::Color::Red;
			 this->ceSoBa->colorTexte = System::Drawing::Color::White;
			 this->ceSoBa->colorTrue = System::Drawing::Color::Lime;
			 this->ceSoBa->Location = System::Drawing::Point(5, 109);
			 this->ceSoBa->Margin = System::Windows::Forms::Padding(4);
			 this->ceSoBa->Name = L"ceSoBa";
			 this->ceSoBa->Size = System::Drawing::Size(119, 23);
			 this->ceSoBa->state = false;
			 this->ceSoBa->TabIndex = 11;
			 this->ceSoBa->texteSize = 12;
			 this->ceSoBa->textFalse = L"Balance";
			 this->ceSoBa->textTrue = L"Balance";
			 // 
			 // ceSoRf
			 // 
			 this->ceSoRf->BackColor = System::Drawing::Color::Red;
			 this->ceSoRf->colorFalse = System::Drawing::Color::Red;
			 this->ceSoRf->colorTexte = System::Drawing::Color::White;
			 this->ceSoRf->colorTrue = System::Drawing::Color::Lime;
			 this->ceSoRf->Location = System::Drawing::Point(5, 140);
			 this->ceSoRf->Margin = System::Windows::Forms::Padding(4);
			 this->ceSoRf->Name = L"ceSoRf";
			 this->ceSoRf->Size = System::Drawing::Size(119, 23);
			 this->ceSoRf->state = false;
			 this->ceSoRf->TabIndex = 10;
			 this->ceSoRf->texteSize = 12;
			 this->ceSoRf->textFalse = L"RFID";
			 this->ceSoRf->textTrue = L"RFID";
			 // 
			 // timerUpdateState
			 // 
			 this->timerUpdateState->Interval = 5000;
			 this->timerUpdateState->Tick += gcnew System::EventHandler(this, &MainForm::timerUpdateState_Tick);
			 // 
			 // MainForm
			 // 
			 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			 this->ClientSize = System::Drawing::Size(1362, 741);
			 this->Controls->Add(this->groupBox1);
			 this->Controls->Add(this->gb1);
			 this->Controls->Add(this->button4);
			 this->Controls->Add(this->btServeurStop);
			 this->Controls->Add(this->btServeurStart);
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
			 this->gb1->ResumeLayout(false);
			 this->groupBox1->ResumeLayout(false);
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


	this->PhotoClientLayout->Size = System::Drawing::Size(this->Width - this->PhotoClientLayout->Location.X, (this->	Height - this->PhotoClientLayout->Location.Y));

	UpdateServeurState();
	



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
			this->Invoke(_DAfficherControlUser, t, 300, 400);
			fs->Close();

		}
		else
		{

		}
		Thread::Sleep(2000);
	}

}

private: System::Void optionToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {


	configForm->Show();
}

private: void UpdateClientState(array<Byte>^ t)
{
	if (t != nullptr)
	{
		Console::WriteLine("reload state");
		Encoding^ encoder = Encoding::ASCII;
		Console::WriteLine(encoder->GetString(t));
		//======================================== Entree ========================
		if (t[0] == '1') { ceEnBr->state = true; }// Barrière
		else { ceEnBr->state = false; }

		if (t[1] == '1') { ceEnBa->state = true; }// Balance
		else { ceEnBa->state = false; }

		if (t[2] == '1') { ceEnRf->state = true; Console::WriteLine("reload statddddde"); }// RFID
		else { ceEnRf->state = false; }
		//======================================== Sortie ========================
		if (t[3] == '1') { ceSoBr->state = true; }// Barrière
		else { ceSoBr->state = false; }

		if (t[4] == '1') { ceSoBa->state = true; }// Balance
		else { ceSoBa->state = false; }

		if (t[5] == '1') { ceSoRf->state = true; }// RFID
		else { ceSoRf->state = false; }
		
	}
}
private: void UpdateServeurState()
{
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
}

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	

	Bitmap^ i = gcnew Bitmap("test2.jpeg");
	ImageConverter^ converter = gcnew ImageConverter();

	array<Byte>^ rt = (array<Byte>^)converter->ConvertTo(i, array<Byte>::typeid);

	list->Add(gcnew Utilisateur("KLEIN-NORTH", "Martin", 2, "5sfd5d", 54, rt));
	AfficherControlUser(list, 350, 550);
}

private: System::Void timerUpdateState_Tick(System::Object^  sender, System::EventArgs^  e) {
	UpdateClientState(pipeServeur->getState());


}
private: System::Void btEntreeOuvrirBarriere_Click(System::Object^  sender, System::EventArgs^  e) {
	pipeServeur->ouvrirBarriere(id_groupe::ENTREE);
}
private: System::Void btSortieFermerBarriere_Click(System::Object^  sender, System::EventArgs^  e) {
	pipeServeur->fermerBarriere(id_groupe::SORTIE);
}
private: System::Void btSortieOuvrirBarriere_Click(System::Object^  sender, System::EventArgs^  e) {
	pipeServeur->ouvrirBarriere(id_groupe::SORTIE);
}
private: System::Void btEntreeFermerBarriere_Click(System::Object^  sender, System::EventArgs^  e) {
	pipeServeur->fermerBarriere(id_groupe::ENTREE);
}

void UpdateAffClient()
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
				 _DAfficherControlUser(t, 300, 400);
				 fs->Close();

			 }
			 else
			 {

			 }
		 }
void OnUpdateClientList(System::Object ^sender, int e)
{
	this->Invoke(_DUpdateAffClient);
}

		 
};



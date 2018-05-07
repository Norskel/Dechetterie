#pragma once
#include "StructDataConfigServeur.h"
#include "Logger.h"
#include "Config.h"
#include "PipeServeur.h"

#define FILE_CONFIG "ConfigServeur.xml"
#define SRV_PROCESS_NAME "Dechetterie-Serveur"
#define PIPE_NAME_STATE_SERV "StateServeur"
#define PIPE_NAME_USER_INFOS_SERV "UserServeur"




using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::NetworkInformation;
using namespace System::Net::Sockets;

using namespace System::Xml::Serialization;

using namespace System::IO;
using namespace System::Text;
using namespace System::Threading;
using namespace System::IO::Pipes;
using namespace System::Diagnostics;


/// <summary>
/// Description r�sum�e de ConfigForm
/// </summary>
public ref class ConfigForm : public System::Windows::Forms::Form
{
public:
	ConfigForm(void)
	{
		InitializeComponent();
		config = Config::GetConfig();
		config->setFileName(FILE_CONFIG);

		_pipeServeur = PipeServeur::GetPipeServeur();


		//Set Image Client Entree
		this->pbBaE->Image = Image::FromFile("image/balance.png");
		this->pbRfE->Image = Image::FromFile("image/rfid_ecran.png");
		this->pbBrE->Image = Image::FromFile("image/barriere.png");

		//Set Image Client Sortie
		this->pbBaS->Image = Image::FromFile("image/balance.png");
		this->pbRfS->Image = Image::FromFile("image/rfid.png");
		this->pbBrS->Image = Image::FromFile("image/barriere.png");

		checkInterface(); //Cherche les interfaces réseaux disponible

	}

protected:
	/// <summary>
	/// Nettoyage des ressources utilis�es.
	/// </summary>
	~ConfigForm()
	{
		if (components)
		{
			delete components;
		}
	}

private: System::Windows::Forms::GroupBox^  gbBalcanceS;
private: ControlInterface::ControlEtat^  CeBaS;
private: System::Windows::Forms::PictureBox^  pbBaS;
private: System::Windows::Forms::GroupBox^  gbRFIDs;
private: ControlInterface::ControlEtat^  CeRfS;
private: System::Windows::Forms::PictureBox^  pbRfS;
private: System::Windows::Forms::GroupBox^  gbBarriereS;
private: ControlInterface::ControlEtat^  CeBrS;
private: System::Windows::Forms::PictureBox^  pbBrS;
private: System::Windows::Forms::ComboBox^  cbInterE;
private: System::Windows::Forms::NumericUpDown^  nudPortE;
private: System::Windows::Forms::GroupBox^  gbBaE;
private: ControlInterface::ControlEtat^  CeBaE;
private: System::Windows::Forms::PictureBox^  pbBaE;
private: System::Windows::Forms::GroupBox^  gbRfE;
private: ControlInterface::ControlEtat^  CeRfE;
private: System::Windows::Forms::PictureBox^  pbRfE;
private: System::Windows::Forms::GroupBox^  gbBrE;
private: ControlInterface::ControlEtat^  CeBrE;
private: System::Windows::Forms::PictureBox^  pbBrE;
private: System::Windows::Forms::Label^  label3;
private: ControlInterface::ControlIPBox^  controlIPBoxBaS;
private: System::Windows::Forms::Label^  label4;
private: ControlInterface::ControlIPBox^  controlIPBoxRfS;
private: System::Windows::Forms::Label^  label5;
private: ControlInterface::ControlIPBox^  controlIPBoxBrS;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  l1;
private: ControlInterface::ControlIPBox^  controlIPBoxBaE;
private: System::Windows::Forms::Label^  label1;
private: ControlInterface::ControlIPBox^  controlIPBoxRfE;
private: System::Windows::Forms::Label^  label2;
private: ControlInterface::ControlIPBox^  controlIPBoxBrE;
private: System::Windows::Forms::Label^  label7;


private: System::Windows::Forms::Button^  btSav;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::TextBox^  tbBddName;
private: System::Windows::Forms::Label^  label11;
private: ControlInterface::ControlIPBox^  tbBddIP;
private: System::Windows::Forms::NumericUpDown^  nudPortBdd;
private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::TextBox^  tbBddPassword;
private: System::Windows::Forms::TextBox^  tbBddUsername;
private: System::Windows::Forms::Timer^  timerUpdate;
private: System::Windows::Forms::TabControl^  tabControl1;
private: System::Windows::Forms::TabPage^  tabEntree;
private: System::Windows::Forms::TabPage^  tabSortie;
private: System::Windows::Forms::TabPage^  tabBDD;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::NumericUpDown^  nudPortS;
private: System::Windows::Forms::ComboBox^  cbInterS;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::Button^  btClose;
private: System::ComponentModel::IContainer^  components;

private:
	/// <summary>
	/// Variable n�cessaire au concepteur.
	/// </summary>
	DataConfigServeur^ _dataConfig; //Config du serveur
	Config^ config;
	PipeServeur^ _pipeServeur;




#pragma region Windows Form Designer generated code
		 /// <summary>
		 /// M�thode requise pour la prise en charge du concepteur - ne modifiez pas
		 /// le contenu de cette m�thode avec l'�diteur de code.
		 /// </summary>

		 void InitializeComponent(void)
		 {
			 this->components = (gcnew System::ComponentModel::Container());
			 this->gbBalcanceS = (gcnew System::Windows::Forms::GroupBox());
			 this->label3 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxBaS = (gcnew ControlInterface::ControlIPBox());
			 this->CeBaS = (gcnew ControlInterface::ControlEtat());
			 this->pbBaS = (gcnew System::Windows::Forms::PictureBox());
			 this->gbRFIDs = (gcnew System::Windows::Forms::GroupBox());
			 this->label4 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxRfS = (gcnew ControlInterface::ControlIPBox());
			 this->CeRfS = (gcnew ControlInterface::ControlEtat());
			 this->pbRfS = (gcnew System::Windows::Forms::PictureBox());
			 this->gbBarriereS = (gcnew System::Windows::Forms::GroupBox());
			 this->label5 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxBrS = (gcnew ControlInterface::ControlIPBox());
			 this->CeBrS = (gcnew ControlInterface::ControlEtat());
			 this->pbBrS = (gcnew System::Windows::Forms::PictureBox());
			 this->label7 = (gcnew System::Windows::Forms::Label());
			 this->label6 = (gcnew System::Windows::Forms::Label());
			 this->cbInterE = (gcnew System::Windows::Forms::ComboBox());
			 this->nudPortE = (gcnew System::Windows::Forms::NumericUpDown());
			 this->gbBaE = (gcnew System::Windows::Forms::GroupBox());
			 this->l1 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxBaE = (gcnew ControlInterface::ControlIPBox());
			 this->CeBaE = (gcnew ControlInterface::ControlEtat());
			 this->pbBaE = (gcnew System::Windows::Forms::PictureBox());
			 this->gbRfE = (gcnew System::Windows::Forms::GroupBox());
			 this->label1 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxRfE = (gcnew ControlInterface::ControlIPBox());
			 this->CeRfE = (gcnew ControlInterface::ControlEtat());
			 this->pbRfE = (gcnew System::Windows::Forms::PictureBox());
			 this->gbBrE = (gcnew System::Windows::Forms::GroupBox());
			 this->label2 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxBrE = (gcnew ControlInterface::ControlIPBox());
			 this->CeBrE = (gcnew ControlInterface::ControlEtat());
			 this->pbBrE = (gcnew System::Windows::Forms::PictureBox());
			 this->btSav = (gcnew System::Windows::Forms::Button());
			 this->label14 = (gcnew System::Windows::Forms::Label());
			 this->label13 = (gcnew System::Windows::Forms::Label());
			 this->tbBddPassword = (gcnew System::Windows::Forms::TextBox());
			 this->tbBddUsername = (gcnew System::Windows::Forms::TextBox());
			 this->label11 = (gcnew System::Windows::Forms::Label());
			 this->tbBddIP = (gcnew ControlInterface::ControlIPBox());
			 this->nudPortBdd = (gcnew System::Windows::Forms::NumericUpDown());
			 this->label12 = (gcnew System::Windows::Forms::Label());
			 this->tbBddName = (gcnew System::Windows::Forms::TextBox());
			 this->timerUpdate = (gcnew System::Windows::Forms::Timer(this->components));
			 this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			 this->tabEntree = (gcnew System::Windows::Forms::TabPage());
			 this->tabSortie = (gcnew System::Windows::Forms::TabPage());
			 this->label8 = (gcnew System::Windows::Forms::Label());
			 this->label9 = (gcnew System::Windows::Forms::Label());
			 this->nudPortS = (gcnew System::Windows::Forms::NumericUpDown());
			 this->cbInterS = (gcnew System::Windows::Forms::ComboBox());
			 this->tabBDD = (gcnew System::Windows::Forms::TabPage());
			 this->label23 = (gcnew System::Windows::Forms::Label());
			 this->btClose = (gcnew System::Windows::Forms::Button());
			 this->gbBalcanceS->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBaS))->BeginInit();
			 this->gbRFIDs->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbRfS))->BeginInit();
			 this->gbBarriereS->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBrS))->BeginInit();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortE))->BeginInit();
			 this->gbBaE->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBaE))->BeginInit();
			 this->gbRfE->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbRfE))->BeginInit();
			 this->gbBrE->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBrE))->BeginInit();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortBdd))->BeginInit();
			 this->tabControl1->SuspendLayout();
			 this->tabEntree->SuspendLayout();
			 this->tabSortie->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortS))->BeginInit();
			 this->tabBDD->SuspendLayout();
			 this->SuspendLayout();
			 // 
			 // gbBalcanceS
			 // 
			 this->gbBalcanceS->Controls->Add(this->label3);
			 this->gbBalcanceS->Controls->Add(this->controlIPBoxBaS);
			 this->gbBalcanceS->Controls->Add(this->CeBaS);
			 this->gbBalcanceS->Controls->Add(this->pbBaS);
			 this->gbBalcanceS->Location = System::Drawing::Point(556, 19);
			 this->gbBalcanceS->Name = L"gbBalcanceS";
			 this->gbBalcanceS->Size = System::Drawing::Size(259, 209);
			 this->gbBalcanceS->TabIndex = 2;
			 this->gbBalcanceS->TabStop = false;
			 this->gbBalcanceS->Text = L"Balance";
			 // 
			 // label3
			 // 
			 this->label3->AutoSize = true;
			 this->label3->Location = System::Drawing::Point(61, 182);
			 this->label3->Name = L"label3";
			 this->label3->Size = System::Drawing::Size(58, 13);
			 this->label3->TabIndex = 8;
			 this->label3->Text = L"Adresse IP";
			 // 
			 // controlIPBoxBaS
			 // 
			 this->controlIPBoxBaS->IP = L"...";
			 this->controlIPBoxBaS->Location = System::Drawing::Point(125, 180);
			 this->controlIPBoxBaS->Name = L"controlIPBoxBaS";
			 this->controlIPBoxBaS->Size = System::Drawing::Size(128, 18);
			 this->controlIPBoxBaS->TabIndex = 7;
			 // 
			 // CeBaS
			 // 
			 this->CeBaS->BackColor = System::Drawing::Color::Red;
			 this->CeBaS->colorFalse = System::Drawing::Color::Red;
			 this->CeBaS->colorTexte = System::Drawing::Color::White;
			 this->CeBaS->colorTrue = System::Drawing::Color::Lime;
			 this->CeBaS->Location = System::Drawing::Point(6, 19);
			 this->CeBaS->Name = L"CeBaS";
			 this->CeBaS->Size = System::Drawing::Size(128, 28);
			 this->CeBaS->state = false;
			 this->CeBaS->TabIndex = 7;
			 this->CeBaS->texteSize = 10;
			 this->CeBaS->textFalse = L"Non connecté";
			 this->CeBaS->textTrue = L"Connecté";
			 // 
			 // pbBaS
			 // 
			 this->pbBaS->Location = System::Drawing::Point(6, 53);
			 this->pbBaS->Name = L"pbBaS";
			 this->pbBaS->Size = System::Drawing::Size(247, 118);
			 this->pbBaS->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			 this->pbBaS->TabIndex = 0;
			 this->pbBaS->TabStop = false;
			 // 
			 // gbRFIDs
			 // 
			 this->gbRFIDs->Controls->Add(this->label4);
			 this->gbRFIDs->Controls->Add(this->controlIPBoxRfS);
			 this->gbRFIDs->Controls->Add(this->CeRfS);
			 this->gbRFIDs->Controls->Add(this->pbRfS);
			 this->gbRFIDs->Location = System::Drawing::Point(291, 19);
			 this->gbRFIDs->Name = L"gbRFIDs";
			 this->gbRFIDs->Size = System::Drawing::Size(259, 209);
			 this->gbRFIDs->TabIndex = 2;
			 this->gbRFIDs->TabStop = false;
			 this->gbRFIDs->Text = L"Totem RFID";
			 // 
			 // label4
			 // 
			 this->label4->AutoSize = true;
			 this->label4->Location = System::Drawing::Point(61, 182);
			 this->label4->Name = L"label4";
			 this->label4->Size = System::Drawing::Size(58, 13);
			 this->label4->TabIndex = 9;
			 this->label4->Text = L"Adresse IP";
			 // 
			 // controlIPBoxRfS
			 // 
			 this->controlIPBoxRfS->IP = L"...";
			 this->controlIPBoxRfS->Location = System::Drawing::Point(125, 180);
			 this->controlIPBoxRfS->Name = L"controlIPBoxRfS";
			 this->controlIPBoxRfS->Size = System::Drawing::Size(128, 18);
			 this->controlIPBoxRfS->TabIndex = 6;
			 // 
			 // CeRfS
			 // 
			 this->CeRfS->BackColor = System::Drawing::Color::Red;
			 this->CeRfS->colorFalse = System::Drawing::Color::Red;
			 this->CeRfS->colorTexte = System::Drawing::Color::White;
			 this->CeRfS->colorTrue = System::Drawing::Color::Lime;
			 this->CeRfS->Location = System::Drawing::Point(6, 19);
			 this->CeRfS->Name = L"CeRfS";
			 this->CeRfS->Size = System::Drawing::Size(128, 28);
			 this->CeRfS->state = false;
			 this->CeRfS->TabIndex = 6;
			 this->CeRfS->texteSize = 10;
			 this->CeRfS->textFalse = L"Non connecté";
			 this->CeRfS->textTrue = L"Connecté";
			 // 
			 // pbRfS
			 // 
			 this->pbRfS->Location = System::Drawing::Point(6, 53);
			 this->pbRfS->Name = L"pbRfS";
			 this->pbRfS->Size = System::Drawing::Size(247, 118);
			 this->pbRfS->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			 this->pbRfS->TabIndex = 0;
			 this->pbRfS->TabStop = false;
			 // 
			 // gbBarriereS
			 // 
			 this->gbBarriereS->Controls->Add(this->label5);
			 this->gbBarriereS->Controls->Add(this->controlIPBoxBrS);
			 this->gbBarriereS->Controls->Add(this->CeBrS);
			 this->gbBarriereS->Controls->Add(this->pbBrS);
			 this->gbBarriereS->Location = System::Drawing::Point(26, 19);
			 this->gbBarriereS->Name = L"gbBarriereS";
			 this->gbBarriereS->Size = System::Drawing::Size(259, 209);
			 this->gbBarriereS->TabIndex = 1;
			 this->gbBarriereS->TabStop = false;
			 this->gbBarriereS->Text = L"Barrière";
			 // 
			 // label5
			 // 
			 this->label5->AutoSize = true;
			 this->label5->Location = System::Drawing::Point(61, 182);
			 this->label5->Name = L"label5";
			 this->label5->Size = System::Drawing::Size(58, 13);
			 this->label5->TabIndex = 10;
			 this->label5->Text = L"Adresse IP";
			 // 
			 // controlIPBoxBrS
			 // 
			 this->controlIPBoxBrS->IP = L"...";
			 this->controlIPBoxBrS->Location = System::Drawing::Point(125, 180);
			 this->controlIPBoxBrS->Name = L"controlIPBoxBrS";
			 this->controlIPBoxBrS->Size = System::Drawing::Size(128, 18);
			 this->controlIPBoxBrS->TabIndex = 4;
			 // 
			 // CeBrS
			 // 
			 this->CeBrS->BackColor = System::Drawing::Color::Red;
			 this->CeBrS->colorFalse = System::Drawing::Color::Red;
			 this->CeBrS->colorTexte = System::Drawing::Color::White;
			 this->CeBrS->colorTrue = System::Drawing::Color::Lime;
			 this->CeBrS->Location = System::Drawing::Point(6, 19);
			 this->CeBrS->Name = L"CeBrS";
			 this->CeBrS->Size = System::Drawing::Size(128, 28);
			 this->CeBrS->state = false;
			 this->CeBrS->TabIndex = 5;
			 this->CeBrS->texteSize = 10;
			 this->CeBrS->textFalse = L"Non connecté";
			 this->CeBrS->textTrue = L"Connecté";
			 // 
			 // pbBrS
			 // 
			 this->pbBrS->Location = System::Drawing::Point(6, 53);
			 this->pbBrS->Name = L"pbBrS";
			 this->pbBrS->Size = System::Drawing::Size(247, 118);
			 this->pbBrS->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			 this->pbBrS->TabIndex = 0;
			 this->pbBrS->TabStop = false;
			 // 
			 // label7
			 // 
			 this->label7->AutoSize = true;
			 this->label7->Location = System::Drawing::Point(125, 247);
			 this->label7->Name = L"label7";
			 this->label7->Size = System::Drawing::Size(26, 13);
			 this->label7->TabIndex = 12;
			 this->label7->Text = L"Port";
			 // 
			 // label6
			 // 
			 this->label6->AutoSize = true;
			 this->label6->Location = System::Drawing::Point(366, 247);
			 this->label6->Name = L"label6";
			 this->label6->Size = System::Drawing::Size(49, 13);
			 this->label6->TabIndex = 11;
			 this->label6->Text = L"Interface";
			 // 
			 // cbInterE
			 // 
			 this->cbInterE->FormattingEnabled = true;
			 this->cbInterE->Location = System::Drawing::Point(421, 244);
			 this->cbInterE->Name = L"cbInterE";
			 this->cbInterE->Size = System::Drawing::Size(129, 21);
			 this->cbInterE->TabIndex = 4;
			 // 
			 // nudPortE
			 // 
			 this->nudPortE->Location = System::Drawing::Point(157, 245);
			 this->nudPortE->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			 this->nudPortE->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 this->nudPortE->Name = L"nudPortE";
			 this->nudPortE->Size = System::Drawing::Size(128, 20);
			 this->nudPortE->TabIndex = 3;
			 this->nudPortE->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 // 
			 // gbBaE
			 // 
			 this->gbBaE->Controls->Add(this->l1);
			 this->gbBaE->Controls->Add(this->controlIPBoxBaE);
			 this->gbBaE->Controls->Add(this->CeBaE);
			 this->gbBaE->Controls->Add(this->pbBaE);
			 this->gbBaE->Location = System::Drawing::Point(556, 19);
			 this->gbBaE->Name = L"gbBaE";
			 this->gbBaE->Size = System::Drawing::Size(259, 209);
			 this->gbBaE->TabIndex = 2;
			 this->gbBaE->TabStop = false;
			 this->gbBaE->Text = L"Balance";
			 // 
			 // l1
			 // 
			 this->l1->AutoSize = true;
			 this->l1->Location = System::Drawing::Point(61, 182);
			 this->l1->Name = L"l1";
			 this->l1->Size = System::Drawing::Size(58, 13);
			 this->l1->TabIndex = 7;
			 this->l1->Text = L"Adresse IP";
			 // 
			 // controlIPBoxBaE
			 // 
			 this->controlIPBoxBaE->IP = L"...";
			 this->controlIPBoxBaE->Location = System::Drawing::Point(125, 180);
			 this->controlIPBoxBaE->Name = L"controlIPBoxBaE";
			 this->controlIPBoxBaE->Size = System::Drawing::Size(128, 18);
			 this->controlIPBoxBaE->TabIndex = 6;
			 // 
			 // CeBaE
			 // 
			 this->CeBaE->BackColor = System::Drawing::Color::Red;
			 this->CeBaE->colorFalse = System::Drawing::Color::Red;
			 this->CeBaE->colorTexte = System::Drawing::Color::White;
			 this->CeBaE->colorTrue = System::Drawing::Color::Lime;
			 this->CeBaE->Location = System::Drawing::Point(6, 19);
			 this->CeBaE->Name = L"CeBaE";
			 this->CeBaE->Size = System::Drawing::Size(128, 28);
			 this->CeBaE->state = false;
			 this->CeBaE->TabIndex = 4;
			 this->CeBaE->texteSize = 10;
			 this->CeBaE->textFalse = L"Non connecté";
			 this->CeBaE->textTrue = L"Connecté";
			 // 
			 // pbBaE
			 // 
			 this->pbBaE->Location = System::Drawing::Point(6, 53);
			 this->pbBaE->Name = L"pbBaE";
			 this->pbBaE->Size = System::Drawing::Size(247, 118);
			 this->pbBaE->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			 this->pbBaE->TabIndex = 0;
			 this->pbBaE->TabStop = false;
			 // 
			 // gbRfE
			 // 
			 this->gbRfE->Controls->Add(this->label1);
			 this->gbRfE->Controls->Add(this->controlIPBoxRfE);
			 this->gbRfE->Controls->Add(this->CeRfE);
			 this->gbRfE->Controls->Add(this->pbRfE);
			 this->gbRfE->Location = System::Drawing::Point(291, 19);
			 this->gbRfE->Name = L"gbRfE";
			 this->gbRfE->Size = System::Drawing::Size(259, 209);
			 this->gbRfE->TabIndex = 2;
			 this->gbRfE->TabStop = false;
			 this->gbRfE->Text = L"Totem RFID";
			 // 
			 // label1
			 // 
			 this->label1->AutoSize = true;
			 this->label1->Location = System::Drawing::Point(61, 182);
			 this->label1->Name = L"label1";
			 this->label1->Size = System::Drawing::Size(58, 13);
			 this->label1->TabIndex = 8;
			 this->label1->Text = L"Adresse IP";
			 // 
			 // controlIPBoxRfE
			 // 
			 this->controlIPBoxRfE->IP = L"...";
			 this->controlIPBoxRfE->Location = System::Drawing::Point(125, 180);
			 this->controlIPBoxRfE->Name = L"controlIPBoxRfE";
			 this->controlIPBoxRfE->Size = System::Drawing::Size(128, 18);
			 this->controlIPBoxRfE->TabIndex = 7;
			 // 
			 // CeRfE
			 // 
			 this->CeRfE->BackColor = System::Drawing::Color::Red;
			 this->CeRfE->colorFalse = System::Drawing::Color::Red;
			 this->CeRfE->colorTexte = System::Drawing::Color::White;
			 this->CeRfE->colorTrue = System::Drawing::Color::Lime;
			 this->CeRfE->Location = System::Drawing::Point(6, 19);
			 this->CeRfE->Name = L"CeRfE";
			 this->CeRfE->Size = System::Drawing::Size(128, 28);
			 this->CeRfE->state = false;
			 this->CeRfE->TabIndex = 3;
			 this->CeRfE->texteSize = 10;
			 this->CeRfE->textFalse = L"Non connecté";
			 this->CeRfE->textTrue = L"Connecté";
			 // 
			 // pbRfE
			 // 
			 this->pbRfE->Location = System::Drawing::Point(6, 53);
			 this->pbRfE->Name = L"pbRfE";
			 this->pbRfE->Size = System::Drawing::Size(247, 118);
			 this->pbRfE->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			 this->pbRfE->TabIndex = 0;
			 this->pbRfE->TabStop = false;
			 // 
			 // gbBrE
			 // 
			 this->gbBrE->Controls->Add(this->label2);
			 this->gbBrE->Controls->Add(this->controlIPBoxBrE);
			 this->gbBrE->Controls->Add(this->CeBrE);
			 this->gbBrE->Controls->Add(this->pbBrE);
			 this->gbBrE->Location = System::Drawing::Point(26, 19);
			 this->gbBrE->Name = L"gbBrE";
			 this->gbBrE->Size = System::Drawing::Size(259, 209);
			 this->gbBrE->TabIndex = 1;
			 this->gbBrE->TabStop = false;
			 this->gbBrE->Text = L"Barrière";
			 // 
			 // label2
			 // 
			 this->label2->AutoSize = true;
			 this->label2->Location = System::Drawing::Point(61, 182);
			 this->label2->Name = L"label2";
			 this->label2->Size = System::Drawing::Size(58, 13);
			 this->label2->TabIndex = 9;
			 this->label2->Text = L"Adresse IP";
			 // 
			 // controlIPBoxBrE
			 // 
			 this->controlIPBoxBrE->IP = L"...";
			 this->controlIPBoxBrE->Location = System::Drawing::Point(125, 180);
			 this->controlIPBoxBrE->Name = L"controlIPBoxBrE";
			 this->controlIPBoxBrE->Size = System::Drawing::Size(128, 18);
			 this->controlIPBoxBrE->TabIndex = 3;
			 // 
			 // CeBrE
			 // 
			 this->CeBrE->BackColor = System::Drawing::Color::Red;
			 this->CeBrE->colorFalse = System::Drawing::Color::Red;
			 this->CeBrE->colorTexte = System::Drawing::Color::White;
			 this->CeBrE->colorTrue = System::Drawing::Color::Lime;
			 this->CeBrE->Location = System::Drawing::Point(6, 19);
			 this->CeBrE->Name = L"CeBrE";
			 this->CeBrE->Size = System::Drawing::Size(128, 28);
			 this->CeBrE->state = false;
			 this->CeBrE->TabIndex = 2;
			 this->CeBrE->texteSize = 10;
			 this->CeBrE->textFalse = L"Non connecté";
			 this->CeBrE->textTrue = L"Connecté";
			 // 
			 // pbBrE
			 // 
			 this->pbBrE->Location = System::Drawing::Point(6, 53);
			 this->pbBrE->Name = L"pbBrE";
			 this->pbBrE->Size = System::Drawing::Size(247, 118);
			 this->pbBrE->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			 this->pbBrE->TabIndex = 0;
			 this->pbBrE->TabStop = false;
			 // 
			 // btSav
			 // 
			 this->btSav->Location = System::Drawing::Point(681, 324);
			 this->btSav->Name = L"btSav";
			 this->btSav->Size = System::Drawing::Size(75, 23);
			 this->btSav->TabIndex = 7;
			 this->btSav->Text = L"Sauvegarde";
			 this->btSav->UseVisualStyleBackColor = true;
			 this->btSav->Click += gcnew System::EventHandler(this, &ConfigForm::btSav_Click);
			 // 
			 // label14
			 // 
			 this->label14->AutoSize = true;
			 this->label14->Location = System::Drawing::Point(28, 138);
			 this->label14->Name = L"label14";
			 this->label14->Size = System::Drawing::Size(71, 13);
			 this->label14->TabIndex = 20;
			 this->label14->Text = L"Mot de passe";
			 // 
			 // label13
			 // 
			 this->label13->AutoSize = true;
			 this->label13->Location = System::Drawing::Point(28, 112);
			 this->label13->Name = L"label13";
			 this->label13->Size = System::Drawing::Size(84, 13);
			 this->label13->TabIndex = 19;
			 this->label13->Text = L"Nom d\'utilisateur";
			 // 
			 // tbBddPassword
			 // 
			 this->tbBddPassword->Location = System::Drawing::Point(223, 135);
			 this->tbBddPassword->Name = L"tbBddPassword";
			 this->tbBddPassword->Size = System::Drawing::Size(128, 20);
			 this->tbBddPassword->TabIndex = 18;
			 this->tbBddPassword->UseSystemPasswordChar = true;
			 // 
			 // tbBddUsername
			 // 
			 this->tbBddUsername->Location = System::Drawing::Point(223, 109);
			 this->tbBddUsername->Name = L"tbBddUsername";
			 this->tbBddUsername->Size = System::Drawing::Size(128, 20);
			 this->tbBddUsername->TabIndex = 17;
			 // 
			 // label11
			 // 
			 this->label11->AutoSize = true;
			 this->label11->Location = System::Drawing::Point(28, 35);
			 this->label11->Name = L"label11";
			 this->label11->Size = System::Drawing::Size(58, 13);
			 this->label11->TabIndex = 9;
			 this->label11->Text = L"Adresse IP";
			 // 
			 // tbBddIP
			 // 
			 this->tbBddIP->IP = L"...";
			 this->tbBddIP->Location = System::Drawing::Point(223, 33);
			 this->tbBddIP->Name = L"tbBddIP";
			 this->tbBddIP->Size = System::Drawing::Size(128, 18);
			 this->tbBddIP->TabIndex = 9;
			 // 
			 // nudPortBdd
			 // 
			 this->nudPortBdd->Location = System::Drawing::Point(223, 57);
			 this->nudPortBdd->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			 this->nudPortBdd->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 this->nudPortBdd->Name = L"nudPortBdd";
			 this->nudPortBdd->Size = System::Drawing::Size(128, 20);
			 this->nudPortBdd->TabIndex = 13;
			 this->nudPortBdd->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 // 
			 // label12
			 // 
			 this->label12->AutoSize = true;
			 this->label12->Location = System::Drawing::Point(28, 86);
			 this->label12->Name = L"label12";
			 this->label12->Size = System::Drawing::Size(136, 13);
			 this->label12->TabIndex = 16;
			 this->label12->Text = L"Nom de la base de donn�e";
			 // 
			 // tbBddName
			 // 
			 this->tbBddName->Location = System::Drawing::Point(223, 83);
			 this->tbBddName->Name = L"tbBddName";
			 this->tbBddName->Size = System::Drawing::Size(128, 20);
			 this->tbBddName->TabIndex = 15;
			 // 
			 // timerUpdate
			 // 
			 this->timerUpdate->Enabled = true;
			 this->timerUpdate->Interval = 500;
			 this->timerUpdate->Tick += gcnew System::EventHandler(this, &ConfigForm::timerUpdate_Tick);
			 // 
			 // tabControl1
			 // 
			 this->tabControl1->Controls->Add(this->tabEntree);
			 this->tabControl1->Controls->Add(this->tabSortie);
			 this->tabControl1->Controls->Add(this->tabBDD);
			 this->tabControl1->Location = System::Drawing::Point(0, 0);
			 this->tabControl1->Name = L"tabControl1";
			 this->tabControl1->SelectedIndex = 0;
			 this->tabControl1->Size = System::Drawing::Size(850, 318);
			 this->tabControl1->TabIndex = 9;
			 // 
			 // tabEntree
			 // 
			 this->tabEntree->Controls->Add(this->label6);
			 this->tabEntree->Controls->Add(this->cbInterE);
			 this->tabEntree->Controls->Add(this->label7);
			 this->tabEntree->Controls->Add(this->gbBrE);
			 this->tabEntree->Controls->Add(this->gbRfE);
			 this->tabEntree->Controls->Add(this->gbBaE);
			 this->tabEntree->Controls->Add(this->nudPortE);
			 this->tabEntree->Location = System::Drawing::Point(4, 22);
			 this->tabEntree->Name = L"tabEntree";
			 this->tabEntree->Padding = System::Windows::Forms::Padding(3);
			 this->tabEntree->Size = System::Drawing::Size(842, 292);
			 this->tabEntree->TabIndex = 0;
			 this->tabEntree->Text = L"Entrée";
			 this->tabEntree->UseVisualStyleBackColor = true;
			 // 
			 // tabSortie
			 // 
			 this->tabSortie->Controls->Add(this->label8);
			 this->tabSortie->Controls->Add(this->label9);
			 this->tabSortie->Controls->Add(this->gbBalcanceS);
			 this->tabSortie->Controls->Add(this->gbRFIDs);
			 this->tabSortie->Controls->Add(this->gbBarriereS);
			 this->tabSortie->Controls->Add(this->nudPortS);
			 this->tabSortie->Controls->Add(this->cbInterS);
			 this->tabSortie->Location = System::Drawing::Point(4, 22);
			 this->tabSortie->Name = L"tabSortie";
			 this->tabSortie->Padding = System::Windows::Forms::Padding(3);
			 this->tabSortie->Size = System::Drawing::Size(842, 292);
			 this->tabSortie->TabIndex = 1;
			 this->tabSortie->Text = L"Sortie";
			 this->tabSortie->UseVisualStyleBackColor = true;
			 // 
			 // label8
			 // 
			 this->label8->AutoSize = true;
			 this->label8->Location = System::Drawing::Point(125, 247);
			 this->label8->Name = L"label8";
			 this->label8->Size = System::Drawing::Size(26, 13);
			 this->label8->TabIndex = 16;
			 this->label8->Text = L"Port";
			 // 
			 // label9
			 // 
			 this->label9->AutoSize = true;
			 this->label9->Location = System::Drawing::Point(366, 247);
			 this->label9->Name = L"label9";
			 this->label9->Size = System::Drawing::Size(49, 13);
			 this->label9->TabIndex = 15;
			 this->label9->Text = L"Interface";
			 // 
			 // nudPortS
			 // 
			 this->nudPortS->Location = System::Drawing::Point(157, 245);
			 this->nudPortS->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			 this->nudPortS->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 this->nudPortS->Name = L"nudPortS";
			 this->nudPortS->Size = System::Drawing::Size(128, 20);
			 this->nudPortS->TabIndex = 13;
			 this->nudPortS->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 // 
			 // cbInterS
			 // 
			 this->cbInterS->FormattingEnabled = true;
			 this->cbInterS->Location = System::Drawing::Point(421, 244);
			 this->cbInterS->Name = L"cbInterS";
			 this->cbInterS->Size = System::Drawing::Size(129, 21);
			 this->cbInterS->TabIndex = 14;
			 // 
			 // tabBDD
			 // 
			 this->tabBDD->Controls->Add(this->label14);
			 this->tabBDD->Controls->Add(this->label23);
			 this->tabBDD->Controls->Add(this->nudPortBdd);
			 this->tabBDD->Controls->Add(this->tbBddUsername);
			 this->tabBDD->Controls->Add(this->tbBddName);
			 this->tabBDD->Controls->Add(this->tbBddPassword);
			 this->tabBDD->Controls->Add(this->tbBddIP);
			 this->tabBDD->Controls->Add(this->label13);
			 this->tabBDD->Controls->Add(this->label11);
			 this->tabBDD->Controls->Add(this->label12);
			 this->tabBDD->Location = System::Drawing::Point(4, 22);
			 this->tabBDD->Name = L"tabBDD";
			 this->tabBDD->Padding = System::Windows::Forms::Padding(3);
			 this->tabBDD->Size = System::Drawing::Size(842, 292);
			 this->tabBDD->TabIndex = 2;
			 this->tabBDD->Text = L"Base de donnée";
			 this->tabBDD->UseVisualStyleBackColor = true;
			 // 
			 // label23
			 // 
			 this->label23->AutoSize = true;
			 this->label23->Location = System::Drawing::Point(28, 59);
			 this->label23->Name = L"label23";
			 this->label23->Size = System::Drawing::Size(26, 13);
			 this->label23->TabIndex = 17;
			 this->label23->Text = L"Port";
			 // 
			 // btClose
			 // 
			 this->btClose->Location = System::Drawing::Point(762, 324);
			 this->btClose->Name = L"btClose";
			 this->btClose->Size = System::Drawing::Size(75, 23);
			 this->btClose->TabIndex = 10;
			 this->btClose->Text = L"Fermer";
			 this->btClose->UseVisualStyleBackColor = true;
			 this->btClose->Click += gcnew System::EventHandler(this, &ConfigForm::btClose_Click);
			 // 
			 // ConfigForm
			 // 
			 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			 this->ClientSize = System::Drawing::Size(849, 354);
			 this->Controls->Add(this->btClose);
			 this->Controls->Add(this->tabControl1);
			 this->Controls->Add(this->btSav);
			 this->Name = L"ConfigForm";
			 this->Text = L"Option";
			 this->Load += gcnew System::EventHandler(this, &ConfigForm::ConfigForm_Load);
			 this->gbBalcanceS->ResumeLayout(false);
			 this->gbBalcanceS->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBaS))->EndInit();
			 this->gbRFIDs->ResumeLayout(false);
			 this->gbRFIDs->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbRfS))->EndInit();
			 this->gbBarriereS->ResumeLayout(false);
			 this->gbBarriereS->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBrS))->EndInit();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortE))->EndInit();
			 this->gbBaE->ResumeLayout(false);
			 this->gbBaE->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBaE))->EndInit();
			 this->gbRfE->ResumeLayout(false);
			 this->gbRfE->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbRfE))->EndInit();
			 this->gbBrE->ResumeLayout(false);
			 this->gbBrE->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbBrE))->EndInit();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortBdd))->EndInit();
			 this->tabControl1->ResumeLayout(false);
			 this->tabEntree->ResumeLayout(false);
			 this->tabEntree->PerformLayout();
			 this->tabSortie->ResumeLayout(false);
			 this->tabSortie->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortS))->EndInit();
			 this->tabBDD->ResumeLayout(false);
			 this->tabBDD->PerformLayout();
			 this->ResumeLayout(false);

		 }
#pragma endregion

	/*---------------------------------------------------------------
	Nom          :  checkInterface
	Description  :  Cherche les interfaces réseaux disponible
	Arguments    :  .
	Valeur renvoyée : .
	-----------------------------------------------------------------*/
	private: void checkInterface()
	{
		IPHostEntry^ host = Dns::GetHostEntry(Dns::GetHostName());

		for each(IPAddress^ ip in host->AddressList)
		{
			if (ip->AddressFamily == AddressFamily::InterNetwork)
			{
				cbInterE->Items->Add(ip);
				cbInterS->Items->Add(ip);
			}
		}
		cbInterE->Items->Add(IPAddress::Loopback);
		cbInterS->Items->Add(IPAddress::Loopback);
		cbInterE->Items->Add(IPAddress::Any);
		cbInterS->Items->Add(IPAddress::Any);
		cbInterE->SelectedValue = IPAddress::Any;
		cbInterS->SelectedValue = IPAddress::Any;
	}

	/*---------------------------------------------------------------
	Nom          :  loadConfigFile
	Description  :  Charge les configs si le fichier existe déjà
	Arguments    :  .
	Valeur renvoyée : .
	-----------------------------------------------------------------*/
	private: void loadConfig()
	{
		_dataConfig = config->getDataConfig();
		if (_dataConfig != nullptr)
		{
			controlIPBoxBaE->IP = _dataConfig->Entree->IPBalance;
			controlIPBoxBrE->IP = _dataConfig->Entree->IPBarriere;
			controlIPBoxRfE->IP = _dataConfig->Entree->IPRFID;
			cbInterE->SelectedItem = IPAddress::Parse(_dataConfig->Entree->Interface);
			nudPortE->Value = _dataConfig->Entree->portServeur;

			controlIPBoxBaS->IP = _dataConfig->Sortie->IPBalance;
			controlIPBoxBrS->IP = _dataConfig->Sortie->IPBarriere;
			controlIPBoxRfS->IP = _dataConfig->Sortie->IPRFID;
			cbInterS->SelectedItem = IPAddress::Parse(_dataConfig->Sortie->Interface);
			nudPortS->Value = _dataConfig->Sortie->portServeur;

			tbBddIP->IP = _dataConfig->IPBDD;
			tbBddName->Text = _dataConfig->NomBDD;
			tbBddPassword->Text = _dataConfig->PasswordBDD;
			tbBddUsername->Text = _dataConfig->UsernameBDD;
			nudPortBdd->Value = _dataConfig->PortBDD;
		}
	}

	/*---------------------------------------------------------------
	Nom          :  ConfigForm_Load
	Description  :  Lorsque la fenetre charge
	-----------------------------------------------------------------*/
	private: System::Void ConfigForm_Load(System::Object^  sender, System::EventArgs^  e) 
	{
		loadConfig();
	}

	/*---------------------------------------------------------------
	Nom          :  btSav_Click
	Description  :  Lorsque on appuie sur sauvegarder
	-----------------------------------------------------------------*/
	private: System::Void btSav_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		_dataConfig->Entree->IPBalance = this->controlIPBoxBaE->IP;
		_dataConfig->Sortie->IPBalance = this->controlIPBoxBaS->IP;

		_dataConfig->Entree->IPBarriere = this->controlIPBoxBrE->IP;
		_dataConfig->Sortie->IPBarriere = this->controlIPBoxBrS->IP;

		_dataConfig->Entree->IPRFID = this->controlIPBoxRfE->IP;
		_dataConfig->Sortie->IPRFID = this->controlIPBoxRfS->IP;

		_dataConfig->Entree->portServeur = Convert::ToInt32(this->nudPortE->Value);
		_dataConfig->Sortie->portServeur = Convert::ToInt32(this->nudPortS->Value);

		_dataConfig->Entree->Interface = ((IPAddress^)cbInterE->SelectedItem)->ToString();
		_dataConfig->Sortie->Interface = ((IPAddress^)cbInterE->SelectedItem)->ToString();

		_dataConfig->NomBDD = tbBddName->Text;
		_dataConfig->UsernameBDD = tbBddUsername->Text;
		_dataConfig->PasswordBDD = tbBddPassword->Text;
		_dataConfig->IPBDD = tbBddIP->IP;
		_dataConfig->PortBDD = Convert::ToInt32(this->nudPortBdd->Value);
		config->setDataConfig(_dataConfig);

		this->Close();
		this->~ConfigForm();
	}

	/*---------------------------------------------------------------
	Nom          :  btClose_Click
	Description  :  Lorsque on appuie sur Fermer
	-----------------------------------------------------------------*/
	private: System::Void btClose_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->Close();
		this->~ConfigForm();
	}

	/*---------------------------------------------------------------
	Nom          :  timerUpdate_Tick
	Description  :  Lorsque le timer tourne
	-----------------------------------------------------------------*/
	private: System::Void timerUpdate_Tick(System::Object^  sender, System::EventArgs^  e) 
	{
		if (_pipeServeur->getServeurState()) // Si le serveur est allumée
		{
			UpdateClientState(_pipeServeur->getClientState());
		}
	}

	/*---------------------------------------------------------------
	Nom          :  UpdateClientState
	Description  :  Mets à jours les états des client sur l'affichage
	Arguments    :  array<Byte>^ : tableau des états des clients
	Valeur renvoyée : .
	-----------------------------------------------------------------*/
	private: System::Void UpdateClientState(array<Byte>^ t)
	{
		if (t != nullptr)
		{
			Encoding^ encoder = Encoding::ASCII;
			Console::WriteLine(encoder->GetString(t));
			//======================================== Entree ========================
			if (t[0] == '1') { CeBrE->state = true; }// Barrière
			else { CeBrE->state = false; }

			if (t[1] == '1') { CeRfE->state = true; }// Balance
			else { CeRfE->state = false; }

			if (t[2] == '1') { CeBaE->state = true; }// RFID
			else { CeBaE->state = false; }
			//======================================== Sortie ========================
			if (t[3] == '1') { CeBrS->state = true; }// Barrière
			else { CeBrS->state = false; }

			if (t[4] == '1') { CeRfS->state = true; }// Balance
			else { CeRfS->state = false; }

			if (t[5] == '1') { CeBaS->state = true; }// RFID
			else { CeBaS->state = false; }

		}
	}
};


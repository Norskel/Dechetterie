#pragma once
#include "StructDataConfigServeur.h"
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

delegate void DelegateState(array<Byte>^ t);


/// <summary>
/// Description résumée de ConfigForm
/// </summary>
public ref class ConfigForm : public System::Windows::Forms::Form
{
public:
	ConfigForm(void)
	{
		InitializeComponent();

		_DcallBackState = gcnew DelegateState(this, &ConfigForm::callbackState);



		this->pictureBox1->Image = Image::FromFile("image/barriere.png");
		this->pictureBox2->Image = Image::FromFile("image/rfid_ecran.png");
		this->pictureBox3->Image = Image::FromFile("image/balance.png");
		this->pictureBox4->Image = Image::FromFile("image/balance.png");
		this->pictureBox5->Image = Image::FromFile("image/rfid.png");
		this->pictureBox6->Image = Image::FromFile("image/barriere.png");


	}

protected:
	/// <summary>
	/// Nettoyage des ressources utilisées.
	/// </summary>
	~ConfigForm()
	{
		if (_thWaitServerMsg != nullptr)
		{

			_thWaitServerMsg->Abort();
		}
		if (components)
		{
			delete components;
		}

	}
private: System::Windows::Forms::GroupBox^  gbSortie;
private: System::Windows::Forms::GroupBox^  gbBalcanceS;
private: ControlInterface::ControlEtat^  CeBaS;
private: System::Windows::Forms::PictureBox^  pictureBox4;
private: System::Windows::Forms::GroupBox^  gbRFIDs;
private: ControlInterface::ControlEtat^  CeRfS;
private: System::Windows::Forms::PictureBox^  pictureBox5;
private: System::Windows::Forms::GroupBox^  gbBarriereS;
private: ControlInterface::ControlEtat^  CeBrS;
private: System::Windows::Forms::PictureBox^  pictureBox6;
private: System::Windows::Forms::GroupBox^  gbEntree;
private: System::Windows::Forms::ComboBox^  cbInterE;
private: System::Windows::Forms::NumericUpDown^  nudPortE;
private: System::Windows::Forms::GroupBox^  gbBalcanceE;
private: ControlInterface::ControlEtat^  CeBaE;
private: System::Windows::Forms::PictureBox^  pictureBox3;
private: System::Windows::Forms::GroupBox^  gbRFIDe;
private: ControlInterface::ControlEtat^  CeRfE;
private: System::Windows::Forms::PictureBox^  pictureBox2;
private: System::Windows::Forms::GroupBox^  gbBarriereE;
private: ControlInterface::ControlEtat^  CeBrE;
private: System::Windows::Forms::PictureBox^  pictureBox1;
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
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::ComboBox^  cbInterS;
private: System::Windows::Forms::NumericUpDown^  nudPortS;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Button^  btEdit;
private: System::Windows::Forms::Button^  btSav;
private: System::Windows::Forms::GroupBox^  gbBdd;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::TextBox^  tbBddName;
private: System::Windows::Forms::Label^  label11;
private: ControlInterface::ControlIPBox^  tbBddIP;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::NumericUpDown^  nudPortBdd;
private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::TextBox^  tbBddPassword;
private: System::Windows::Forms::TextBox^  tbBddUsername;




private:
	/// <summary>
	/// Variable nécessaire au concepteur.
	/// </summary>
	Boolean _edit = false;
	Thread^ _thWaitServerMsg;
	//EventWaitHandle^ ewh;

	NamedPipeClientStream^ _pipeClient;
	DelegateState^ _DcallBackState;




private: System::Windows::Forms::Timer^  timerUpdate;
private: System::ComponentModel::IContainer^  components;


#pragma region Windows Form Designer generated code
		 /// <summary>
		 /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		 /// le contenu de cette méthode avec l'éditeur de code.
		 /// </summary>

		 void InitializeComponent(void)
		 {
			 this->components = (gcnew System::ComponentModel::Container());
			 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ConfigForm::typeid));
			 this->gbSortie = (gcnew System::Windows::Forms::GroupBox());
			 this->label8 = (gcnew System::Windows::Forms::Label());
			 this->gbBalcanceS = (gcnew System::Windows::Forms::GroupBox());
			 this->label3 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxBaS = (gcnew ControlInterface::ControlIPBox());
			 this->CeBaS = (gcnew ControlInterface::ControlEtat());
			 this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			 this->label9 = (gcnew System::Windows::Forms::Label());
			 this->gbRFIDs = (gcnew System::Windows::Forms::GroupBox());
			 this->label4 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxRfS = (gcnew ControlInterface::ControlIPBox());
			 this->CeRfS = (gcnew ControlInterface::ControlEtat());
			 this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			 this->cbInterS = (gcnew System::Windows::Forms::ComboBox());
			 this->nudPortS = (gcnew System::Windows::Forms::NumericUpDown());
			 this->gbBarriereS = (gcnew System::Windows::Forms::GroupBox());
			 this->label5 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxBrS = (gcnew ControlInterface::ControlIPBox());
			 this->CeBrS = (gcnew ControlInterface::ControlEtat());
			 this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			 this->gbEntree = (gcnew System::Windows::Forms::GroupBox());
			 this->label7 = (gcnew System::Windows::Forms::Label());
			 this->label6 = (gcnew System::Windows::Forms::Label());
			 this->cbInterE = (gcnew System::Windows::Forms::ComboBox());
			 this->nudPortE = (gcnew System::Windows::Forms::NumericUpDown());
			 this->gbBalcanceE = (gcnew System::Windows::Forms::GroupBox());
			 this->l1 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxBaE = (gcnew ControlInterface::ControlIPBox());
			 this->CeBaE = (gcnew ControlInterface::ControlEtat());
			 this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			 this->gbRFIDe = (gcnew System::Windows::Forms::GroupBox());
			 this->label1 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxRfE = (gcnew ControlInterface::ControlIPBox());
			 this->CeRfE = (gcnew ControlInterface::ControlEtat());
			 this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			 this->gbBarriereE = (gcnew System::Windows::Forms::GroupBox());
			 this->label2 = (gcnew System::Windows::Forms::Label());
			 this->controlIPBoxBrE = (gcnew ControlInterface::ControlIPBox());
			 this->CeBrE = (gcnew ControlInterface::ControlEtat());
			 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			 this->btEdit = (gcnew System::Windows::Forms::Button());
			 this->btSav = (gcnew System::Windows::Forms::Button());
			 this->gbBdd = (gcnew System::Windows::Forms::GroupBox());
			 this->label14 = (gcnew System::Windows::Forms::Label());
			 this->label13 = (gcnew System::Windows::Forms::Label());
			 this->tbBddPassword = (gcnew System::Windows::Forms::TextBox());
			 this->tbBddUsername = (gcnew System::Windows::Forms::TextBox());
			 this->label12 = (gcnew System::Windows::Forms::Label());
			 this->tbBddName = (gcnew System::Windows::Forms::TextBox());
			 this->label11 = (gcnew System::Windows::Forms::Label());
			 this->tbBddIP = (gcnew ControlInterface::ControlIPBox());
			 this->label10 = (gcnew System::Windows::Forms::Label());
			 this->nudPortBdd = (gcnew System::Windows::Forms::NumericUpDown());
			 this->timerUpdate = (gcnew System::Windows::Forms::Timer(this->components));
			 this->gbSortie->SuspendLayout();
			 this->gbBalcanceS->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			 this->gbRFIDs->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortS))->BeginInit();
			 this->gbBarriereS->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			 this->gbEntree->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortE))->BeginInit();
			 this->gbBalcanceE->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			 this->gbRFIDe->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			 this->gbBarriereE->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			 this->gbBdd->SuspendLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortBdd))->BeginInit();
			 this->SuspendLayout();
			 // 
			 // gbSortie
			 // 
			 this->gbSortie->Controls->Add(this->label8);
			 this->gbSortie->Controls->Add(this->gbBalcanceS);
			 this->gbSortie->Controls->Add(this->label9);
			 this->gbSortie->Controls->Add(this->gbRFIDs);
			 this->gbSortie->Controls->Add(this->cbInterS);
			 this->gbSortie->Controls->Add(this->nudPortS);
			 this->gbSortie->Controls->Add(this->gbBarriereS);
			 this->gbSortie->Location = System::Drawing::Point(532, 12);
			 this->gbSortie->Name = L"gbSortie";
			 this->gbSortie->Size = System::Drawing::Size(514, 641);
			 this->gbSortie->TabIndex = 5;
			 this->gbSortie->TabStop = false;
			 this->gbSortie->Text = L"Sortie";
			 // 
			 // label8
			 // 
			 this->label8->AutoSize = true;
			 this->label8->Location = System::Drawing::Point(42, 545);
			 this->label8->Name = L"label8";
			 this->label8->Size = System::Drawing::Size(26, 13);
			 this->label8->TabIndex = 16;
			 this->label8->Text = L"Port";
			 // 
			 // gbBalcanceS
			 // 
			 this->gbBalcanceS->Controls->Add(this->label3);
			 this->gbBalcanceS->Controls->Add(this->controlIPBoxBaS);
			 this->gbBalcanceS->Controls->Add(this->CeBaS);
			 this->gbBalcanceS->Controls->Add(this->pictureBox4);
			 this->gbBalcanceS->Location = System::Drawing::Point(6, 353);
			 this->gbBalcanceS->Name = L"gbBalcanceS";
			 this->gbBalcanceS->Size = System::Drawing::Size(485, 161);
			 this->gbBalcanceS->TabIndex = 2;
			 this->gbBalcanceS->TabStop = false;
			 this->gbBalcanceS->Text = L"Balance";
			 // 
			 // label3
			 // 
			 this->label3->AutoSize = true;
			 this->label3->Location = System::Drawing::Point(355, 23);
			 this->label3->Name = L"label3";
			 this->label3->Size = System::Drawing::Size(58, 13);
			 this->label3->TabIndex = 8;
			 this->label3->Text = L"Adresse IP";
			 // 
			 // controlIPBoxBaS
			 // 
			 this->controlIPBoxBaS->IP = L"...";
			 this->controlIPBoxBaS->Location = System::Drawing::Point(322, 39);
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
			 this->CeBaS->Location = System::Drawing::Point(322, 63);
			 this->CeBaS->Name = L"CeBaS";
			 this->CeBaS->Size = System::Drawing::Size(128, 28);
			 this->CeBaS->state = false;
			 this->CeBaS->TabIndex = 7;
			 this->CeBaS->texteSize = 10;
			 this->CeBaS->textFalse = L"Non connecté";
			 this->CeBaS->textTrue = L"Connecté";
			 // 
			 // pictureBox4
			 // 
			 this->pictureBox4->Location = System::Drawing::Point(17, 19);
			 this->pictureBox4->Name = L"pictureBox4";
			 this->pictureBox4->Size = System::Drawing::Size(264, 118);
			 this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			 this->pictureBox4->TabIndex = 0;
			 this->pictureBox4->TabStop = false;
			 // 
			 // label9
			 // 
			 this->label9->AutoSize = true;
			 this->label9->Location = System::Drawing::Point(19, 583);
			 this->label9->Name = L"label9";
			 this->label9->Size = System::Drawing::Size(49, 13);
			 this->label9->TabIndex = 15;
			 this->label9->Text = L"Interface";
			 // 
			 // gbRFIDs
			 // 
			 this->gbRFIDs->Controls->Add(this->label4);
			 this->gbRFIDs->Controls->Add(this->controlIPBoxRfS);
			 this->gbRFIDs->Controls->Add(this->CeRfS);
			 this->gbRFIDs->Controls->Add(this->pictureBox5);
			 this->gbRFIDs->Location = System::Drawing::Point(6, 186);
			 this->gbRFIDs->Name = L"gbRFIDs";
			 this->gbRFIDs->Size = System::Drawing::Size(485, 161);
			 this->gbRFIDs->TabIndex = 2;
			 this->gbRFIDs->TabStop = false;
			 this->gbRFIDs->Text = L"Totem RFID";
			 // 
			 // label4
			 // 
			 this->label4->AutoSize = true;
			 this->label4->Location = System::Drawing::Point(355, 23);
			 this->label4->Name = L"label4";
			 this->label4->Size = System::Drawing::Size(58, 13);
			 this->label4->TabIndex = 9;
			 this->label4->Text = L"Adresse IP";
			 // 
			 // controlIPBoxRfS
			 // 
			 this->controlIPBoxRfS->IP = L"...";
			 this->controlIPBoxRfS->Location = System::Drawing::Point(322, 37);
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
			 this->CeRfS->Location = System::Drawing::Point(322, 63);
			 this->CeRfS->Name = L"CeRfS";
			 this->CeRfS->Size = System::Drawing::Size(128, 28);
			 this->CeRfS->state = false;
			 this->CeRfS->TabIndex = 6;
			 this->CeRfS->texteSize = 10;
			 this->CeRfS->textFalse = L"Non connecté";
			 this->CeRfS->textTrue = L"Connecté";
			 // 
			 // pictureBox5
			 // 
			 this->pictureBox5->Location = System::Drawing::Point(17, 19);
			 this->pictureBox5->Name = L"pictureBox5";
			 this->pictureBox5->Size = System::Drawing::Size(247, 118);
			 this->pictureBox5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			 this->pictureBox5->TabIndex = 0;
			 this->pictureBox5->TabStop = false;
			 // 
			 // cbInterS
			 // 
			 this->cbInterS->FormattingEnabled = true;
			 this->cbInterS->Location = System::Drawing::Point(83, 580);
			 this->cbInterS->Name = L"cbInterS";
			 this->cbInterS->Size = System::Drawing::Size(129, 21);
			 this->cbInterS->TabIndex = 14;
			 // 
			 // nudPortS
			 // 
			 this->nudPortS->Location = System::Drawing::Point(83, 543);
			 this->nudPortS->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			 this->nudPortS->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 this->nudPortS->Name = L"nudPortS";
			 this->nudPortS->Size = System::Drawing::Size(128, 20);
			 this->nudPortS->TabIndex = 13;
			 this->nudPortS->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 // 
			 // gbBarriereS
			 // 
			 this->gbBarriereS->Controls->Add(this->label5);
			 this->gbBarriereS->Controls->Add(this->controlIPBoxBrS);
			 this->gbBarriereS->Controls->Add(this->CeBrS);
			 this->gbBarriereS->Controls->Add(this->pictureBox6);
			 this->gbBarriereS->Location = System::Drawing::Point(6, 19);
			 this->gbBarriereS->Name = L"gbBarriereS";
			 this->gbBarriereS->Size = System::Drawing::Size(485, 161);
			 this->gbBarriereS->TabIndex = 1;
			 this->gbBarriereS->TabStop = false;
			 this->gbBarriereS->Text = L"Barrière";
			 // 
			 // label5
			 // 
			 this->label5->AutoSize = true;
			 this->label5->Location = System::Drawing::Point(355, 23);
			 this->label5->Name = L"label5";
			 this->label5->Size = System::Drawing::Size(58, 13);
			 this->label5->TabIndex = 10;
			 this->label5->Text = L"Adresse IP";
			 // 
			 // controlIPBoxBrS
			 // 
			 this->controlIPBoxBrS->IP = L"...";
			 this->controlIPBoxBrS->Location = System::Drawing::Point(322, 37);
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
			 this->CeBrS->Location = System::Drawing::Point(322, 63);
			 this->CeBrS->Name = L"CeBrS";
			 this->CeBrS->Size = System::Drawing::Size(128, 28);
			 this->CeBrS->state = false;
			 this->CeBrS->TabIndex = 5;
			 this->CeBrS->texteSize = 10;
			 this->CeBrS->textFalse = L"Non connecté";
			 this->CeBrS->textTrue = L"Connecté";
			 // 
			 // pictureBox6
			 // 

			 this->pictureBox6->Location = System::Drawing::Point(17, 19);
			 this->pictureBox6->Name = L"pictureBox6";
			 this->pictureBox6->Size = System::Drawing::Size(247, 118);
			 this->pictureBox6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			 this->pictureBox6->TabIndex = 0;
			 this->pictureBox6->TabStop = false;
			 // 
			 // gbEntree
			 // 
			 this->gbEntree->Controls->Add(this->label7);
			 this->gbEntree->Controls->Add(this->label6);
			 this->gbEntree->Controls->Add(this->cbInterE);
			 this->gbEntree->Controls->Add(this->nudPortE);
			 this->gbEntree->Controls->Add(this->gbBalcanceE);
			 this->gbEntree->Controls->Add(this->gbRFIDe);
			 this->gbEntree->Controls->Add(this->gbBarriereE);
			 this->gbEntree->Location = System::Drawing::Point(12, 12);
			 this->gbEntree->Name = L"gbEntree";
			 this->gbEntree->Size = System::Drawing::Size(514, 641);
			 this->gbEntree->TabIndex = 4;
			 this->gbEntree->TabStop = false;
			 this->gbEntree->Text = L"Entrée";
			 this->gbEntree->Enter += gcnew System::EventHandler(this, &ConfigForm::gbEntree_Enter);
			 // 
			 // label7
			 // 
			 this->label7->AutoSize = true;
			 this->label7->Location = System::Drawing::Point(38, 545);
			 this->label7->Name = L"label7";
			 this->label7->Size = System::Drawing::Size(26, 13);
			 this->label7->TabIndex = 12;
			 this->label7->Text = L"Port";
			 // 
			 // label6
			 // 
			 this->label6->AutoSize = true;
			 this->label6->Location = System::Drawing::Point(15, 583);
			 this->label6->Name = L"label6";
			 this->label6->Size = System::Drawing::Size(49, 13);
			 this->label6->TabIndex = 11;
			 this->label6->Text = L"Interface";
			 // 
			 // cbInterE
			 // 
			 this->cbInterE->FormattingEnabled = true;
			 this->cbInterE->Location = System::Drawing::Point(78, 580);
			 this->cbInterE->Name = L"cbInterE";
			 this->cbInterE->Size = System::Drawing::Size(129, 21);
			 this->cbInterE->TabIndex = 4;
			 // 
			 // nudPortE
			 // 
			 this->nudPortE->Location = System::Drawing::Point(79, 543);
			 this->nudPortE->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			 this->nudPortE->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 this->nudPortE->Name = L"nudPortE";
			 this->nudPortE->Size = System::Drawing::Size(128, 20);
			 this->nudPortE->TabIndex = 3;
			 this->nudPortE->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 // 
			 // gbBalcanceE
			 // 
			 this->gbBalcanceE->Controls->Add(this->l1);
			 this->gbBalcanceE->Controls->Add(this->controlIPBoxBaE);
			 this->gbBalcanceE->Controls->Add(this->CeBaE);
			 this->gbBalcanceE->Controls->Add(this->pictureBox3);
			 this->gbBalcanceE->Location = System::Drawing::Point(6, 353);
			 this->gbBalcanceE->Name = L"gbBalcanceE";
			 this->gbBalcanceE->Size = System::Drawing::Size(485, 161);
			 this->gbBalcanceE->TabIndex = 2;
			 this->gbBalcanceE->TabStop = false;
			 this->gbBalcanceE->Text = L"Balance";
			 // 
			 // l1
			 // 
			 this->l1->AutoSize = true;
			 this->l1->Location = System::Drawing::Point(350, 23);
			 this->l1->Name = L"l1";
			 this->l1->Size = System::Drawing::Size(58, 13);
			 this->l1->TabIndex = 7;
			 this->l1->Text = L"Adresse IP";
			 // 
			 // controlIPBoxBaE
			 // 
			 this->controlIPBoxBaE->IP = L"...";
			 this->controlIPBoxBaE->Location = System::Drawing::Point(319, 39);
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
			 this->CeBaE->Location = System::Drawing::Point(319, 65);
			 this->CeBaE->Name = L"CeBaE";
			 this->CeBaE->Size = System::Drawing::Size(128, 28);
			 this->CeBaE->state = false;
			 this->CeBaE->TabIndex = 4;
			 this->CeBaE->texteSize = 10;
			 this->CeBaE->textFalse = L"Non connecté";
			 this->CeBaE->textTrue = L"Connecté";
			 // 
			 // pictureBox3
			 // 
			 this->pictureBox3->Location = System::Drawing::Point(17, 19);
			 this->pictureBox3->Name = L"pictureBox3";
			 this->pictureBox3->Size = System::Drawing::Size(264, 118);
			 this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			 this->pictureBox3->TabIndex = 0;
			 this->pictureBox3->TabStop = false;
			 // 
			 // gbRFIDe
			 // 
			 this->gbRFIDe->Controls->Add(this->label1);
			 this->gbRFIDe->Controls->Add(this->controlIPBoxRfE);
			 this->gbRFIDe->Controls->Add(this->CeRfE);
			 this->gbRFIDe->Controls->Add(this->pictureBox2);
			 this->gbRFIDe->Location = System::Drawing::Point(6, 186);
			 this->gbRFIDe->Name = L"gbRFIDe";
			 this->gbRFIDe->Size = System::Drawing::Size(485, 161);
			 this->gbRFIDe->TabIndex = 2;
			 this->gbRFIDe->TabStop = false;
			 this->gbRFIDe->Text = L"Totem RFID";
			 // 
			 // label1
			 // 
			 this->label1->AutoSize = true;
			 this->label1->Location = System::Drawing::Point(350, 23);
			 this->label1->Name = L"label1";
			 this->label1->Size = System::Drawing::Size(58, 13);
			 this->label1->TabIndex = 8;
			 this->label1->Text = L"Adresse IP";
			 // 
			 // controlIPBoxRfE
			 // 
			 this->controlIPBoxRfE->IP = L"...";
			 this->controlIPBoxRfE->Location = System::Drawing::Point(319, 39);
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
			 this->CeRfE->Location = System::Drawing::Point(319, 65);
			 this->CeRfE->Name = L"CeRfE";
			 this->CeRfE->Size = System::Drawing::Size(128, 28);
			 this->CeRfE->state = false;
			 this->CeRfE->TabIndex = 3;
			 this->CeRfE->texteSize = 10;
			 this->CeRfE->textFalse = L"Non connecté";
			 this->CeRfE->textTrue = L"Connecté";
			 // 
			 // pictureBox2
			 // 
			 this->pictureBox2->Location = System::Drawing::Point(17, 19);
			 this->pictureBox2->Name = L"pictureBox2";
			 this->pictureBox2->Size = System::Drawing::Size(247, 118);
			 this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			 this->pictureBox2->TabIndex = 0;
			 this->pictureBox2->TabStop = false;
			 // 
			 // gbBarriereE
			 // 
			 this->gbBarriereE->Controls->Add(this->label2);
			 this->gbBarriereE->Controls->Add(this->controlIPBoxBrE);
			 this->gbBarriereE->Controls->Add(this->CeBrE);
			 this->gbBarriereE->Controls->Add(this->pictureBox1);
			 this->gbBarriereE->Location = System::Drawing::Point(6, 19);
			 this->gbBarriereE->Name = L"gbBarriereE";
			 this->gbBarriereE->Size = System::Drawing::Size(485, 161);
			 this->gbBarriereE->TabIndex = 1;
			 this->gbBarriereE->TabStop = false;
			 this->gbBarriereE->Text = L"Barrière";
			 // 
			 // label2
			 // 
			 this->label2->AutoSize = true;
			 this->label2->Location = System::Drawing::Point(350, 23);
			 this->label2->Name = L"label2";
			 this->label2->Size = System::Drawing::Size(58, 13);
			 this->label2->TabIndex = 9;
			 this->label2->Text = L"Adresse IP";
			 // 
			 // controlIPBoxBrE
			 // 
			 this->controlIPBoxBrE->IP = L"...";
			 this->controlIPBoxBrE->Location = System::Drawing::Point(319, 39);
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
			 this->CeBrE->Location = System::Drawing::Point(319, 66);
			 this->CeBrE->Name = L"CeBrE";
			 this->CeBrE->Size = System::Drawing::Size(128, 28);
			 this->CeBrE->state = false;
			 this->CeBrE->TabIndex = 2;
			 this->CeBrE->texteSize = 10;
			 this->CeBrE->textFalse = L"Non connecté";
			 this->CeBrE->textTrue = L"Connecté";
			 // 
			 // pictureBox1
			 // 
			 this->pictureBox1->Location = System::Drawing::Point(17, 19);
			 this->pictureBox1->Name = L"pictureBox1";
			 this->pictureBox1->Size = System::Drawing::Size(247, 118);
			 this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			 this->pictureBox1->TabIndex = 0;
			 this->pictureBox1->TabStop = false;
			 // 
			 // btEdit
			 // 
			 this->btEdit->Location = System::Drawing::Point(12, 757);
			 this->btEdit->Name = L"btEdit";
			 this->btEdit->Size = System::Drawing::Size(75, 23);
			 this->btEdit->TabIndex = 6;
			 this->btEdit->Text = L"Edit";
			 this->btEdit->UseVisualStyleBackColor = true;
			 this->btEdit->Click += gcnew System::EventHandler(this, &ConfigForm::btEdit_Click);
			 // 
			 // btSav
			 // 
			 this->btSav->Location = System::Drawing::Point(93, 757);
			 this->btSav->Name = L"btSav";
			 this->btSav->Size = System::Drawing::Size(75, 23);
			 this->btSav->TabIndex = 7;
			 this->btSav->Text = L"Sauvegarde";
			 this->btSav->UseVisualStyleBackColor = true;
			 this->btSav->Click += gcnew System::EventHandler(this, &ConfigForm::btSav_Click);
			 // 
			 // gbBdd
			 // 
			 this->gbBdd->Controls->Add(this->label14);
			 this->gbBdd->Controls->Add(this->label13);
			 this->gbBdd->Controls->Add(this->tbBddPassword);
			 this->gbBdd->Controls->Add(this->tbBddUsername);
			 this->gbBdd->Controls->Add(this->label12);
			 this->gbBdd->Controls->Add(this->tbBddName);
			 this->gbBdd->Controls->Add(this->label11);
			 this->gbBdd->Controls->Add(this->tbBddIP);
			 this->gbBdd->Controls->Add(this->label10);
			 this->gbBdd->Controls->Add(this->nudPortBdd);
			 this->gbBdd->Location = System::Drawing::Point(12, 660);
			 this->gbBdd->Name = L"gbBdd";
			 this->gbBdd->Size = System::Drawing::Size(1034, 91);
			 this->gbBdd->TabIndex = 8;
			 this->gbBdd->TabStop = false;
			 this->gbBdd->Text = L"Base de donnée";
			 // 
			 // label14
			 // 
			 this->label14->AutoSize = true;
			 this->label14->Location = System::Drawing::Point(817, 30);
			 this->label14->Name = L"label14";
			 this->label14->Size = System::Drawing::Size(71, 13);
			 this->label14->TabIndex = 20;
			 this->label14->Text = L"Mot de passe";
			 // 
			 // label13
			 // 
			 this->label13->AutoSize = true;
			 this->label13->Location = System::Drawing::Point(627, 30);
			 this->label13->Name = L"label13";
			 this->label13->Size = System::Drawing::Size(84, 13);
			 this->label13->TabIndex = 19;
			 this->label13->Text = L"Nom d\'utilisateur";
			 // 
			 // tbBddPassword
			 // 
			 this->tbBddPassword->Location = System::Drawing::Point(820, 46);
			 this->tbBddPassword->Name = L"tbBddPassword";
			 this->tbBddPassword->Size = System::Drawing::Size(132, 20);
			 this->tbBddPassword->TabIndex = 18;
			 this->tbBddPassword->UseSystemPasswordChar = true;
			 // 
			 // tbBddUsername
			 // 
			 this->tbBddUsername->Location = System::Drawing::Point(630, 46);
			 this->tbBddUsername->Name = L"tbBddUsername";
			 this->tbBddUsername->Size = System::Drawing::Size(132, 20);
			 this->tbBddUsername->TabIndex = 17;
			 // 
			 // label12
			 // 
			 this->label12->AutoSize = true;
			 this->label12->Location = System::Drawing::Point(438, 30);
			 this->label12->Name = L"label12";
			 this->label12->Size = System::Drawing::Size(135, 13);
			 this->label12->TabIndex = 16;
			 this->label12->Text = L"Nom de la base de donnée";
			 // 
			 // tbBddName
			 // 
			 this->tbBddName->Location = System::Drawing::Point(441, 46);
			 this->tbBddName->Name = L"tbBddName";
			 this->tbBddName->Size = System::Drawing::Size(132, 20);
			 this->tbBddName->TabIndex = 15;
			 // 
			 // label11
			 // 
			 this->label11->AutoSize = true;
			 this->label11->Location = System::Drawing::Point(95, 30);
			 this->label11->Name = L"label11";
			 this->label11->Size = System::Drawing::Size(58, 13);
			 this->label11->TabIndex = 9;
			 this->label11->Text = L"Adresse IP";
			 // 
			 // tbBddIP
			 // 
			 this->tbBddIP->IP = L"...";
			 this->tbBddIP->Location = System::Drawing::Point(98, 48);
			 this->tbBddIP->Name = L"tbBddIP";
			 this->tbBddIP->Size = System::Drawing::Size(128, 18);
			 this->tbBddIP->TabIndex = 9;
			 // 
			 // label10
			 // 
			 this->label10->AutoSize = true;
			 this->label10->Location = System::Drawing::Point(259, 30);
			 this->label10->Name = L"label10";
			 this->label10->Size = System::Drawing::Size(26, 13);
			 this->label10->TabIndex = 14;
			 this->label10->Text = L"Port";
			 // 
			 // nudPortBdd
			 // 
			 this->nudPortBdd->Location = System::Drawing::Point(262, 46);
			 this->nudPortBdd->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
			 this->nudPortBdd->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 this->nudPortBdd->Name = L"nudPortBdd";
			 this->nudPortBdd->Size = System::Drawing::Size(128, 20);
			 this->nudPortBdd->TabIndex = 13;
			 this->nudPortBdd->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			 // 
			 // timerUpdate
			 // 
			 this->timerUpdate->Enabled = true;
			 this->timerUpdate->Interval = 200;
			 this->timerUpdate->Tick += gcnew System::EventHandler(this, &ConfigForm::timerUpdate_Tick);
			 // 
			 // ConfigForm
			 // 
			 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			 this->ClientSize = System::Drawing::Size(1058, 792);
			 this->Controls->Add(this->gbBdd);
			 this->Controls->Add(this->btSav);
			 this->Controls->Add(this->btEdit);
			 this->Controls->Add(this->gbSortie);
			 this->Controls->Add(this->gbEntree);
			 this->Name = L"ConfigForm";
			 this->Text = L"ConfigForm";
			 this->Load += gcnew System::EventHandler(this, &ConfigForm::ConfigForm_Load);
			 this->gbSortie->ResumeLayout(false);
			 this->gbSortie->PerformLayout();
			 this->gbBalcanceS->ResumeLayout(false);
			 this->gbBalcanceS->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			 this->gbRFIDs->ResumeLayout(false);
			 this->gbRFIDs->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortS))->EndInit();
			 this->gbBarriereS->ResumeLayout(false);
			 this->gbBarriereS->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			 this->gbEntree->ResumeLayout(false);
			 this->gbEntree->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortE))->EndInit();
			 this->gbBalcanceE->ResumeLayout(false);
			 this->gbBalcanceE->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			 this->gbRFIDe->ResumeLayout(false);
			 this->gbRFIDe->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			 this->gbBarriereE->ResumeLayout(false);
			 this->gbBarriereE->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			 this->gbBdd->ResumeLayout(false);
			 this->gbBdd->PerformLayout();
			 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortBdd))->EndInit();
			 this->ResumeLayout(false);

		 }
#pragma endregion
private: System::Void gbEntree_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void btSav_Click(System::Object^  sender, System::EventArgs^  e) {
	DataConfigServeur^ cs = gcnew DataConfigServeur();
	cs->Entree->IPBalance = this->controlIPBoxBaE->IP;
	cs->Sortie->IPBalance = this->controlIPBoxBaS->IP;

	cs->Entree->IPBarriere = this->controlIPBoxBrE->IP;
	cs->Sortie->IPBarriere = this->controlIPBoxBrS->IP;

	cs->Entree->IPRFID = this->controlIPBoxRfE->IP;
	cs->Sortie->IPRFID = this->controlIPBoxRfS->IP;

	cs->Entree->portServeur = Convert::ToInt32(this->nudPortE->Value);
	cs->Sortie->portServeur = Convert::ToInt32(this->nudPortS->Value);

	cs->Entree->Interface = ((IPAddress^)cbInterE->SelectedItem)->ToString();
	cs->Entree->Interface = ((IPAddress^)cbInterE->SelectedItem)->ToString();

	cs->NomBDD = tbBddName->Text;
	cs->UsernameBDD = tbBddUsername->Text;
	cs->PasswordBDD = tbBddPassword->Text;
	cs->IPBDD = tbBddIP->IP;
	cs->PortBDD = Convert::ToInt32(this->nudPortBdd->Value);
	FileStream^ fs;
	bool fileOpened = false;
	XmlSerializer^ serializer = gcnew XmlSerializer(DataConfigServeur::typeid);
	do
	{
		try
		{
			fileOpened = false;
			fs = File::Open((String^)FILE_CONFIG, System::IO::FileMode::Create);

		}
		catch (...)
		{
			Console::WriteLine("[ Save Configuration ] Erreur à l'ouverture de " + FILE_CONFIG);
			fileOpened = true;
		}
	} while (fileOpened);

	serializer->Serialize(fs, cs);
	fs->Close();
	_edit = false;



}
private: System::Void btEdit_Click(System::Object^  sender, System::EventArgs^  e) {
	_edit = true;
}
private: System::Void timerUpdate_Tick(System::Object^  sender, System::EventArgs^  e) {
	if (_edit)
	{
		//if (_thWaitServerMsg != nullptr)
		//{
		//	ewh->Set();
		//}
		controlIPBoxBaE->Enabled = true;
		controlIPBoxBaS->Enabled = true;
		controlIPBoxBrE->Enabled = true;
		controlIPBoxBrS->Enabled = true;
		controlIPBoxRfE->Enabled = true;
		controlIPBoxRfS->Enabled = true;
		nudPortBdd->Enabled = true;
		nudPortE->Enabled = true;
		nudPortS->Enabled = true;
		tbBddIP->Enabled = true;
		tbBddName->Enabled = true;
		tbBddPassword->Enabled = true;
		tbBddUsername->Enabled = true;
		cbInterE->Enabled = true;
		cbInterS->Enabled = true;
		CeBaE->Visible = false;
		CeBaS->Visible = false;
		CeBrE->Visible = false;
		CeBrS->Visible = false;
		CeRfE->Visible = false;
		CeRfS->Visible = false;

	}
	else
	{
		//if (_thWaitServerMsg != nullptr )
		//{
		//	ewh->Reset();
		//}
		controlIPBoxBaE->Enabled = false;
		controlIPBoxBaS->Enabled = false;
		controlIPBoxBrE->Enabled = false;
		controlIPBoxBrS->Enabled = false;
		controlIPBoxRfE->Enabled = false;
		controlIPBoxRfS->Enabled = false;
		nudPortBdd->Enabled = false;
		nudPortE->Enabled = false;
		nudPortS->Enabled = false;
		tbBddIP->Enabled = false;
		tbBddName->Enabled = false;
		tbBddPassword->Enabled = false;
		tbBddUsername->Enabled = false;
		cbInterE->Enabled = false;
		cbInterS->Enabled = false;
		CeBaE->Visible = true;
		CeBaS->Visible = true;
		CeBrE->Visible = true;
		CeBrS->Visible = true;
		CeRfE->Visible = true;
		CeRfS->Visible = true;
	}
}
private: System::Void ConfigForm_Load(System::Object^  sender, System::EventArgs^  e) {

	searchInterface();

	if (System::IO::File::Exists(FILE_CONFIG))
	{
		FileStream^ fs;
		bool fileOpened = false;
		do
		{
			try
			{
				fileOpened = false;
				fs = File::Open((String^)FILE_CONFIG, System::IO::FileMode::Open);

			}
			catch (...)
			{
				Console::WriteLine("[ Configuration ] Erreur à l'ouverture de " + FILE_CONFIG);
				fileOpened = true;
			}
		} while (fileOpened);
		XmlSerializer^ serializer = gcnew XmlSerializer(DataConfigServeur::typeid);
		DataConfigServeur^ cs = (DataConfigServeur^)serializer->Deserialize(fs);
		fs->Close();
		controlIPBoxBaE->IP = cs->Entree->IPBalance;
		controlIPBoxBrE->IP = cs->Entree->IPBarriere;
		controlIPBoxRfE->IP = cs->Entree->IPRFID;
		cbInterE->SelectedItem = IPAddress::Parse(cs->Entree->Interface);
		nudPortE->Value = cs->Entree->portServeur;

		controlIPBoxBaS->IP = cs->Sortie->IPBalance;
		controlIPBoxBrS->IP = cs->Sortie->IPBarriere;
		controlIPBoxRfS->IP = cs->Sortie->IPRFID;
		cbInterS->SelectedItem = IPAddress::Parse(cs->Sortie->Interface);
		nudPortS->Value = cs->Sortie->portServeur;

		tbBddIP->IP = cs->IPBDD;
		tbBddName->Text = cs->NomBDD;
		tbBddPassword->Text = cs->PasswordBDD;
		tbBddUsername->Text = cs->UsernameBDD;
		nudPortBdd->Value = cs->PortBDD;

		_edit = false;


	}
	else
	{
		_edit = true;
	}
	_thWaitServerMsg = gcnew Thread(gcnew ThreadStart(this, &ConfigForm::fctThreadWaitMsgServ));
	_thWaitServerMsg->Name = "ThreadWait msg state Srv";
	_thWaitServerMsg->Start();
}

private: void searchInterface()
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
private: void fctThreadWaitMsgServ()
{
	Thread::Sleep(500);
	bool serverStart = false;
	do
	{
		array<Process^>^ listProcess = Process::GetProcessesByName(SRV_PROCESS_NAME);
		for each (Process^ var in listProcess)
		{
			Console::WriteLine(var->ToString());
			if (var->ToString() == "System.Diagnostics.Process (" + SRV_PROCESS_NAME + ")")
			{
				_pipeClient = gcnew NamedPipeClientStream(".", PIPE_NAME_STATE_SERV, PipeDirection::InOut);
				try
					//Console::WriteLine(_pipeClient->IsConnected);
				{
					_pipeClient->Connect();
					serverStart = true;

				}
				catch (...)
				{

				}
				break;
			}

		}
	} while (!serverStart);

	while (true)
	{
		//Console::WriteLine(_pipeClient->IsConnected);
		if (_pipeClient->IsConnected)
		{
			array<Byte>^ buffer = gcnew array<Byte>(6);
			_pipeClient->Read(buffer, 0, 6);
			Console::WriteLine("[ Client State Srv ] Reception ");
			Invoke(_DcallBackState, buffer);

		}
		else
		{
			_pipeClient->Close();
			Console::WriteLine("[ Client State Srv ] Connexion interrompu");

			try
			{
				_pipeClient->Connect();
				Console::WriteLine("[ Client State Srv ] Reconnexion");
			}
			catch (...)
			{
				Thread::Sleep(500);
			}

		}
	}
}
private: void callbackState(array<Byte>^ t)
{
	if (t[0] == 1) { CeBrE->state = true; }
	else { CeBrE->state = false; }
	if (t[2] == 1) { CeRfE->state = true; }
	else { CeRfE->state = false; }
	if (t[1] == 1) { CeBaE->state = true; }
	else { CeBaE->state = false; }
	if (t[3] == 1) { CeBrS->state = true; }
	else { CeBrS->state = false; }
	if (t[5] == 1) { CeRfS->state = true; }
	else { CeRfS->state = false; }
	if (t[4] == 1) { CeBaS->state = true; }
	else { CeBaS->state = false; }

}

};


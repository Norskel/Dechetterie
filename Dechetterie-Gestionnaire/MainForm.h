#pragma once
#include "ConfigBddForm.h"
#include "BDD.h"
#define FILE_CONFIG "Config.xml"

	using namespace System;
	using namespace System::Windows;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	using namespace System::Threading;

	static public enum class userFonction : int { nonDef, NEW, EDIT,VIEW };

	delegate void GetRFIDIDDelegate(String^ id);

	/// <summary>
	/// Description résumée de MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{

		
	public:
		MainForm(void)
		{
			InitializeComponent();



			this->btClose->BackgroundImage = Image::FromFile("Icon/icons8-fermer.png");
			this->btConfig->BackgroundImage = Image::FromFile("Icon/icons8-Config.png");

			this->btSave->BackgroundImage = Image::FromFile("Icon/icons8-save.png");
			this->btDelete->BackgroundImage = Image::FromFile("Icon/icons8-deleteUser.png");			
			this->btEdit->BackgroundImage = Image::FromFile("Icon/icons8-editUser.png");			
			this->btStat->BackgroundImage = Image::FromFile("Icon/icons8-stats.png");
			this->btFacture->BackgroundImage = Image::FromFile("Icon/icons8-facture.png");

			this->btUser->Image = Image::FromFile("Icon/icons8-User.png");
			this->btDechet->Image = Image::FromFile("Icon/icons8-dechet.png");
			this->btFact->Image = Image::FromFile("Icon/icons8-facture.png");






			if (!System::IO::File::Exists(FILE_CONFIG))
			{
				if (_configBddForm->IsDisposed)
				{
					_configBddForm = gcnew ConfigBddForm();
				}
				_configBddForm->ShowDialog();
				_bdd->connect();

			}
			else
			{
				_bdd->connect();

			}
			getRFID += gcnew GetRFIDIDDelegate(this, &MainForm::editRFID);
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::IO::Ports::SerialPort^  serialPort1;

	private: System::Windows::Forms::Panel^  panelUser;




	private: System::ComponentModel::IContainer^  components;




	private: System::Windows::Forms::DataGridView^  dgvUser;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  id;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nom;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  prenom;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  id_rfid;
	private: System::Windows::Forms::Panel^  panelUserInfo;









	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::NumericUpDown^  nudNum;
	private: System::Windows::Forms::NumericUpDown^  nudCodePostal;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  tbVille;
	private: System::Windows::Forms::TextBox^  tbRue;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  tbRFID;
	private: System::Windows::Forms::TextBox^  tbPrenom;
	private: System::Windows::Forms::TextBox^  tbNom;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::DataGridView^  dgvUserHistorique;
	private: System::Windows::Forms::Button^  btAdd;



	private: System::Windows::Forms::Timer^  timerUpdateUserInterface;

			 ConfigBddForm^ _configBddForm = gcnew ConfigBddForm();
			 userFonction _editUser = userFonction::nonDef;
			 int _userSelectedID = -1;
			 BDD^ _bdd = BDD::getBdd();
			 int nbUser = 0;
			 DataUser^ _userSelected = nullptr;



	private: System::Windows::Forms::Panel^  panelHeader;
	private: System::Windows::Forms::Button^  btClose;







	private: System::Windows::Forms::Panel^  panel1;

private: System::Windows::Forms::Button^  btConfig;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  date;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  poids;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  typeDechet;
private: System::Windows::Forms::Button^  btDelete;
private: System::Windows::Forms::Button^  btStat;


private: System::Windows::Forms::Button^  btSave;
private: System::Windows::Forms::Button^  btFacture;




private: System::Windows::Forms::Button^  btEdit;
private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
private: System::Windows::Forms::Button^  btUser;



private: System::Windows::Forms::Button^  btDechet;
private: System::Windows::Forms::Button^  btFact;





			 GetRFIDIDDelegate^ getRFID;

			 
				

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->panelUser = (gcnew System::Windows::Forms::Panel());
			this->panelUserInfo = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->btEdit = (gcnew System::Windows::Forms::Button());
			this->btDelete = (gcnew System::Windows::Forms::Button());
			this->btSave = (gcnew System::Windows::Forms::Button());
			this->btStat = (gcnew System::Windows::Forms::Button());
			this->btFacture = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->nudNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->nudCodePostal = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->tbVille = (gcnew System::Windows::Forms::TextBox());
			this->tbRue = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->tbRFID = (gcnew System::Windows::Forms::TextBox());
			this->tbPrenom = (gcnew System::Windows::Forms::TextBox());
			this->tbNom = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->dgvUserHistorique = (gcnew System::Windows::Forms::DataGridView());
			this->date = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->poids = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->typeDechet = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btAdd = (gcnew System::Windows::Forms::Button());
			this->dgvUser = (gcnew System::Windows::Forms::DataGridView());
			this->id = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nom = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->prenom = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->id_rfid = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->timerUpdateUserInterface = (gcnew System::Windows::Forms::Timer(this->components));
			this->panelHeader = (gcnew System::Windows::Forms::Panel());
			this->btClose = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->btDechet = (gcnew System::Windows::Forms::Button());
			this->btFact = (gcnew System::Windows::Forms::Button());
			this->btConfig = (gcnew System::Windows::Forms::Button());
			this->btUser = (gcnew System::Windows::Forms::Button());
			this->panelUser->SuspendLayout();
			this->panelUserInfo->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudCodePostal))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvUserHistorique))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvUser))->BeginInit();
			this->panelHeader->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 2400;
			this->serialPort1->PortName = L"COM10";
			this->serialPort1->ReadBufferSize = 12;
			this->serialPort1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &MainForm::serialPort1_DataReceived);
			// 
			// panelUser
			// 
			this->panelUser->Controls->Add(this->panelUserInfo);
			this->panelUser->Controls->Add(this->btAdd);
			this->panelUser->Controls->Add(this->dgvUser);
			this->panelUser->Location = System::Drawing::Point(332, 38);
			this->panelUser->Name = L"panelUser";
			this->panelUser->Size = System::Drawing::Size(1184, 589);
			this->panelUser->TabIndex = 1;
			this->panelUser->Visible = false;
			// 
			// panelUserInfo
			// 
			this->panelUserInfo->Controls->Add(this->flowLayoutPanel1);
			this->panelUserInfo->Controls->Add(this->label10);
			this->panelUserInfo->Controls->Add(this->label9);
			this->panelUserInfo->Controls->Add(this->label8);
			this->panelUserInfo->Controls->Add(this->nudNum);
			this->panelUserInfo->Controls->Add(this->nudCodePostal);
			this->panelUserInfo->Controls->Add(this->label7);
			this->panelUserInfo->Controls->Add(this->label6);
			this->panelUserInfo->Controls->Add(this->tbVille);
			this->panelUserInfo->Controls->Add(this->tbRue);
			this->panelUserInfo->Controls->Add(this->label5);
			this->panelUserInfo->Controls->Add(this->label4);
			this->panelUserInfo->Controls->Add(this->label3);
			this->panelUserInfo->Controls->Add(this->label2);
			this->panelUserInfo->Controls->Add(this->tbRFID);
			this->panelUserInfo->Controls->Add(this->tbPrenom);
			this->panelUserInfo->Controls->Add(this->tbNom);
			this->panelUserInfo->Controls->Add(this->label1);
			this->panelUserInfo->Controls->Add(this->dgvUserHistorique);
			this->panelUserInfo->Location = System::Drawing::Point(677, 0);
			this->panelUserInfo->Name = L"panelUserInfo";
			this->panelUserInfo->Size = System::Drawing::Size(533, 586);
			this->panelUserInfo->TabIndex = 2;
			this->panelUserInfo->Visible = false;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->btEdit);
			this->flowLayoutPanel1->Controls->Add(this->btDelete);
			this->flowLayoutPanel1->Controls->Add(this->btSave);
			this->flowLayoutPanel1->Controls->Add(this->btStat);
			this->flowLayoutPanel1->Controls->Add(this->btFacture);
			this->flowLayoutPanel1->Location = System::Drawing::Point(453, 0);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(77, 346);
			this->flowLayoutPanel1->TabIndex = 27;
			// 
			// btEdit
			// 
			this->btEdit->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btEdit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btEdit->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->btEdit->Location = System::Drawing::Point(3, 3);
			this->btEdit->Name = L"btEdit";
			this->btEdit->Size = System::Drawing::Size(62, 62);
			this->btEdit->TabIndex = 11;
			this->btEdit->UseVisualStyleBackColor = true;
			this->btEdit->Click += gcnew System::EventHandler(this, &MainForm::btEdit_Click);
			// 
			// btDelete
			// 
			this->btDelete->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btDelete->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->btDelete->Location = System::Drawing::Point(3, 71);
			this->btDelete->Name = L"btDelete";
			this->btDelete->Size = System::Drawing::Size(62, 62);
			this->btDelete->TabIndex = 26;
			this->btDelete->UseVisualStyleBackColor = true;
			this->btDelete->Click += gcnew System::EventHandler(this, &MainForm::btDelete_Click);
			// 
			// btSave
			// 
			this->btSave->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btSave->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btSave->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->btSave->Location = System::Drawing::Point(3, 139);
			this->btSave->Name = L"btSave";
			this->btSave->Size = System::Drawing::Size(62, 62);
			this->btSave->TabIndex = 24;
			this->btSave->UseVisualStyleBackColor = true;
			this->btSave->Click += gcnew System::EventHandler(this, &MainForm::btSave_Click);
			// 
			// btStat
			// 
			this->btStat->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btStat->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btStat->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->btStat->Location = System::Drawing::Point(3, 207);
			this->btStat->Name = L"btStat";
			this->btStat->Size = System::Drawing::Size(62, 62);
			this->btStat->TabIndex = 25;
			this->btStat->UseVisualStyleBackColor = true;
			this->btStat->Click += gcnew System::EventHandler(this, &MainForm::btStat_Click);
			// 
			// btFacture
			// 
			this->btFacture->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btFacture->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btFacture->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->btFacture->Location = System::Drawing::Point(3, 275);
			this->btFacture->Name = L"btFacture";
			this->btFacture->Size = System::Drawing::Size(62, 62);
			this->btFacture->TabIndex = 23;
			this->btFacture->UseVisualStyleBackColor = true;
			this->btFacture->Click += gcnew System::EventHandler(this, &MainForm::btFacture_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(26, 304);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(100, 26);
			this->label10->TabIndex = 17;
			this->label10->Text = L"Historique";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(28, 176);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(45, 13);
			this->label9->TabIndex = 16;
			this->label9->Text = L"Numero";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(28, 254);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(63, 13);
			this->label8->TabIndex = 15;
			this->label8->Text = L"Code Postal";
			// 
			// nudNum
			// 
			this->nudNum->Location = System::Drawing::Point(116, 174);
			this->nudNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->nudNum->Name = L"nudNum";
			this->nudNum->Size = System::Drawing::Size(187, 20);
			this->nudNum->TabIndex = 14;
			// 
			// nudCodePostal
			// 
			this->nudCodePostal->Location = System::Drawing::Point(116, 252);
			this->nudCodePostal->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999999, 0, 0, 0 });
			this->nudCodePostal->Name = L"nudCodePostal";
			this->nudCodePostal->Size = System::Drawing::Size(187, 20);
			this->nudCodePostal->TabIndex = 13;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(29, 229);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(28, 13);
			this->label7->TabIndex = 12;
			this->label7->Text = L"Ville";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(29, 203);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(25, 13);
			this->label6->TabIndex = 11;
			this->label6->Text = L"Rue";
			// 
			// tbVille
			// 
			this->tbVille->Location = System::Drawing::Point(116, 226);
			this->tbVille->Name = L"tbVille";
			this->tbVille->Size = System::Drawing::Size(187, 20);
			this->tbVille->TabIndex = 9;
			// 
			// tbRue
			// 
			this->tbRue->Location = System::Drawing::Point(116, 200);
			this->tbRue->Name = L"tbRue";
			this->tbRue->Size = System::Drawing::Size(187, 20);
			this->tbRue->TabIndex = 8;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(59, 143);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(45, 13);
			this->label5->TabIndex = 7;
			this->label5->Text = L"Adresse";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(29, 82);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(44, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Prenom";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(29, 108);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(40, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"ID RFID";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(29, 59);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(29, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Nom";
			// 
			// tbRFID
			// 
			this->tbRFID->Location = System::Drawing::Point(116, 105);
			this->tbRFID->MaxLength = 10;
			this->tbRFID->Name = L"tbRFID";
			this->tbRFID->Size = System::Drawing::Size(187, 20);
			this->tbRFID->TabIndex = 4;
			// 
			// tbPrenom
			// 
			this->tbPrenom->Location = System::Drawing::Point(116, 79);
			this->tbPrenom->Name = L"tbPrenom";
			this->tbPrenom->Size = System::Drawing::Size(187, 20);
			this->tbPrenom->TabIndex = 3;
			// 
			// tbNom
			// 
			this->tbNom->Location = System::Drawing::Point(116, 53);
			this->tbNom->Name = L"tbNom";
			this->tbNom->Size = System::Drawing::Size(187, 20);
			this->tbNom->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(16, 14);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(118, 26);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Information ";
			// 
			// dgvUserHistorique
			// 
			this->dgvUserHistorique->AllowUserToAddRows = false;
			this->dgvUserHistorique->AllowUserToDeleteRows = false;
			this->dgvUserHistorique->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvUserHistorique->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->date,
					this->poids, this->typeDechet
			});
			this->dgvUserHistorique->Location = System::Drawing::Point(21, 343);
			this->dgvUserHistorique->Name = L"dgvUserHistorique";
			this->dgvUserHistorique->ReadOnly = true;
			this->dgvUserHistorique->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
			this->dgvUserHistorique->Size = System::Drawing::Size(500, 216);
			this->dgvUserHistorique->TabIndex = 0;
			// 
			// date
			// 
			this->date->HeaderText = L"Date";
			this->date->MinimumWidth = 120;
			this->date->Name = L"date";
			this->date->ReadOnly = true;
			this->date->Width = 120;
			// 
			// poids
			// 
			this->poids->HeaderText = L"Poids";
			this->poids->MinimumWidth = 80;
			this->poids->Name = L"poids";
			this->poids->ReadOnly = true;
			// 
			// typeDechet
			// 
			this->typeDechet->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->typeDechet->HeaderText = L"Type de dêchet";
			this->typeDechet->MinimumWidth = 80;
			this->typeDechet->Name = L"typeDechet";
			this->typeDechet->ReadOnly = true;
			// 
			// btAdd
			// 
			this->btAdd->Location = System::Drawing::Point(246, 535);
			this->btAdd->Name = L"btAdd";
			this->btAdd->Size = System::Drawing::Size(120, 23);
			this->btAdd->TabIndex = 1;
			this->btAdd->Text = L"Ajouter un utilisateur";
			this->btAdd->UseVisualStyleBackColor = true;
			this->btAdd->Click += gcnew System::EventHandler(this, &MainForm::btAdd_Click);
			// 
			// dgvUser
			// 
			this->dgvUser->AllowUserToAddRows = false;
			this->dgvUser->AllowUserToDeleteRows = false;
			this->dgvUser->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dgvUser->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->id, this->nom,
					this->prenom, this->id_rfid
			});
			this->dgvUser->Location = System::Drawing::Point(73, 23);
			this->dgvUser->Name = L"dgvUser";
			this->dgvUser->ReadOnly = true;
			this->dgvUser->Size = System::Drawing::Size(533, 464);
			this->dgvUser->TabIndex = 0;
			this->dgvUser->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::dgvUser_CellClick);
			// 
			// id
			// 
			this->id->FillWeight = 20;
			this->id->HeaderText = L"ID";
			this->id->Name = L"id";
			this->id->ReadOnly = true;
			// 
			// nom
			// 
			this->nom->HeaderText = L"Nom";
			this->nom->Name = L"nom";
			this->nom->ReadOnly = true;
			// 
			// prenom
			// 
			this->prenom->HeaderText = L"Prenom";
			this->prenom->Name = L"prenom";
			this->prenom->ReadOnly = true;
			// 
			// id_rfid
			// 
			this->id_rfid->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->id_rfid->HeaderText = L"ID RFID";
			this->id_rfid->Name = L"id_rfid";
			this->id_rfid->ReadOnly = true;
			// 
			// timerUpdateUserInterface
			// 
			this->timerUpdateUserInterface->Tick += gcnew System::EventHandler(this, &MainForm::timerUpdateUserInterface_Tick);
			// 
			// panelHeader
			// 
			this->panelHeader->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)));
			this->panelHeader->Controls->Add(this->btClose);
			this->panelHeader->Dock = System::Windows::Forms::DockStyle::Top;
			this->panelHeader->Location = System::Drawing::Point(0, 0);
			this->panelHeader->Name = L"panelHeader";
			this->panelHeader->Size = System::Drawing::Size(1516, 38);
			this->panelHeader->TabIndex = 5;
			this->panelHeader->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panelHeader_MouseDown);
			this->panelHeader->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panelHeader_MouseMove);
			this->panelHeader->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panelHeader_MouseUp);
			// 
			// btClose
			// 
			this->btClose->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btClose->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(31)));
			this->btClose->Location = System::Drawing::Point(1481, 3);
			this->btClose->Name = L"btClose";
			this->btClose->Size = System::Drawing::Size(32, 32);
			this->btClose->TabIndex = 0;
			this->btClose->UseVisualStyleBackColor = true;
			this->btClose->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->panel1->Controls->Add(this->btDechet);
			this->panel1->Controls->Add(this->btFact);
			this->panel1->Controls->Add(this->btConfig);
			this->panel1->Controls->Add(this->btUser);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel1->Location = System::Drawing::Point(0, 38);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(335, 589);
			this->panel1->TabIndex = 9;
			// 
			// btDechet
			// 
			this->btDechet->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->btDechet->FlatAppearance->BorderSize = 0;
			this->btDechet->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btDechet->Font = (gcnew System::Drawing::Font(L"Calibri", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btDechet->ForeColor = System::Drawing::Color::White;
			this->btDechet->Location = System::Drawing::Point(0, 114);
			this->btDechet->Margin = System::Windows::Forms::Padding(0);
			this->btDechet->Name = L"btDechet";
			this->btDechet->Size = System::Drawing::Size(317, 108);
			this->btDechet->TabIndex = 13;
			this->btDechet->Text = L"Dechet";
			this->btDechet->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->btDechet->UseVisualStyleBackColor = false;
			// 
			// btFact
			// 
			this->btFact->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->btFact->FlatAppearance->BorderSize = 0;
			this->btFact->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btFact->Font = (gcnew System::Drawing::Font(L"Calibri", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btFact->ForeColor = System::Drawing::Color::White;
			this->btFact->Location = System::Drawing::Point(0, 229);
			this->btFact->Margin = System::Windows::Forms::Padding(0);
			this->btFact->Name = L"btFact";
			this->btFact->Size = System::Drawing::Size(317, 108);
			this->btFact->TabIndex = 12;
			this->btFact->Text = L"Facture";
			this->btFact->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->btFact->UseVisualStyleBackColor = false;
			// 
			// btConfig
			// 
			this->btConfig->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->btConfig->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btConfig->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(60)), static_cast<System::Int32>(static_cast<System::Byte>(60)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->btConfig->Location = System::Drawing::Point(12, 343);
			this->btConfig->Name = L"btConfig";
			this->btConfig->Size = System::Drawing::Size(62, 62);
			this->btConfig->TabIndex = 9;
			this->btConfig->UseVisualStyleBackColor = true;
			this->btConfig->Click += gcnew System::EventHandler(this, &MainForm::btConfig_Click);
			// 
			// btUser
			// 
			this->btUser->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->btUser->FlatAppearance->BorderSize = 0;
			this->btUser->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btUser->Font = (gcnew System::Drawing::Font(L"Calibri", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btUser->ForeColor = System::Drawing::Color::White;
			this->btUser->Location = System::Drawing::Point(0, 0);
			this->btUser->Margin = System::Windows::Forms::Padding(0);
			this->btUser->Name = L"btUser";
			this->btUser->Size = System::Drawing::Size(317, 108);
			this->btUser->TabIndex = 11;
			this->btUser->Text = L"Utilisateur";
			this->btUser->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
			this->btUser->UseVisualStyleBackColor = false;
			this->btUser->Click += gcnew System::EventHandler(this, &MainForm::button1_Click_1);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(40)));
			this->ClientSize = System::Drawing::Size(1516, 627);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->panelUser);
			this->Controls->Add(this->panelHeader);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MainForm";
			this->panelUser->ResumeLayout(false);
			this->panelUserInfo->ResumeLayout(false);
			this->panelUserInfo->PerformLayout();
			this->flowLayoutPanel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudCodePostal))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvUserHistorique))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvUser))->EndInit();
			this->panelHeader->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {
		if (_editUser == userFonction::NEW || _editUser == userFonction::EDIT)
		{
			SerialPort^ sp = (SerialPort^)sender;
			
			String^ indata = sp->ReadExisting();
			Console::Write(indata);
			Invoke(getRFID, indata);
			Thread::Sleep(1000);
			
			
		}
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		serialPort1->Open();
	}
	private: System::Void baseDeDonnéeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if (_configBddForm->IsDisposed)
		{
			_configBddForm = gcnew ConfigBddForm();
		}
		_configBddForm->Show();
	}
	private: System::Void dgvUser_CellClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		
		Console::WriteLine(dgvUser->Rows[e->RowIndex]->Cells[0]->Value + " "+ dgvUser->Rows[e->RowIndex]->Cells[1]->Value);
		_userSelectedID = Convert::ToInt64(dgvUser->Rows[e->RowIndex]->Cells[0]->Value);
		_userSelected = _bdd->getUserByID(_userSelectedID);
		_editUser = userFonction::VIEW;
		dgvUserHistorique->Rows->Clear();
		for each (DataHistorique^ var in _bdd->getTableHistoriqueByIdUser(_userSelectedID))
		{
			
			dgvUserHistorique->Rows->Add(var->dt, var->Poids, _bdd->getDechetByID(var->ID_Dechet)->Nom);
		}

		tbNom->Text = _userSelected->Nom;
		tbPrenom->Text = _userSelected->Prenom;
		tbRFID->Text = _userSelected->ID_RFID;

		tbVille->Text = _userSelected->Ville;
		tbRue->Text = _userSelected->Adresse;
		nudNum->Value = _userSelected->numero;
		nudCodePostal->Value = _userSelected->Code_Postal;

	}

	private: System::Void btEdit_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		_editUser = userFonction::EDIT;
	}
	private: System::Void btDelete_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		_bdd->deleteUserByID(_userSelectedID);
	}
	private: System::Void btSave_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if (_editUser == userFonction::NEW)
		{
			_userSelected = nullptr;
			_userSelected = gcnew DataUser();
		}

		_userSelected->Nom = tbNom->Text;
		_userSelected->Prenom = tbPrenom->Text;
		_userSelected->ID_RFID = tbRFID->Text;

		_userSelected->Ville = tbVille->Text;
		_userSelected->Adresse = tbRue->Text;
		_userSelected->numero = Convert::ToInt64(nudNum->Value);
		_userSelected->Code_Postal = Convert::ToInt64(nudCodePostal->Value);

		switch (_editUser)
		{
		case userFonction::NEW: //new
			_bdd->addUser(_userSelected);

			break;
		case userFonction::EDIT: //edit
			_bdd->updateUser(_userSelected);
			break;

		}
		_editUser = userFonction::VIEW;
		nbUser = -1;
		
	}
	private: System::Void btStat_Click(System::Object^  sender, System::EventArgs^  e) 
	{

	}
	private: System::Void btFacture_Click(System::Object^  sender, System::EventArgs^  e) 
	{

	}
	private: System::Void btAdd_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		tbNom->Text = "";
		tbPrenom->Text = "";
		tbRFID->Text = "";

		tbVille->Text = "";
		tbRue->Text = "";
		nudNum->Value = 0;
		nudCodePostal->Value = 0;
		_editUser = userFonction::NEW;

	}

	private: System::Void timerUpdateUserInterface_Tick(System::Object^  sender, System::EventArgs^  e) 
	{
		switch (_editUser)
		{
		case userFonction::nonDef:
			panelUserInfo->Visible = false;
			break;
		case userFonction::NEW: // new
			panelUserInfo->Visible = true;
			dgvUserHistorique->Visible = false;

			btAdd->Enabled = false;
			btDelete->Enabled = false;
			btEdit->Enabled = false;
			btFacture->Enabled = false;
			btStat->Enabled = false;
			btSave->Enabled = true;

			btDelete->Visible = false;
			btEdit->Visible = false;
			btFacture->Visible = false;
			btStat->Visible = false;
			btSave->Visible = true;

			tbNom->Enabled = true;
			tbPrenom->Enabled = true;
			tbRFID->Enabled = true;
			tbRue->Enabled = true;
			tbVille->Enabled = true;
			nudNum->Enabled = true;
			nudCodePostal->Enabled = true;

		
			break;
		case userFonction::EDIT: // edit
			panelUserInfo->Visible = true;
			dgvUserHistorique->Visible = false;

			btAdd->Enabled = false;
			btDelete->Enabled = false;
			btEdit->Enabled = false;
			btFacture->Enabled = false;
			btStat->Enabled = false;
			btSave->Enabled = true;

			btDelete->Visible = false;
			btEdit->Visible = false;
			btFacture->Visible = false;
			btStat->Visible = false;
			btSave->Visible = true;

			tbNom->Enabled = true;
			tbPrenom->Enabled = true;
			tbRFID->Enabled = true;
			tbRue->Enabled = true;
			tbVille->Enabled = true;
			nudNum->Enabled = true;
			nudCodePostal->Enabled = true;

			break;
		case userFonction::VIEW: // view
			panelUserInfo->Visible = true;
			dgvUserHistorique->Visible = true;

			btAdd->Enabled = true;
			btDelete->Enabled = true;
			btEdit->Enabled = true;
			btFacture->Enabled = true;
			btStat->Enabled = true;
			btSave->Enabled = true;

			btAdd->Visible = true;
			btDelete->Visible = true;
			btEdit->Visible = true;
			btFacture->Visible = true;
			btStat->Visible = true;
			btSave->Visible = false;

			tbNom->Enabled = false;
			tbPrenom->Enabled = false;
			tbRFID->Enabled = false;
			tbRue->Enabled = false;
			tbVille->Enabled = false;
			nudNum->Enabled = false;
			nudCodePostal->Enabled = false;
			break;



		}
		Console::Write(dgvUserHistorique->Columns[0]->Width + " ");
		Console::Write(dgvUserHistorique->Columns[1]->Width + " ");
		Console::WriteLine(dgvUserHistorique->Columns[2]->Width);
		List<DataUser^>^ t = _bdd->getTableUser("");
		if (nbUser != t->Count)
		{
			nbUser = t->Count;
			dgvUser->Rows->Clear();
			for each (DataUser^ var in t)
			{
				dgvUser->Rows->Add(var->ID, var->Nom, var->Prenom, var->ID_RFID);
			}
		}

		if (_editUser == userFonction::VIEW && _userSelected != nullptr)
		{

		}



	}
			 void editRFID(String^ id)
			 {
				 if (_editUser == userFonction::NEW || _editUser == userFonction::EDIT)
				 {
					 if (id->Length  > 10 && id[0] == '\n')
					 {
						 Console::WriteLine("Delagate :::");

						 Console::Write(id);
						 id = id->Remove(11);
						 id = id->Remove(0, 1);
						 Console::Write(id);
						 tbRFID->Text = id;
					 }

				 }
			 }
	private: System::Void btDechet_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		panelUser->Visible = false;
		//panelDechet->Visible = true;
		timerUpdateUserInterface->Enabled = false;
	}

	private: bool mouseDown;
	private: Point lastLocation;
	private: System::Void panelHeader_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		mouseDown = true;
		lastLocation = e->Location;
	}
	private: System::Void panelHeader_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		mouseDown = false;
	}
	private: System::Void panelHeader_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		if (mouseDown)
		{
			this->Location = Point((this->Location.X - lastLocation.X) + e->X, (this->Location.Y - lastLocation.Y) + e->Y);
			this->Update();
		}
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->Close();
	}
	private: System::Void controlButtonIcon1_OnClick(System::Object^  sender, System::Int32 e) {
	panelUser->Visible = true;
	//panelDechet->Visible = false;
	timerUpdateUserInterface->Enabled = true;
}
	private: System::Void btConfig_Click(System::Object^  sender, System::EventArgs^  e) {
	if (_configBddForm->IsDisposed)
	{
		_configBddForm = gcnew ConfigBddForm();
	}
	_configBddForm->Show();
}
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		panelUser->Visible = true;
		//panelDechet->Visible = false;
		timerUpdateUserInterface->Enabled = true;
	}
};


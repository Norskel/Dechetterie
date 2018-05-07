#pragma once
#include "BDD.h"


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace MySql::Data::MySqlClient;

	/// <summary>
	/// Description résumée de MainForm
	/// </summary>

	static public enum class informationMode : int { nonDef, NEW, EDIT, VIEW };

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			bddConnection = BDD::getBdd();
			bddConnection->connect();
			InitializeComponent();
			updateUserList("");
			updateInformation(1, informationMode::nonDef);
			userLv->FullRowSelect = true;
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

	private: BDD^ bddConnection;
			 informationMode imode = informationMode::nonDef;
			 int user_id_select = 0;
	private: System::Windows::Forms::ListView^  userLv;




	protected:
	private: System::Windows::Forms::ColumnHeader^  chNom;
	private: System::Windows::Forms::ColumnHeader^  chPrenom;
	private: System::Windows::Forms::ColumnHeader^  chIdRfid;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::Panel^  userPanel;


	private: System::Windows::Forms::Button^  userBtAddUser;
	private: System::Windows::Forms::Panel^  userPanelInfo;


	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  optionToolStripMenuItem;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::NumericUpDown^  userNudNum;
	private: System::Windows::Forms::NumericUpDown^  userNudCodePostal;


	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  userTbVille;

	private: System::Windows::Forms::TextBox^  userTbRue;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  userTbRFID;

	private: System::Windows::Forms::TextBox^  userTbPrenom;

	private: System::Windows::Forms::TextBox^  userTbNom;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ListView^  userLvHist;


	private: System::Windows::Forms::ColumnHeader^  chHistDate;
	private: System::Windows::Forms::ColumnHeader^  chHistPoids;
	private: System::Windows::Forms::ColumnHeader^  chHistDechet;
	private: System::Windows::Forms::TextBox^  userTbSearch;

	private: System::Windows::Forms::Button^  userBtDelUser;
	private: System::Windows::Forms::Panel^  userPanelTextBoxInfo;
	private: System::Windows::Forms::Panel^  userPanelHistorique;






	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::ColumnHeader^  chID;
	private: System::Windows::Forms::Panel^  userPanelSav;

	private: System::Windows::Forms::Button^  userBtSav;
	private: System::Windows::Forms::Button^  userBtSavAnnuler;
	private: System::Windows::Forms::Button^  userBtStats;
	private: System::Windows::Forms::Button^  userBtFactures;
	private: System::Windows::Forms::Button^  userBtEdit;
	private: System::Windows::Forms::Panel^  userPanelBt;
private: System::Windows::Forms::TabPage^  tabPage3;
private: System::Windows::Forms::DataVisualization::Charting::Chart^  statsChartQuantiter;
private: System::Windows::Forms::DataGridView^  userDgvFacture;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  userDgvFactureDate;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  userDgvFactureTotal;
private: System::Windows::Forms::DataGridViewButtonColumn^  userDgvFactureBt;







	protected:

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->chID = (gcnew System::Windows::Forms::ColumnHeader());
			this->userLv = (gcnew System::Windows::Forms::ListView());
			this->chNom = (gcnew System::Windows::Forms::ColumnHeader());
			this->chPrenom = (gcnew System::Windows::Forms::ColumnHeader());
			this->chIdRfid = (gcnew System::Windows::Forms::ColumnHeader());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->userPanel = (gcnew System::Windows::Forms::Panel());
			this->userTbSearch = (gcnew System::Windows::Forms::TextBox());
			this->userBtDelUser = (gcnew System::Windows::Forms::Button());
			this->userBtAddUser = (gcnew System::Windows::Forms::Button());
			this->userPanelInfo = (gcnew System::Windows::Forms::Panel());
			this->userPanelBt = (gcnew System::Windows::Forms::Panel());
			this->userBtEdit = (gcnew System::Windows::Forms::Button());
			this->userBtStats = (gcnew System::Windows::Forms::Button());
			this->userBtFactures = (gcnew System::Windows::Forms::Button());
			this->userPanelSav = (gcnew System::Windows::Forms::Panel());
			this->userBtSav = (gcnew System::Windows::Forms::Button());
			this->userBtSavAnnuler = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->userPanelHistorique = (gcnew System::Windows::Forms::Panel());
			this->userDgvFacture = (gcnew System::Windows::Forms::DataGridView());
			this->userDgvFactureDate = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->userDgvFactureTotal = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->userDgvFactureBt = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->userLvHist = (gcnew System::Windows::Forms::ListView());
			this->chHistDate = (gcnew System::Windows::Forms::ColumnHeader());
			this->chHistPoids = (gcnew System::Windows::Forms::ColumnHeader());
			this->chHistDechet = (gcnew System::Windows::Forms::ColumnHeader());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->userPanelTextBoxInfo = (gcnew System::Windows::Forms::Panel());
			this->userTbNom = (gcnew System::Windows::Forms::TextBox());
			this->userTbPrenom = (gcnew System::Windows::Forms::TextBox());
			this->userTbRFID = (gcnew System::Windows::Forms::TextBox());
			this->userNudNum = (gcnew System::Windows::Forms::NumericUpDown());
			this->userNudCodePostal = (gcnew System::Windows::Forms::NumericUpDown());
			this->userTbVille = (gcnew System::Windows::Forms::TextBox());
			this->userTbRue = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->statsChartQuantiter = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->optionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->userPanel->SuspendLayout();
			this->userPanelInfo->SuspendLayout();
			this->userPanelBt->SuspendLayout();
			this->userPanelSav->SuspendLayout();
			this->userPanelHistorique->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->userDgvFacture))->BeginInit();
			this->userPanelTextBoxInfo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->userNudNum))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->userNudCodePostal))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->statsChartQuantiter))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// chID
			// 
			this->chID->Text = L"ID";
			this->chID->Width = 0;
			// 
			// userLv
			// 
			this->userLv->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(4) {
				this->chNom, this->chPrenom,
					this->chIdRfid, this->chID
			});
			this->userLv->GridLines = true;
			this->userLv->Location = System::Drawing::Point(15, 38);
			this->userLv->Name = L"userLv";
			this->userLv->Size = System::Drawing::Size(476, 507);
			this->userLv->TabIndex = 0;
			this->userLv->UseCompatibleStateImageBehavior = false;
			this->userLv->View = System::Windows::Forms::View::Details;
			this->userLv->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::userLv_SelectedIndexChanged);
			// 
			// chNom
			// 
			this->chNom->Text = L"Nom";
			this->chNom->Width = 120;
			// 
			// chPrenom
			// 
			this->chPrenom->Text = L"Prénom";
			this->chPrenom->Width = 120;
			// 
			// chIdRfid
			// 
			this->chIdRfid->Text = L"ID RFID";
			this->chIdRfid->Width = 99;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(531, 379);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 24);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1499, 585);
			this->tabControl1->TabIndex = 2;
			this->tabControl1->Click += gcnew System::EventHandler(this, &MainForm::tabControl1_Click);
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->userPanel);
			this->tabPage1->Controls->Add(this->userPanelInfo);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1491, 559);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Utilisateur";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// userPanel
			// 
			this->userPanel->Controls->Add(this->userTbSearch);
			this->userPanel->Controls->Add(this->userBtDelUser);
			this->userPanel->Controls->Add(this->userBtAddUser);
			this->userPanel->Controls->Add(this->userLv);
			this->userPanel->Dock = System::Windows::Forms::DockStyle::Left;
			this->userPanel->Location = System::Drawing::Point(3, 3);
			this->userPanel->Name = L"userPanel";
			this->userPanel->Size = System::Drawing::Size(506, 553);
			this->userPanel->TabIndex = 2;
			// 
			// userTbSearch
			// 
			this->userTbSearch->Location = System::Drawing::Point(291, 9);
			this->userTbSearch->Name = L"userTbSearch";
			this->userTbSearch->Size = System::Drawing::Size(200, 20);
			this->userTbSearch->TabIndex = 3;
			this->userTbSearch->TextChanged += gcnew System::EventHandler(this, &MainForm::userTbSearch_TextChanged);
			// 
			// userBtDelUser
			// 
			this->userBtDelUser->Location = System::Drawing::Point(144, 9);
			this->userBtDelUser->Name = L"userBtDelUser";
			this->userBtDelUser->Size = System::Drawing::Size(123, 23);
			this->userBtDelUser->TabIndex = 2;
			this->userBtDelUser->Text = L"Supprimer l\'utilisateur";
			this->userBtDelUser->UseVisualStyleBackColor = true;
			this->userBtDelUser->Click += gcnew System::EventHandler(this, &MainForm::userBtDelUser_Click);
			// 
			// userBtAddUser
			// 
			this->userBtAddUser->Location = System::Drawing::Point(15, 9);
			this->userBtAddUser->Name = L"userBtAddUser";
			this->userBtAddUser->Size = System::Drawing::Size(123, 23);
			this->userBtAddUser->TabIndex = 1;
			this->userBtAddUser->Text = L"Ajouter un utilisateur";
			this->userBtAddUser->UseVisualStyleBackColor = true;
			this->userBtAddUser->Click += gcnew System::EventHandler(this, &MainForm::userBtAddUser_Click);
			// 
			// userPanelInfo
			// 
			this->userPanelInfo->Controls->Add(this->userPanelBt);
			this->userPanelInfo->Controls->Add(this->userPanelSav);
			this->userPanelInfo->Controls->Add(this->label1);
			this->userPanelInfo->Controls->Add(this->userPanelHistorique);
			this->userPanelInfo->Controls->Add(this->label9);
			this->userPanelInfo->Controls->Add(this->userPanelTextBoxInfo);
			this->userPanelInfo->Controls->Add(this->label5);
			this->userPanelInfo->Controls->Add(this->label8);
			this->userPanelInfo->Controls->Add(this->label6);
			this->userPanelInfo->Controls->Add(this->label4);
			this->userPanelInfo->Controls->Add(this->label7);
			this->userPanelInfo->Controls->Add(this->label2);
			this->userPanelInfo->Controls->Add(this->label3);
			this->userPanelInfo->Dock = System::Windows::Forms::DockStyle::Right;
			this->userPanelInfo->Location = System::Drawing::Point(515, 3);
			this->userPanelInfo->Name = L"userPanelInfo";
			this->userPanelInfo->Size = System::Drawing::Size(973, 553);
			this->userPanelInfo->TabIndex = 1;
			// 
			// userPanelBt
			// 
			this->userPanelBt->Controls->Add(this->userBtEdit);
			this->userPanelBt->Controls->Add(this->userBtStats);
			this->userPanelBt->Controls->Add(this->userBtFactures);
			this->userPanelBt->Location = System::Drawing::Point(361, 9);
			this->userPanelBt->Name = L"userPanelBt";
			this->userPanelBt->Size = System::Drawing::Size(103, 100);
			this->userPanelBt->TabIndex = 39;
			// 
			// userBtEdit
			// 
			this->userBtEdit->Location = System::Drawing::Point(5, 3);
			this->userBtEdit->Name = L"userBtEdit";
			this->userBtEdit->Size = System::Drawing::Size(95, 23);
			this->userBtEdit->TabIndex = 36;
			this->userBtEdit->Text = L"Editer";
			this->userBtEdit->UseVisualStyleBackColor = true;
			this->userBtEdit->Click += gcnew System::EventHandler(this, &MainForm::userBtEdit_Click);
			// 
			// userBtStats
			// 
			this->userBtStats->Location = System::Drawing::Point(5, 68);
			this->userBtStats->Name = L"userBtStats";
			this->userBtStats->Size = System::Drawing::Size(95, 23);
			this->userBtStats->TabIndex = 38;
			this->userBtStats->Text = L"Statistique";
			this->userBtStats->UseVisualStyleBackColor = true;
			// 
			// userBtFactures
			// 
			this->userBtFactures->Location = System::Drawing::Point(5, 45);
			this->userBtFactures->Name = L"userBtFactures";
			this->userBtFactures->Size = System::Drawing::Size(95, 23);
			this->userBtFactures->TabIndex = 37;
			this->userBtFactures->Text = L"Factures";
			this->userBtFactures->UseVisualStyleBackColor = true;
			// 
			// userPanelSav
			// 
			this->userPanelSav->Controls->Add(this->userBtSav);
			this->userPanelSav->Controls->Add(this->userBtSavAnnuler);
			this->userPanelSav->Location = System::Drawing::Point(366, 241);
			this->userPanelSav->Name = L"userPanelSav";
			this->userPanelSav->Size = System::Drawing::Size(103, 63);
			this->userPanelSav->TabIndex = 35;
			this->userPanelSav->Visible = false;
			// 
			// userBtSav
			// 
			this->userBtSav->Location = System::Drawing::Point(3, 29);
			this->userBtSav->Name = L"userBtSav";
			this->userBtSav->Size = System::Drawing::Size(95, 23);
			this->userBtSav->TabIndex = 1;
			this->userBtSav->Text = L"Sauvegarder";
			this->userBtSav->UseVisualStyleBackColor = true;
			this->userBtSav->Click += gcnew System::EventHandler(this, &MainForm::userBtSav_Click);
			// 
			// userBtSavAnnuler
			// 
			this->userBtSavAnnuler->Location = System::Drawing::Point(3, 4);
			this->userBtSavAnnuler->Name = L"userBtSavAnnuler";
			this->userBtSavAnnuler->Size = System::Drawing::Size(95, 23);
			this->userBtSavAnnuler->TabIndex = 0;
			this->userBtSavAnnuler->Text = L"Annuler";
			this->userBtSavAnnuler->UseVisualStyleBackColor = true;
			this->userBtSavAnnuler->Click += gcnew System::EventHandler(this, &MainForm::userBtSavAnnuler_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::Black;
			this->label1->Location = System::Drawing::Point(26, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(118, 26);
			this->label1->TabIndex = 17;
			this->label1->Text = L"Information ";
			// 
			// userPanelHistorique
			// 
			this->userPanelHistorique->Controls->Add(this->userDgvFacture);
			this->userPanelHistorique->Controls->Add(this->label10);
			this->userPanelHistorique->Controls->Add(this->userLvHist);
			this->userPanelHistorique->Location = System::Drawing::Point(12, 310);
			this->userPanelHistorique->Name = L"userPanelHistorique";
			this->userPanelHistorique->Size = System::Drawing::Size(956, 235);
			this->userPanelHistorique->TabIndex = 34;
			// 
			// userDgvFacture
			// 
			this->userDgvFacture->AllowUserToAddRows = false;
			this->userDgvFacture->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->userDgvFacture->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->userDgvFactureDate,
					this->userDgvFactureTotal, this->userDgvFactureBt
			});
			this->userDgvFacture->Location = System::Drawing::Point(475, 49);
			this->userDgvFacture->Name = L"userDgvFacture";
			this->userDgvFacture->ReadOnly = true;
			this->userDgvFacture->Size = System::Drawing::Size(343, 183);
			this->userDgvFacture->TabIndex = 34;
			this->userDgvFacture->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::userDgvFacture_CellContentClick);
			// 
			// userDgvFactureDate
			// 
			this->userDgvFactureDate->HeaderText = L"Date";
			this->userDgvFactureDate->Name = L"userDgvFactureDate";
			this->userDgvFactureDate->ReadOnly = true;
			// 
			// userDgvFactureTotal
			// 
			this->userDgvFactureTotal->HeaderText = L"Total";
			this->userDgvFactureTotal->Name = L"userDgvFactureTotal";
			this->userDgvFactureTotal->ReadOnly = true;
			// 
			// userDgvFactureBt
			// 
			this->userDgvFactureBt->HeaderText = L"Afficher";
			this->userDgvFactureBt->Name = L"userDgvFactureBt";
			this->userDgvFactureBt->ReadOnly = true;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Calibri", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::Black;
			this->label10->Location = System::Drawing::Point(14, 16);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(100, 26);
			this->label10->TabIndex = 33;
			this->label10->Text = L"Historique";
			// 
			// userLvHist
			// 
			this->userLvHist->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->chHistDate, this->chHistPoids,
					this->chHistDechet
			});
			this->userLvHist->GridLines = true;
			this->userLvHist->Location = System::Drawing::Point(3, 49);
			this->userLvHist->Name = L"userLvHist";
			this->userLvHist->Size = System::Drawing::Size(451, 183);
			this->userLvHist->TabIndex = 2;
			this->userLvHist->UseCompatibleStateImageBehavior = false;
			this->userLvHist->View = System::Windows::Forms::View::Details;
			// 
			// chHistDate
			// 
			this->chHistDate->Text = L"Date";
			this->chHistDate->Width = 120;
			// 
			// chHistPoids
			// 
			this->chHistPoids->Text = L"Poids";
			this->chHistPoids->Width = 120;
			// 
			// chHistDechet
			// 
			this->chHistDechet->Text = L"Type de dechet";
			this->chHistDechet->Width = 99;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::Black;
			this->label9->Location = System::Drawing::Point(38, 171);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(59, 18);
			this->label9->TabIndex = 32;
			this->label9->Text = L"Numero";
			// 
			// userPanelTextBoxInfo
			// 
			this->userPanelTextBoxInfo->Controls->Add(this->userTbNom);
			this->userPanelTextBoxInfo->Controls->Add(this->userTbPrenom);
			this->userPanelTextBoxInfo->Controls->Add(this->userTbRFID);
			this->userPanelTextBoxInfo->Controls->Add(this->userNudNum);
			this->userPanelTextBoxInfo->Controls->Add(this->userNudCodePostal);
			this->userPanelTextBoxInfo->Controls->Add(this->userTbVille);
			this->userPanelTextBoxInfo->Controls->Add(this->userTbRue);
			this->userPanelTextBoxInfo->Location = System::Drawing::Point(132, 50);
			this->userPanelTextBoxInfo->Name = L"userPanelTextBoxInfo";
			this->userPanelTextBoxInfo->Size = System::Drawing::Size(190, 224);
			this->userPanelTextBoxInfo->TabIndex = 33;
			// 
			// userTbNom
			// 
			this->userTbNom->Location = System::Drawing::Point(0, 0);
			this->userTbNom->Name = L"userTbNom";
			this->userTbNom->Size = System::Drawing::Size(187, 20);
			this->userTbNom->TabIndex = 18;
			// 
			// userTbPrenom
			// 
			this->userTbPrenom->Location = System::Drawing::Point(0, 26);
			this->userTbPrenom->Name = L"userTbPrenom";
			this->userTbPrenom->Size = System::Drawing::Size(187, 20);
			this->userTbPrenom->TabIndex = 19;
			// 
			// userTbRFID
			// 
			this->userTbRFID->Location = System::Drawing::Point(0, 52);
			this->userTbRFID->MaxLength = 10;
			this->userTbRFID->Name = L"userTbRFID";
			this->userTbRFID->Size = System::Drawing::Size(187, 20);
			this->userTbRFID->TabIndex = 20;
			// 
			// userNudNum
			// 
			this->userNudNum->Location = System::Drawing::Point(0, 121);
			this->userNudNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->userNudNum->Name = L"userNudNum";
			this->userNudNum->Size = System::Drawing::Size(187, 20);
			this->userNudNum->TabIndex = 30;
			// 
			// userNudCodePostal
			// 
			this->userNudCodePostal->Location = System::Drawing::Point(0, 199);
			this->userNudCodePostal->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999999, 0, 0, 0 });
			this->userNudCodePostal->Name = L"userNudCodePostal";
			this->userNudCodePostal->Size = System::Drawing::Size(187, 20);
			this->userNudCodePostal->TabIndex = 29;
			// 
			// userTbVille
			// 
			this->userTbVille->Location = System::Drawing::Point(0, 173);
			this->userTbVille->Name = L"userTbVille";
			this->userTbVille->Size = System::Drawing::Size(187, 20);
			this->userTbVille->TabIndex = 26;
			// 
			// userTbRue
			// 
			this->userTbRue->Location = System::Drawing::Point(0, 147);
			this->userTbRue->Name = L"userTbRue";
			this->userTbRue->Size = System::Drawing::Size(187, 20);
			this->userTbRue->TabIndex = 25;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::Black;
			this->label5->Location = System::Drawing::Point(62, 138);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(58, 18);
			this->label5->TabIndex = 24;
			this->label5->Text = L"Adresse";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::Black;
			this->label8->Location = System::Drawing::Point(38, 249);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(81, 18);
			this->label8->TabIndex = 31;
			this->label8->Text = L"Code Postal";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::Black;
			this->label6->Location = System::Drawing::Point(39, 198);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(32, 18);
			this->label6->TabIndex = 27;
			this->label6->Text = L"Rue";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::Black;
			this->label4->Location = System::Drawing::Point(39, 77);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(57, 18);
			this->label4->TabIndex = 22;
			this->label4->Text = L"Prenom";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::Black;
			this->label7->Location = System::Drawing::Point(39, 224);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(37, 18);
			this->label7->TabIndex = 28;
			this->label7->Text = L"Ville";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::Black;
			this->label2->Location = System::Drawing::Point(39, 54);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(38, 18);
			this->label2->TabIndex = 21;
			this->label2->Text = L"Nom";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Calibri", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::Black;
			this->label3->Location = System::Drawing::Point(39, 103);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(52, 18);
			this->label3->TabIndex = 23;
			this->label3->Text = L"ID RFID";
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(1491, 559);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->statsChartQuantiter);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(1491, 559);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"tabPage3";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// statsChartQuantiter
			// 
			chartArea1->Name = L"ChartArea1";
			this->statsChartQuantiter->ChartAreas->Add(chartArea1);
			this->statsChartQuantiter->Location = System::Drawing::Point(58, 47);
			this->statsChartQuantiter->Name = L"statsChartQuantiter";
			this->statsChartQuantiter->Size = System::Drawing::Size(300, 300);
			this->statsChartQuantiter->TabIndex = 0;
			this->statsChartQuantiter->Text = L"chart1";
			title1->Name = L"Title1";
			title1->Text = L"Dechets";
			this->statsChartQuantiter->Titles->Add(title1);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->optionToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1499, 24);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// optionToolStripMenuItem
			// 
			this->optionToolStripMenuItem->Name = L"optionToolStripMenuItem";
			this->optionToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->optionToolStripMenuItem->Text = L"Option";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1499, 609);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->userPanel->ResumeLayout(false);
			this->userPanel->PerformLayout();
			this->userPanelInfo->ResumeLayout(false);
			this->userPanelInfo->PerformLayout();
			this->userPanelBt->ResumeLayout(false);
			this->userPanelSav->ResumeLayout(false);
			this->userPanelHistorique->ResumeLayout(false);
			this->userPanelHistorique->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->userDgvFacture))->EndInit();
			this->userPanelTextBoxInfo->ResumeLayout(false);
			this->userPanelTextBoxInfo->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->userNudNum))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->userNudCodePostal))->EndInit();
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->statsChartQuantiter))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	void updateUserList(String^ search)
	{
		if (bddConnection->ping())
		{
			userLv->Items->Clear();
			for each (DataUser^ var in bddConnection->getTableUser(search))
			{
				ListViewItem^ lvi = gcnew ListViewItem(var->Nom);
				lvi->SubItems->Add(var->Prenom);
				lvi->SubItems->Add(var->ID_RFID);
				lvi->SubItems->Add(var->ID.ToString());

				userLv->Items->Add(lvi);
			}
		}
	}
	void updateFactureList(int idUser)
	{
		userDgvFacture->Rows->Clear();
		List<DataFacture^>^ ldf = gcnew List<DataFacture^>;
		ldf = bddConnection->getFacture(idUser);
		for each (DataFacture^ var in ldf)
		{

			float t = 0;
			for each (DataHistorique^ var in var->listHistorique)
			{
				t += (var->Poids) * (bddConnection->getDechetByID(var->ID_Dechet)->Prix);

			}
			userDgvFacture->Rows->Add(var->dt->ToString("MM/yyyy"), Convert::ToString(t)+" €");

			
		}
	}
	//void updateFactureList(int idUser)
	//{
	//	userDgvFacture->Rows->Clear();
	//	List<DataFacture^>^ ldf = gcnew List<DataFacture^>;
	//	ldf = bddConnection->getFacture(idUser);
	//	for each (DataFacture^ var in ldf)
	//	{
	//		userDgvFacture->Rows->Add(var->dt->ToString("MM/yyyy"));
	//	}
	//}

	void updateInformation(int idUser, informationMode mode)
	{
		DataUser^ du = gcnew DataUser();
		switch (mode)
		{
		case informationMode::nonDef:
			userPanelInfo->Visible = false;


			break;
		case informationMode::NEW:
			userPanelInfo->Visible = true;
			userPanelHistorique->Visible = false;
			userPanelTextBoxInfo->Visible = true;
			userPanelTextBoxInfo->Enabled = true;
			userPanelSav->Visible = true;
			userPanelBt->Visible = false;

			break;
		case informationMode::EDIT:
			userPanelInfo->Visible = true;
			userPanelHistorique->Visible = false;
			userPanelTextBoxInfo->Visible = true;
			userPanelTextBoxInfo->Enabled = true;
			userPanelSav->Visible = true;
			userPanelBt->Visible = false;

			du = bddConnection->getUserByID(idUser);

			userTbNom->Text = du->Nom;
			userTbPrenom->Text = du->Prenom;
			userTbRFID->Text = du->ID_RFID;

			userTbVille->Text = du->Ville;
			userTbRue->Text = du->Adresse;
			userNudNum->Value = du->numero;
			userNudCodePostal->Value = du->Code_Postal;


			break;
		case informationMode::VIEW:
			userPanelInfo->Visible = true;
			userPanelHistorique->Visible = true;
			userPanelTextBoxInfo->Visible = true;
			userPanelTextBoxInfo->Enabled = false;
			userPanelSav->Visible = false;
			userPanelBt->Visible = true;


			du = bddConnection->getUserByID(idUser);
			userTbNom->Text = du->Nom;
			userTbPrenom->Text = du->Prenom;
			userTbRFID->Text = du->ID_RFID;

			userTbVille->Text = du->Ville;
			userTbRue->Text = du->Adresse;
			userNudNum->Value = du->numero;
			userNudCodePostal->Value = du->Code_Postal;
			

			updateFactureList(idUser);
			

			userLvHist->Items->Clear();
			for each (DataHistorique^ var in bddConnection->getTableHistoriqueByIdUser(du->ID))
			{
				ListViewItem^ lvi = gcnew ListViewItem(var->dt->ToString());
				lvi->SubItems->Add(var->Poids.ToString());
				try
				{
					DataDechet^ dd = bddConnection->getDechetByID(var->ID_Dechet);
					lvi->SubItems->Add(dd->Nom);

				}
				catch (...)
				{
					lvi->SubItems->Add("N/A ("+var->ID_Dechet+")");
				}
				

				userLvHist->Items->Add(lvi);
			}
			break;
		}
		imode = mode;
	}


private: System::Void userLv_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	if (userLv->SelectedItems->Count == 1)
	{
		user_id_select = Convert::ToInt64(userLv->SelectedItems[0]->SubItems[3]->Text);
		updateInformation(user_id_select, informationMode::VIEW);
		Console::WriteLine(userLv->SelectedItems[0]->Text);
		Console::WriteLine(userLv->SelectedItems[0]->SubItems[1]->Text);
		Console::WriteLine(userLv->SelectedItems[0]->SubItems[2]->Text);
		Console::WriteLine(userLv->SelectedItems[0]->SubItems->Count);
		Console::WriteLine(userLv->SelectedItems[0]->SubItems[3]->Text);
	}
	else
	{
		//updateInformation(0, informationMode::nonDef);
	}
	//Console::WriteLine(listView1->SelectedItems->Count);
	

}
private: System::Void userTbSearch_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	updateUserList(userTbSearch->Text);
}
private: System::Void userBtSav_Click(System::Object^  sender, System::EventArgs^  e) 
{
	DataUser^ du = gcnew DataUser();

	du->Nom = userTbNom->Text;
	du->Prenom = userTbPrenom->Text;
	du->ID_RFID = userTbRFID->Text;

	du->Ville = userTbVille->Text;
	du->Adresse = userTbRue->Text;
	du->numero = Convert::ToInt64(userNudNum->Value);
	du->Code_Postal = Convert::ToInt64(userNudCodePostal->Value);

	switch (imode)
	{
	case informationMode::NEW:

		bddConnection->addUser(du);
		updateInformation(0, informationMode::nonDef);
		break;
	case informationMode::EDIT:
		du->ID = user_id_select;
		bddConnection->updateUser(du);
		updateInformation(du->ID, informationMode::VIEW);
		break;
	}
	updateUserList(userTbSearch->Text);
}
private: System::Void userBtSavAnnuler_Click(System::Object^  sender, System::EventArgs^  e) {
	switch (imode)
	{
	case informationMode::NEW:
		updateInformation(0, informationMode::nonDef);

		break;
	case informationMode::EDIT:
		updateInformation(user_id_select, informationMode::VIEW);
		break;
	}
}
private: System::Void userBtEdit_Click(System::Object^  sender, System::EventArgs^  e) {
	updateInformation(user_id_select, informationMode::EDIT);
}
private: System::Void userBtAddUser_Click(System::Object^  sender, System::EventArgs^  e) {
	userTbNom->Text = "";
	userTbPrenom->Text = "";
	userTbRFID->Text = "";

	userTbVille->Text = "";
	userTbRue->Text = "";
	userNudNum->Value = 0;
	userNudCodePostal->Value = 0;
	updateInformation(0, informationMode::NEW);

}
private: System::Void userBtDelUser_Click(System::Object^  sender, System::EventArgs^  e) {
	DataUser^ du = gcnew DataUser();
	du = bddConnection->getUserByID(user_id_select);

	if (MessageBox::Show("Voulez-vous vraiment supprimer l'utilisateur " + du->Nom + " " + du->Prenom + " ?", "Supprimer un utilisateur", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == ::DialogResult::Yes)
	{
		bddConnection->deleteUserByID(user_id_select);
		updateInformation(0, informationMode::nonDef);
		updateUserList(userTbSearch->Text);
	}
}
private: System::Void tabControl1_Click(System::Object^  sender, System::EventArgs^  e) {
	statsChartQuantiter->Series->Add("Dechet");
	statsChartQuantiter->Series["Dechet"]->Points->AddXY("Bois", 120);
}

private: System::Void userDgvFacture_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
	if (e->ColumnIndex == 3)
	{
		userDgvFacture->Rows[e->RowIndex];
	}
}
};


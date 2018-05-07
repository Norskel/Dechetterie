#pragma once
#include "StructDataConfigGestionnaire.h"
#define FILE_CONFIG "Config.xml"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::NetworkInformation;
using namespace System::IO;
using namespace System::IO::Ports;
using namespace System::Xml::Serialization;
using namespace MySql::Data::MySqlClient;


	/// <summary>
	/// Description résumée de ConfigBddForm
	/// </summary>
public ref class ConfigBddForm : public System::Windows::Forms::Form
{
public:
	ConfigBddForm(void)
	{
		InitializeComponent();
		this->btClose->BackgroundImage = Image::FromFile("Icon/icons8-fermer.png");

	}

protected:
	/// <summary>
	/// Nettoyage des ressources utilisées.
	/// </summary>
	~ConfigBddForm()
	{
		if (components)
		{
			delete components;
		}
	}
private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::TextBox^  tbBddPassword;
private: System::Windows::Forms::TextBox^  tbBddUsername;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::TextBox^  tbBddName;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::NumericUpDown^  nudPortBdd;
private: ControlInterface::ControlIPBox^  tbBddIP;
private: System::Windows::Forms::Button^  btTestCo;
private: ControlInterface::ControlEtat^  ceBddConnect;
private: System::Windows::Forms::Button^  btSauvegarde; 
private: System::Windows::Forms::GroupBox^  groupBox1;
private: System::Windows::Forms::Panel^  panel1;
private: System::Windows::Forms::Button^  btClose;

private: System::Windows::Forms::GroupBox^  groupBox2;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::ComboBox^  cbPort;

		 DataConfigGestionnaire^ _config = gcnew DataConfigGestionnaire();

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
		this->label14 = (gcnew System::Windows::Forms::Label());
		this->label13 = (gcnew System::Windows::Forms::Label());
		this->tbBddPassword = (gcnew System::Windows::Forms::TextBox());
		this->tbBddUsername = (gcnew System::Windows::Forms::TextBox());
		this->label12 = (gcnew System::Windows::Forms::Label());
		this->tbBddName = (gcnew System::Windows::Forms::TextBox());
		this->label11 = (gcnew System::Windows::Forms::Label());
		this->label10 = (gcnew System::Windows::Forms::Label());
		this->nudPortBdd = (gcnew System::Windows::Forms::NumericUpDown());
		this->btTestCo = (gcnew System::Windows::Forms::Button());
		this->btSauvegarde = (gcnew System::Windows::Forms::Button());
		this->ceBddConnect = (gcnew ControlInterface::ControlEtat());
		this->tbBddIP = (gcnew ControlInterface::ControlIPBox());
		this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
		this->panel1 = (gcnew System::Windows::Forms::Panel());
		this->btClose = (gcnew System::Windows::Forms::Button());
		this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->cbPort = (gcnew System::Windows::Forms::ComboBox());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortBdd))->BeginInit();
		this->groupBox1->SuspendLayout();
		this->panel1->SuspendLayout();
		this->groupBox2->SuspendLayout();
		this->SuspendLayout();
		// 
		// label14
		// 
		this->label14->AutoSize = true;
		this->label14->Location = System::Drawing::Point(176, 101);
		this->label14->Name = L"label14";
		this->label14->Size = System::Drawing::Size(80, 15);
		this->label14->TabIndex = 20;
		this->label14->Text = L"Mot de passe";
		// 
		// label13
		// 
		this->label13->AutoSize = true;
		this->label13->Location = System::Drawing::Point(14, 101);
		this->label13->Name = L"label13";
		this->label13->Size = System::Drawing::Size(102, 15);
		this->label13->TabIndex = 19;
		this->label13->Text = L"Nom d\'utilisateur";
		// 
		// tbBddPassword
		// 
		this->tbBddPassword->Location = System::Drawing::Point(179, 117);
		this->tbBddPassword->Name = L"tbBddPassword";
		this->tbBddPassword->Size = System::Drawing::Size(132, 23);
		this->tbBddPassword->TabIndex = 18;
		this->tbBddPassword->UseSystemPasswordChar = true;
		// 
		// tbBddUsername
		// 
		this->tbBddUsername->Location = System::Drawing::Point(17, 117);
		this->tbBddUsername->Name = L"tbBddUsername";
		this->tbBddUsername->Size = System::Drawing::Size(132, 23);
		this->tbBddUsername->TabIndex = 17;
		// 
		// label12
		// 
		this->label12->AutoSize = true;
		this->label12->Location = System::Drawing::Point(13, 62);
		this->label12->Name = L"label12";
		this->label12->Size = System::Drawing::Size(150, 15);
		this->label12->TabIndex = 16;
		this->label12->Text = L"Nom de la base de donnée";
		// 
		// tbBddName
		// 
		this->tbBddName->Location = System::Drawing::Point(16, 78);
		this->tbBddName->Name = L"tbBddName";
		this->tbBddName->Size = System::Drawing::Size(132, 23);
		this->tbBddName->TabIndex = 15;
		// 
		// label11
		// 
		this->label11->AutoSize = true;
		this->label11->Location = System::Drawing::Point(13, 23);
		this->label11->Name = L"label11";
		this->label11->Size = System::Drawing::Size(64, 15);
		this->label11->TabIndex = 9;
		this->label11->Text = L"Adresse IP";
		// 
		// label10
		// 
		this->label10->AutoSize = true;
		this->label10->Location = System::Drawing::Point(176, 23);
		this->label10->Name = L"label10";
		this->label10->Size = System::Drawing::Size(30, 15);
		this->label10->TabIndex = 14;
		this->label10->Text = L"Port";
		// 
		// nudPortBdd
		// 
		this->nudPortBdd->Location = System::Drawing::Point(179, 39);
		this->nudPortBdd->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65536, 0, 0, 0 });
		this->nudPortBdd->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		this->nudPortBdd->Name = L"nudPortBdd";
		this->nudPortBdd->Size = System::Drawing::Size(128, 23);
		this->nudPortBdd->TabIndex = 13;
		this->nudPortBdd->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
		// 
		// btTestCo
		// 
		this->btTestCo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->btTestCo->Location = System::Drawing::Point(331, 19);
		this->btTestCo->Name = L"btTestCo";
		this->btTestCo->Size = System::Drawing::Size(106, 40);
		this->btTestCo->TabIndex = 21;
		this->btTestCo->Text = L"Test Connection";
		this->btTestCo->UseVisualStyleBackColor = true;
		this->btTestCo->Click += gcnew System::EventHandler(this, &ConfigBddForm::btTestCo_Click);
		// 
		// btSauvegarde
		// 
		this->btSauvegarde->Location = System::Drawing::Point(559, 236);
		this->btSauvegarde->Name = L"btSauvegarde";
		this->btSauvegarde->Size = System::Drawing::Size(106, 23);
		this->btSauvegarde->TabIndex = 24;
		this->btSauvegarde->Text = L"Sauvegarder";
		this->btSauvegarde->UseVisualStyleBackColor = true;
		this->btSauvegarde->Click += gcnew System::EventHandler(this, &ConfigBddForm::btSauvegarde_Click);
		// 
		// ceBddConnect
		// 
		this->ceBddConnect->BackColor = System::Drawing::Color::Red;
		this->ceBddConnect->colorFalse = System::Drawing::Color::Red;
		this->ceBddConnect->colorTexte = System::Drawing::Color::White;
		this->ceBddConnect->colorTrue = System::Drawing::Color::LimeGreen;
		this->ceBddConnect->Location = System::Drawing::Point(331, 65);
		this->ceBddConnect->Name = L"ceBddConnect";
		this->ceBddConnect->Size = System::Drawing::Size(106, 20);
		this->ceBddConnect->state = false;
		this->ceBddConnect->TabIndex = 22;
		this->ceBddConnect->texteSize = 10;
		this->ceBddConnect->textFalse = L"Non connecté";
		this->ceBddConnect->textTrue = L"Connecté";
		// 
		// tbBddIP
		// 
		this->tbBddIP->IP = L"...";
		this->tbBddIP->Location = System::Drawing::Point(16, 39);
		this->tbBddIP->Name = L"tbBddIP";
		this->tbBddIP->Size = System::Drawing::Size(132, 20);
		this->tbBddIP->TabIndex = 10;
		// 
		// groupBox1
		// 
		this->groupBox1->Controls->Add(this->tbBddPassword);
		this->groupBox1->Controls->Add(this->tbBddName);
		this->groupBox1->Controls->Add(this->label10);
		this->groupBox1->Controls->Add(this->ceBddConnect);
		this->groupBox1->Controls->Add(this->label12);
		this->groupBox1->Controls->Add(this->btTestCo);
		this->groupBox1->Controls->Add(this->nudPortBdd);
		this->groupBox1->Controls->Add(this->label14);
		this->groupBox1->Controls->Add(this->tbBddUsername);
		this->groupBox1->Controls->Add(this->tbBddIP);
		this->groupBox1->Controls->Add(this->label11);
		this->groupBox1->Controls->Add(this->label13);
		this->groupBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->groupBox1->ForeColor = System::Drawing::Color::White;
		this->groupBox1->Location = System::Drawing::Point(12, 45);
		this->groupBox1->Name = L"groupBox1";
		this->groupBox1->Size = System::Drawing::Size(447, 185);
		this->groupBox1->TabIndex = 25;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = L"Base de donnée";
		// 
		// panel1
		// 
		this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
			static_cast<System::Int32>(static_cast<System::Byte>(31)));
		this->panel1->Controls->Add(this->btClose);
		this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
		this->panel1->Location = System::Drawing::Point(0, 0);
		this->panel1->Name = L"panel1";
		this->panel1->Size = System::Drawing::Size(686, 39);
		this->panel1->TabIndex = 26;
		this->panel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ConfigBddForm::panel1_MouseDown);
		this->panel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ConfigBddForm::panel1_MouseMove);
		this->panel1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ConfigBddForm::panel1_MouseUp);
		// 
		// btClose
		// 
		this->btClose->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->btClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->btClose->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(31)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
			static_cast<System::Int32>(static_cast<System::Byte>(31)));
		this->btClose->Location = System::Drawing::Point(651, 4);
		this->btClose->Name = L"btClose";
		this->btClose->Size = System::Drawing::Size(32, 32);
		this->btClose->TabIndex = 27;
		this->btClose->UseVisualStyleBackColor = true;
		this->btClose->Click += gcnew System::EventHandler(this, &ConfigBddForm::btClose_Click);
		// 
		// groupBox2
		// 
		this->groupBox2->Controls->Add(this->label1);
		this->groupBox2->Controls->Add(this->cbPort);
		this->groupBox2->Location = System::Drawing::Point(465, 46);
		this->groupBox2->Name = L"groupBox2";
		this->groupBox2->Size = System::Drawing::Size(200, 184);
		this->groupBox2->TabIndex = 27;
		this->groupBox2->TabStop = false;
		this->groupBox2->Text = L"Autre";
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(13, 22);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(26, 13);
		this->label1->TabIndex = 23;
		this->label1->Text = L"Port";
		// 
		// cbPort
		// 
		this->cbPort->FormattingEnabled = true;
		this->cbPort->Location = System::Drawing::Point(16, 38);
		this->cbPort->Name = L"cbPort";
		this->cbPort->Size = System::Drawing::Size(121, 21);
		this->cbPort->TabIndex = 0;
		// 
		// ConfigBddForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(40)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
			static_cast<System::Int32>(static_cast<System::Byte>(40)));
		this->ClientSize = System::Drawing::Size(686, 287);
		this->Controls->Add(this->groupBox2);
		this->Controls->Add(this->panel1);
		this->Controls->Add(this->groupBox1);
		this->Controls->Add(this->btSauvegarde);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		this->Name = L"ConfigBddForm";
		this->Text = L"ConfigBddForm";
		this->Load += gcnew System::EventHandler(this, &ConfigBddForm::ConfigBddForm_Load);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPortBdd))->EndInit();
		this->groupBox1->ResumeLayout(false);
		this->groupBox1->PerformLayout();
		this->panel1->ResumeLayout(false);
		this->groupBox2->ResumeLayout(false);
		this->groupBox2->PerformLayout();
		this->ResumeLayout(false);

	}
#pragma endregion

	private: bool mouseDown;
	private: Point lastLocation;

	private: System::Void btTestCo_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		// Ping's the local machine.
		Ping ^ pingSender = gcnew Ping;
		PingReply ^ reply = pingSender->Send(IPAddress::Parse(tbBddIP->IP));
		if (reply->Status == IPStatus::Success)
		{
			Console::WriteLine("Address: {0}", reply->Address->ToString());
			Console::WriteLine("RoundTrip time: {0}", reply->RoundtripTime);
			Console::WriteLine("Time to live: {0}", reply->Options->Ttl);
			Console::WriteLine("Don't fragment: {0}", reply->Options->DontFragment);
			Console::WriteLine("Buffer size: {0}", reply->Buffer->Length);

			String^ infoConnection = "SERVER=" + tbBddIP->IP + "; DATABASE=" + tbBddName->Text + "; PORT=" + Convert::ToString(this->nudPortBdd->Value) + "; UID=" + tbBddUsername->Text + "; PASSWORD=" + tbBddPassword->Text + "";
			MySqlConnection^ con = gcnew MySqlConnection(infoConnection);
			try
			{
				con->Open();
				con->Ping();
				ceBddConnect->state = true;

			}
			catch (...)
			{
				ceBddConnect->textFalse = "Accès bloquée";
				ceBddConnect->state = false;

			}

		}
		else
		{
			Console::WriteLine(reply->Status);
			ceBddConnect->textFalse = "Hôte inexistant";
			ceBddConnect->state = false;


		}
	}
	private: System::Void btClose_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->Close();
	}
	private: System::Void btSauvegarde_Click(System::Object^  sender, System::EventArgs^  e) 
	{

		_config->NomBDD = tbBddName->Text;
		_config->UsernameBDD = tbBddUsername->Text;
		_config->PasswordBDD = tbBddPassword->Text;
		_config->IPBDD = tbBddIP->IP;
		_config->PortBDD = Convert::ToInt32(this->nudPortBdd->Value);
		_config->COM = (String^)cbPort->SelectedItem;
		FileStream^ fs;
		bool fileOpened = false;
		XmlSerializer^ serializer = gcnew XmlSerializer(DataConfigGestionnaire::typeid);
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

		serializer->Serialize(fs, _config);
		fs->Close();
	}
	private: System::Void ConfigBddForm_Load(System::Object^  sender, System::EventArgs^  e) 
	{
		ceBddConnect->textFalse = "";

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
			XmlSerializer^ serializer = gcnew XmlSerializer(DataConfigGestionnaire::typeid);
			_config = (DataConfigGestionnaire^)serializer->Deserialize(fs);
			fs->Close();

			tbBddIP->IP = _config->IPBDD;
			tbBddName->Text = _config->NomBDD;
			tbBddPassword->Text = _config->PasswordBDD;
			tbBddUsername->Text = _config->UsernameBDD;
			nudPortBdd->Value = _config->PortBDD;

		}

		array<String^>^ serialPorts;
		try
		{
			serialPorts = SerialPort::GetPortNames();
			cbPort->SelectedItem = _config->COM;
		}
		catch (...) {}
		for each (String^ var in serialPorts)
		{
			cbPort->Items->Add(var);
		}
	}

	private: System::Void panel1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		mouseDown = true;
		lastLocation = e->Location;
	}
	private: System::Void panel1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		if (mouseDown)
		{
			this->Location = Point((this->Location.X - lastLocation.X) + e->X, (this->Location.Y - lastLocation.Y) + e->Y);
			this->Update();
		}
	}
	private: System::Void panel1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		mouseDown = false;
	}
};


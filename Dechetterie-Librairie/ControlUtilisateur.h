#pragma once
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ControlInterface {

	/// <summary>
	/// Description résumée de Utilisateur
	/// </summary>
	public ref class ControlUtilisateur : public System::Windows::Forms::UserControl
	{
	public:
		ControlUtilisateur()
		{
			InitializeComponent();

		}


		[Category("Configuration")]
		[Description("Photo")]
		property Bitmap ^ photo
		{
			Bitmap ^ get() { return _photo; }
			void set(Bitmap ^ value)
			{
				_photo = value;

			}
		}
		[Category("Configuration")]
		[Description("Nom")]
		property String ^ nom
		{
			String ^ get() { return _nom; }
			void set(String ^ value)
			{
				_nom = value;

			}
		}
		[Category("Configuration")]
		[Description("Prenom")]
		property String ^ prenom
		{
			String ^ get() { return _prenom; }
			void set(String ^ value)
			{
				_prenom = value;

			}
		}
		[Category("Configuration")]
		[Description("Type de dechet !//")]
		property int typeDechet
		{
			int get() { return _typeDechet; }
			void set(int value)
			{
				_typeDechet = value;

			}
		}

		[Category("Configuration")]
		[Description("Duree depuis l'arrivée !")]
		property DateTime temp
		{
			DateTime get() { return _temp; }
			void set(DateTime value)
			{
				_temp = value;

			}
		}


	private: System::Windows::Forms::Label^  lTemp;
	private: System::Windows::Forms::Label^  l1;
	private: System::Windows::Forms::Label^  lTypeDechet;
	private: Bitmap^ _photo;
	private: Bitmap^ _photoF;
	private: String^ _nom = "";
	private: String^ _prenom = "";
	private: int _typeDechet = 0;
	private: System::Windows::Forms::Timer^  timerUpdate;

	private: DateTime _temp = DateTime::Parse("00:00:00");






	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>

	public:


		~ControlUtilisateur()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  lNom;
	private: System::Windows::Forms::Label^  lPrenom;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code->
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->lNom = (gcnew System::Windows::Forms::Label());
			this->lPrenom = (gcnew System::Windows::Forms::Label());
			this->lTemp = (gcnew System::Windows::Forms::Label());
			this->l1 = (gcnew System::Windows::Forms::Label());
			this->lTypeDechet = (gcnew System::Windows::Forms::Label());
			this->timerUpdate = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->pictureBox1->Location = System::Drawing::Point(3, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(640, 480);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// lNom
			// 
			this->lNom->AutoSize = true;
			this->lNom->BackColor = System::Drawing::Color::Transparent;
			this->lNom->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lNom->ForeColor = System::Drawing::Color::White;
			this->lNom->Location = System::Drawing::Point(15, 400);
			this->lNom->Name = L"lNom";
			this->lNom->Size = System::Drawing::Size(77, 31);
			this->lNom->TabIndex = 1;
			this->lNom->Text = L"NOM";
			// 
			// lPrenom
			// 
			this->lPrenom->AutoSize = true;
			this->lPrenom->BackColor = System::Drawing::Color::Transparent;
			this->lPrenom->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lPrenom->ForeColor = System::Drawing::Color::White;
			this->lPrenom->Location = System::Drawing::Point(15, 443);
			this->lPrenom->Name = L"lPrenom";
			this->lPrenom->Size = System::Drawing::Size(108, 31);
			this->lPrenom->TabIndex = 2;
			this->lPrenom->Text = L"Prenom";
			// 
			// lTemp
			// 
			this->lTemp->AutoSize = true;
			this->lTemp->BackColor = System::Drawing::Color::Transparent;
			this->lTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lTemp->ForeColor = System::Drawing::Color::White;
			this->lTemp->Location = System::Drawing::Point(3, 3);
			this->lTemp->Name = L"lTemp";
			this->lTemp->Size = System::Drawing::Size(120, 31);
			this->lTemp->TabIndex = 3;
			this->lTemp->Text = L"00:00:00";
			// 
			// l1
			// 
			this->l1->AutoSize = true;
			this->l1->BackColor = System::Drawing::Color::Transparent;
			this->l1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->l1->ForeColor = System::Drawing::Color::White;
			this->l1->Location = System::Drawing::Point(392, 443);
			this->l1->Name = L"l1";
			this->l1->Size = System::Drawing::Size(201, 31);
			this->l1->TabIndex = 4;
			this->l1->Text = L"Type de dechet";
			// 
			// lTypeDechet
			// 
			this->lTypeDechet->AutoSize = true;
			this->lTypeDechet->BackColor = System::Drawing::Color::Transparent;
			this->lTypeDechet->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lTypeDechet->ForeColor = System::Drawing::Color::White;
			this->lTypeDechet->Location = System::Drawing::Point(599, 443);
			this->lTypeDechet->Name = L"lTypeDechet";
			this->lTypeDechet->Size = System::Drawing::Size(29, 31);
			this->lTypeDechet->TabIndex = 5;
			this->lTypeDechet->Text = L"0";
			// 
			// timerUpdate
			// 
			this->timerUpdate->Enabled = true;
			this->timerUpdate->Interval = 500;
			this->timerUpdate->Tick += gcnew System::EventHandler(this, &ControlUtilisateur::timerUpdate_Tick);
			// 
			// ControlUtilisateur
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->Controls->Add(this->lTypeDechet);
			this->Controls->Add(this->l1);
			this->Controls->Add(this->lTemp);
			this->Controls->Add(this->lPrenom);
			this->Controls->Add(this->lNom);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"ControlUtilisateur";
			this->Size = System::Drawing::Size(648, 488);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void timerUpdate_Tick(System::Object^  sender, System::EventArgs^  e) {

		//debug->Text = ("H = " + this->Size.Height + " W = " + this->Size.Width);

		this->pictureBox1->Size = System::Drawing::Size((this->Size.Width - 8), (this->Size.Height - 8));
		//debug->Text += (" -H = " + (this->Size.Height - 8) + " W = " + (this->Size.Width - 8));
		//debug->Text += ("pb H = " + this->pictureBox1->Size.Height + " W = " + pictureBox1->Size.Width);

		this->lNom->Location = System::Drawing::Point(15, (this->Size.Height - 88));
		this->lPrenom->Location = System::Drawing::Point(15, (this->Size.Height - 41));

		this->l1->Location = System::Drawing::Point((this->Size.Width - 256), (this->Size.Height - 41));
		this->lTypeDechet->Location = System::Drawing::Point((this->Size.Width - 49), (this->Size.Height - 41));

		this->Refresh();

		try
		{
			this->lNom->Text = _nom;
			this->lPrenom->Text = _prenom;
			this->lTemp->Text = (DateTime::Now.Subtract(_temp)).ToString();
			this->lTypeDechet->Text = Convert::ToString(_typeDechet);
		}
		catch (...)
		{


		}
		try
		{
			_photoF = gcnew Bitmap(_photo, this->pictureBox1->Size.Width, this->pictureBox1->Size.Height);
			this->pictureBox1->Image = _photoF;
		}
		catch (...)
		{


		}


	}

	};
}

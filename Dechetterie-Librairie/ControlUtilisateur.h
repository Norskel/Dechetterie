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
		[Description("Liste des icones de type de dechet")]
		property array<Bitmap^>^ listDechet
		{
			array<Bitmap^>^ get() { return _listDechet; }
			void set(array<Bitmap^>^ value)
			{
				_listDechet = value;

			}
		}
		[Category("Configuration")]
		[Description("Type de dechet ")]
		property int IdTypeDechet
		{
			int get() { return _IDTypeDechet; }
			void set(int value)
			{
				_IDTypeDechet = value;

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


	private: Bitmap^ _photo;
	private: Bitmap^ _photoF;
	private: Bitmap^ _typeDechet;
	private: Bitmap^ _typeDechetF;

	private: String^ _nom = "";
	private: String^ _prenom = "";
	private: int _IDTypeDechet = 0;
	private: array<Bitmap^>^ _listDechet;
	private: System::Windows::Forms::Timer^  timerUpdate;


	private: System::Windows::Forms::Label^  labelTypeDechet;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Label^  lNom;
	private: System::Windows::Forms::Label^  lPrenom;
	private: System::ComponentModel::IContainer^  components;

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
			this->timerUpdate = (gcnew System::Windows::Forms::Timer(this->components));
			this->labelTypeDechet = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
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
			this->lNom->Font = (gcnew System::Drawing::Font(L"Calibri", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lNom->ForeColor = System::Drawing::Color::White;
			this->lNom->Location = System::Drawing::Point(15, 400);
			this->lNom->Name = L"lNom";
			this->lNom->Size = System::Drawing::Size(94, 42);
			this->lNom->TabIndex = 1;
			this->lNom->Text = L"NOM";
			// 
			// lPrenom
			// 
			this->lPrenom->AutoSize = true;
			this->lPrenom->BackColor = System::Drawing::Color::Transparent;
			this->lPrenom->Font = (gcnew System::Drawing::Font(L"Calibri", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lPrenom->ForeColor = System::Drawing::Color::White;
			this->lPrenom->Location = System::Drawing::Point(15, 443);
			this->lPrenom->Name = L"lPrenom";
			this->lPrenom->Size = System::Drawing::Size(129, 42);
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
			// timerUpdate
			// 
			this->timerUpdate->Enabled = true;
			this->timerUpdate->Interval = 500;
			this->timerUpdate->Tick += gcnew System::EventHandler(this, &ControlUtilisateur::timerUpdate_Tick);
			// 
			// labelTypeDechet
			// 
			this->labelTypeDechet->AutoSize = true;
			this->labelTypeDechet->BackColor = System::Drawing::Color::Transparent;
			this->labelTypeDechet->Font = (gcnew System::Drawing::Font(L"Calibri", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelTypeDechet->ForeColor = System::Drawing::Color::White;
			this->labelTypeDechet->Location = System::Drawing::Point(528, 388);
			this->labelTypeDechet->Name = L"labelTypeDechet";
			this->labelTypeDechet->Size = System::Drawing::Size(0, 42);
			this->labelTypeDechet->TabIndex = 7;
			this->labelTypeDechet->Visible = false;
			// 
			// ControlUtilisateur
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->Controls->Add(this->labelTypeDechet);
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

	private: System::Void timerUpdate_Tick(System::Object^  sender, System::EventArgs^  e) 
	{
		this->pictureBox1->Size = System::Drawing::Size((this->Size.Width - 8), (this->Size.Height - 8));
		this->lNom->Location = System::Drawing::Point(15, (this->Size.Height - 88));
		this->lPrenom->Location = System::Drawing::Point(15, (this->Size.Height - 41));

		this->Refresh();

		try
		{
			this->lNom->Text = _nom;
			this->lPrenom->Text = _prenom;
			this->lTemp->Text = (DateTime::Now.Subtract(_temp)).ToString("hh\\:mm\\:ss");
		}catch (...){}

		try
		{
			_photoF = gcnew Bitmap(_photo, this->pictureBox1->Size.Width, this->pictureBox1->Size.Height);
		}
		catch (...){}

		try
		{
			labelTypeDechet->Visible = false;
			Graphics^ g = Graphics::FromImage(_photoF);
			g->DrawImage(_listDechet[IdTypeDechet], this->Width - 110, this->Height - 110, 100, 100);
		}
		catch (...)
		{
			labelTypeDechet->Visible = true;
			labelTypeDechet->Text = IdTypeDechet.ToString();
		}
		this->pictureBox1->Image = _photoF;

	}

};
}

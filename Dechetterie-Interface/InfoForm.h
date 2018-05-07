#pragma once

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	/// <summary>
	/// Description résumée de InfoForm
	/// </summary>
	public ref class InfoForm : public System::Windows::Forms::Form
	{
	public:
		InfoForm(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~InfoForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Button^  btClose;
	private: System::Windows::Forms::Button^  btLicence;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  btBug;
	private: System::Windows::Forms::LinkLabel^  linkLabel1;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btClose = (gcnew System::Windows::Forms::Button());
			this->btLicence = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btBug = (gcnew System::Windows::Forms::Button());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(346, 45);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Interface Dechetterie";
			// 
			// btClose
			// 
			this->btClose->Location = System::Drawing::Point(513, 212);
			this->btClose->Name = L"btClose";
			this->btClose->Size = System::Drawing::Size(75, 23);
			this->btClose->TabIndex = 1;
			this->btClose->Text = L"Fermer";
			this->btClose->UseVisualStyleBackColor = true;
			this->btClose->Click += gcnew System::EventHandler(this, &InfoForm::btClose_Click);
			// 
			// btLicence
			// 
			this->btLicence->Location = System::Drawing::Point(22, 212);
			this->btLicence->Name = L"btLicence";
			this->btLicence->Size = System::Drawing::Size(130, 23);
			this->btLicence->TabIndex = 2;
			this->btLicence->Text = L"Information de licence";
			this->btLicence->UseVisualStyleBackColor = true;
			this->btLicence->Click += gcnew System::EventHandler(this, &InfoForm::btLicence_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(17, 64);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(44, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"1.2.5";
			// 
			// btBug
			// 
			this->btBug->Location = System::Drawing::Point(158, 212);
			this->btBug->Name = L"btBug";
			this->btBug->Size = System::Drawing::Size(112, 23);
			this->btBug->TabIndex = 4;
			this->btBug->Text = L"Siganler un bug";
			this->btBug->UseVisualStyleBackColor = true;
			this->btBug->Click += gcnew System::EventHandler(this, &InfoForm::btBug_Click);
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->Location = System::Drawing::Point(228, 157);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(55, 13);
			this->linkLabel1->TabIndex = 5;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"linkLabel1";
			// 
			// InfoForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(600, 247);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->btBug);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->btLicence);
			this->Controls->Add(this->btClose);
			this->Controls->Add(this->label1);
			this->Name = L"InfoForm";
			this->Text = L"InfoForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btLicence_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Process::Start("https://github.com/Norskel/Dechetterie/blob/master/LICENSE");
	}
	private: System::Void btClose_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->Close();
		this->~InfoForm();
	}
	private: System::Void btBug_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		Process::Start("https://github.com/Norskel/Dechetterie/issues");
	}
};


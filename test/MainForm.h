#pragma once



	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	protected:
	private: System::Windows::Forms::Panel^  panel2;
	private: ControlInterface::ControlButtonIcon^  controlButtonIcon3;
	private: ControlInterface::ControlButtonIcon^  controlButtonIcon2;
	private: ControlInterface::ControlButtonIcon^  controlButtonIcon1;

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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->controlButtonIcon3 = (gcnew ControlInterface::ControlButtonIcon());
			this->controlButtonIcon2 = (gcnew ControlInterface::ControlButtonIcon());
			this->controlButtonIcon1 = (gcnew ControlInterface::ControlButtonIcon());
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(13)), static_cast<System::Int32>(static_cast<System::Byte>(13)),
				static_cast<System::Int32>(static_cast<System::Byte>(13)));
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(984, 33);
			this->panel1->TabIndex = 0;
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::SystemColors::ControlDark;
			this->panel2->Controls->Add(this->controlButtonIcon3);
			this->panel2->Controls->Add(this->controlButtonIcon2);
			this->panel2->Controls->Add(this->controlButtonIcon1);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(0, 33);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(300, 477);
			this->panel2->TabIndex = 1;
			// 
			// controlButtonIcon3
			// 
			this->controlButtonIcon3->backColor = System::Drawing::SystemColors::ControlDarkDark;
			this->controlButtonIcon3->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->controlButtonIcon3->icon = nullptr;
			this->controlButtonIcon3->Location = System::Drawing::Point(0, 192);
			this->controlButtonIcon3->Name = L"controlButtonIcon3";
			this->controlButtonIcon3->Size = System::Drawing::Size(300, 90);
			this->controlButtonIcon3->state = false;
			this->controlButtonIcon3->TabIndex = 2;
			this->controlButtonIcon3->text = L"Utilisateur";
			this->controlButtonIcon3->textColor = System::Drawing::SystemColors::ControlLightLight;
			this->controlButtonIcon3->OnClick += gcnew System::EventHandler<System::Int32 >(this, &MainForm::controlButtonIcon3_OnClick_1);
			// 
			// controlButtonIcon2
			// 
			this->controlButtonIcon2->backColor = System::Drawing::SystemColors::ControlDarkDark;
			this->controlButtonIcon2->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->controlButtonIcon2->icon = nullptr;
			this->controlButtonIcon2->Location = System::Drawing::Point(0, 96);
			this->controlButtonIcon2->Name = L"controlButtonIcon2";
			this->controlButtonIcon2->Size = System::Drawing::Size(300, 90);
			this->controlButtonIcon2->state = false;
			this->controlButtonIcon2->TabIndex = 1;
			this->controlButtonIcon2->text = L"Utilisateur";
			this->controlButtonIcon2->textColor = System::Drawing::SystemColors::ControlLightLight;
			this->controlButtonIcon2->OnClick += gcnew System::EventHandler<System::Int32 >(this, &MainForm::controlButtonIcon2_OnClick_1);
			// 
			// controlButtonIcon1
			// 
			this->controlButtonIcon1->backColor = System::Drawing::SystemColors::ControlDarkDark;
			this->controlButtonIcon1->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->controlButtonIcon1->icon = nullptr;
			this->controlButtonIcon1->Location = System::Drawing::Point(0, 0);
			this->controlButtonIcon1->Name = L"controlButtonIcon1";
			this->controlButtonIcon1->Size = System::Drawing::Size(300, 90);
			this->controlButtonIcon1->state = true;
			this->controlButtonIcon1->TabIndex = 0;
			this->controlButtonIcon1->text = L"Utilisateur";
			this->controlButtonIcon1->textColor = System::Drawing::SystemColors::ControlLightLight;
			this->controlButtonIcon1->OnClick += gcnew System::EventHandler<System::Int32 >(this, &MainForm::controlButtonIcon1_OnClick_1);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(984, 510);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->panel2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

		Resources::ResourceManager^ resManager = gcnew Resources::ResourceManager("test.MainForm", Reflection::Assembly::GetExecutingAssembly());

	private: System::Void controlButtonIcon1_Load(System::Object^  sender, System::EventArgs^  e) {

		controlButtonIcon1->icon = safe_cast<Image^>(resManager->GetObject("icons8-addUser"));
	}
private: System::Void controlButtonIcon2_Load(System::Object^  sender, System::EventArgs^  e) {
	controlButtonIcon1->icon = safe_cast<Image^>(resManager->GetObject("icons8-User"));
}



private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	Console::WriteLine("load");
}
private: System::Void controlButtonIcon3_OnClick(System::Object^  sender, System::Int32 e) {


}
private: System::Void controlButtonIcon1_OnClick(System::Object^  sender, System::Int32 e) {

}
private: System::Void controlButtonIcon2_OnClick(System::Object^  sender, System::Int32 e) {

}


private: System::Void controlButtonIcon1_OnClick_1(System::Object^  sender, System::Int32 e) {
	Console::WriteLine("Click bt 1");
	controlButtonIcon1->state = true;
	controlButtonIcon2->state = false;
	controlButtonIcon3->state = false;
}
private: System::Void controlButtonIcon2_OnClick_1(System::Object^  sender, System::Int32 e) {
	Console::WriteLine("Click bt 2");
	controlButtonIcon2->state = true;
	controlButtonIcon1->state = false;
	controlButtonIcon3->state = false;
}
private: System::Void controlButtonIcon3_OnClick_1(System::Object^  sender, System::Int32 e) {
	Console::WriteLine("Click bt 3");
	controlButtonIcon3->state = true;
	controlButtonIcon2->state = false;
	controlButtonIcon1->state = false;
}
};


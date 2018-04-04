#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ControlInterface {

	/// <summary>
	/// Description résumée de ControlEtat
	/// </summary>
	public ref class ControlEtat : public System::Windows::Forms::UserControl
	{
	public:
		ControlEtat(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
		}

		[Category("Configuration")]
		[Description("Texte à l'état false")]
		property String ^ textFalse
		{
			String ^ get() { return _textFalse; }
			void set(String ^ value)
			{
				_textFalse = value;

			}
		}
		[Category("Configuration")]
		[Description("Texte à l'état true")]
		property String ^ textTrue
		{
			String ^ get() { return _textTrue; }
			void set(String ^ value)
			{
				_textTrue = value;

			}
		}
		[Category("Configuration")]
		[Description("Couleur à l'état false")]
		property Color colorFalse
		{
			Color get() { return _colorFalse; }
			void set(Color value)
			{
				_colorFalse = value;

			}
		}
		[Category("Configuration")]
		[Description("Couleur à l'état true")]
		property Color colorTrue
		{
			Color get() { return _colorTrue; }
			void set(Color value)
			{
				_colorTrue = value;

			}
		}
		[Category("Configuration")]
		[Description("Couleur du texte")]
		property Color colorTexte
		{
			Color get() { return _colorTexte; }
			void set(Color value)
			{
				_colorTexte = value;

			}
		}
		[Category("Configuration")]
		[Description("Etat")]
		property Boolean state
		{
			Boolean get() { return _state; }
			void set(Boolean value)
			{
				_state = value;

			}
		}
		[Category("Configuration")]
		[Description("Taille de la police du texte")]
		property float texteSize
		{
			float get() { return _textSize; }
			void set(float value)
			{
				_textSize = value;

			}
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~ControlEtat()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  lState;
	private: System::ComponentModel::IContainer^  components;
	protected:

	protected:

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>

		Color _colorTrue = Color::Lime;
		Color _colorTexte = Color::White;
		String^ _textTrue;
		String^ _textFalse;
		Boolean _state = false;
		Color _colorFalse = Color::Red;
		float _textSize = 10;
	private: System::Windows::Forms::Timer^  timerUpdate;





#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
			 /// le contenu de cette méthode avec l'éditeur de code->
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 this->lState = (gcnew System::Windows::Forms::Label());
				 this->timerUpdate = (gcnew System::Windows::Forms::Timer(this->components));
				 this->SuspendLayout();
				 // 
				 // lState
				 // 
				 this->lState->AutoSize = true;
				 this->lState->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->lState->Location = System::Drawing::Point(53, 61);
				 this->lState->Name = L"lState";
				 this->lState->Size = System::Drawing::Size(30, 15);
				 this->lState->TabIndex = 0;
				 this->lState->Text = L"OFF";
				 // 
				 // timerUpdate
				 // 
				 this->timerUpdate->Enabled = true;
				 this->timerUpdate->Interval = 500;
				 this->timerUpdate->Tick += gcnew System::EventHandler(this, &ControlEtat::timerUpdate_Tick);
				 // 
				 // ControlEtat
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->Controls->Add(this->lState);
				 this->Name = L"ControlEtat";
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void timerUpdate_Tick(System::Object^  sender, System::EventArgs^  e) {

		this->lState->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", _textSize, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		this->lState->ForeColor = _colorTexte;
		if (_state)
		{
			this->BackColor = _colorTrue;
			lState->Text = _textTrue;
		}
		else
		{
			this->BackColor = _colorFalse;
			lState->Text = _textFalse;

		}

		this->lState->Location = System::Drawing::Point(((this->Width / 2) - (lState->Width / 2)), ((this->Height / 2) - (lState->Height / 2)));

	}
	};
}

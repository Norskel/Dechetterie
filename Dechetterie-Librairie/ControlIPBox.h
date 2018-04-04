#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace ControlInterface {

	/// <summary>
	/// Description résumée de ControlIPBox
	/// </summary>
	public ref class ControlIPBox : public System::Windows::Forms::UserControl
	{





		/** Returns whether all Box1 thru Box4 have a valid IP octet
		* \return True if valid, false otherwise
		* */
	public: bool IsValid()
	{
		try
		{
			int checkval = int::Parse(Box1->Text);
			if (checkval < 0 || checkval > 255)
				return false;
			checkval = int::Parse(Box2->Text);
			if (checkval < 0 || checkval > 255)
				return false;
			checkval = int::Parse(Box3->Text);
			if (checkval < 0 || checkval > 255)
				return false;
			checkval = int::Parse(Box4->Text);
			if (checkval < 0 || checkval > 255)
				return false;
			else
				return true;
		}
		catch (...)
		{
			return false;
		}
	}
	public:
		ControlIPBox(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
		}
		[Category("Configuration")]
		[Description("Adresse IP")]
		property String ^ IP
		{
			String ^ get() { return Box1->Text + "." + Box2->Text + "." + Box3->Text + "." + Box4->Text; }
			void set(String ^ value)
			{
				if (value != "" && value != nullptr)
				{
					array<String^>^ pieces = value->Split('.');

					Box1->Text = pieces[0];
					Box2->Text = pieces[1];
					Box3->Text = pieces[2];
					Box4->Text = pieces[3];
				}
				else
				{
					Box1->Text = "";
					Box2->Text = "";
					Box3->Text = "";
					Box4->Text = "";
				}

			}
		}



	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~ControlIPBox()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  Box4;
	private: System::Windows::Forms::TextBox^  Box3;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  Box2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  Box1;

	protected:








	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code->
		/// </summary>

#pragma endregion

	private: System::Void InitializeComponent() {
		this->panel1 = (gcnew System::Windows::Forms::Panel());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->Box4 = (gcnew System::Windows::Forms::TextBox());
		this->Box3 = (gcnew System::Windows::Forms::TextBox());
		this->Box2 = (gcnew System::Windows::Forms::TextBox());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->Box1 = (gcnew System::Windows::Forms::TextBox());
		this->panel1->SuspendLayout();
		this->SuspendLayout();
		// 
		// panel1
		// 
		this->panel1->BackColor = System::Drawing::SystemColors::Window;
		this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
		this->panel1->Controls->Add(this->label3);
		this->panel1->Controls->Add(this->label2);
		this->panel1->Controls->Add(this->Box4);
		this->panel1->Controls->Add(this->Box3);
		this->panel1->Controls->Add(this->Box2);
		this->panel1->Controls->Add(this->label1);
		this->panel1->Controls->Add(this->Box1);
		this->panel1->Location = System::Drawing::Point(0, 0);
		this->panel1->Name = L"panel1";
		this->panel1->Size = System::Drawing::Size(128, 18);
		this->panel1->TabIndex = 1;
		// 
		// label3
		// 
		this->label3->Location = System::Drawing::Point(24, 0);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(8, 13);
		this->label3->TabIndex = 6;
		this->label3->Text = L".";
		// 
		// label2
		// 
		this->label2->Location = System::Drawing::Point(88, 0);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(8, 13);
		this->label2->TabIndex = 5;
		this->label2->Text = L".";
		// 
		// Box4
		// 
		this->Box4->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->Box4->Location = System::Drawing::Point(100, 0);
		this->Box4->MaxLength = 3;
		this->Box4->Name = L"Box4";
		this->Box4->Size = System::Drawing::Size(20, 13);
		this->Box4->TabIndex = 4;
		this->Box4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->Box4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ControlIPBox::Box4_KeyPress);
		// 
		// Box3
		// 
		this->Box3->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->Box3->Location = System::Drawing::Point(64, 0);
		this->Box3->MaxLength = 3;
		this->Box3->Name = L"Box3";
		this->Box3->Size = System::Drawing::Size(20, 13);
		this->Box3->TabIndex = 3;
		this->Box3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->Box3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ControlIPBox::Box3_KeyPress);
		// 
		// Box2
		// 
		this->Box2->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->Box2->Location = System::Drawing::Point(32, 0);
		this->Box2->MaxLength = 3;
		this->Box2->Name = L"Box2";
		this->Box2->Size = System::Drawing::Size(20, 13);
		this->Box2->TabIndex = 2;
		this->Box2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->Box2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ControlIPBox::Box2_KeyPress);
		// 
		// label1
		// 
		this->label1->Location = System::Drawing::Point(56, 0);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(8, 13);
		this->label1->TabIndex = 1;
		this->label1->Text = L".";
		// 
		// Box1
		// 
		this->Box1->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->Box1->Location = System::Drawing::Point(4, 0);
		this->Box1->MaxLength = 3;
		this->Box1->Name = L"Box1";
		this->Box1->Size = System::Drawing::Size(20, 13);
		this->Box1->TabIndex = 1;
		this->Box1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		this->Box1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &ControlIPBox::Box1_KeyPress);
		// 
		// ControlIPBox
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->Controls->Add(this->panel1);
		this->Name = L"ControlIPBox";
		this->Size = System::Drawing::Size(128, 18);
		this->panel1->ResumeLayout(false);
		this->panel1->PerformLayout();
		this->ResumeLayout(false);

	}
	private: bool IsValid(String^ inString)
	{
		try
		{
			int theValue = int::Parse(inString);
			if (theValue >= 0 && theValue <= 255)
				return true;
			else
			{
				MessageBox::Show("Must Be Between 0 and 255", "Out Of Range");
				return false;
			}
		}
		catch (...)
		{
			return false;
		}
	}

	private: void Box_Enter(Object^ sender, System::EventArgs e)
	{
		TextBox^ tb = (TextBox^)sender;
		tb->SelectAll();
	}

	private: void label_EnabledChanged(Object^ sender, System::EventArgs e)
	{
		Label^ lbl = (Label^)sender;
		if (lbl->Enabled)
			lbl->BackColor = SystemColors::Window;
		else
			lbl->BackColor = SystemColors::Control;
	}

	private: void panel1_EnabledChanged(Object^ sender, System::EventArgs e)
	{
		Panel^ pan = (Panel^)sender;
		if (pan->Enabled)
			pan->BackColor = SystemColors::Window;
		else
			pan->BackColor = SystemColors::Control;
	}
	private: System::Void Box1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		//Only Accept a '.', a numeral, or backspace
		if (e->KeyChar.ToString() == "." || Char::IsDigit(e->KeyChar) || e->KeyChar == 8)
		{
			//If the key pressed is a '.'
			if (e->KeyChar.ToString() == ".")
			{
				//If the Text is a valid ip octet move to the next box
				if (Box1->Text != "" && Box1->Text->Length != Box1->SelectionLength)
				{
					if (IsValid(Box1->Text))
						Box2->Focus();
					else
						Box1->SelectAll();
				}
				e->Handled = true;
			}

			//If we are not overwriting the whole text
			else if (Box1->SelectionLength != Box1->Text->Length)
			{
				//Check that the new Text value will be a valid
				// ip octet then move on to next box
				if (Box1->Text->Length == 2)
				{
					if (e->KeyChar == 8)
						Box1->Text->Remove(Box1->Text->Length - 1, 1);
					else if (!IsValid(Box1->Text + e->KeyChar.ToString()))
					{
						Box1->SelectAll();
						e->Handled = true;
					}
					else
					{
						Box2->Focus();
					}
				}
			}
		}
		//Do nothing if the keypress is not numeral, backspace, or '.'
		else
			e->Handled = true;
	}
	private: System::Void Box2_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		if (e->KeyChar.ToString() == "." || Char::IsDigit(e->KeyChar) || e->KeyChar == 8)
		{
			if (e->KeyChar.ToString() == ".")
			{
				if (Box2->Text != "" && Box2->Text->Length != Box2->SelectionLength)
				{
					if (IsValid(Box1->Text))
						Box3->Focus();
					else
						Box2->SelectAll();
				}
				e->Handled = true;
			}
			else if (Box2->SelectionLength != Box2->Text->Length)
			{
				if (Box2->Text->Length == 2)
				{
					if (e->KeyChar == 8)
					{
						Box2->Text->Remove(Box2->Text->Length - 1, 1);
					}
					else if (!IsValid(Box2->Text + e->KeyChar.ToString()))
					{
						Box2->SelectAll();
						e->Handled = true;
					}
					else
					{
						Box3->Focus();
					}
				}
			}
			else if (Box2->Text->Length == 0 && e->KeyChar == 8)
			{
				Box1->Focus();
				Box1->SelectionStart = Box1->Text->Length;
			}
		}
		else
			e->Handled = true;

	}

	private: System::Void Box3_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		if (e->KeyChar.ToString() == "." || Char::IsDigit(e->KeyChar) || e->KeyChar == 8)
		{
			if (e->KeyChar.ToString() == ".")
			{
				if (Box3->Text != "" && Box3->SelectionLength != Box3->Text->Length)
				{
					if (IsValid(Box1->Text))
						Box4->Focus();
					else
						Box3->SelectAll();
				}
				e->Handled = true;
			}
			else if (Box3->SelectionLength != Box3->Text->Length)
			{
				if (Box3->Text->Length == 2)
				{
					if (e->KeyChar == 8)
					{
						Box3->Text->Remove(Box3->Text->Length - 1, 1);
					}
					else if (!IsValid(Box3->Text + e->KeyChar.ToString()))
					{
						Box3->SelectAll();
						e->Handled = true;
					}
					else
					{
						Box4->Focus();
					}
				}
			}
			else if (Box3->Text->Length == 0 && e->KeyChar == 8)
			{
				Box2->Focus();
				Box2->SelectionStart = Box2->Text->Length;
			}
		}
		else
			e->Handled = true;
	}
	private: System::Void Box4_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
		//Similar to Box3 but ignores the '.' character and does not advance
		//to the next box.  Also Box3 is previous box for backspace case->
		if (Char::IsDigit(e->KeyChar) || e->KeyChar == 8)
		{
			if (Box4->SelectionLength != Box4->Text->Length)
			{
				if (Box4->Text->Length == 2)
				{
					if (e->KeyChar == 8)
					{
						Box4->Text->Remove(Box4->Text->Length - 1, 1);
					}
					else if (!IsValid(Box4->Text + e->KeyChar.ToString()))
					{
						Box4->SelectAll();
						e->Handled = true;
					}
				}
			}
			else if (Box4->Text->Length == 0 && e->KeyChar == 8)
			{
				Box3->Focus();
				Box3->SelectionStart = Box3->Text->Length;
			}
		}
		else
			e->Handled = true;
	}
	};
}

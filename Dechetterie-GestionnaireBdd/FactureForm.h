#pragma once
#include "BDD.h"

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de FactureForm
	/// </summary>
	public ref class FactureForm : public System::Windows::Forms::Form
	{
	public:
		FactureForm(int factureID)
		{
			factureId = factureID;
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
		}

	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~FactureForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  lDate;
	private: System::Windows::Forms::Label^  lNumero;
	private: System::Windows::Forms::ListView^  lv;

	private: System::Windows::Forms::ColumnHeader^  chDesignation;
	private: System::Windows::Forms::ColumnHeader^  chPrixUnitaire;
	private: System::Windows::Forms::ColumnHeader^  chQuantite;
	private: System::Windows::Forms::ColumnHeader^  chUnite;
	private: System::Windows::Forms::ColumnHeader^  chPrixTotal;
	private: System::Windows::Forms::Label^  lPrenomNom;
	private: System::Windows::Forms::Label^  lRueAdresse;
	private: System::Windows::Forms::Label^  lCodePostalVille;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  lPrixTotal;

			 int factureId;
			 BDD^ bdd;
			 DataFacture^df;
			 DataUser^ du;
			 List<DataHistorique^>^ lh;
			 float total = 0.0;


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
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->lDate = (gcnew System::Windows::Forms::Label());
			this->lNumero = (gcnew System::Windows::Forms::Label());
			this->lv = (gcnew System::Windows::Forms::ListView());
			this->chDesignation = (gcnew System::Windows::Forms::ColumnHeader());
			this->chPrixUnitaire = (gcnew System::Windows::Forms::ColumnHeader());
			this->chQuantite = (gcnew System::Windows::Forms::ColumnHeader());
			this->chUnite = (gcnew System::Windows::Forms::ColumnHeader());
			this->chPrixTotal = (gcnew System::Windows::Forms::ColumnHeader());
			this->lPrenomNom = (gcnew System::Windows::Forms::Label());
			this->lRueAdresse = (gcnew System::Windows::Forms::Label());
			this->lCodePostalVille = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->lPrixTotal = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(56, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(85, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Facture";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(21, 158);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(95, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Numéro de facture";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(21, 181);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(92, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Date de la facture";
			// 
			// lDate
			// 
			this->lDate->AutoSize = true;
			this->lDate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lDate->Location = System::Drawing::Point(133, 181);
			this->lDate->Name = L"lDate";
			this->lDate->Size = System::Drawing::Size(27, 13);
			this->lDate->TabIndex = 3;
			this->lDate->Text = L"n/a";
			// 
			// lNumero
			// 
			this->lNumero->AutoSize = true;
			this->lNumero->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lNumero->Location = System::Drawing::Point(133, 158);
			this->lNumero->Name = L"lNumero";
			this->lNumero->Size = System::Drawing::Size(27, 13);
			this->lNumero->TabIndex = 3;
			this->lNumero->Text = L"n/a";
			// 
			// lv
			// 
			this->lv->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
				this->chDesignation, this->chPrixUnitaire,
					this->chQuantite, this->chUnite, this->chPrixTotal
			});
			this->lv->GridLines = true;
			this->lv->Location = System::Drawing::Point(24, 238);
			this->lv->Name = L"lv";
			this->lv->Size = System::Drawing::Size(563, 325);
			this->lv->TabIndex = 6;
			this->lv->UseCompatibleStateImageBehavior = false;
			this->lv->View = System::Windows::Forms::View::Details;
			// 
			// chDesignation
			// 
			this->chDesignation->Text = L"Désignation";
			this->chDesignation->Width = 200;
			// 
			// chPrixUnitaire
			// 
			this->chPrixUnitaire->Text = L"Prix unitaire";
			this->chPrixUnitaire->Width = 100;
			// 
			// chQuantite
			// 
			this->chQuantite->Text = L"Quantité";
			this->chQuantite->Width = 99;
			// 
			// chUnite
			// 
			this->chUnite->Text = L"Unité";
			// 
			// chPrixTotal
			// 
			this->chPrixTotal->Text = L"Prix total";
			this->chPrixTotal->Width = 100;
			// 
			// lPrenomNom
			// 
			this->lPrenomNom->AutoSize = true;
			this->lPrenomNom->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lPrenomNom->Location = System::Drawing::Point(360, 92);
			this->lPrenomNom->Name = L"lPrenomNom";
			this->lPrenomNom->Size = System::Drawing::Size(27, 13);
			this->lPrenomNom->TabIndex = 7;
			this->lPrenomNom->Text = L"n/a";
			// 
			// lRueAdresse
			// 
			this->lRueAdresse->AutoSize = true;
			this->lRueAdresse->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lRueAdresse->Location = System::Drawing::Point(360, 116);
			this->lRueAdresse->Name = L"lRueAdresse";
			this->lRueAdresse->Size = System::Drawing::Size(27, 13);
			this->lRueAdresse->TabIndex = 9;
			this->lRueAdresse->Text = L"n/a";
			// 
			// lCodePostalVille
			// 
			this->lCodePostalVille->AutoSize = true;
			this->lCodePostalVille->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lCodePostalVille->Location = System::Drawing::Point(360, 139);
			this->lCodePostalVille->Name = L"lCodePostalVille";
			this->lCodePostalVille->Size = System::Drawing::Size(27, 13);
			this->lCodePostalVille->TabIndex = 10;
			this->lCodePostalVille->Text = L"n/a";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(219, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(122, 25);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Dechetterie";
			// 
			// lPrixTotal
			// 
			this->lPrixTotal->AutoSize = true;
			this->lPrixTotal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lPrixTotal->Location = System::Drawing::Point(498, 577);
			this->lPrixTotal->Name = L"lPrixTotal";
			this->lPrixTotal->Size = System::Drawing::Size(27, 13);
			this->lPrixTotal->TabIndex = 12;
			this->lPrixTotal->Text = L"n/a";
			// 
			// FactureForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(621, 799);
			this->Controls->Add(this->lPrixTotal);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->lCodePostalVille);
			this->Controls->Add(this->lRueAdresse);
			this->Controls->Add(this->lPrenomNom);
			this->Controls->Add(this->lv);
			this->Controls->Add(this->lNumero);
			this->Controls->Add(this->lDate);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"FactureForm";
			this->Text = L"FactureForm";
			this->Load += gcnew System::EventHandler(this, &FactureForm::FactureForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: System::Void FactureForm_Load(System::Object^  sender, System::EventArgs^  e) {
	bdd = BDD::getBdd();
	try
	{
		
		df = bdd->getFactureByID(factureId);
		du = bdd->getUserByID(df->ID_Utilisateur);
		bdd->UpdateFacture(du->ID);
		df = bdd->getFactureByID(factureId);
		lh = bdd->getTableHistoriqueByFactureID(factureId);

		lPrenomNom->Text = du->Prenom + " " + du->Nom;
		lRueAdresse->Text = du->numero + " " + du->Adresse;
		lCodePostalVille->Text = du->Code_Postal + " " + du->Ville;
		
		lNumero->Text = factureId.ToString();
		lDate->Text = df->dt->ToString();

		for each (DataHistorique^ var in lh)
		{
			DataDechet^dd = bdd->getDechetByID(var->ID_Dechet);
			ListViewItem^ lvi = gcnew ListViewItem(dd->Nom);
			lvi->SubItems->Add(dd->Prix.ToString());
			lvi->SubItems->Add(var->Poids.ToString());
			lvi->SubItems->Add("kg");
			lvi->SubItems->Add((var->Poids*dd->Prix).ToString());
			total += (var->Poids*dd->Prix);

			lv->Items->Add(lvi);
		}
		lPrixTotal->Text = total.ToString();

	}
	catch (...)
	{

	}
}
};


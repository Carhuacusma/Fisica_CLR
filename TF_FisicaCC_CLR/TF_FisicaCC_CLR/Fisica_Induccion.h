#pragma once
#include "simulacion.h"

namespace TFFisicaCCCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Fisica_Induccion
	/// </summary>
	public ref class Fisica_Induccion : public System::Windows::Forms::Form
	{
	public:
		Fisica_Induccion(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Fisica_Induccion()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ picBoxDetectpr;
	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Fisica_Induccion::typeid));
			this->picBoxDetectpr = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBoxDetectpr))->BeginInit();
			this->SuspendLayout();
			// 
			// picBoxDetectpr
			// 
			this->picBoxDetectpr->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->picBoxDetectpr->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->picBoxDetectpr->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"picBoxDetectpr.Image")));
			this->picBoxDetectpr->Location = System::Drawing::Point(22, 12);
			this->picBoxDetectpr->Name = L"picBoxDetectpr";
			this->picBoxDetectpr->Size = System::Drawing::Size(199, 165);
			this->picBoxDetectpr->TabIndex = 0;
			this->picBoxDetectpr->TabStop = false;
			// 
			// Fisica_Induccion
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(547, 332);
			this->Controls->Add(this->picBoxDetectpr);
			this->Name = L"Fisica_Induccion";
			this->Text = L"Fisica_Induccion";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBoxDetectpr))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}

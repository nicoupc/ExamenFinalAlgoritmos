#pragma once

#include <ctime>
#include <cstdlib>
#include "CBacteria.h"
#include "COrgano.h"

namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic; // Para List<>

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		List<CBacteria^>^ bacterias;
		Bitmap^ spriteBacteria;
		// Imágenes de órganos
		List<COrgano^>^ organos;
		Bitmap^ imgCorazonSano;
		Bitmap^ imgCorazonInfectado;
		Bitmap^ imgPulmonSano;
		Bitmap^ imgPulmonInfectado;
		Bitmap^ imgRinonSano;
		Bitmap^ imgRinonInfectado;
		Bitmap^ imgCerebroSano;
		Bitmap^ imgCerebroInfectado;


	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			srand(static_cast<unsigned int>(time(0))); // Semilla para números aleatorios

			spriteBacteria = gcnew Bitmap("Bacteria.png");
			bacterias = gcnew List<CBacteria^>();

			// Cargar imágenes
			imgCorazonSano = gcnew Bitmap("Corazon.png");
			imgCorazonInfectado = gcnew Bitmap("CorazonInfectado.png");
			imgPulmonSano = gcnew Bitmap("Pulmon.png");
			imgPulmonInfectado = gcnew Bitmap("PulmonInfectado.png");
			imgRinonSano = gcnew Bitmap("Rinon.png");
			imgRinonInfectado = gcnew Bitmap("RinonInfectado.png");
			imgCerebroSano = gcnew Bitmap("Cerebro.png");
			imgCerebroInfectado = gcnew Bitmap("CerebroInfectado.png");

			// Crear órganos
			organos = gcnew List<COrgano^>();
			organos->Add(gcnew COrgano(imgCorazonSano, imgCorazonInfectado, this->ClientSize.Width, this->ClientSize.Height));
			organos->Add(gcnew COrgano(imgPulmonSano, imgPulmonInfectado, this->ClientSize.Width, this->ClientSize.Height));
			organos->Add(gcnew COrgano(imgRinonSano, imgRinonInfectado, this->ClientSize.Width, this->ClientSize.Height));
			organos->Add(gcnew COrgano(imgCerebroSano, imgCerebroInfectado, this->ClientSize.Width, this->ClientSize.Height));

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::Timer^ timer1;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(1100, 800);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::presionarTecla);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::soltarTecla);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ context = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = context->Allocate(g, this->ClientRectangle);
		buffer->Graphics->DrawImage(this->BackgroundImage, 0, 0, this->ClientSize.Width, this->ClientSize.Height);

		for each (COrgano ^ o in organos) {
			o->dibujar(buffer->Graphics);
		}

		for each (CBacteria ^ b in bacterias) {
			b->mover(this->ClientSize.Width, this->ClientSize.Height);
			b->dibujar(buffer->Graphics);
		}

		buffer->Render();
		delete buffer;
		delete g;
	}
	private: System::Void soltarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	}
	private: System::Void presionarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::E) {
			int cantidadBacterias = 4 + rand() % 3; // entre 4 y 6

			for (int i = 0; i < cantidadBacterias; i++) {
				bacterias->Add(gcnew CBacteria(spriteBacteria, this->ClientSize.Width, this->ClientSize.Height));
			}
		}
	}
	};
}

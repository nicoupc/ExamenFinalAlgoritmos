#pragma once

#include "CEnfermera.h"
#include "CEnfermo.h"

namespace ExamenFinalAlgoritmos {

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
		CEnfermera^ enfermera;
		Label^ lblVidas;
		Label^ lblContador;
		DateTime tiempoInicio;
		int contador = 0;
		List<CEnfermo^>^ enfermos;

	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			enfermera = gcnew CEnfermera();
			tiempoInicio = DateTime::Now;

			enfermos = gcnew List<CEnfermo^>();
			Random^ r = gcnew Random();
			int cantidad = r->Next(5, 8);
			for (int i = 0; i < cantidad; i++) {
				int px = r->Next(0, this->ClientSize.Width - 60);
				int py = r->Next(0, this->ClientSize.Height - 60);
				enfermos->Add(gcnew CEnfermo("Enfermo.jpg", px, py, r->Next(4, 10)));
			}
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
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

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
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			//
			// Labels for Vidas
			//
			this->lblVidas = gcnew Label();
			this->lblVidas->AutoSize = true;
			this->lblVidas->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
			this->lblVidas->ForeColor = Color::Red;
			this->lblVidas->BackColor = Color::Transparent;
			this->lblVidas->Text = "Vidas: ";
			this->Controls->Add(this->lblVidas);
			//
			// Labels for Contador
			//
			this->lblContador = gcnew Label();
			this->lblContador->AutoSize = true;
			this->lblContador->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
			this->lblContador->ForeColor = Color::Black;
			this->lblContador->BackColor = Color::Transparent;
			this->lblContador->Text = "Contador: ";
			this->Controls->Add(this->lblContador);

			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(900, 600);
			this->Name = L"MyForm";
			this->Text = L"Virus 2035.10";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::presionarTecla);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::soltarTecla);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ context = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = context->Allocate(g, this->ClientRectangle);
		buffer->Graphics->Clear(Color::White);

		enfermera->mover(this->ClientSize.Width, this->ClientSize.Height);

		enfermera->dibujar(buffer);

		for each (CEnfermo ^ e in enfermos) {
			e->mover(this->ClientSize.Width, this->ClientSize.Height);
			e->dibujar(buffer);

			if (!enfermera->estaInvulnerable() && e->getRectangulo().IntersectsWith(enfermera->obtenerRectangulo())) {
				enfermera->reducirVidas();
				enfermera->activarInvulnerabilidad();
			}
		}

		// Vidas – esquina superior derecha
		lblVidas->Location = Point(this->ClientSize.Width - lblVidas->PreferredWidth - 10, 10);

		// Contador – esquina superior izquierda
		lblContador->Location = Point(10, 10);

		lblVidas->Text = "Vidas: " + enfermera->getVidas();

		TimeSpan tiempoTranscurrido = DateTime::Now - tiempoInicio;
		int segundos = tiempoTranscurrido.Seconds + tiempoTranscurrido.Minutes * 60;

		lblContador->Location = Point(10, 10);
		lblContador->Text = "Tiempo: " + segundos + "s";

		// Mostrar el dibujo
		buffer->Render();

		// Liberar recursos
		delete buffer;
		delete g;
	}
	private: System::Void soltarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		enfermera->setDireccion(Ninguna);
	}
	private: System::Void presionarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Down) {
			enfermera->setDireccion(Abajo);
		}
		else if (e->KeyCode == Keys::Left) {
			enfermera->setDireccion(Izquierda);
		}
		else if (e->KeyCode == Keys::Right) {
			enfermera->setDireccion(Derecha);
		}
		else if (e->KeyCode == Keys::Up) {
			enfermera->setDireccion(Arriba);
		}
	}
	};
}

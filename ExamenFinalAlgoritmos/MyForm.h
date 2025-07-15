#pragma once

#include <cstdlib> // para rand
#include <ctime>   // para time
#include "CEnfermera.h"
#include "CEnfermo.h"
#include "CVacuna.h"
#include "CVacunaDisparada.h"

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
		List<CVacuna^>^ vacunas;
		int inventarioVacunas = 0;
		Label^ lblVacunas;
		List<CVacunaDisparada^>^ vacunasDisparadas;
		int contadorCurados = 0;
		Label^ lblCurados;
		Bitmap^ sprite;
		Bitmap^ imagenCurado;
		bool mostrarVictoria = false;

	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			// Inicializar el generador de números aleatorios
			srand(static_cast<unsigned int>(time(0))); // Semilla para números aleatorios

			enfermera = gcnew CEnfermera();
			tiempoInicio = DateTime::Now;

			sprite = gcnew Bitmap("Enfermo.jpg");
			imagenCurado = gcnew Bitmap("Curado.jpg");

			// Crear enfermos
			enfermos = gcnew List<CEnfermo^>();
			int cantidad = 5 + rand() % 3; // entre 5 y 7

			for (int i = 0; i < cantidad; i++) {
				int px = rand() % (this->ClientSize.Width - 60);
				int py = rand() % (this->ClientSize.Height - 60);
				int velocidad = 4 + rand() % 9; // entre 4 y 12
				enfermos->Add(gcnew CEnfermo(sprite, px, py, velocidad));
			}

			// Crear vacunas
			vacunas = gcnew List<CVacuna^>();
			int cantidadVacunas = enfermos->Count + rand() % enfermos->Count; // entre n y (2n - 1)

			for (int i = 0; i < cantidadVacunas; i++) {
				vacunas->Add(gcnew CVacuna(this->ClientSize.Width, this->ClientSize.Height));
			}

			vacunasDisparadas = gcnew List<CVacunaDisparada^>();
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
			// Label for inventario de vacunas
			this->lblVacunas = gcnew Label();
			this->lblVacunas->AutoSize = true;
			this->lblVacunas->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
			this->lblVacunas->ForeColor = Color::DarkGreen;
			this->lblVacunas->BackColor = Color::Transparent;
			this->lblVacunas->Text = "Vacunas: 0";
			this->Controls->Add(this->lblVacunas);
			// Label for contador de curados
			lblCurados = gcnew Label();
			lblCurados->AutoSize = true;
			lblCurados->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
			lblCurados->ForeColor = Color::DarkBlue;
			lblCurados->BackColor = Color::Transparent;
			lblCurados->Text = "Curados: 0";
			this->Controls->Add(lblCurados);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1000, 600);
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

		for (int i = vacunas->Count - 1; i >= 0; i--) {
			if (vacunas[i]->getRectangulo().IntersectsWith(enfermera->obtenerRectangulo())) {
				vacunas->RemoveAt(i);
				inventarioVacunas++;
			}
			else {
				vacunas[i]->dibujar(buffer);
			}
		}

		for (int i = vacunasDisparadas->Count - 1; i >= 0; i--) {
			CVacunaDisparada^ disparo = vacunasDisparadas[i];
			disparo->mover();

			bool colisiono = false;

			for each(CEnfermo ^ enfermo in enfermos) {
				if (!enfermo->estaCurado() &&
					disparo->getRectangulo().IntersectsWith(enfermo->getRectangulo())) {

					enfermo->curar(imagenCurado); // <- Cambia su sprite y estado
					vacunasDisparadas->RemoveAt(i);
					colisiono = true;
					contadorCurados++;
					break;
				}
			}

			if (colisiono) continue;

			if (disparo->getX() < 0 || disparo->getY() < 0 ||
				disparo->getX() > this->ClientSize.Width ||
				disparo->getY() > this->ClientSize.Height) {

				vacunasDisparadas->RemoveAt(i);
				enfermera->reducirVidas(); // falla -> pierde vida
				continue;
			}

			disparo->dibujar(buffer);
		}

		for each(CEnfermo ^ e in enfermos) {
			e->mover(this->ClientSize.Width, this->ClientSize.Height);
			e->dibujar(buffer);

			if (!enfermera->estaInvulnerable() &&
				!e->estaCurado() &&
				e->getRectangulo().IntersectsWith(enfermera->obtenerRectangulo())) {

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

		lblVacunas->Location = Point((this->ClientSize.Width - lblVacunas->PreferredWidth) / 2, 10);
		lblVacunas->Text = "Vacunas: " + inventarioVacunas;

		lblCurados->Location = Point(10, 40); // debajo de lblContador
		lblCurados->Text = "Curados: " + contadorCurados;

		if (enfermera->getVidas() <= 0) {
			timer1->Stop(); // Detener el juego

			MessageBox::Show("VIRUS EXTREMO", "FIN DEL JUEGO", MessageBoxButtons::OK, MessageBoxIcon::Error);

			Application::Exit(); // Cierra la aplicación
			return;
		}

		bool todosCurados = true;
		for each(CEnfermo ^ e in enfermos) {
			if (!e->estaCurado()) {
				todosCurados = false;
				break;
			}
		}

		if (todosCurados) {
			mostrarVictoria = true;
		}

		// Mostrar el dibujo
		buffer->Render();

		if (mostrarVictoria) {
			timer1->Stop();
			MessageBox::Show("MISION CUMPLIDA", "¡Felicidades!", MessageBoxButtons::OK, MessageBoxIcon::Information);
			Application::Exit();
		}

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
		else if (e->KeyCode == Keys::V) {
			if (inventarioVacunas > 0) {
				inventarioVacunas--;

				DireccionVacuna dir;

				switch (enfermera->getUltimaDireccion()) {
				case Derecha: dir = VDerecha; break;
				case Izquierda: dir = VIzquierda; break;
				case Arriba: dir = VArriba; break;
				case Abajo: dir = VAbajo; break;
				default: dir = VAbajo;
				}

				int px = enfermera->getX() + 20;
				int py = enfermera->getY() + 20;

				vacunasDisparadas->Add(gcnew CVacunaDisparada("Vacuna.png", px, py, dir));
			}
			else {
				MessageBox::Show("No cuenta con vacuna disponible!", "Inventario vacío", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}
	}
	};
}

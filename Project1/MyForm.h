#pragma once

#include <ctime>
#include <cstdlib>
#include "CBacteria.h"
#include "COrgano.h"
#include "CDrix.h"
#include "CProyectil.h"

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
		Bitmap^ imgRinonSano;
		Bitmap^ imgRinonInfectado;
		Bitmap^ imgHigadoSano;
		Bitmap^ imgHigadoInfectado;
		CDrix^ drix;
		bool mostrarDrix;
		List<CProyectil^>^ proyectiles;
		Bitmap^ imgAspirina;
		Bitmap^ imgPastilla;
		int contadorAspirina = 0;
		int contadorPastilla = 0;
		DateTime tiempoInicio;
		bool juegoTerminado = false;
		bool juegoActivo = false;

		void guardarResultados() {
			TimeSpan duracion = DateTime::Now - tiempoInicio;
			int segundos = (int)duracion.TotalSeconds;

			System::IO::StreamWriter^ archivo = gcnew System::IO::StreamWriter("RESULTADOS.TXT");
			archivo->WriteLine("Tiempo total (segundos): " + segundos);
			archivo->WriteLine("Total de Pastillas utilizadas: " + contadorPastilla);
			archivo->WriteLine("Total de Aspirinas utilizadas: " + contadorAspirina);
			archivo->Close();
		}

		void dibujarContadores(Graphics^ g) {
			TimeSpan transcurrido = DateTime::Now - tiempoInicio;
			int segundos = (int)transcurrido.TotalSeconds;

			StringFormat^ formato = gcnew StringFormat();
			formato->Alignment = StringAlignment::Near;

			System::Drawing::Font^ fuente = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			SolidBrush^ brush = gcnew SolidBrush(Color::White);

			g->DrawString("Tiempo: " + segundos + "s", fuente, brush, 10, 10, formato);
			g->DrawString("Aspirinas disparadas: " + contadorAspirina, fuente, brush, 10, 40, formato);
			g->DrawString("Pastillas disparadas: " + contadorPastilla, fuente, brush, 10, 70, formato);
		}

	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			srand(static_cast<unsigned int>(time(0))); // Semilla para números aleatorios
			tiempoInicio = DateTime::Now;

			spriteBacteria = gcnew Bitmap("Bacteria.png");
			bacterias = gcnew List<CBacteria^>();

			// Cargar imágenes
			imgCorazonSano = gcnew Bitmap("Corazon.png");
			imgCorazonInfectado = gcnew Bitmap("CorazonInfectado.png");
			imgRinonSano = gcnew Bitmap("Rinon.png");
			imgRinonInfectado = gcnew Bitmap("RinonInfectado.png");
			imgHigadoSano = gcnew Bitmap("Higado.png");
			imgHigadoInfectado = gcnew Bitmap("HigadoInfectado.png");

			// Crear órganos
			organos = gcnew List<COrgano^>();
			organos->Add(gcnew COrgano(imgCorazonSano, imgCorazonInfectado, this->ClientSize.Width, this->ClientSize.Height));
			organos->Add(gcnew COrgano(imgRinonSano, imgRinonInfectado, this->ClientSize.Width, this->ClientSize.Height));
			organos->Add(gcnew COrgano(imgHigadoSano, imgHigadoInfectado, this->ClientSize.Width, this->ClientSize.Height));

			drix = gcnew CDrix();
			mostrarDrix = false;

			imgAspirina = gcnew Bitmap("Aspirina.png");
			imgPastilla = gcnew Bitmap("Pastilla.png");
			proyectiles = gcnew List<CProyectil^>();
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

		// Ayuda IA
		for each (CBacteria ^ b in bacterias) {
			b->mover(this->ClientSize.Width, this->ClientSize.Height);
			b->dibujar(buffer->Graphics);

			Rectangle rectBacteria = b->getRectangulo();

			for each (COrgano ^ o in organos) {
				if (!o->estaInfectado() && rectBacteria.IntersectsWith(o->getRectangulo())) {
					o->infectar();
				}
			}
		}

		mostrarDrix = false;

		// Ayuda IA
		for each (COrgano ^ o in organos) {
			if (o->estaInfectado()) {
				mostrarDrix = true;
				break;
			}
		}

		// Ayuda IA
		if (mostrarDrix) {
			drix->mover(this->ClientSize.Width, this->ClientSize.Height);
			drix->dibujar(buffer);
		}

		// Ayuda IA
		for (int i = proyectiles->Count - 1; i >= 0; i--) {
			CProyectil^ p = proyectiles[i];
			p->mover();
			p->dibujar(buffer->Graphics);

			// Detectar impacto
			if (p->getTipo() == TipoProyectil::Aspirina) {
				for (int j = bacterias->Count - 1; j >= 0; j--) {
					if (p->obtenerRectangulo().IntersectsWith(bacterias[j]->getRectangulo())) {
						bacterias->RemoveAt(j);
						proyectiles->RemoveAt(i);
						break;
					}
				}
			}
			else if (p->getTipo() == TipoProyectil::Pastilla) {
				for each (COrgano ^ o in organos) {
					if (o->estaInfectado() && p->obtenerRectangulo().IntersectsWith(o->getRectangulo())) {
						o->curar();
						o->dibujar(buffer->Graphics); // redibuja al instante con la imagen sana
						proyectiles->RemoveAt(i);
						break;
					}
				}
			}

			if (i < proyectiles->Count && p->estaFuera(this->ClientSize.Width, this->ClientSize.Height))
				proyectiles->RemoveAt(i);
		}

		// Ayuda IA
		bool todosSaludables = true;
		for each (COrgano ^ o in organos) {
			if (o->estaInfectado()) {
				todosSaludables = false;
				break;
			}
		}

		dibujarContadores(buffer->Graphics);

		buffer->Render();

		if (juegoActivo && !juegoTerminado && bacterias->Count == 0 && todosSaludables) {
			guardarResultados();
			juegoTerminado = true;
			timer1->Enabled = false;
			MessageBox::Show(
				"¡Felicidades! Drix ha completado su misión saludable con éxito.\n\n"
				"Los resultados han sido guardados en el archivo RESULTADOS.TXT.\n"
				"Gracias por jugar!",
				"Victoria",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
			// Terminar el juego
			Application::Exit();
		}

		delete buffer;
		delete g;
	}
	private: System::Void soltarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (mostrarDrix) {
			if (e->KeyCode == Keys::Up || e->KeyCode == Keys::Down ||
				e->KeyCode == Keys::Left || e->KeyCode == Keys::Right) {
				drix->setDireccion(DireccionDrix::Ninguna);
			}
		}
	}
	private: System::Void presionarTecla(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::E) {
			juegoActivo = true;
			int cantidadBacterias = 4 + rand() % 3;
			for (int i = 0; i < cantidadBacterias; i++) {
				bacterias->Add(gcnew CBacteria(spriteBacteria, this->ClientSize.Width, this->ClientSize.Height));
			}
		}

		// Ayuda IA
		if (mostrarDrix) {
			if (e->KeyCode == Keys::Up)        drix->setDireccion(DireccionDrix::Arriba);
			else if (e->KeyCode == Keys::Down) drix->setDireccion(DireccionDrix::Abajo);
			else if (e->KeyCode == Keys::Left) drix->setDireccion(DireccionDrix::Izquierda);
			else if (e->KeyCode == Keys::Right)drix->setDireccion(DireccionDrix::Derecha);
		}

		// Ayuda IA
		if (mostrarDrix) {
			if (e->KeyCode == Keys::A) {
				proyectiles->Add(gcnew CProyectil(imgAspirina, TipoProyectil::Aspirina, drix->getX(), drix->getY(), drix->getUltimaDireccion()));
				contadorAspirina++;
			}
			else if (e->KeyCode == Keys::P) {
				proyectiles->Add(gcnew CProyectil(imgPastilla, TipoProyectil::Pastilla, drix->getX(), drix->getY(), drix->getUltimaDireccion()));
				contadorPastilla++;
			}
		}
	}
	};
}

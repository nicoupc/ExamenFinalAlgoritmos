#pragma once
using namespace System;
using namespace System::Drawing;

enum DireccionEnfermera { Ninguna, Abajo, Izquierda, Derecha, Arriba };

ref class CEnfermera {
private:
	int x, y;
	int ancho, alto;
	int indiceX, indiceY;
	int vidas;
	float velocidad;
	DireccionEnfermera direccion;
	DireccionEnfermera ultimaDireccion;
	Bitmap^ imagen;

public:
	CEnfermera() {
		// Inicializar variables
		x = 100;
		y = 100;
		//ancho = 32;
		//alto = 48;
		indiceX = 0;
		indiceY = 0;

		velocidad = 15;
		direccion = Ninguna;
		ultimaDireccion = Abajo;

		imagen = gcnew Bitmap("Enfermera.png");

		int columnas = 4;
		int filas = 4;

		ancho = imagen->Width / columnas;
		alto = imagen->Height / filas;
		vidas = 3;
	}

	void mover(int anchoVentana, int altoVentana)
	{
		switch (direccion) {
		case Abajo:
			indiceY = 0;
			indiceX = (indiceX + 1) % 4;
			y += velocidad;
			ultimaDireccion = Abajo;
			break;
		case Izquierda:
			indiceY = 1;
			indiceX = (indiceX + 1) % 4;
			x -= velocidad;
			ultimaDireccion = Izquierda;
			break;
		case Derecha:
			indiceY = 2;
			indiceX = (indiceX + 1) % 4;
			x += velocidad;
			ultimaDireccion = Derecha;
			break;
		case Arriba:
			indiceY = 3;
			indiceX = (indiceX + 1) % 4;
			y -= velocidad;
			ultimaDireccion = Arriba;
			break;
		case Ninguna:
			indiceX = 0;
			indiceY = static_cast<int>(ultimaDireccion) - 1;
			break;
		}

		// Limitar movimiento dentro de la ventana
		if (x < 0) x = 0;
		if (y < 0) y = 0;
		if (x + ancho > anchoVentana) x = anchoVentana - ancho;
		if (y + alto > altoVentana) y = altoVentana - alto;
	}

	void dibujar(BufferedGraphics^ buffer) {
		Rectangle origen = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle destino = Rectangle(x, y, ancho, alto);

		buffer->Graphics->DrawImage(imagen, destino, origen, GraphicsUnit::Pixel);

		// Dibujar rectangulo rojo para colisiones si queres visualizarlo
		Pen^ pen = gcnew Pen(Color::Red, 2);
		buffer->Graphics->DrawRectangle(pen, obtenerRectangulo());
	}

	Rectangle obtenerRectangulo() {
		return Rectangle(x, y, ancho, alto);
	}

	void setDireccion(DireccionEnfermera nueva) {
		direccion = nueva;
	}

	void reducirVidas() {
		vidas--;
	}

	int getX() { return x; }
	int getY() { return y; }
	int getVidas() { return vidas; }

	DireccionEnfermera getUltimaDireccion() { return ultimaDireccion; }
};

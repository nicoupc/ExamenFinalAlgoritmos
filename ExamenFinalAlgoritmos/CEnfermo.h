#pragma once
#include <cstdlib> // para rand
using namespace System;
using namespace System::Drawing;

ref class CEnfermo {
private:
    int x, y;
    int direccion; // 0: derecha, 1: izquierda, 2: arriba, 3: abajo
    int velocidad;
    int pasosRestantes;
    int ancho, alto;
    int animacion; // frame horizontal
    Bitmap^ sprite;
    int columnas = 3; // 3 columnas
    int filas = 4;     // 4 direcciones

public:
    CEnfermo(String^ ruta, int px, int py, int _velocidad) {
        sprite = gcnew Bitmap(ruta); // imagen completa
        ancho = sprite->Width / columnas;
        alto = sprite->Height / filas;

        x = px;
        y = py;
        velocidad = _velocidad;
        direccion = rand() % 4;
        pasosRestantes = 20 + rand() % 21;
        animacion = 0;
    }

    void mover(int anchoVentana, int altoVentana) {
        // Movimiento por dirección
        switch (direccion) {
        case 0: if (x + velocidad + ancho <= anchoVentana) x += velocidad; else direccion = 1; break;
        case 1: if (x - velocidad >= 0) x -= velocidad; else direccion = 0; break;
        case 2: if (y - velocidad >= 0) y -= velocidad; else direccion = 3; break;
        case 3: if (y + velocidad + alto <= altoVentana) y += velocidad; else direccion = 2; break;
        }

        animacion = (animacion + 1) % columnas;

        pasosRestantes--;
        if (pasosRestantes <= 0) {
            direccion = rand() % 4;
            pasosRestantes = 20 + rand() % 21;
        }
    }

    void dibujar(BufferedGraphics^ buffer) {
        int filaAnimacion = 0;
        if (direccion == 0) filaAnimacion = 2;      // derecha -> fila 2
        else if (direccion == 1) filaAnimacion = 1; // izquierda -> fila 1
        else if (direccion == 2) filaAnimacion = 3; // arriba -> fila 3
        else if (direccion == 3) filaAnimacion = 0; // abajo -> fila 0

        Rectangle origen = Rectangle(animacion * ancho, filaAnimacion * alto, ancho, alto);
        Rectangle destino = Rectangle(x, y, ancho, alto);
        buffer->Graphics->DrawImage(sprite, destino, origen, GraphicsUnit::Pixel);
		// Si quieres ver el rectángulo de colisión, descomenta la siguiente línea
		buffer->Graphics->DrawRectangle(gcnew Pen(Color::Red, 2), getRectangulo());
    }

    Rectangle getRectangulo() {
        return Rectangle(x, y, ancho, alto); // margen para colisiones
    }
};

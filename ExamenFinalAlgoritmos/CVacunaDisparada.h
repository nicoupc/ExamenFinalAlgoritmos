#pragma once

using namespace System;
using namespace System::Drawing;

enum DireccionVacuna { VDerecha, VIzquierda, VArriba, VAbajo };

ref class CVacunaDisparada {
private:
    int x, y;
    int dx, dy;
    int ancho, alto;
    Bitmap^ imagen;

public:
    CVacunaDisparada(String^ ruta, int px, int py, DireccionVacuna dir) {
        imagen = gcnew Bitmap(ruta);
        ancho = 32; // tamaño del proyectil
        alto = 32;

        x = px;
        y = py;

        int velocidad = 15;
        dx = dy = 0;

        switch (dir) {
        case VDerecha: dx = velocidad; break;
        case VIzquierda: dx = -velocidad; break;
        case VArriba: dy = -velocidad; break;
        case VAbajo: dy = velocidad; break;
        }
    }

    void mover() {
        x += dx;
        y += dy;
    }

    void dibujar(BufferedGraphics^ buffer) {
        buffer->Graphics->DrawImage(imagen, Rectangle(x, y, ancho, alto));
		// Si estás depurando colisiones, activa la línea siguiente:
		buffer->Graphics->DrawRectangle(Pens::Red, Rectangle(x, y, ancho, alto));
    }

    Rectangle getRectangulo() {
        return Rectangle(x, y, ancho, alto);
    }

    int getX() { return x; }
    int getY() { return y; }
};
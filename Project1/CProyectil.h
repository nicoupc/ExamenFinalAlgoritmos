#pragma once
using namespace System;
using namespace System::Drawing;

enum TipoProyectil { Aspirina, Pastilla };

public ref class CProyectil {
private:
    int x, y;
    int dx, dy;
    int ancho, alto;
    Bitmap^ imagen;
    TipoProyectil tipo;

public:
    // Ayuda IA
    CProyectil(Bitmap^ img, TipoProyectil tipo_, int startX, int startY, DireccionDrix dir) {
        imagen = img;
        tipo = tipo_;
        ancho = 20;
        alto = 20;

        x = startX;
        y = startY;

        int velocidad = 20;

        dx = 0; dy = 0;
        switch (dir) {
        case Abajo: dy = velocidad; break;
        case Arriba: dy = -velocidad; break;
        case Izquierda: dx = -velocidad; break;
        case Derecha: dx = velocidad; break;
        default: dy = velocidad; break;
        }
    }

    void mover() {
        x += dx;
        y += dy;
    }

    void dibujar(Graphics^ g) {
        g->DrawImage(imagen, x, y, ancho, alto);
        // Dibujar un borde rojo para visualizar el rectángulo
        //g->DrawRectangle(Pens::Red, x, y, ancho, alto);
    }

    Rectangle obtenerRectangulo() {
        return Rectangle(x, y, ancho, alto);
    }

    TipoProyectil getTipo() {
        return tipo;
    }

    bool estaFuera(int w, int h) {
        return x < 0 || y < 0 || x > w || y > h;
    }
};

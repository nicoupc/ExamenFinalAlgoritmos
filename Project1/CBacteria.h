#pragma once
using namespace System;
using namespace System::Drawing;

public ref class CBacteria {
private:
    Bitmap^ sprite;
    int x, y;
    int dx, dy;
    int velocidad;
    int ancho, alto;

public:
    CBacteria(Bitmap^ imagen, int anchoForm, int altoForm) {
        sprite = imagen;
        ancho = 40;
        alto = 40;
        x = rand() % (anchoForm - ancho);
        y = rand() % (altoForm - alto);
        velocidad = 6 + rand() % 5; // más rápido que el personaje

        // Movimiento aleatorio inicial
        dx = (rand() % 3 - 1) * velocidad; // -vel, 0, vel
        dy = (rand() % 3 - 1) * velocidad;
        if (dx == 0 && dy == 0) dx = velocidad; // evitar quedarse quieta
    }

    void mover(int anchoForm, int altoForm) {
        x += dx;
        y += dy;

        // Rebote en bordes
        if (x < 0 || x + ancho > anchoForm) dx = -dx;
        if (y < 0 || y + alto > altoForm) dy = -dy;
    }

    void dibujar(Graphics^ g) {
        g->DrawImage(sprite, x, y, ancho, alto);
    }

    Rectangle getRectangulo() {
        return Rectangle(x, y, ancho, alto);
    }
};

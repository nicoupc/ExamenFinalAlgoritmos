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
    int columnas = 4;
    int filas = 3;
    int indiceX, indiceY;
    int anchoOriginal, altoOriginal;

public:
    // Ayuda IA
    CBacteria(Bitmap^ imagen, int anchoForm, int altoForm) {
        sprite = imagen;

        columnas = 4;
        filas = 3;

        anchoOriginal = sprite->Width / columnas;
        altoOriginal = sprite->Height / filas;

        ancho = (int)(anchoOriginal * 0.3);
        alto = (int)(altoOriginal * 0.3);

        indiceX = rand() % columnas;
        indiceY = rand() % filas;

        x = rand() % (anchoForm - ancho);
        y = rand() % (altoForm - alto);

        velocidad = 6 + rand() % 5;

        dx = (rand() % 3 - 1) * velocidad;
        dy = (rand() % 3 - 1) * velocidad;
        if (dx == 0 && dy == 0) dx = velocidad;
    }

    void mover(int anchoForm, int altoForm) {
        x += dx;
        y += dy;

        // Rebote en bordes
        if (x < 0 || x + ancho > anchoForm) dx = -dx;
        if (y < 0 || y + alto > altoForm) dy = -dy;
    }

    // Ayuda IA
    void dibujar(Graphics^ g) {
        Rectangle origen = Rectangle(indiceX * anchoOriginal, indiceY * altoOriginal, anchoOriginal, altoOriginal);
        Rectangle destino = Rectangle(x, y, ancho, alto);
        g->DrawImage(sprite, destino, origen, GraphicsUnit::Pixel);

        // Borde rojo opcional
        //g->DrawRectangle(Pens::Red, x, y, ancho, alto);
    }

    Rectangle getRectangulo() {
        return Rectangle(x, y, ancho, alto);
    }
};



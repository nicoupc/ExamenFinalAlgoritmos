#pragma once
using namespace System;
using namespace System::Drawing;

public ref class COrgano {
private:
    Bitmap^ imagenSana;
    Bitmap^ imagenInfectada;
    Bitmap^ actual;
    int x, y;
    int ancho, alto;
    bool infectado;

public:
    COrgano(Bitmap^ sana, Bitmap^ infectada, int anchoForm, int altoForm) {
        imagenSana = sana;
        imagenInfectada = infectada;
        actual = imagenSana;
        ancho = 60;
        alto = 60;
        x = rand() % (anchoForm - ancho);
        y = rand() % (altoForm - alto);
        infectado = false;
    }

    void dibujar(Graphics^ g) {
        g->DrawImage(actual, x, y, ancho, alto);
        // Dibujar un borde rojo para visualizar el rectángulo
        //g->DrawRectangle(Pens::Red, x, y, ancho, alto);
    }

    Rectangle getRectangulo() {
        return Rectangle(x, y, ancho, alto);
    }

    void infectar() {
        infectado = true;
        actual = imagenInfectada;
    }

    void curar() {
        infectado = false;
        actual = imagenSana;
    }

    bool estaInfectado() {
        return infectado;
    }
};

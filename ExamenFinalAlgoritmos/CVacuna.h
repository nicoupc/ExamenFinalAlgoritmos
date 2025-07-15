#pragma once

using namespace System;
using namespace System::Drawing;

ref class CVacuna {
private:
    int x, y;
    int ancho, alto;
    Bitmap^ imagen;

    // Tamaño deseado para dibujo y colisión
    int TAMANIO = 32;

public:
    CVacuna(int anchoVentana, int altoVentana) {
        imagen = gcnew Bitmap("Vacuna.png");

        ancho = TAMANIO;
        alto = TAMANIO;

        x = rand() % (anchoVentana - ancho);
        y = rand() % (altoVentana - alto);
    }

    void dibujar(BufferedGraphics^ buffer) {
        buffer->Graphics->DrawImage(imagen, Rectangle(x, y, ancho, alto));
        // Si estás depurando colisiones, activá la línea siguiente:
        buffer->Graphics->DrawRectangle(Pens::Red, Rectangle(x, y, ancho, alto));
    }

    Rectangle getRectangulo() {
        return Rectangle(x, y, ancho, alto);
    }
};

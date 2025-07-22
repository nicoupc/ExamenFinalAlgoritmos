#pragma once
using namespace System;
using namespace System::Drawing;

enum DireccionDrix { Ninguna, Abajo, Izquierda, Derecha, Arriba };

public ref class CDrix {
private:
    int x, y;
    int ancho, alto;
    int indiceX, indiceY;
    float velocidad;
    DireccionDrix direccion;
    DireccionDrix ultimaDireccion;
    Bitmap^ sprite;

public:
    CDrix() {
        sprite = gcnew Bitmap("Drix.png");
        velocidad = 10;

        int columnas = 3;
        int filas = 4;

        ancho = sprite->Width / columnas;
        alto = sprite->Height / filas;

        x = 900; // aparece en el lado derecho
        y = 300;

        direccion = Ninguna;
        ultimaDireccion = Abajo;
        indiceX = 0;
        indiceY = 0;
    }

    void mover(int anchoVentana, int altoVentana) {
        if (direccion != Ninguna) {
            indiceX = (indiceX + 1) % 3;
            indiceY = static_cast<int>(direccion) - 1;
            ultimaDireccion = direccion;

            switch (direccion) {
            case Abajo:    y += velocidad; break;
            case Arriba:   y -= velocidad; break;
            case Izquierda: x -= velocidad; break;
            case Derecha:   x += velocidad; break;
            }
        }
        else {
            indiceX = 0;
            indiceY = static_cast<int>(ultimaDireccion) - 1;
        }

        // límites
        if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x + ancho > anchoVentana) x = anchoVentana - ancho;
        if (y + alto > altoVentana) y = altoVentana - alto;
    }

    void dibujar(BufferedGraphics^ buffer) {
        Rectangle origen = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
        Rectangle destino = Rectangle(x, y, ancho, alto);
        buffer->Graphics->DrawImage(sprite, destino, origen, GraphicsUnit::Pixel);
        // Dibujar un borde rojo para visualizar el rectángulo
        //buffer->Graphics->DrawRectangle(Pens::Red, x, y, ancho, alto);
    }

    Rectangle obtenerRectangulo() {
        return Rectangle(x, y, ancho, alto); // margen opcional
    }

    void setDireccion(DireccionDrix nueva) {
        direccion = nueva;
    }

    int getX() { return x; }
    int getY() { return y; }
    DireccionDrix getDireccion() { return direccion; }
    DireccionDrix getUltimaDireccion() {
        return ultimaDireccion;
    }
};

#ifndef NAVE_H
#define NAVE_H
#include <stdio.h>
#include <iostream>
#include "windows.h"
#include <stdlib.h>
#include <conio.h>

#define ARRIBA      72  //todas las teclas tienen asociado un numero
#define IZQUIERDA   75  //estos son especialmente para las flechas del teclado
#define DERECHA     77
#define ABAJO       80

void gotoxy(int x, int y);

using namespace std;

class Nave
{
private:
    int x,y;
    int corazones;
    int vidas;
public:
    Nave(int, int, int, int);
    ~Nave();
    void pintar();
    void borrar();  //para borrar el rastro de las posiciones
    void mover();
    void pintarCorazones();
    void morir();
    void decrecerCorazones();
    int getX();
    int getY();
    int getVidas();
};

#endif // NAVE_H

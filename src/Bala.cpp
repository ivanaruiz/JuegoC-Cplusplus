#include "Bala.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

Bala::Bala(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Bala::getX()
{
    return this->x;
}

int Bala::getY()
{
    return this->y;
}

void Bala::mover()
{
    //borro el "rastro de la bala"
    gotoxy(x,y);
    cout<<" ";

    //en este caso la bala "sube", por eso decremento el eje y
    //recordar que en la consola el eje y est� "al rev�s"; al decrementar, sube.
    y--;

    //y dibujo la bala en el nuevo lugar
    gotoxy(x,y);
    printf("*");
}

//para verificar si la bala se pas� del limite del eje y
bool Bala::fuera()
{
    if(y==4)            //porque est� en el tope(de arriba)
        return true;    //o sea es verdad que lleg� al l�mite
    return false;
}

#ifndef ASTEROIDE_H
#define ASTEROIDE_H
#include "Nave.h"
#include "windows.h"

void gotoxy(int x, int y);

class Asteroide
{
    private:
        int x;
        int y;
    public:
        Asteroide(int, int);
        void pintar();
        void mover();
        void choque(Nave &N);
        int getX();
        int getY();
};
#endif // ASTEROIDE_H

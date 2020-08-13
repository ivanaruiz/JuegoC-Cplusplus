#ifndef BALA_H
#define BALA_H
#include <stdio.h>

void gotoxy(int x, int y);

class Bala
{
    private:
        int x;
        int y;
    public:
        Bala(int, int);
        void mover();
        bool fuera();
        int getX();
        int getY();
};


#endif // BALA_H

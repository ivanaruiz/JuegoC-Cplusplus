#include "Asteroide.h"

//constructor parametrizado
Asteroide::Asteroide(int x, int y)
{
    this->x = x;
    this->y = y;
}

//getters
int Asteroide::getX()
{
    return this->x;
}

int Asteroide::getY()
{
    return this->y;
}

//la nave es solo un caracter, asi que no hay mucho que dibujar
void Asteroide::pintar()
{
    gotoxy(x,y);
    printf("%c",31);
}

void Asteroide::mover()
{
    gotoxy(x,y);    cout<<" ";  //borramos el rastro anterior
    y++;    //incrementamos el eje vertical para dar efecto de que cae

    if(y>32)    //este es el limite del eje y (recordar que nuestro limite era y=33)
    {
        x = rand()%71+4;    //en caso de pasarnos de ese limite, entonces "desaparece" y
        y = 4;              //vuelva arriba de todo para volver a salir
                            //el eje x es aleatorio para que siempre salga de distintos lugares
    }
    pintar();
}

//le paso por referencia el objeto de la clase Nave, puesto que
//sus valores también se deben modificar, no solo los del asteroide
void Asteroide::choque(Nave &N)
{
    //analizamos si hay choque, la x sola es la del asteroide
    if(x>= N.getX() && x<N.getX()+6             //6 es por el ancho de la nave
       && y >= N.getY() && y<=N.getY()+2)       //2 es por el alto de la nave
    //básicamente verifica que las coordenadas de ambos se estén tocando para que haya choque

    {
        Beep(300, 200);
        N.decrecerCorazones();
        N.borrar();
        N.pintar(); //hacemos esto porque la nave se despinta cuando le pasa por encima un asteroide
        N.pintarCorazones();

        //en caso de que hubo choque, un asteroide vuelve a salir de arriba de tod
        x= rand()%71 + 4;
        y= 4;
    }
}


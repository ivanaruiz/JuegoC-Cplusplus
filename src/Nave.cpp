#include "Nave.h"

//constructor parametrizado
Nave::Nave(int x, int y, int corazones, int vidas)
{
    this->x = x;
    this->y = y;
    this->corazones = corazones;
    this->vidas = vidas;
}

Nave::~Nave()
{
}

///////////////////////////////////////////////////////////

//getters
int Nave::getX()
{
    return this->x;
}

int Nave::getY()
{
    return this->y;
}

int Nave::getVidas()
{
    return this->vidas;
}

void Nave::decrecerCorazones()
{
    corazones--;
}

///////////////////////////////////////////////////////////

void Nave::pintar()
{
    //para imprimir estos caracteres voy  con click derecho a la barra de titulo de la consola,
    //presionar en "propiedades", "fuente", y elegir "fuentes de mapa bits" y aceptar.
    //(por las dudas aclaro que antes estaba tildada la opcion "consolas")
    gotoxy(x,y);
    printf("  %c", 30); //la parte superior de la nave

    gotoxy(x, y+1);     //notar que incremento y, significa que imprimo la parte media de la nave
    printf(" %cX%c", 40, 41);

    //y finalmente imprimo la parte inferior
    gotoxy(x, y+2);
    printf("%c%c %c%c", 30, 219, 219, 30);
}

///////////////////////////////////////////////////////////

//con esta función borro el "rastro de la nave"
void Nave::borrar()
{
    gotoxy(x,y);
    cout << "        ";

    gotoxy(x,y+1);
    cout << "        ";

    gotoxy(x,y+2);
    cout << "        ";
}

///////////////////////////////////////////////////////////


void Nave::mover()
{
    //kbhit es una funcion que detecta si se ha presionado una tecla
    if(kbhit()) //si se presionó una tecla..
    {
        char tecla = getch();   //con getch le pasamos el valor de lo que se presiona a variable tecla

        //para borrar el rastro de la nave al moverme
        //o sea me posiciono en las coordenadas anteriores
        borrar();

        //ahora sí evalúo la tecla a presionar
        if(tecla == IZQUIERDA   && x>3)         x--;    //con la segunda condicion no permito que
                                                        //se vaya la nave de los limites
        if(tecla == DERECHA     && (x+6)<75)    x++;    //el 6 se refiere al grosor de la nave, es decir,
                                                        //en el eje x, la nave mide 5 caracteres, por tanto
                                                        //debo avanzar hasta la 6ta posición
        if(tecla == ARRIBA      && y>4)         y--;
        if(tecla == ABAJO       && (y+3)<33)    y++;    //lo mismo aquí, 3 es el largo (long) de la nave

        //pinto la nave en su nueva posicion cuando se ha tocado una tecla
        pintar();

        pintarCorazones();
    }
}

///////////////////////////////////////////////////////////


void Nave::pintarCorazones()
{
    //vidas
    gotoxy(50,2);
    printf("VIDAS %d", this->vidas);

    gotoxy(64,2);
    cout << "SALUD";
    //corazones
    gotoxy(70,2);
    cout << "      ";
    for(int i=0; i<corazones; i++)
    {
        gotoxy(70+i,2);
        printf("%c", 3);
    }
}

///////////////////////////////////////////////////////////

void Nave::morir()
{
    if(corazones==0)
    {
        Beep(200, 200);
        borrar();   //primero borramos la nave
        //esto sería una animación de la explosión
        gotoxy(x,y);    printf("  **  ");
        gotoxy(x,y+1);  printf(" **** ");
        gotoxy(x,y+2);  printf("  **  ");
        Sleep(200); //la vemos un ratito a la explosión, por eso el Sleep

        borrar();   //y borramos la explosión, (el dibujo anterior)
        gotoxy(x,y);    printf(" * ** * "); //sigue otra explosión
        gotoxy(x,y+1);  printf("  ****  ");
        gotoxy(x,y+2);  printf(" * ** * ");
        Sleep(200);

        borrar();   //borramos la última explosión
        vidas--;
        corazones = 3;  //reinicio a 3 corazones pero con una vida menos (salvo que llegue a 0 vidas)
        pintarCorazones();
        pintar();   //y pinto la nave para volver a jugar
    }
}

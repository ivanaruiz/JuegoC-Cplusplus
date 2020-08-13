#include <iostream>
#include <windows.h>    //nos sirve para la posición del cursor
#include <conio.h>      //sirve para las teclas de movimiento
#include "list"
#include "Nave.h"
#include "Asteroide.h"
#include "Bala.h"

#include "registrarPuntuaciones/lista.h"
#include "Lista.h"
#include <string>
#include <string.h>

using namespace std;

//Las funciones de lista simplemente enlazada
void crearLista(tLista * pl);
int ponerUltimoLista(tLista * pl, const void * d, unsigned tam);
int sacarUltimoLista(tLista * pl, const void * d, unsigned tam);
int cmp_puntos(const void *e1, const void *e2);
int ponerOrden(tLista * pl, void * d, unsigned tam, int (*cmp)(const void *, const void *));
void grabar(tLista * pl, FILE * fp);

void inicio();
void sonidoFinal();
void titulo();

//cambié el tamaño de la ventana de consola
//click derecho en la barra de la consola, "propiedades" -> "layout" o "diseño"
//"tamaño de la ventana" ancho 80 - alto 35 (antes estaba en 85 y 32)


//esta función es la más importante y la que utilizaré todo el tiempo
//solo se trata de ubicar cierto caracter en las coordenadas x e y
void gotoxy(int x, int y)
{
    //creamos un handle, que es identificador
    //es para identificar la ventana que queremos manipular
    HANDLE hCon;

    /**tomamos el control de la salida de la consola con el handle,
    porque la accion de dar posicion a un caracter en la pantalla
    es una accion de salida**/
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    //COORD es una estructura, creamos un objeto de esa estructura
    //y luego damos valores a los atributos X e Y
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;    //tener en cuenta que la coordenada Y está invertidas acá

    //lo que hace esta funcion es tomar el control de la consola,
    //y pasarle coordenadas
    SetConsoleCursorPosition(hCon, dwPos);
    //luego de esto le mandamos lo que queremos imprimir con un cout o printf
}

void ocultarCursor(bool valor)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    //creamos una estructura
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;     //toma valores de 1 a 100
                        //es el estilo del cursor, es el grosor del cursor
    cci.bVisible = valor;   //si le paso un bool false, no se mostrará el cursor en pantalla
                            //esto es para durante la partida ya que parpadea constantemente y molesta
    //podemos controlar las caracteristicas de nuestro cursor
    SetConsoleCursorInfo(hCon, &cci);
}

//el cuadrito lindo del exterior
void pintarLimites()
{
    //pintamos las horizontales
    for(int i=2; i<78 ; i++)
    {
        gotoxy(i,3);
        printf("%c", 205);
        gotoxy(i,33);
        printf("%c", 205);
    }
    //pintamos las verticales
    for(int i=4; i<33; i++)
    {
        gotoxy(2,i);
        printf("%c", 186);
        gotoxy(77,i);
        printf("%c", 186);
    }

    //los 4 bordes
    gotoxy(2,3);    printf("%c", 201);
    gotoxy(2,33);   printf("%c", 200);
    gotoxy(77,3);   printf("%c", 187);
    gotoxy(77,33);  printf("%c", 188);
}

//*************************************************************************************//
//*************************************************************************************//

int main()
{
    //con esta línea dejo la resolución de mi pantalla igual para cualquier máquina
    system("mode con: cols=80 lines=35");

    SetConsoleTitle("+SHOOTING ROCKET+");

    pintarLimites();

    char opcion[10];
    do
    {

    inicio();

    gotoxy(3,20);
    printf("Comenzar juego (SI/NO) : ");
    fflush(stdin);

    gotoxy(26,20);   printf("             ");   //borro el rastro por si el usuario ingresó caracteres
                                                //invalidos, ejemplo "gfd"
    gotoxy(26,20);
    gets(opcion);

    if(strcmp(opcion, "NO")==0 || strcmp(opcion, "no")==0 || strcmp(opcion, "No")==0 ||
       strcmp(opcion, "nO")==0 || strcmp(opcion, "n")==0 || strcmp(opcion, "N")==0)
    {
        system("cls");
        gotoxy(3,3);
        cout << "Saliendo del juego..\n"<< endl;
        system("pause");
        exit(0);
    }


    //ACÁ empieza el juego (en caso de entrar al if)
    if(strcmp(opcion, "si")==0 || strcmp(opcion, "SI")==0 || strcmp(opcion, "Si")==0 ||
       strcmp(opcion, "sI")==0 || strcmp(opcion, "s")==0 || strcmp(opcion, "S")==0)
    {
    gotoxy(3,22);
    printf("Velocidad del juego: 1)Normal 2) Veloz");
    gotoxy(3,23);
    printf("Ingrese opcion elegida: ");
    int vel;
    scanf("%d", &vel);

    system("cls");
    pintarLimites();

    gotoxy(3,6);
    ocultarCursor(false);

    //creo el objeto nave y le mando las coordenadas x e y, los corazones, y las vidas
    Nave n(37,30,3,3);
    n.pintar();
    n.pintarCorazones();

    //creo listas para los casos de asteroides y balas, puesto que serán muchos elementos
    //al crear listas también creo iteradores
    list<Asteroide*>A;
    list<Asteroide*>::iterator itA;

    list<Bala*> B;              //tenemos una lista de punteros
    list<Bala*>::iterator it;   //con esto recorremos la lista


    //vamos a crear 3 asteroides al principio
    for(int i=0; i<3; i++ )
    {
        //push_back es una función que viene dentro de lista
        A.push_back(new Asteroide(rand()%75+3, rand()%5+4));
    }

    bool game_over = false;

    int puntos = 0;

    while(!game_over)   //el juego necesita ejecutarse todo el tiempo(hasta que uno pierda)
    {
        gotoxy(4,2);
        printf("PUNTOS: %d", puntos);
        if(kbhit())
        {
            char tecla = getch();
            if(tecla==9)    //por si el usuario desea pausar la partida
            {
                gotoxy(35,17);
                printf("PAUSA");
                gotoxy(22,18);
                system("pause");    //una vez que toque cualquier tecla para despausar,
                gotoxy(35,17);      //borro las palabras de PAUSA y el system("pause")
                printf("     ");
                gotoxy(22,18);
                printf("                                       ");
            }

            if(tecla == 's' || tecla == 'S')    //estas son las teclas de tiro
                if(n.getY()>5)
                //este if es para que la nave solo dispare en ese rango(por debajo de la coord y>5)
                //ya que si toca el limite superior, también dispara y eso está mal y buguea el juego
                    B.push_back(new Bala(n.getX()+2, n.getY()-1));
                    //notar que las coordenadas son según el objeto nave, por eso uso los getters
        }

        for(it=B.begin(); it!=B.end(); it++)
        {
            //con el asterisco desreferencio al puntero
            //y ya puedo acceder al contenido
            (*it)->mover();
            //verificamos si cada bala creada llegó al límite
            if((*it)->fuera())
            {
                gotoxy((*it)->getX(), (*it)->getY());    //nos situamos en la coord de la bala
                cout << " ";
                delete(*it);    //elimino al elemento de la lista(la bala)
                //tomo el siguiente valor de la lista
                it = B.erase(it);
                //con eso es como que vuelvo a hacer los enlaces
            }
        }

        for(itA = A.begin(); itA!= A.end(); itA++)
        {
            (*itA)->mover();
            (*itA)->choque(n);    //evaluamos si hay choque
        }

        //esta parte es para detectar el choque entre bala y asteroide
        for(itA = A.begin() ; itA!= A.end(); itA++)
        {
            for(it= B.begin(); it!=B.end(); it++)
            {
                //las posiciones donde se chocan
                if((*itA)->getX() == (*it)->getX() &&
                   ( (*itA)->getY()+1 == (*it)->getY() ||
                     (*itA)->getY()   == (*it)->getY()) )
                {
                    //borro la bala
                    gotoxy((*it)->getX() , (*it)->getY());
                    printf(" ");
                    delete(*it);
                    //como se pierde el hilo al hacer eso, hacemos
                    //y asi pasamos al siguiente elemento de la lista
                    it = B.erase(it);

                    //borro el asteroide
                    //pero ademas tendremos que crear otro
                    A.push_back(new Asteroide(rand()%74+3 , 4));
                    //aca borro al asteroide chocado entonces
                    gotoxy((*itA)->getX() , (*itA)->getY());
                    printf(" ");
                    delete(*itA);
                    itA = A.erase(itA);

                    puntos+=5;
                }
            }
        }
        if(n.getVidas()==0)
            game_over= true;

        n.morir();
        n.mover();

        //para que no se sature el procesador
        //puesto que se ejecutara demasiadas veces,
        //haremos lo siguiente
        if(vel==1)
            Sleep(50);  //30  //detiene la ejecucion del programa por 30 milisegunds
        if(vel==2)
            Sleep(30);
        //con esto son menos iteraciones por segundo
    }

    //salidos del while significa que la nave murió, partida finalizada

    sonidoFinal();

    system("cls");
    pintarLimites();

    titulo();

    gotoxy(5,8);
    ocultarCursor(true);
    printf("INGRESE SU NOMBRE: ");  //de aquí en adelante empiezo a usar lenguaje C
    char nombre[30];
    fflush(stdin);
    gets(nombre);

    //paso a mayusculas el nombre
    for(int i=0; i<30; i++)
        nombre[i] = toupper(nombre[i]);


    gotoxy(5,10);
    printf("GAME OVER.\t PUNTOS TOTALES: %d\n\n", puntos);

    //el nombre y los puntos los paso a un registro de una estructura
    //asi luego lo puedo sumar a la lista ya que la lista la estoy usando con una estructura
    tJugador nuevo;
    strcpy(nuevo.nombre, nombre);
    nuevo.puntuacion = puntos;

    gotoxy(5,13);
    printf("LISTA DE MAXIMAS PUNTUACIONES:\n");
    tJugador lis;

    //creo una lista y voy a bajar los datos que leo desde archivo binario
    tLista pl;
    crearLista(&pl);

    //voy a hacer una solo lectura de registro.dat, para bajar los datos de él
    FILE * fp = fopen("registrarPuntuaciones/registro.dat", "rb");
    if(!fp)
        return 1;

    fread(&lis, sizeof(tJugador), 1, fp);
    while(!feof(fp))
    {
        //a medida que bajo, paso los registros a mi lista creada recientemente
        ponerUltimoLista(&pl, &lis, sizeof(tJugador));
        fread(&lis, sizeof(tJugador), 1, fp);
    }
    fclose(fp);



    tJugador elim;

    //nuevamente abro el archivo pero esta vez lo voy a modificar
    //ya que metere al ultimo jugador junto a su puntuacion en caso de que entre al ranking

    fp= fopen("registrarPuntuaciones/registro.dat", "r+b");
    if(!fp)
        return 1;

    //en caso de que entre al ranking, entonces debo eliminar el ultimo nodo de la lista
    //(siempre deben quedar 5 registros nomás (5 jugadores))
    if(ponerOrden(&pl, &nuevo, sizeof(tJugador), cmp_puntos))
        sacarUltimoLista(&pl, &elim, sizeof(tJugador));

    //finalmente grabo en el archivo binario actualizado
    grabar(&pl, fp);

    fclose(fp);


    //por último leo el archivo actualizado y muestro los datos

    fp = fopen("registrarPuntuaciones/registro.dat", "rb");
    if(!fp)
        return 1;

    int aumentar=15;
    fread(&lis, sizeof(tJugador), 1, fp);
    while(!feof(fp))
    {
        gotoxy(5,aumentar);
        printf("%-29s %d\n", lis.nombre, lis.puntuacion);
        fread(&lis, sizeof(tJugador), 1, fp);
        aumentar++;
    }
    fclose(fp);


    gotoxy(5, aumentar+2);
    system("pause");
    system("cls");
    pintarLimites();
    }

    }//acá se cierra el dowhile
    while(strcmp(opcion, "NO")!=0 || strcmp(opcion, "no")!=0 || strcmp(opcion, "No")!=0 ||
          strcmp(opcion, "nO")!=0 || strcmp(opcion, "n")!=0 || strcmp(opcion, "N")!=0);

    return 0;
}

//*************************************************************************************//
//*************************************************************************************//

void inicio()
{
    titulo();

    gotoxy(3,8);
    printf("MOVER LA NAVE CON LAS FECHAS DEL TECLADO.");
    gotoxy(3,9);
    printf("DISPARAR A LOS ASTEROIDES ENEMIGOS CON LA TECLA 'S'");
    gotoxy(3,10);
    printf("PARA PAUSAR EL JUEGO, PULSAR TECLA 'TAB'.");
    gotoxy(3,12);
    printf("EN CASO DE NO VISUALIZAR BIEN LOS DIBUJOS,");
    gotoxy(3,13);
    printf("HACER CLICK DERECHO EN LA BARRA DE CONSOLA Y SELECCIONAR LO SIGUIENTE:");
    gotoxy(3,14);
    printf("'PROPIEDADES'->'FUENTE'->'FUENTES DE MAPA DE BITS',");
    gotoxy(3,16);
    printf("EN CASO DE DESEAR CAMBIAR TAMANIO A LA VENTANA,");
    gotoxy(3,17);
    printf("HACER CLICK DERECHO EN LA BARRA DE LA CONSOLA Y SELECCIONAR:");
    gotoxy(3,18);
    printf("'PROPIEDADES'->'FUENTE'->Y ELEGIR LA OPCION DESEADA EN TAMANIO.");

    gotoxy(3,32);
    printf("PROGRAMACION A CARGO DE IVANA RUIZ.");
}

void titulo()
{
    gotoxy(32,4);
    printf("===============");
    gotoxy(32,5);
    printf("SHOOTING ROCKET");
    gotoxy(32,6);
    printf("===============");
}

void sonidoFinal()
{
    Beep(100,200);
    Beep(300,300);
    Beep(100,200);
    Beep(400,200);
    Beep(200,400);
}

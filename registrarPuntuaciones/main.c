#include "lista.h"


int main()
{
    FILE* arch = fopen("registro.dat","wb");

    if(!arch)
        return 1;

    tLista pl;

    crearLista(&pl);

    //creo una lista con 5 jugadores por default, los 5 son iguales
    //luego en el juego esto se ira actualizando
    tJugador vec[] ={   {"JUGADOR", 0},
                        {"JUGADOR", 0},
                        {"JUGADOR", 0},
                        {"JUGADOR", 0},
                        {"JUGADOR",
                        0}};

    int tamVec= sizeof(vec)/sizeof(tJugador);

    for(int i=0; i<tamVec; i++)
    {
        ponerPrimeroLista(&pl, vec+i, sizeof(tJugador));
    }

    fwrite(vec, sizeof(vec), 1, arch);

    fclose(arch);

    system("pause");
    return 0;
}

/**
Objetivo de este ejecutable: crear una lista simplemente enlazada que contenga 5 nodos (5 jugadores)
con datos por default que ser�n todos iguales (JUGADOR 0  para todos).
Luego guardamos estos datos en un archivo binario llamado registro.dat
Este programa no har� m�s nada.
Luego en el juego, al final de cada partida, se abrir� el archivo registro.dat, se volcar�n sus
datos a una lista nueva creada desde all�, y luego se pisar�n los datos con nuevos jugadores
que superen las puntuaciones ya registradas. En caso de registrarse un nuevo jugador, este se pone
en orden en la lista, y adem�s debe eliminarse el �ltimo nodo, puesto que ese quedar� con el
puntaje m�s bajo.
Ejemplo.
En la primera reiteraci�n tenemos
JUGADOR 0
JUGADOR 0
JUGADOR 0
JUGADOR 0
JUGADOR 0
Si el jugador que ingres� sus datos, por ejemplo, PEPE 20. Entonces la lista quedar� as� conformada:
PEPE    20
JUGADOR 0
JUGADOR 0
JUGADOR 0
JUGADOR 0
Otro ejemplo, tenemos una lista conformada as�:
PEPE    80
TOTO    70
BEBE    50
LOLO    40
PIPI    20
Y un nuevo jugador ingresa sus datos as�: MEME  60. Entonces la lista final ser�:
PEPE    80
TOTO    70
MEME    60
BEBE    50
LOLO    40
Finalmente la lista final se guarda actualizada.
**/

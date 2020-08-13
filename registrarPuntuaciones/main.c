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
con datos por default que serán todos iguales (JUGADOR 0  para todos).
Luego guardamos estos datos en un archivo binario llamado registro.dat
Este programa no hará más nada.
Luego en el juego, al final de cada partida, se abrirá el archivo registro.dat, se volcarán sus
datos a una lista nueva creada desde allí, y luego se pisarán los datos con nuevos jugadores
que superen las puntuaciones ya registradas. En caso de registrarse un nuevo jugador, este se pone
en orden en la lista, y además debe eliminarse el último nodo, puesto que ese quedará con el
puntaje más bajo.
Ejemplo.
En la primera reiteración tenemos
JUGADOR 0
JUGADOR 0
JUGADOR 0
JUGADOR 0
JUGADOR 0
Si el jugador que ingresó sus datos, por ejemplo, PEPE 20. Entonces la lista quedará así conformada:
PEPE    20
JUGADOR 0
JUGADOR 0
JUGADOR 0
JUGADOR 0
Otro ejemplo, tenemos una lista conformada así:
PEPE    80
TOTO    70
BEBE    50
LOLO    40
PIPI    20
Y un nuevo jugador ingresa sus datos así: MEME  60. Entonces la lista final será:
PEPE    80
TOTO    70
MEME    60
BEBE    50
LOLO    40
Finalmente la lista final se guarda actualizada.
**/

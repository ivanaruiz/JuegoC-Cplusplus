#include "lista.h"

void crearLista(tLista * pl)
{
    *pl = NULL;
}

//*******************************************************************************//
//*******************************************************************************//

//También podría haber usado la primitiva de ponerUltimoLista, pero da igual ya que
//mis datos iniciales son todos iguales (JUGADOR 0)
int ponerPrimeroLista(tLista * pl, const void * d, unsigned tam)
{
    tNodo * nue = (tNodo*)malloc(sizeof(tNodo));

    if(!nue)
    {
        printf("Lista llena. No se pudo crear jugador.\n");
        return 0;
    }

    //reservo memoria para el tamaño que me dijeron que mide el dato
    nue->info = malloc(tam);

    if(!nue->info)
    {
        printf("No se pudo crear jugador.\n");
        free(nue);
        return 0;
    }

    //si llego aca es porque pudo crear al nodo jugador
    nue->tamInfo = tam;
    memcpy(nue->info, d, tam);

    //engancho a la lista
    nue->sig = *pl;
    *pl = nue;

    return 1;
}

//*******************************************************************************//
//*******************************************************************************//

//No uso esta función pero la dejo por si quiero ver la lista en este ejecutable
void mostrarLista(const tLista * pl)
{
    while(*pl)
    {
        tJugador * jug = (tJugador *)((*pl)->info);
        printf("%-29s %d\n", jug->nombre, jug->puntuacion);    //casteamos para mostrar
        pl = &(*pl)->sig;
    }
}


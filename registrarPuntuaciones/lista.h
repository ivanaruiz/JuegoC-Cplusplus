#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MINIMO(x,y) ((x)<=(y) ? (x):(y))

typedef struct
{
    char nombre[30];
    int puntuacion;
}tJugador;

typedef struct sNodo
{
    void * info;
    unsigned tamInfo;
    struct sNodo * sig;
}tNodo;

typedef tNodo * tLista;

//Primitivas de lista simplemente enlazada
void crearLista(tLista * pl);
int ponerPrimeroLista(tLista * pl, const void * d, unsigned tam);
void mostrarLista(const tLista * pl);

#endif // LISTA_H_INCLUDED

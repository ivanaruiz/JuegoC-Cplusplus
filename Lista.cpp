#include "registrarPuntuaciones/lista.h"

//Las funciones de lista ya est�n mejor explicadas en el archivo de registrarPuntuaciones

void crearLista(tLista * pl)
{
    *pl = NULL;
}

//*************************************************************************************//
//*************************************************************************************//

//funci�n que me servir� para que, al leer del archivo binario registro.dat, pueda leer los registros
//guardados y volcarlos a una nueva lista en este ejecutable.
//simplemente a cada registro lo pongo �ltimo en mi nueva lista aqu� creada

int ponerUltimoLista(tLista * pl, const void * d, unsigned tam)
{
    tNodo * nue = (tNodo*)malloc(sizeof(tNodo));

    if(!nue)
    {
        printf("Lista llena. No se creo jugador.\n");
        return 0;
    }

    //reservo memoria para el tama�o que me dijeron que mide el dato
    nue->info = malloc(tam);

    if(!nue->info)
    {
        printf("No se pudo crear jugador\n");
        free(nue);
        return 0;
    }

    //si llego aca es porque pudo crear al nodo jugador
    nue->tamInfo = tam;
    memcpy(nue->info, d, tam);

    nue->sig = NULL;

    while(*pl)
        pl = &(*pl)->sig;   //avanzo hasta el final de la lista

    *pl = nue;  //y engancho a la lista mi nuevo nodo jugador

    return 1;
}

//*************************************************************************************//
//*************************************************************************************//

//funci�n que me servir� en caso de que el jugador haya obtenido una puntuaci�n alta que entre
//en el ranking de los 5 mejores. en ese caso, se debe ingresar el nuevo jugador, pero tambi�n
//se debe borrar el �ltimo registro puesto que habr� quedado con la menor puntuaci�n en 6� lugar.

int sacarUltimoLista(tLista * pl, const void * d, unsigned tam)
{
    if(!*pl)
        return 0;

    while((*pl)->sig)
    {
        pl = &(*pl)->sig;
    }

    free((*pl)->info);
    free(*pl);

    *pl = NULL;

    return 1;
}

//*************************************************************************************//
//*************************************************************************************//

//simplemente uso esta funci�n para leer cada nodo de la lista desde el inicio hasta el final,
//y luego lo grabo (actualizo) en registro.dat
void grabar(tLista * pl, FILE * fp)
{
    while(*pl)
    {
        fwrite((*pl)->info, sizeof(tJugador),1,fp);
        pl = &(*pl)->sig;
    }
}

//*************************************************************************************//
//*************************************************************************************//

//en caso de que el jugador entre en el ranking de los 5 mejores, entonces debo colocarlo
//en la posici�n correcta.
//para eso debo buscar esa posici�n. arranco buscando desde la primer posici�n y comparo.

int ponerOrden(tLista * pl, void * d, unsigned tam, int (*cmp)(const void *, const void *))
{
    if(!*pl)
        return 0;

    while(*pl)
    {
        if(cmp(d , (*pl)->info ) > 0)   //si compruebo que mi nuevo jugador es mayor al nodo leido..
                                        //entonces debo colocarlo all�
        {
            tNodo * nue = (tNodo*)malloc(sizeof(tNodo));
            if(!nue)
            {
                return 0;
            }

            //reservo memoria para el tama�o que me dijeron que mide el dato
            nue->info = malloc(tam);

            if(!nue->info)
            {
            printf("No se pudo crear jugador\n");
            free(nue);
            return 0;
            }

            //llegados ac� es porque pudimos crear exitosamente el nuevo nodo para ingresar jugador
            nue->tamInfo = tam;
            memcpy(nue->info, d, tam);

            //y engancho a la lista
            nue->sig = *pl;
            *pl= nue;

            return 1;   //si todo esto sucedi�, entonces ya corto el ciclo y salgo exitosamente
                        //con un return 1 que es de TRUE
        }
        pl = &(*pl)->sig;   //si aun mi jugador es menor, entonces sigo buscando avanzando en la lista
    }

    return 0;
}

//*************************************************************************************//
//*************************************************************************************//

//funci�n de comparaci�n de numeros enteros, es decir puntuaci�n del nodo le�do de la lista
//con la puntuaci�n de mi jugador
int cmp_puntos(const void *e1, const void *e2)
{
    const tJugador * a1 = (const tJugador *) e1;
    const tJugador * a2 = (const tJugador *) e2;
    return a1->puntuacion - a2->puntuacion;
}

//*************************************************************************************//
//*************************************************************************************//

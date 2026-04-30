//____________________________________
//BIBLIOTECAS
//____________________________________
#include<stdio.h>
#include<stdlib.h>

//____________________________________
//ESTRUCTURAS
//____________________________________
struct
{
    int TareaID; //Numérico autoincremental comenzando en 1000
    char * Descripcion;
    int Duracion; //entre 10 - 100
}typedef Tarea;

struct
{
    Tarea T;
    Nodo * Siguiente;
}typedef Nodo;

Nodo *CrearListaVacia();

//____________________________________
//DECLARACION DE FUNCIONES
//____________________________________


//____________________________________
//FUNCION MAIN
//____________________________________
int main()
{
    

    return 0;
}

//____________________________________
//DEFINICION DE FUNCIONES
//____________________________________
Nodo *CrearListaVacia()
{
    return NULL;
}
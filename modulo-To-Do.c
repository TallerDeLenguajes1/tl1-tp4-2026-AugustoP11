//____________________________________
//BIBLIOTECAS
//____________________________________
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//____________________________________
//ESTRUCTURAS
//____________________________________
typedef struct Tarea
{
    int TareaID; //Numérico autoincremental comenzando en 1000
    char * Descripcion;
    int Duracion; //entre 10 - 100
} Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo * Siguiente;
} Nodo;


//____________________________________
//DECLARACION DE FUNCIONES
//____________________________________

//Funcion para crear lista vacia
Nodo * CrearListaVacia();

//Funcion para cargar una tarea (se agrega al final de la lista)
Nodo * CargarTarea(Nodo * L, int id);

//Funcion para imprimir los nodos de las listas
void MostrarLista(Nodo * L);


//____________________________________
//FUNCION MAIN
//____________________________________
int main()
{
    // Creo las cabeceras de las listas
    Nodo * TareasPendientes = CrearListaVacia();
    Nodo * TareasRealizadas = CrearListaVacia();


    //Interfaz para la carga de tareas pendientes
    int confirmarCargaDeTarea = 2;
    int id = 1000;

    do
    {
        printf("\n¿Quiere cargar una nueva tarea? Ingrese '1' para cargar tarea o '0' para salir.\n");
        scanf("%d", &confirmarCargaDeTarea);
        fflush(stdin);
        switch (confirmarCargaDeTarea)
        {
        case 1:
            TareasPendientes = CargarTarea(TareasPendientes, id);
            id++;
            break;
        default:
            break;
        }

    } while (confirmarCargaDeTarea != 0);

    MostrarLista(TareasPendientes);

    return 0;
}

//____________________________________
//DEFINICION DE FUNCIONES
//____________________________________

//Funcion para crear lista vacia
Nodo * CrearListaVacia()
{
    return NULL;
}

//Funcion para cargar una tarea (se agrega al final de la lista)
Nodo * CargarTarea(Nodo * L, int id)
{
    char Buff[100];
    int duracion;
    Nodo * NNodo = (Nodo *)malloc(sizeof(Nodo));
    NNodo->T.TareaID = id;
    printf("\nIngrese una descripcion de la tarea:\n");
    gets(Buff);
    NNodo->T.Descripcion = (char *)malloc(strlen(Buff)*sizeof(char)+1);
    strcpy(NNodo->T.Descripcion, Buff);
    printf("\nIngrese la duracion de la tarea en horas (entero):\n");
    scanf("%d", &duracion);
    NNodo->T.Duracion = duracion;
    NNodo->Siguiente = NULL;

    //A continuacion hago la insercion del nodo al final de la lista
    Nodo * Aux = L;

    if (Aux == NULL)
    {
        L = NNodo;
    } else {
        while (Aux->Siguiente != NULL)
        {
            Aux = Aux->Siguiente;
        }
        Aux->Siguiente = NNodo;
    }

    return L;
}

//Funcion para imprimir los nodos de las listas
void MostrarLista(Nodo * L)
{
    if (L == NULL)
    {
        printf("\nNo hay tareas para mostrar.\n");
    } else {
        Nodo * Aux = L;
        do
        {
            printf("\nDescripcion de la tarea: %s\n", Aux->T.Descripcion);
            printf("ID de la tarea: %d\n", Aux->T.TareaID);
            printf("Duracion de la tarea: %d\n", Aux->T.Duracion);
            printf("-------------------\n");

            Aux = Aux->Siguiente;
        } while (Aux->Siguiente != NULL);
    }
}
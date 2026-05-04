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

//Funcion para transferir tareas pendientes a tareas realizadas
void TransferirPendientesARealizadas(Nodo ** Pendientes, Nodo ** Realizadas);

//Funcion para consultar tareas por id o palabra clave
void consultarTareas(Nodo * Pendientes, Nodo * Realizadas);


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

    //Muestro la lista
    //MostrarLista(TareasPendientes);

    //Interfaz para mostrar tareas y para transferir tareas pendientes a la lista de tareas realizadas
    int confirmarOpcion = 10;

    do
    {
        printf("\nIngrese '1' para mostrar la lista de tareas pendientes\nIngrese '2' para mostrar la lista de las tareas realizadas\nIngrese '3' para ingresar el id de una tarea pendiente que se haya completado\nIngrese '4' para consultar tareas\nIngrese '0' para salir\n");
        scanf("%d", &confirmarOpcion);
        switch (confirmarOpcion)
        {
        //Opcion para mostrar la lista de tareas pendientes
        case 1:
            printf("\n------TAREAS PENDIENTES------");
            MostrarLista(TareasPendientes);
            break;
        
        //Opcion para mostrar la lista de tareas realizadas
        case 2:
            printf("\n------TAREAS REALIZADAS------");
            MostrarLista(TareasRealizadas);
            break;

        //Opcion para marcar por id como completadas tareas pendientes
        case 3:
            TransferirPendientesARealizadas(&TareasPendientes, &TareasRealizadas);
            break;

        case 4:
            consultarTareas(TareasPendientes, TareasRealizadas);
            break;
        default:
            break;
        }
    } while (confirmarOpcion != 0);
    
    //____________Libero memoria____________
    Nodo * AuxPendientes = TareasPendientes;
    Nodo * AuxRealizadas = TareasRealizadas;

    //Libero memoria de la lista TareasPendientes
    while (AuxPendientes != NULL)
    {
        free(AuxPendientes->T.Descripcion);
        AuxPendientes->T.Descripcion = NULL;
        AuxPendientes = AuxPendientes->Siguiente;
    }
    free(TareasPendientes);
    TareasPendientes = NULL;

    //Libero memoria de la lista TareasRealizadas
    while (AuxRealizadas != NULL)
    {
        free(AuxRealizadas->T.Descripcion);
        AuxRealizadas->T.Descripcion = NULL;
        AuxRealizadas = AuxRealizadas->Siguiente;
    }
    free(TareasRealizadas);
    TareasRealizadas = NULL;

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
        } while (Aux != NULL);
    }
}

//Funcion para transferir tareas pendientes a tareas realizadas
void TransferirPendientesARealizadas(Nodo ** Pendientes, Nodo ** Realizadas)
{
    int id;
    printf("\nIngrese el ID de la tarea a marcar como completada: ");
    scanf("%d", &id);
    fflush(stdin);

    Nodo * Aux = (*Pendientes);
    Nodo * AuxAnt = NULL;
    while (Aux != NULL && Aux->T.TareaID != id)
    {
        AuxAnt = Aux;
        Aux = Aux->Siguiente;
    }
    //Si es que encontro el id, muevo la tarea de pendientes a realizadas, si no no hago nada
    if (Aux != NULL)
    {
        if (Aux == (*Pendientes))
        {
            (*Pendientes) = Aux->Siguiente;
        } else {
            AuxAnt->Siguiente = Aux->Siguiente;
        }
        Aux->Siguiente = NULL;
        
        //Agrego la tarea al comienzo de la lista de tareas realizadas
        Aux->Siguiente = (*Realizadas);
        (*Realizadas) = Aux;
    }
}

//Funcion para consultar tareas por id o palabra clave
void consultarTareas(Nodo * Pendientes, Nodo * Realizadas)
{
    int opcion = 10;
    printf("\n\nIngrese '5' para consultar tarea por ID\nIngrese '6' para consultar tarea por palabra clave\n");
    scanf("%d", &opcion);
    fflush(stdin);
    int idConsultado = 999;
    char Buff[100];
    Nodo * AuxPendientes = Pendientes;
    Nodo * AuxRealizadas = Realizadas;
    int flag = 0;

    switch (opcion)
    {
    //Consulta de tarea por id
    case 5:
        printf("\nIngrese el id de la tarea a consultar: ");
        scanf("%d", &idConsultado);

        while (AuxPendientes != NULL)
        {
            if (AuxPendientes->T.TareaID == idConsultado)
            {
                printf("\n-----------TAREA ENCONTRADA-----------");
                printf("\nDescripcion de la tarea: %s\n", AuxPendientes->T.Descripcion);
                printf("ID de la tarea: %d\n", AuxPendientes->T.TareaID);
                printf("Duracion de la tarea: %d\n", AuxPendientes->T.Duracion);
                printf("ESTADO: PENDIENTE\n");
                printf("---------------------------------------\n");
                flag = 1;
                break;
            }
            AuxPendientes = AuxPendientes->Siguiente;
        }

        //Si no encontro la tarea en la lista de tareas pendientes busco en la lista de tareas realizadas
        if (flag != 1)
        {
            while (AuxRealizadas != NULL)
            {
            if (AuxRealizadas->T.TareaID == idConsultado)
            {
                printf("\n-----------TAREA ENCONTRADA-----------");
                printf("\nDescripcion de la tarea: %s\n", AuxRealizadas->T.Descripcion);
                printf("ID de la tarea: %d\n", AuxRealizadas->T.TareaID);
                printf("Duracion de la tarea: %d\n", AuxRealizadas->T.Duracion);
                printf("ESTADO: REALIZADA\n");
                printf("---------------------------------------\n");
                flag = 1;
                break;
            }
            AuxRealizadas = AuxRealizadas->Siguiente;
            }
        }
        
        //Si no se encuentra la tarea lo indico
        if (flag != 1)
        {
            printf("\nNo se encontro la tarea con ID: %d\n", idConsultado);
        }
        break;
    
    //Consulta de tarea por palabra clave
    case 6:
        printf("\nIngrese una palabra clave para consultar en tareas: ");
        gets(Buff);
        char * coincidencia;

        //Busco primero en la lista de tareas pendientes
        while (AuxPendientes != NULL)
        {
            coincidencia = strstr(AuxPendientes->T.Descripcion, Buff);
            if (coincidencia != NULL)
            {
                printf("\n-----------TAREA ENCONTRADA-----------");
                printf("\nDescripcion de la tarea: %s\n", AuxPendientes->T.Descripcion);
                printf("ID de la tarea: %d\n", AuxPendientes->T.TareaID);
                printf("Duracion de la tarea: %d\n", AuxPendientes->T.Duracion);
                printf("ESTADO: PENDIENTE\n");
                printf("---------------------------------------\n");
                flag = 1;
                break;
            }
            coincidencia = NULL;
            AuxPendientes = AuxPendientes->Siguiente;
        }
        
        //Busco en la lista de tareas realizadas
        while (AuxRealizadas != NULL)
        {
            coincidencia = strstr(AuxRealizadas->T.Descripcion, Buff);
            if (coincidencia != NULL)
            {
                printf("\n-----------TAREA ENCONTRADA-----------");
                printf("\nDescripcion de la tarea: %s\n", AuxRealizadas->T.Descripcion);
                printf("ID de la tarea: %d\n", AuxRealizadas->T.TareaID);
                printf("Duracion de la tarea: %d\n", AuxRealizadas->T.Duracion);
                printf("ESTADO: REALIZADA\n");
                printf("---------------------------------------\n");
                flag = 1;
                break;
            }
            coincidencia = NULL;
            AuxRealizadas = AuxRealizadas->Siguiente;
        }

        //Si no se encuentra la tarea lo indico
        if (flag != 1)
        {
            printf("\nNo se encontro la tarea con la palabra clave: %s\n", Buff);
        }
        break;

    default:
        break;
    }
}
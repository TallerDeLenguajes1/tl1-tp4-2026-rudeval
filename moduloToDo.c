#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct tTarea{ 
    int TareaID;//Numérico autoincremental comenzando en 1000 
    char *Descripcion;    
    int Duracion; // entre 10 – 100  
}tTarea;  

typedef struct tNodo{ 
    tTarea * datosTarea;  //cambiamos a puntero
    struct tNodo *Siguiente;  
}tNodo; 

void limpiarBuffer();
tTarea * crearYcargarTarea(int id);
tNodo * crearNodo(tTarea * datos);
tNodo * crearListaVacia();
void insertarNodoEnLista(tNodo ** lista, tNodo * nodo);
tNodo * buscarNodo(tNodo*lista, int idBuscado);


int main(){
    srand(time(NULL));

    printf("\n----Carga de tareas----");
    
        //creo lista vacia
        tNodo * ListaPendientes = crearListaVacia(); //inicializamos lista - Lista=NULL
        
        int i=0, id=1000, continuar=1;
        
        do
        {
            //creo y cargo tarea
            printf("\nTarea [%d]", id);
            tTarea * TareaCreada = crearYcargarTarea(id); //crea una tarea y devuelve el puntero a ella
            printf("Descripcion ingresada: %s", TareaCreada->Descripcion);

            //creo nodo
            tNodo * nuevoNodo = crearNodo(TareaCreada);//recibe la direc de la tarea y devuelve un p al nodo

            //insertamos nodo en lista
            insertarNodoEnLista(&ListaPendientes, nuevoNodo);//insertamos nodo en lista - &Lista = direcc de memoria de Lista, Lista=0x0

            id++;
            printf("\n¿Continuar=1 | Finalizar=0?");
                scanf("%d", &continuar);
                limpiarBuffer();

        } while (continuar!=0);

    printf("\n----Tareas pendientes --> tareas realizadas----");
        //creo lista vacia
        tNodo * ListaRealizadas = crearListaVacia(); //inicializamos lista - Lista=NULL
        int idMover, continuar=1;
        do
        {
            printf("\nIngrese id de tarea a mover: ");
                scanf("%d", &idMover);

            //buscamos tarea a mover
            tNodo * tareaAmover = buscarNodo(ListaPendientes, idMover);

            //eliminamos de ListaRealizadas la tarea
            
            //insertamos tarea en tareaRealizada
            insertarNodoEnLista(&ListaRealizadas, tareaAmover);

            printf("\n¿Continuar=1 | Finalizar=0?");
                scanf("%d", &continuar);
        } while (continuar!=0);


        
    //liberamos memoria

    return 0;
}


tTarea * crearYcargarTarea(int id){

    tTarea *tareas = (tTarea *) malloc(sizeof(tTarea)); //reservo la memoria para la tarea, y la asigno a un puntero tipo tTarea
    
    tareas->TareaID = id; 

    char buff[50];
    printf("\n\tIngrese descripcion de tarea [%d]: ", tareas->TareaID);
        fgets(buff, sizeof(buff), stdin);
        tareas->Descripcion = (char *) malloc (sizeof(char) * strlen(buff) + 1); // Reserva de memoria para la cadena pero aumento 1 byte para el carcter nulo
        strcpy(tareas->Descripcion, buff);  

    tareas->Duracion= rand()%91 + 10; //rand entre 10 y 100
    
    return tareas; //devuelve el puntero a la tarea creada;
}

tNodo * crearNodo(tTarea * datos){ //recibe punt a tTarea y devuelve un nodo
    tNodo *pNodo = (tNodo *)malloc(sizeof(tNodo)); //reservo memoria para el nodo y almaceno la dire en punt
    pNodo->datosTarea = datos; //copia toda la estructura
    pNodo->Siguiente = NULL;
    return pNodo;
}

tNodo * crearListaVacia() //inicializamos, apuntando el puntero a NULL
{
    return NULL;
}

void insertarNodoEnLista(tNodo ** lista, tNodo * nuevoNodo){ //(** es punt a punt de lista) xq necesito pasar la direc de memoria del punt a lista
                                                        //pasamos la direc de memoria de la lista de afuera q es un punt.
    nuevoNodo->Siguiente = *lista; //*lista=direcc de vble lista
                                //el nuevo nodo apunta al que era el primero, al comienzo de la lista
    *lista = nuevoNodo; //lista empieza en el nuevo nodo
}

tNodo * buscarNodo(tNodo*lista, int idBuscado){
    tNodo * aux = lista; //apuntamos con punt aux a la cabecera de la lista a recorrer
    while (aux && aux->datosTarea->TareaID != idBuscado) //aux != NULL && ... 
    {
        aux = aux->Siguiente;
    }
    return aux;
}

tNodo * quitarNodo(tNodo **lista, tTarea datos){
    tNodo * nodoAux = (*lista); //es la direcc del punt que apunta a la lista, para modificarla desde la cabecera
    tNodo * nodoAnterior = NULL;

}

void limpiarBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} 
    //sigue tomando info desde stdin buscando algun valor distinto a salto de linea o endOfFile
    //usar despues de scanf para numeros, antes del fgets para tomar cadena
}









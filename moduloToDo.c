#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tTarea{ 
    int TareaID;//Numérico autoincremental comenzando en 1000 
    char *Descripcion;  //       
    int Duracion; // entre 10 – 100  
}tTarea;  

typedef struct tNodo{ 
    tTarea * datosTarea;  //cambiamos a puntero
    struct tNodo *Siguiente;  
}tNodo; 

tTarea * crearYcargarTarea();
tNodo * crearNodo(tTarea * datos);
tNodo * crearListaVacia();
void insertarNodoEnLista(tNodo ** lista, tNodo * nodo);



int main(){

    tTarea * TareaCreada = crearYcargarTarea(); //crea una tarea y devuelve el puntero a ella
    tNodo * nuevoNodo = crearNodo(TareaCreada); //recibe la direc de la tarea y devuelve un p al nodo
    tNodo * Lista = crearListaVacia(); //inicializamos lista - Lista=NULL
    insertarNodoEnLista(&Lista, nuevoNodo);//insertamos nodo en lista - &Lista = direcc de memoria de Lista

    return 0;
}


tTarea * crearYcargarTarea(){
    tTarea *tareas = (tTarea *) malloc(sizeof(tTarea)); //reservo la memoria para la tarea, y la asigno a un puntero tipo tTarea
    tareas->TareaID = 1000; //!
    tareas->Duracion= 10;
    tareas->Descripcion = "descripcion"; //hacer con strcpy
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
                                                        //pasamos la direc de memoria de la lista q es un punt.
    nuevoNodo->Siguiente = *lista; //*lista=direcc de vble lista
                                //el nuevo nodo apunta al que era el primero
    *lista = nuevoNodo; //lista empieza en el nuevo nodo
}








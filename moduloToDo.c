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
void insertarNodoAlInicio(tNodo ** lista, tNodo * nodo);
tNodo * quitarNodoPorID(tNodo **lista, int id);
void mostrarLista(tNodo*lista);
tNodo * buscarNodoID(tNodo*lista, int idBuscado); 
tNodo * buscarNodoClave(tNodo*lista, char * clave);
void liberarLista(tNodo *lista)


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

            //creo nodo
            tNodo * nuevoNodo = crearNodo(TareaCreada);//recibe la direc de la tarea y devuelve un p al nodo

            //insertamos nodo en lista
            insertarNodoAlInicio(&ListaPendientes, nuevoNodo);//insertamos nodo en lista - &Lista = direcc de memoria de Lista, Lista=0x0

            id++;
            printf("\nContinuar=1 | Finalizar=0 ");
                scanf("%d", &continuar);
                limpiarBuffer();

        } while (continuar!=0);

    printf("\n----Tareas pendientes --> tareas realizadas----");
        //creo lista vacia
        tNodo * ListaRealizadas = crearListaVacia(); //inicializamos lista - Lista=NULL
        int idMover;
        continuar=1;
        do
        {
            printf("\nIngrese id de tarea a mover: ");
                scanf("%d", &idMover);

            //buscamos tarea a mover y la eliminamos de la listaPendientes
            tNodo * tareaAmover = quitarNodoPorID(&ListaPendientes, idMover);
            if (tareaAmover != NULL)
            {
                //insertamos tarea en tareaRealizada
                insertarNodoAlInicio(&ListaRealizadas, tareaAmover);
            }else
            {
                printf("\nNo se encontro la tarea");
            }
            
            printf("\nContinuar=1 | Finalizar=0 ");
                scanf("%d", &continuar);
                limpiarBuffer();
        } while (continuar!=0);

    printf("\n----Listado de Tareas pendientes----");
        mostrarLista(ListaPendientes);
    printf("\n----Listado de Tareas Realizadas----");
        mostrarLista(ListaRealizadas);

    printf("\n----Buscar tarea por ID----");
        int idBuscar;
        printf("\nIngrese el id:");
            scanf("%d",&idBuscar);

        //buscar en pendientes
        tNodo * tareaPorId = buscarNodoID(ListaPendientes, idBuscar);
        if (tareaPorId != NULL)
        {
            
            printf("\n\tTarea encontrada en PENDIENTES: ");
                printf("\n\tID: %d", tareaPorId->datosTarea->TareaID);
                printf("\n\tDescripcion: %s", tareaPorId->datosTarea->Descripcion);
                printf("\n\tDuracion: %d\n", tareaPorId->datosTarea->Duracion);
        }else {
            //buscar en realizadas
            tareaPorId = buscarNodoID(ListaRealizadas, idBuscar);

            if (tareaPorId != NULL)
            {
                printf("\n\tTarea encontrada en REALIZADAS: ");
                    printf("\n\tID: %d", tareaPorId->datosTarea->TareaID);
                    printf("\n\tDescripcion: %s", tareaPorId->datosTarea->Descripcion);
                    printf("\n\tDuracion: %d\n", tareaPorId->datosTarea->Duracion);
            }else { 
            printf("\n\tTarea no encontrada ");
            }
        }

    printf("\n----Buscar tarea por CLAVE----");
        char clave[50];
        printf("\nIngrese palabra clave: ");
        fgets(clave, sizeof(clave), stdin);
    
    
        
    //liberamos memoria
    liberarLista(ListaPendientes);
    liberarLista(ListaRealizadas);

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

void insertarNodoAlInicio(tNodo ** lista, tNodo * nuevoNodo){ //(** es punt a punt de lista) xq necesito pasar la direc de memoria del punt a lista
                                                        //pasamos la direc de memoria de la lista de afuera q es un punt.
    nuevoNodo->Siguiente = *lista; //*lista=direcc de vble lista
                                //el nuevo nodo apunta al que era el primero, al comienzo de la lista
    *lista = nuevoNodo; //lista empieza en el nuevo nodo
}

tNodo * quitarNodoPorID(tNodo **lista, int id){
    tNodo * nodoAux = (*lista); //es la direcc del punt que apunta a la lista, para modificarla desde la cabecera
    tNodo * nodoAnterior = NULL;
    while (nodoAux != NULL && nodoAux->datosTarea->TareaID != id)
    {
        nodoAnterior = nodoAux;
        nodoAux = nodoAux->Siguiente;
    }

    if (nodoAux != NULL)
    {
        if (nodoAux == (*lista))        
        {
            (*lista) = nodoAux->Siguiente;
        }else
        {
            nodoAnterior->Siguiente = nodoAux->Siguiente;
        }
        nodoAux->Siguiente = NULL;

    }

    return (nodoAux);

}

void mostrarLista(tNodo*lista){
    tNodo *aux = lista; //aux para no perder la primera posicion
    if (aux == NULL)
    {
        printf("\n\tLista vacia");
        return; //corta aquí
    }
    
    while (aux != NULL) //recorremos todos los nodos
    {
        printf("\n\tTarea[%d]", aux->datosTarea->TareaID);
        printf("\n\t\tDescripcion: %s", aux->datosTarea->Descripcion);
        printf("\n\t\tDuracion: %d", aux->datosTarea->Duracion);  

        aux = aux->Siguiente; //avanzamos de nodo
    }
    
}

tNodo * buscarNodoID(tNodo*lista, int idBuscado){
    tNodo * aux = lista; //apuntamos con punt aux a la cabecera de la lista a recorrer
    while (aux && aux->datosTarea->TareaID != idBuscado) //aux != NULL && ... 
    {
        aux = aux->Siguiente;
    }
    return aux;
}

tNodo * buscarNodoClave(tNodo*lista, char * clave){
    tNodo *aux = lista;
    while (aux != NULL && strstr(aux->datosTarea->Descripcion, clave) == NULL)
    {
        aux = aux->Siguiente;
    }

    return aux;
}

void liberarLista(tNodo *lista){  //recorremos la lista liberando cada malloc hecho
    tNodo *aux;

    while (lista != NULL){
        aux = lista;
        lista = lista->Siguiente;

        free(aux->datosTarea->Descripcion);
        free(aux->datosTarea);
        free(aux);
    }
}

void limpiarBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} 
    //sigue tomando info desde stdin buscando algun valor distinto a salto de linea o endOfFile
    //usar despues de scanf para numeros, antes del fgets para tomar cadena
}









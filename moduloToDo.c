#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tTarea{ 
    int TareaID;//Numérico autoincremental comenzando en 1000 
    char *Descripcion;  //       
    int Duracion; // entre 10 – 100  
}tTarea;  

typedef struct tNodo{ 
    tTarea datoTarea;  
    struct tNodo *Siguiente;  
}tNodo; 

tNodo * crearListaVacia();
tNodo * crearNodo(tTarea datos);


int main(){
    tNodo * tTareasPendientes = crearListaVacia(); //start
    tNodo * tTareasRealizadas = crearListaVacia();; 

    return 0;
}

tNodo * crearListaVacia()
{
    return NULL;
}

tNodo * crearNodo(tTarea datos){
    tNodo *pNodo = (tNodo *)malloc(sizeof(tNodo));
    //debo pasar la direccion del dato a pNodo?
    //*pNodo->datoTarea = datos.Descripcion;
}








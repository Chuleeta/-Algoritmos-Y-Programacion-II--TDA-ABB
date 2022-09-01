#include "abb.h"
#include <stddef.h>
#include <stdlib.h>


abb_t* abb_crear(abb_comparador comparador){
  if(!comparador)
    return NULL;

  abb_t* arbol = calloc(1, sizeof(abb_t));
  if(!arbol)
    return NULL;
  arbol->comparador = comparador;

  return arbol;
}


//Recibe un nodo_actual y un nodo_nuevo y se llama asi misma hasta no haber nodo, ahi devuelve el nodo_nuevo
nodo_abb_t* insertar_elemento(nodo_abb_t* nodo_actual, nodo_abb_t* nodo_nuevo, abb_comparador comparador){
  if (!nodo_actual)
    return nodo_nuevo;

  if(comparador(nodo_actual->elemento, nodo_nuevo->elemento) > 0)
    nodo_actual->izquierda = insertar_elemento(nodo_actual->izquierda, nodo_nuevo, comparador);
  else  
    nodo_actual->derecha = insertar_elemento(nodo_actual->derecha, nodo_nuevo, comparador);

  return nodo_actual;
}


abb_t* abb_insertar(abb_t* arbol, void* elemento){
  if(!arbol)
    return NULL;

  nodo_abb_t* nodo_nuevo = calloc(1, sizeof(nodo_abb_t));
  if(!nodo_nuevo)
    return NULL;
    
  nodo_nuevo->elemento = elemento;
    
  if(!arbol->nodo_raiz){
    arbol->nodo_raiz = nodo_nuevo;
    arbol->tamanio++;
    return arbol;
  }

  insertar_elemento(arbol->nodo_raiz, nodo_nuevo, arbol->comparador);

  arbol->tamanio++;
  return arbol;
}


//Recibe un nodo y recorre siempre el hijo derecho, una vez no tenga mas hijos derechos 
//devuelve el ultimo hijo derecho valido
nodo_abb_t* nodo_izquierdo_mas_derecho(nodo_abb_t* nodo){
  if(nodo){
    if(nodo->derecha)
      nodo = nodo_izquierdo_mas_derecho(nodo->derecha);
  }

  return nodo;
}


/*
Recibe un nodo_actual, lo recorre hasta encontrar el elmento pedido. De no ser asi devuelve NULL. 
Si lo encuentra se encarga de guardar el elemento del nodo a quitar y elimina el nodo ademas de
conectar a los hijos de este respetando el orden del arbol.
*/
nodo_abb_t* quitar_elemento(nodo_abb_t** nodo_actual, void* elemento, abb_comparador comparador, void** elemento_quitado){

  if(!(*nodo_actual)) return (*nodo_actual);
  else if(comparador(elemento, (*nodo_actual)->elemento) < 0)
    (*nodo_actual)->izquierda = quitar_elemento(&(*nodo_actual)->izquierda, elemento, comparador, elemento_quitado);
  else if(comparador(elemento, (*nodo_actual)->elemento) > 0)
    (*nodo_actual)->derecha = quitar_elemento(&(*nodo_actual)->derecha, elemento, comparador, elemento_quitado);
  
  else{
    //sin hijos
    if((*nodo_actual)->derecha == NULL && (*nodo_actual)->izquierda == NULL){
      (*elemento_quitado) = (*nodo_actual)->elemento;
      free((*nodo_actual));
      (*nodo_actual) = NULL;
    }

    //un hijo, el izquierdo
    else if((*nodo_actual)->derecha == NULL){
      nodo_abb_t* nodo_temporal = (*nodo_actual);
      (*elemento_quitado) = (*nodo_actual)->elemento;
      (*nodo_actual) = (*nodo_actual)->izquierda;
      free(nodo_temporal);
    }
    //un hijo, el derecho
    else if((*nodo_actual)->izquierda == NULL){
      (*elemento_quitado) = (*nodo_actual)->elemento;
      nodo_abb_t* nodo_temporal = (*nodo_actual);
      (*nodo_actual) = (*nodo_actual)->derecha;
      free(nodo_temporal);
    }

    //dos hijos
    else{
      (*elemento_quitado) = (*nodo_actual)->elemento;
      nodo_abb_t* nodo_predecesor = nodo_izquierdo_mas_derecho((*nodo_actual)->izquierda);
      (*nodo_actual)->elemento = nodo_predecesor->elemento;
      void* elemento_quitado_a_eliminar = NULL;
      (*nodo_actual)->izquierda = quitar_elemento(&(*nodo_actual)->izquierda, nodo_predecesor->elemento, comparador, &elemento_quitado_a_eliminar);
    }
  }


  return (*nodo_actual);
}


void* abb_quitar(abb_t* arbol, void *elemento){
  if(!arbol || (arbol->tamanio == 0))
    return NULL;

  void* elemento_quitado = NULL;
  quitar_elemento(&arbol->nodo_raiz, elemento, arbol->comparador, &elemento_quitado);
  if(!elemento_quitado)
    return NULL;
  arbol->tamanio--;
  if(arbol->tamanio == 0)
    arbol->nodo_raiz = NULL;

  return elemento_quitado;
}


void* buscar_elemento(nodo_abb_t* nodo_actual, void* elemento, abb_comparador comparador){
  while(nodo_actual){
    int resultado_comparacion = comparador(elemento, nodo_actual->elemento);
    if(resultado_comparacion == 0){
      return nodo_actual->elemento;
    }else if(resultado_comparacion < 0){
      nodo_actual = nodo_actual->izquierda;
    }else{
      nodo_actual = nodo_actual->derecha;
    }
  }

  return NULL;
}


void* abb_buscar(abb_t* arbol, void* elemento){
  if(!arbol)
    return NULL;

  void* elemento_encontrado = buscar_elemento(arbol->nodo_raiz, elemento, arbol->comparador);
  if(!elemento_encontrado)
    return NULL;
  return elemento_encontrado;
}


bool abb_vacio(abb_t* arbol){
  if(!arbol || arbol->tamanio == 0)
    return true;
  return false;
}


size_t abb_tamanio(abb_t *arbol){
  if(!arbol)
    return 0;
  return arbol->tamanio;
}


//Recorre los hijos del nodo y los libera
void nodo_abb_destruir(nodo_abb_t* nodo, void (*destructor)(void *)){
  if(nodo){
    if(nodo->izquierda != NULL)
      nodo_abb_destruir(nodo->izquierda, destructor);
    if(nodo->derecha != NULL)
      nodo_abb_destruir(nodo->derecha, destructor);
    if(destructor)
      destructor(nodo->elemento);
    free(nodo);
  }
}


void abb_destruir(abb_t *arbol){
  if(arbol){
    abb_destruir_todo(arbol, NULL);
  }
}


void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *)){
  if(arbol){
    if(arbol->nodo_raiz != NULL && arbol->tamanio > 0){
      nodo_abb_destruir(arbol->nodo_raiz, destructor);
    }
    free(arbol);
  }
}


//Recorre el arbol INORDEN aplicandole la funcion pasada por parametro, devuelve a cuantos elemento le pudo aplicar la funcion
size_t abb_con_cada_elemento_inorden(nodo_abb_t* nodo_actual, bool (*funcion)(void *, void *), void *aux, bool* puedo_seguir){
  if(!nodo_actual)
    return 0;
  size_t contador = 1;
  
  if(*puedo_seguir)
    contador += abb_con_cada_elemento_inorden(nodo_actual->izquierda, funcion, aux, puedo_seguir);

  if(*puedo_seguir){
    *puedo_seguir = funcion(nodo_actual->elemento, aux);
  }else contador --;
  
  if(*puedo_seguir)
    contador += abb_con_cada_elemento_inorden(nodo_actual->derecha, funcion, aux, puedo_seguir);

  return contador;
}


//Recorre el arbol PREORDEN aplicandole la funcion pasada por parametro, devuelve a cuantos elemento le pudo aplicar la funcion
size_t abb_con_cada_elemento_preorden(nodo_abb_t* nodo_actual, bool (*funcion)(void *, void *), void *aux, bool* puedo_seguir){
  if(!nodo_actual)
    return 0;
  size_t contador = 1;
  
  *puedo_seguir = funcion(nodo_actual->elemento, aux);

  if(*puedo_seguir){
    contador += abb_con_cada_elemento_preorden(nodo_actual->izquierda, funcion, aux, puedo_seguir);
  }
  if(*puedo_seguir){
    contador += abb_con_cada_elemento_preorden(nodo_actual->derecha, funcion, aux, puedo_seguir);
  }

  return contador;
}


//Recorre el arbol POSTORDEN aplicandole la funcion pasada por parametro, devuelve a cuantos elemento le pudo aplicar la funcion
size_t abb_con_cada_elemento_postorden(nodo_abb_t* nodo_actual, bool (*funcion)(void *, void *), void *aux, bool* puedo_seguir){
  if(!nodo_actual)
    return 0;
  size_t contador = 1;

  if(*puedo_seguir)
    contador += abb_con_cada_elemento_postorden(nodo_actual->izquierda, funcion, aux, puedo_seguir);
  else
    contador--;
  if(*puedo_seguir)
    contador += abb_con_cada_elemento_postorden(nodo_actual->derecha, funcion, aux, puedo_seguir);
  
  if(*puedo_seguir){
    *puedo_seguir = funcion(nodo_actual->elemento, aux);
  }else contador--;

  return contador;
}



size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido, bool (*funcion)(void *, void *), void *aux){
  if(!arbol || !funcion)
    return 0;

  bool puedo_seguir = true;
  
  if(recorrido == INORDEN){
    return abb_con_cada_elemento_inorden(arbol->nodo_raiz, funcion, aux, &puedo_seguir);
  }
  else if(recorrido == PREORDEN){
    return abb_con_cada_elemento_preorden(arbol->nodo_raiz, funcion, aux, &puedo_seguir);
  }
  
  return abb_con_cada_elemento_postorden(arbol->nodo_raiz, funcion, aux, &puedo_seguir);
}


//Recorre el arbol INORDEN, guarda los elementos recorridos en el array, devuelve cuantos elementos pudo guardar
size_t abb_recorrer_inorden(nodo_abb_t* nodo, abb_recorrido recorrido, void** array, size_t tamanio_array, size_t* tamanio_actual){
  if(!nodo)
    return 0;
  size_t contador = 0;
  contador += abb_recorrer_inorden(nodo->izquierda, recorrido, array, tamanio_array, tamanio_actual);
  
  if((*tamanio_actual) < tamanio_array){
    *(array + (*tamanio_actual)) = nodo->elemento;
    (*tamanio_actual)++;
    contador++;
  }

  contador += abb_recorrer_inorden(nodo->derecha, recorrido, array, tamanio_array, tamanio_actual);
  
  return contador;
}


//Recorre el arbol PREORDEN, guarda los elementos recorridos en el array, devuelve cuantos elementos pudo guardar
size_t abb_recorrer_preorden(nodo_abb_t* nodo, abb_recorrido recorrido, void** array, size_t tamanio_array, size_t* tamanio_actual){
  if(!nodo)
    return 0;
  size_t contador = 0;
  
  if((*tamanio_actual) < tamanio_array){
    *(array + (*tamanio_actual)) = nodo->elemento;
    (*tamanio_actual)++;
    contador++;
  }
  
  contador += abb_recorrer_preorden(nodo->izquierda, recorrido, array, tamanio_array, tamanio_actual);

  contador += abb_recorrer_preorden(nodo->derecha, recorrido, array, tamanio_array, tamanio_actual);
  
  return contador;
}


//Recorre el arbol POSTORDEN, guarda los elementos recorridos en el array, devuelve cuantos elementos pudo guardar
size_t abb_recorrer_postorden(nodo_abb_t* nodo, abb_recorrido recorrido, void** array, size_t tamanio_array, size_t* tamanio_actual){
  if(!nodo)
    return 0;
  size_t contador = 0;
  contador += abb_recorrer_postorden(nodo->izquierda, recorrido, array, tamanio_array, tamanio_actual);
  
  contador += abb_recorrer_postorden(nodo->derecha, recorrido, array, tamanio_array, tamanio_actual);
  
  if((*tamanio_actual) < (tamanio_array)){
    *(array + (*tamanio_actual)) = nodo->elemento;
    (*tamanio_actual)++;
    contador++;
  }
  
  return contador;
}


size_t abb_recorrer(abb_t* arbol, abb_recorrido recorrido, void** array, size_t tamanio_array){
  if(!arbol)
    return 0;
  size_t tamanio_actual_incial = 0;

  if(recorrido == INORDEN){
    return abb_recorrer_inorden(arbol->nodo_raiz, recorrido, array, tamanio_array, &tamanio_actual_incial);
  }else if(recorrido == PREORDEN){
    return abb_recorrer_preorden(arbol->nodo_raiz, recorrido, array, tamanio_array, &tamanio_actual_incial);
  }

  return abb_recorrer_postorden(arbol->nodo_raiz, recorrido, array, tamanio_array, &tamanio_actual_incial);
}
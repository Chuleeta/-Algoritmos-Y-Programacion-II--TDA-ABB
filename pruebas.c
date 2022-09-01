#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

#include <stdlib.h>
#include <stdbool.h>


int funcion_comparar(void* elemento1, void* elemento2){
  return (*(int*)elemento1 - *(int*)elemento2);
}


void prueboCrearYDestruirUnABB_DevuelvoUnABB(){
  abb_t* arbol;

  pa2m_afirmar((arbol = abb_crear(funcion_comparar)), "Se puede crear un ABB");
  pa2m_afirmar(arbol->tamanio == 0, "Al crear un ABB el tamanio es el correcto");
  pa2m_afirmar(arbol->nodo_raiz == NULL, "Al crear un ABB su raiz no apunta a nada");
  pa2m_afirmar((arbol->comparador == funcion_comparar), "Al crear un ABB su funcion comparador es la correcta");
  pa2m_afirmar(abb_crear(NULL) == NULL, "No se puede crear un ABB con una funcion comparadora invalida");

  abb_destruir(arbol);
}


void prueboInsertarUnElementoEnUnABB_DevuelvoElABB(){
  abb_t* arbol = abb_crear(funcion_comparar);

  int numero_random_1 = 214;
  int numero_random_2 = 874;
  int numero_random_3 = 69;
  int numero_random_4 = 420;
  int numero_random_5 = 7;
  

  pa2m_afirmar(abb_insertar(NULL, &numero_random_1) == NULL, "No se puedo insertar un elemento en un arbol invalido");
  pa2m_afirmar(abb_insertar(arbol, &numero_random_1), "Se puedo insertar 1 elemento");
  pa2m_afirmar(abb_insertar(arbol, &numero_random_2), "Se puedo insertar 2 elementos");
  pa2m_afirmar(abb_insertar(arbol, &numero_random_3), "Se puedo insertar 3 elementos");
  pa2m_afirmar(abb_insertar(arbol, &numero_random_4), "Se puedo insertar 4 elementos");
  pa2m_afirmar(abb_insertar(arbol, &numero_random_5), "Se puedo insertar 5 elementos");
  pa2m_afirmar(arbol->tamanio == 5, "El tamanio del arbol es el correcto");

  pa2m_afirmar(((arbol->nodo_raiz->elemento) == &numero_random_1), "El nodo raiz es correcto");
  pa2m_afirmar(((arbol->nodo_raiz->izquierda->elemento) == &numero_random_3), "El nodo izquierdo al raiz es correcto");
  pa2m_afirmar(((arbol->nodo_raiz->derecha->elemento) == &numero_random_2), "El nodo derecho al raiz es correcto");
  pa2m_afirmar(((arbol->nodo_raiz->izquierda->izquierda->elemento) == &numero_random_5), "El nodo es correcto");
  pa2m_afirmar(((arbol->nodo_raiz->derecha->izquierda->elemento) == &numero_random_4), "El nodo es correcto");

  abb_destruir(arbol);
}


void prueboQuitarUnElementoDeUnABB_DevuelvoElElemento(){
  abb_t* arbol = abb_crear(funcion_comparar);
  abb_t* arbol_para_quitar_dos_hijos = abb_crear(funcion_comparar);
  abb_t* arbol_vacio = abb_crear(funcion_comparar);
  abb_t* arbol_2 = abb_crear(funcion_comparar);
  abb_t* arbol_3 = abb_crear(funcion_comparar);
  abb_t* arbol_4 = abb_crear(funcion_comparar);
  abb_t* arbol_5 = abb_crear(funcion_comparar);
  abb_t* arbol_6 = abb_crear(funcion_comparar);

  int numero_random_1 = 214;
  int numero_random_2 = 874;
  int numero_random_3 = 69;
  int numero_random_4 = 420;
  int numero_random_5 = 7;

  int numero_random_6 = 350;
  int numero_random_7 = 400;
  int numero_random_8 = 405;
  int numero_random_9 = 430;

  int numero_1 = 1;
  int numero_2 = 2;
  int numero_3 = 3;
  int numero_4 = 4;
  int numero_5 = 5;
  int numero_6 = 6;
  int numero_7 = 7;

  int numero_no_existente = 5;

  abb_insertar(arbol, &numero_random_1);
  abb_insertar(arbol, &numero_random_2);
  abb_insertar(arbol, &numero_random_3);
  abb_insertar(arbol, &numero_random_4);
  abb_insertar(arbol, &numero_random_5);

  abb_insertar(arbol_para_quitar_dos_hijos, &numero_random_1);
  abb_insertar(arbol_para_quitar_dos_hijos, &numero_random_2);
  abb_insertar(arbol_para_quitar_dos_hijos, &numero_random_3);
  abb_insertar(arbol_para_quitar_dos_hijos, &numero_random_4);
  abb_insertar(arbol_para_quitar_dos_hijos, &numero_random_5);
  abb_insertar(arbol_para_quitar_dos_hijos, &numero_random_6);
  abb_insertar(arbol_para_quitar_dos_hijos, &numero_random_7);
  abb_insertar(arbol_para_quitar_dos_hijos, &numero_random_8);
  abb_insertar(arbol_para_quitar_dos_hijos, &numero_random_9);

  abb_insertar(arbol_2, &numero_4);
  abb_insertar(arbol_2, &numero_2);
  abb_insertar(arbol_2, &numero_6);
  abb_insertar(arbol_2, &numero_1);
  abb_insertar(arbol_2, &numero_3);
  abb_insertar(arbol_2, &numero_5);
  abb_insertar(arbol_2, &numero_7);

  abb_insertar(arbol_3, &numero_2);
  abb_insertar(arbol_3, &numero_1);
  abb_insertar(arbol_3, &numero_6);
  abb_insertar(arbol_3, &numero_5);
  abb_insertar(arbol_3, &numero_7);

  abb_insertar(arbol_4, &numero_1);

  abb_insertar(arbol_5, &numero_1);
  abb_insertar(arbol_5, &numero_2);

  abb_insertar(arbol_6, &numero_1);
  abb_insertar(arbol_6, &numero_6);
  abb_insertar(arbol_6, &numero_5);
  abb_insertar(arbol_6, &numero_7);


  void* elemento1 = abb_quitar(arbol, &numero_random_2);

  pa2m_afirmar((elemento1 == &numero_random_2), "Se puede quitar un elemento del arbol");
  pa2m_afirmar((arbol->tamanio == 4), "Al quitar un elemento del arbol la cantidad disminuye");
  
  void* elemento2 = abb_quitar(arbol, &numero_random_4);
  
  pa2m_afirmar((elemento2 == &numero_random_4), "Se puede quitar un elemento del arbol que era hijo de otro elemento ya quitado");
  pa2m_afirmar((arbol->tamanio == 3), "Al quitar un elemento del arbol la cantidad disminuye");

  void* elemento3 = abb_quitar(arbol_para_quitar_dos_hijos, &numero_random_1);

  pa2m_afirmar(elemento3 == &numero_random_1, "Se puede sacar el nodo raiz");
  pa2m_afirmar((arbol_para_quitar_dos_hijos->tamanio == 8), "Al quitar el nodo raiz del arbol la cantidad disminuye");
  pa2m_afirmar(arbol_para_quitar_dos_hijos->nodo_raiz->elemento == &numero_random_3, "Al quitar el nodo_raiz queda como nueva raiz el elemento mas cercano a este de la izquierda");

  pa2m_afirmar(abb_quitar(arbol_2, &numero_4) == &numero_4, "Pruebo sacar el nodo raiz de un arbol con mas de un hijo");
  pa2m_afirmar((arbol_2->tamanio == 6), "Al quitar el nodo raiz del arbol la cantidad disminuye");

  pa2m_afirmar(abb_quitar(arbol_3, &numero_2) == &numero_2, "Pruebo sacar el nodo raiz de un arbol con mas de un hijo");
  pa2m_afirmar((arbol_3->tamanio == 4), "Al quitar el nodo raiz del arbol la cantidad disminuye");
  pa2m_afirmar(arbol_3->nodo_raiz->elemento == &numero_1, "El nodo raiz es el correcto");
  
  pa2m_afirmar(abb_quitar(arbol_3, &numero_1) == &numero_1, "Pruebo sacar el nodo raiz de un arbol con un solo subarbol");
  pa2m_afirmar((arbol_3->tamanio == 3), "Al quitar el nodo raiz del arbol la cantidad disminuye");

  pa2m_afirmar(abb_quitar(arbol_4, &numero_1) == &numero_1, "Pruebo sacar el nodo raiz de un arbol con un nodo");
  pa2m_afirmar((arbol_4->tamanio == 0), "Al quitar el nodo raiz del arbol la cantidad disminuye");
  pa2m_afirmar(!arbol_4->nodo_raiz, "El nodo raiz es el correcto");

  pa2m_afirmar(abb_quitar(arbol_5, &numero_1) == &numero_1, "Pruebo sacar el nodo raiz de un arbol con un hijo");

  pa2m_afirmar((arbol_5->tamanio == 1), "Al quitar el nodo raiz del arbol la cantidad disminuye");
  pa2m_afirmar(arbol_5->nodo_raiz->elemento == &numero_2, "El nodo raiz es el correcto");


  pa2m_afirmar(abb_quitar(arbol_6, &numero_1) == &numero_1, "Pruebo sacar el nodo raiz de un arbol con solo un subarbol derecho");
  pa2m_afirmar((arbol_6->tamanio == 3), "Al quitar el nodo raiz del arbol la cantidad disminuye");
  pa2m_afirmar(arbol_6->nodo_raiz->elemento == &numero_6, "El nodo raiz es el correcto");

  void* elemento4 = abb_quitar(arbol, &numero_no_existente);

  pa2m_afirmar(( elemento4 == NULL), "No encuentra un elemento que no esta en el arbol");
  pa2m_afirmar((abb_quitar(NULL, &numero_random_3) == NULL), "No encuentra un elemento en un arbol NULL");
  pa2m_afirmar((abb_quitar(arbol_vacio, &numero_random_3) == NULL), "No encuentra un elemento en un arbol vacio");



  abb_destruir(arbol_para_quitar_dos_hijos);
  abb_destruir(arbol);
  abb_destruir(arbol_vacio);
  abb_destruir(arbol_2);
  abb_destruir(arbol_3);
  abb_destruir(arbol_4);
  abb_destruir(arbol_5);
  abb_destruir(arbol_6);
}


void prueboBuscarUnElementoEnUnABB_DevuelveElElemento(){
  abb_t* arbol = abb_crear(funcion_comparar);

  int numero_random_1 = 214;
  int numero_random_2 = 874;
  int numero_random_3 = 69;
  int numero_random_4 = 420;
  int numero_random_5 = 7;

  int numero_inexistento = 55;

  abb_insertar(arbol, &numero_random_1);
  abb_insertar(arbol, &numero_random_2);
  abb_insertar(arbol, &numero_random_3);
  abb_insertar(arbol, &numero_random_4);
  abb_insertar(arbol, &numero_random_5);

  pa2m_afirmar(abb_buscar(arbol, &numero_random_4) == &numero_random_4,"Al buscar un elemento que esta en el arbol devuelve ese mismo elemento");
  pa2m_afirmar(abb_buscar(arbol, &numero_inexistento) == NULL,"Al buscar un elemento que no existe en un arbol devuelve que no lo pudo encontrar");
  pa2m_afirmar(abb_buscar(NULL, &numero_random_4) == NULL,"Al buscar un elemento en un arbol invalido devuelve que no lo pudo encontrar");

  abb_destruir(arbol);
}

bool mostrar_numeros_menores_a_otro(void* elemento, void* aux){
  if((*(int*)elemento) < (*(int*)aux)){
    return true;
  }

  return false;
}


void prueboAplciarUnaFuncionACadaElementoDeUnArbolEnElOrdenIndicado(){
  abb_t* arbol = abb_crear(funcion_comparar);
  abb_t* arbol_2 = abb_crear(funcion_comparar);


  int numero_random_1 = 214;
  int numero_random_2 = 874;
  int numero_random_3 = 69;
  int numero_random_4 = 420;
  int numero_random_5 = 7;
  int numero_random_6 = 401;
  int numero_random_7 = 350;
  int numero_random_8 = 405;
  int numero_random_9 = 430;

  int numero_aux = 400;

  abb_insertar(arbol, &numero_random_1);
  abb_insertar(arbol, &numero_random_2);
  abb_insertar(arbol, &numero_random_3);
  abb_insertar(arbol, &numero_random_4);
  abb_insertar(arbol, &numero_random_5);

  abb_insertar(arbol_2, &numero_random_1);
  abb_insertar(arbol_2, &numero_random_2);
  abb_insertar(arbol_2, &numero_random_3);
  abb_insertar(arbol_2, &numero_random_4);
  abb_insertar(arbol_2, &numero_random_5);
  abb_insertar(arbol_2, &numero_random_6);
  abb_insertar(arbol_2, &numero_random_7);
  abb_insertar(arbol_2, &numero_random_8);
  abb_insertar(arbol_2, &numero_random_9);
  

  pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, mostrar_numeros_menores_a_otro, &numero_aux) == 4, "Recorre un arbol inorden correctamente");
  pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, mostrar_numeros_menores_a_otro, &numero_aux) == 4, "Recorre un arbol preorden correctamente");
  pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, mostrar_numeros_menores_a_otro, &numero_aux) == 3, "Recorre un arbol postorden correctamente");

  pa2m_afirmar(abb_con_cada_elemento(arbol_2, INORDEN, mostrar_numeros_menores_a_otro, &numero_aux) == 5, "Recorre un arbol_2 inorden correctamente");
  pa2m_afirmar(abb_con_cada_elemento(arbol_2, PREORDEN, mostrar_numeros_menores_a_otro, &numero_aux) == 4, "Recorre un arbol_2 preorden correctamente");
  pa2m_afirmar(abb_con_cada_elemento(arbol_2, POSTORDEN, mostrar_numeros_menores_a_otro, &numero_aux) == 4, "Recorre un arbol_2 postorden correctamente");

  
  pa2m_afirmar(abb_con_cada_elemento(NULL, INORDEN, mostrar_numeros_menores_a_otro, &numero_aux) == 0, "Al recorrer un arbol invalido devuelve 0");
  


  abb_destruir(arbol);
  abb_destruir(arbol_2);
}


void prueboRecorrerElArbolEnElOrdenEspecificadoEIntentoGuardarlosEnUnArray(){
  abb_t* arbol = abb_crear(funcion_comparar);

  int numero_random_1 = 214;
  int numero_random_2 = 874;
  int numero_random_3 = 69;
  int numero_random_4 = 420;
  int numero_random_5 = 7;

  abb_insertar(arbol, &numero_random_1);
  abb_insertar(arbol, &numero_random_2);
  abb_insertar(arbol, &numero_random_3);
  abb_insertar(arbol, &numero_random_4);
  abb_insertar(arbol, &numero_random_5);

  int* numeros_guardados[3];

  pa2m_afirmar(abb_recorrer(arbol, INORDEN, (void**)numeros_guardados, 3) == 3,"Pruebo recorrer el arbol INORDEN y coloco 3 elementos en un array de tamanio 3");
  pa2m_afirmar(abb_recorrer(arbol, PREORDEN, (void**)numeros_guardados, 3) == 3,"Pruebo recorrer el arbol PREORDEN y coloco 3 elementos en un array de tamanio 3");
  pa2m_afirmar(abb_recorrer(arbol, POSTORDEN, (void**)numeros_guardados, 3) == 3,"Pruebo recorrer el arbol POSTORDEN y coloco 3 elementos en un array de tamanio 3");

  pa2m_afirmar(abb_recorrer(NULL, POSTORDEN, (void**)numeros_guardados, 3) == 0,"Pruebo recorrer un arbol invalido");

  abb_destruir(arbol);
}


int main(){
  pa2m_nuevo_grupo("Pruebas de Crear ABB y Destruirlo");
  prueboCrearYDestruirUnABB_DevuelvoUnABB();

  pa2m_nuevo_grupo("Pruebas de Insertar Un Elemento En Un ABB");
  prueboInsertarUnElementoEnUnABB_DevuelvoElABB();

  pa2m_nuevo_grupo("Pruebas de Quitar Un Elemento De Un ABB");
  prueboQuitarUnElementoDeUnABB_DevuelvoElElemento();

  pa2m_nuevo_grupo("Pruebas de Buscar Un Elemento En Un ABB");
  prueboBuscarUnElementoEnUnABB_DevuelveElElemento();

  pa2m_nuevo_grupo("Pruebas Con Cada Elemento De Un ABB");
  prueboAplciarUnaFuncionACadaElementoDeUnArbolEnElOrdenIndicado();

  pa2m_nuevo_grupo("Pruebas de Recorrer El ABB y Depositar Elementos En Array");
  prueboRecorrerElArbolEnElOrdenEspecificadoEIntentoGuardarlosEnUnArray();

  return pa2m_mostrar_reporte();
}

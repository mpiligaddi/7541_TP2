#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ERROR -1
#define EXITO 0
#define MAX_RUTA 100

/*
 * Comparador de elementos. Recibe dos elementos del heap y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*); 

typedef struct heap {
	void** vector;
	int tope;
	heap_comparador comparador;
} heap_t;

/*
Pre: -
Post: Crea un heap y reserva la memoria necesaria para la estructura. 
Comparador se utiliza para comparar dos elementos.
Devuelve un puntero a un heap creado o NULL en caso de error. 
*/

heap_t* heap_crear(heap_comparador comparador);

/*
Pre: -
Post: Inserta un elemento en el heap. Devuelve 0 si pudo insertar o -1 si no pudo. 
*/

int heap_insertar(heap_t* heap, void* elemento);

/*
Pre: -
Post: Intercambia las posiciones de dos elementos pertenecientes al heap. 
*/

void swap(void** vector, int i, int j);

/*
Pre: -
Post: Devuelve la posicion en la que se encuentra el hijo izquierdo de un nodo del heap. 
*/

int posicion_hijo_izquierdo(int n);

/*
Pre: 
Post: Devuelve la posicion en la que se encuentra el hijo derecho de un nodo del heap.
*/

int posicion_hijo_derecho(int n);

/*
Pre: -
Post: Intercambia las posiciones de un elemento actual con el elemento que esta en la posicion de su padre. El elemento actual ahora estara en una posicion mas abajo
*/

void sift_down(heap_t* heap, int n);

/*
Pre: -
Post: Intercambia las posiciones de un elemento actual con el elemento que esta en la posicion de su padre. El elemento actual ahora estara en una posicion mas arriba
*/

void sift_up(heap_t* heap, int n);

/*
Pre: -
Post: Extrae la raiz del heap y devuelve el elemento que se encontraba alli
*/

void* heap_extraer_raiz(heap_t* heap);

/*
Pre: -
Post: Devuelve el elemento en la posicion indicada, donde 0 es el primer elemento. Si no existe dicha posicion devuelve NULL.
*/

void* heap_elemento_raiz(heap_t* heap);

/*
Pre: -
Post: Determina si el heap está vacío. Devuelve true si está vacío o el heap es NULL, false si el heap tiene elementos.
 */

bool heap_vacio(heap_t* heap);

/*
Pre: 
Post: Destruye el heap liberando la memoria reservada por el mismo.
*/

void heap_destruir(heap_t* heap);

#endif /* __HEAP_H__ */
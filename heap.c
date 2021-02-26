#include "heap.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define PADRE_ES_MAYOR -1
#define PRIMERO_ES_MAYOR 1
#define PRIMERO_ES_MENOR -1

// -----------------------------------------------------------------------------------
// -----------------------------FUNCIONES PUBLICAS------------------------------------
// -----------------------------------------------------------------------------------

heap_t* heap_crear(heap_comparador comparador) {
	if(!comparador) {
		return NULL;
	}
	heap_t* heap_nuevo = NULL;
	heap_nuevo = malloc(sizeof(heap_t));
	if(!heap_nuevo) {
		return NULL;
	}
	heap_nuevo->vector = NULL;
	heap_nuevo->comparador = comparador;
	heap_nuevo->tope = 0;

	return heap_nuevo;
}

void swap(void** vector, int i, int j) {
	if(!vector) return;
	void* auxiliar = vector[i];
	vector[i] = vector[j];
	vector[j] = auxiliar;
}

int posicion_padre(int n) {
	return (n-1)/2;
}

int posicion_hijo_izquierdo(int n) {
	return 2*n+1;
}

int posicion_hijo_derecho(int n) {
	return 2*n+2;
}

void sift_down(heap_t* heap, int n) {
	int pos_mayor;
	int pos_izquierda = posicion_hijo_izquierdo(n);
	int pos_derecha = posicion_hijo_derecho(n);
	if(pos_izquierda >= heap->tope) return;
	if(pos_derecha >= heap->tope) pos_mayor = pos_izquierda;
	else {
		if(heap->comparador(heap->vector[pos_derecha], heap->vector[pos_izquierda])== PRIMERO_ES_MENOR) pos_mayor = pos_derecha;
		else pos_mayor = pos_izquierda;
	}
	if(heap->comparador(heap->vector[pos_mayor], heap->vector[n]) == PRIMERO_ES_MENOR) {
		swap(heap->vector, pos_mayor, n);
		sift_down(heap, pos_mayor);
	}
}

void sift_up(heap_t* heap, int n) {
	if((!heap) || (n == 0)) return;
	int padre = posicion_padre(n);
	int comparador = heap->comparador(heap->vector[n],heap->vector[padre]);
	if(comparador == PADRE_ES_MAYOR) { 
		swap(heap->vector,n,padre);
		sift_up(heap,padre);
	}
}

int heap_insertar(heap_t* heap, void* elemento) { 
	if(!heap) return ERROR;

	void* auxiliar = NULL;
  	auxiliar = realloc(heap->vector, sizeof(void*)*(heap->tope+1));
  	if(!auxiliar) return ERROR;

	heap->vector = auxiliar;
	(heap->tope)++;

	heap->vector[heap->tope-1] = elemento;
	sift_up(heap, heap->tope-1);

	return EXITO;
}

void* heap_extraer_raiz(heap_t* heap) {
	if(heap->tope == 0) return 0;

	void* valor = heap->vector[0];

	heap->vector[0] = heap->vector[heap->tope-1];
	(heap->tope)--;

	if(heap->tope != 0) sift_down(heap,0);
	return valor;
}

void* heap_elemento_raiz(heap_t* heap) {
	if(heap_vacio(heap)) return NULL;
	void* valor = heap->vector[0];
	return valor;
}

bool heap_vacio(heap_t* heap) {
	if((!heap) || (heap->tope == 0)) {
		return true;
	}
	return false;
}

void heap_destruir(heap_t* heap) {
	if(heap) {
		for(int i = 0 ; i < heap->tope ; i++) {
	  		if(heap->vector[i]) free(heap->vector[i]);
	  	}
		free(heap->vector);
	}
	free(heap);
}
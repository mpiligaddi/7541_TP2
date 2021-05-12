#include "heap.h"
#include "pa2mm.h"
#include <stdbool.h>
#include <stdlib.h>

#define ERROR -1
#define EXITO 0
#define PRIMERO_ES_MAYOR 1
#define PRIMERO_ES_MENOR -1
#define MAX_RUTA 100

/*
Pre: Recibe dos elemento de tipo void* para comparar
Post: Devuelve 1 en caso de que el primero sea mayor al segundo y -1 en caso de que no.
*/

int comparador_elementos(void* primer_elemento, void* segundo_elemento) {

	int primer_numero = *(int*)primer_elemento;
	int segundo_numero = *(int*)segundo_elemento;

	if(primer_numero > segundo_numero) {
		return PRIMERO_ES_MAYOR;
	}
	return PRIMERO_ES_MENOR;

}

/*
Pre: Recibe una clave a un elemento
Post: Devuelve el elemento
*/

int* crear_elemento(int clave){
    int* elemento = (int*)malloc(sizeof(int));
    if(elemento)
        *elemento = clave;
    return elemento;
}

/*
Pre: Recibe un heap
Post: Libera lo apuntado por los elementos del heap, los elementos del heap y al heap. 
*/

void liberar_heap(heap_t* heap) {
	while(heap->tope > 0) {
		free(heap_extraer_raiz(heap));
	}
	heap_destruir(heap);
}

/*
Pre: Recibe un heap
Post: Imprime por pantalla el vector que contiene a los elementos del mismo.
*/

void imprimir_vector_heap(heap_t* heap) {
	for(int i = 0 ; i < heap->tope ; i++) {
    	printf("%i ", *((int*)(heap->vector[i])));
  	}
  	printf("\n");
}

void probar_creacion_heap() {

	pa2m_nuevo_grupo("PRUEBAS DE CREACION DEL HEAP");
	heap_t* heap_nuevo = heap_crear(comparador_elementos);
	pa2m_afirmar(heap_nuevo != NULL, "Puedo crear un heap");
	pa2m_afirmar(heap_nuevo->vector == NULL, "Vector del heap inicializado a NULL");
	pa2m_afirmar(heap_nuevo->tope == 0, "Tope del heap inicializado a 0");
	heap_destruir(heap_nuevo);
	heap_nuevo = heap_crear(NULL); 
	pa2m_afirmar(heap_nuevo == NULL, "Error al pasar un comparador NULL");

}

void probar_insersion_y_eliminacion_de_elementos_heap() {

	pa2m_nuevo_grupo("PRUEBAS DE INSERCION Y ELIMINACION DE ELEMENTOS EN EL HEAP");
	heap_t* heap_con_elementos = heap_crear(comparador_elementos); 
	heap_t* heap_nuevo_con_elementos = heap_crear(comparador_elementos); 

	int elementos_insertados_nuevos = 0;

	int* elemento_1 = crear_elemento(1);
	int* elemento_2 = crear_elemento(3);
	int* elemento_3 = crear_elemento(5);
	int* elemento_4 = crear_elemento(2);
	int* elemento_5 = crear_elemento(10);
	
	heap_insertar(heap_nuevo_con_elementos, elemento_1);
    heap_insertar(heap_nuevo_con_elementos, elemento_2);
    heap_insertar(heap_nuevo_con_elementos, elemento_3);
    heap_insertar(heap_nuevo_con_elementos, elemento_4);
    heap_insertar(heap_nuevo_con_elementos, elemento_5);

    printf("Elementos del vector del heap: (deberia ser 1 2 5 3 10): ");
	imprimir_vector_heap(heap_nuevo_con_elementos);
  	void* elemento = heap_extraer_raiz(heap_nuevo_con_elementos);
  	printf("Extraigo la raiz (valor %i)\n",*((int*)elemento));
  	free(elemento);
  	printf("Elementos del vector del heap: (deberia ser 2 3 5 10): ");
	imprimir_vector_heap(heap_nuevo_con_elementos);

	elemento = heap_extraer_raiz(heap_nuevo_con_elementos);
  	printf("Extraigo la raiz (valor %i)\n",*((int*)elemento));
  	free(elemento);
  	printf("Elementos del vector del heap: (deberia ser 3 10 5): ");
	imprimir_vector_heap(heap_nuevo_con_elementos);

	elemento = heap_extraer_raiz(heap_nuevo_con_elementos);
  	printf("Extraigo la raiz (valor %i)\n",*((int*)elemento));
  	free(elemento);
  	printf("Elementos del vector del heap: (deberia ser 5 10): ");
	imprimir_vector_heap(heap_nuevo_con_elementos);

	elemento = heap_extraer_raiz(heap_nuevo_con_elementos);
  	printf("Extraigo la raiz (valor %i)\n",*((int*)elemento));
  	free(elemento);
  	printf("Elementos del vector del heap: (deberia ser 10): ");
	imprimir_vector_heap(heap_nuevo_con_elementos);

	elemento = heap_extraer_raiz(heap_nuevo_con_elementos);
  	printf("Extraigo la raiz (valor %i)\n",*((int*)elemento));
  	free(elemento);

  	pa2m_afirmar(heap_vacio(heap_nuevo_con_elementos) == true, "Se pudieron extraer todos los elementos insertados en el heap. El heap esta vacio.");

	pa2m_afirmar(heap_insertar(heap_con_elementos, crear_elemento(0)) == 0, "Puedo insertar un elemento en un heap vacio");
	pa2m_afirmar((*((int*)(heap_elemento_raiz(heap_con_elementos))) == 0), "El elemento de la raiz del heap es el 0");
	for(int i = 1 ; i < 1000 ; i++) {
		if (heap_insertar(heap_con_elementos, crear_elemento(i)) == 0) {
			if(elementos_insertados_nuevos == 9) {
				pa2m_afirmar(elementos_insertados_nuevos == 9, "Se pueden insertar 10 elementos en el heap");
			}
			else if(elementos_insertados_nuevos == 49) {
				pa2m_afirmar(elementos_insertados_nuevos == 49, "Se pueden insertar 50 elementos en el heap");
			}
			(elementos_insertados_nuevos)++;
		}
	}
	pa2m_afirmar(elementos_insertados_nuevos == 999, "Se pueden insertar 1000 elementos en el heap");
	liberar_heap(heap_con_elementos);
	liberar_heap(heap_nuevo_con_elementos);

}

void probar_heap_vacio() {

	pa2m_nuevo_grupo("PRUEBAS DE HEAP VACIO");
	heap_t* heap_nuevo = heap_crear(comparador_elementos);
	pa2m_afirmar(heap_vacio(NULL) == true, "Un heap NULL es un heap vacio");
	pa2m_afirmar(heap_vacio(heap_nuevo) == true, "Un heap con tope igual a 0 es un heap vacio");
	pa2m_afirmar(heap_extraer_raiz(heap_nuevo) == NULL, "Devuelve NULL en caso de querer extraer la raiz de un heap vacio");
	heap_t* heap_nuevo_con_elementos = heap_crear(comparador_elementos);
	int* auxiliar = crear_elemento(0);
	for(int i = 1 ; i < 5 ; i++) {
		heap_insertar(heap_nuevo_con_elementos, crear_elemento(i));
	}
	pa2m_afirmar(heap_vacio(heap_nuevo_con_elementos) != true, "Un heap con tope mayor a 0 no es un heap vacio");

	free(auxiliar);
	liberar_heap(heap_nuevo);
	liberar_heap(heap_nuevo_con_elementos);

}

int main() {

	probar_creacion_heap();
	probar_insersion_y_eliminacion_de_elementos_heap();
	probar_heap_vacio();

	pa2m_mostrar_reporte();

	return 0;

}


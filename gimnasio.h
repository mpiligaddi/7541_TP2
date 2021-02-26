#ifndef __GIMNASIO_H__
#define __GIMNASIO_H__

#include "lista.h"
#include "heap.h"

#define MAX_NOMBRE 100
#define MAX_ENTRENADORES 300
#define MAX_RUTA 100

typedef int (*funcion_batalla)(void*, void*); 

typedef struct pokemon {
	char nombre[MAX_NOMBRE];
	int velocidad;
	int defensa;
	int ataque;
	int puntos_extra;
}pokemon_t;

typedef struct entrenador {
	char nombre[MAX_NOMBRE];
	pokemon_t* pokemon;
	lista_t* lista_pokemones_para_combatir;
	lista_t* lista_pokemones_obtenidos;
}entrenador_t;

typedef struct lider {
	char nombre[MAX_NOMBRE];
	pokemon_t* pokemon;
	lista_t* lista_pokemones_para_combatir;
	lista_t* lista_pokemones_obtenidos;
}lider_t;

typedef struct gimnasio {
	char nombre[MAX_NOMBRE];
	lider_t* lider;
	int dificultad;
	int id_puntero_funcion;
	funcion_batalla batalla;
	entrenador_t* entrenador;
	lista_t* pila_entrenadores;
}gimnasio_t;

typedef struct personaje {
	char nombre[MAX_NOMBRE];
	pokemon_t* pokemon;
	lista_t* lista_pokemones_para_combatir;
	lista_t* lista_pokemones_obtenidos;
}personaje_t;

/*
Pre: Recibe dos elementos del heap
Post: Devuelve 0 en caso de ser elementos iguales, 1 si el primer elemento es mayor al segundo o -1 si el primer elemento es menor al segundo.
*/

int comparador_gimnasios(void* gym_1, void* gym_2);

/*
Pre: -
Post: Agrega un gimnasio al heap a partir de un archivo de texto. Devuelve el gimnasio agregado.
*/

gimnasio_t* agregar_arch_gimnasio(heap_t* heap);

/*
Pre: -
Post: Muestra por pantalla la informacion del gimnasio actual
*/

void mostrar_gimnasio(heap_t* heap_gimnasio);

/*
Pre: -
Post: Agrega un personaje principal para ser utilizado durante todo el juego, a partir de un archivo de texto. Devuelve el personaje agregado.
*/

personaje_t* agregar_arch_personaje_principal();

/*
Pre: Recibe un personaje principal ya cargado al juego
Post: Muestra por pantalla la informacion del personaje principal actual
*/

void mostrar_personaje_principal(personaje_t* personaje);

/*
Pre: Recibe un personaje principal ya cargado al juego
Post: Intercambia un "pokemon obtenido" del personaje principal con un "pokemon de batalla" del mismo, para que el primero pueda ser utilizado en las batallas
*/

void cambiar_pokemon_para_batalla(personaje_t* personaje);

/*
Pre: Recibe un heap en donde ya hay por lo menos 1 gimnasios cargados, con un personaje principal 
Post: Realiza el bucle para que la partida se realice. Si el ganador es el pokemon del personaje principal, se devolvera 1. Si el ganador es el pokemon del entrenador del gimnasio actual, se devolvera -1
*/

int comenzar_batalla(heap_t* heap_gimnasio,personaje_t* personaje,bool simulacion, int* opcion_elegida);

/*
Pre: Recibe un heap en donde ya hay por lo menos 1 gimnasios cargados, con un personaje principal 
Post: Transfiere uno de los pokemones de batalla del lider del gimnasio actual al grupo de los pokemones obtenidos del personaje principal, por ganar ese gimnasio
*/

void tomar_trofeo_prestado(heap_t* heap_gimnasio, personaje_t* personaje);

/*
Pre: 
Post: Libera la memoria reservada para todos los elementos del gimnasio actual
*/

void liberar_gimnasio(heap_t* heap_gimnasio);

/*
Pre: -
Post: Libera la memoria reservada para todos los elementos de todos los gimnasios cargados
*/

void liberar_todo(heap_t* heap_gimnasio, personaje_t* personaje_principal);

#endif /* __GIMNASIO_H__ */
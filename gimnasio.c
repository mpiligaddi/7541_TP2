#include "batallas.h"
#include "gimnasio.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define FONDO_AMARILLO "\e[103m"
#define FONDO_CYAN "\e[46m"
#define FONDO_VIOLETA "\e[45m"
#define FONDO_MAGENTA "\e[105m"
#define FONDO_VERDE "\e[42m"
#define FONDO_GRIS "\e[107m"
#define FONDO_ROJO "\e[41m"
#define FONDO_NEGRO "\e[40m"
#define NORMAL "\e[0m"
#define VERDE "\e[32;1m"
#define NEGRO "\e[30m"
#define VACIO 0
#define MAX_LETRA 2
#define MAX_POKEMON 6
#define NUEVO_NOMBRE "sin nombre"
#define NUEVO_LIDER "sin lider"
#define MAX_PKM_PARA_BATALLA 6
#define MAX_LEIDOS 4
#define FORMATO_INICIAL "%c;"
#define FORMATO_GIMNASIO "%99[^;];%i;%i\n"
#define FORMATO_LIDER "%99[^\n]\n"
#define FORMATO_POKEMON "%99[^;];%i;%i;%i\n"
#define FORMATO_ENTRENADOR "%99[^\n]\n"
#define TURNO_PERDIDO -1
#define TURNO_GANADO 1
#define BATALLA_1 1 
#define BATALLA_2 2
#define BATALLA_3 3
#define BATALLA_4 4
#define BATALLA_5 5
#define SIGUIENTE_TURNO 1
#define FIN -1
#define MAX_MEJORA 63
#define ERROR_AUX 0
#define ARCH_NO_ACEPTADO_AUX 0
#define ARCH_ACEPTADO_AUX 1
#define CANT_MINIMA 6
#define ARCH_GYM "gym.txt"
#define ARCH_PERSONAJE "personaje.txt"
const char LETRA_E_SEC = 'E';
const char LETRA_P_SEC = 'P';
const char LETRA_L_SEC = 'L';
const char LETRA_G_SEC = 'G';
const char LETRA_N_SEC = 'N';
const char LETRA = 'W';

// -----------------------------------------------------------------------------------
// -----------------------------FUNCIONES PRIVADAS------------------------------------
// -----------------------------------------------------------------------------------

/*
Pre: -
Post: Crea un gimnasio y reserva la memoria necesaria para la estructura.
Devuelve un puntero a un gimnasio creado o NULL en caso de error. 
*/

gimnasio_t* crear_gimnasio() {
	gimnasio_t* gimnasio = malloc(sizeof(gimnasio_t));

	if(!gimnasio) {
		return NULL;
	}
	strcpy(gimnasio->nombre,NUEVO_NOMBRE);
	gimnasio->lider = NULL;
	gimnasio->entrenador = NULL;
	gimnasio->dificultad = 0;
	gimnasio->id_puntero_funcion = 0;
	gimnasio->pila_entrenadores = lista_crear();
	if(!gimnasio->pila_entrenadores) {
		free(gimnasio);
		return NULL;
	}
	return gimnasio; 
}

/*
Pre: -
Post: Crea un lider y reserva la memoria necesaria para la estructura. 
Devuelve un puntero a un lider creado o NULL en caso de error. 
*/

lider_t* crear_lider() {
	lider_t* lider = malloc(sizeof(lider_t));

	if(!lider) {
		return NULL;
	}
	strcpy(lider->nombre,NUEVO_NOMBRE);
	lider->pokemon = NULL;
	lider->lista_pokemones_para_combatir = lista_crear();
	if((!lider->lista_pokemones_para_combatir)){
		free(lider);
		return NULL;
	}
	lider->lista_pokemones_obtenidos = lista_crear();
	if((!lider->lista_pokemones_obtenidos)){
		free(lider->lista_pokemones_para_combatir);
		free(lider);
		return NULL;
	}
	return lider;
}

/*
Pre: -
Post: Crea un entrenador y reserva la memoria necesaria para la estructura. 
Devuelve un puntero a un entrenador creado o NULL en caso de error. 
*/

entrenador_t* crear_entrenador() {
	entrenador_t* entrenador = malloc(sizeof(entrenador_t));

	if(!entrenador) {
		return NULL;
	}
	strcpy(entrenador->nombre,NUEVO_NOMBRE);
	entrenador->pokemon = NULL;
	entrenador->lista_pokemones_para_combatir = lista_crear();
	if((!entrenador->lista_pokemones_para_combatir)){
		free(entrenador);
		return NULL;
	}
	entrenador->lista_pokemones_obtenidos = lista_crear();
	if((!entrenador->lista_pokemones_obtenidos)){
		free(entrenador->lista_pokemones_para_combatir);
		free(entrenador);
		return NULL;
	}
	return entrenador;
}

/*
Pre: -
Post: Crea un personaje y reserva la memoria necesaria para la estructura. 
Devuelve un puntero a un personaje creado o NULL en caso de error. 
*/

personaje_t* crear_personaje() {
	personaje_t* personaje_principal = malloc(sizeof(personaje_t));

	if(personaje_principal == NULL) {
		return NULL;
	}
	strcpy(personaje_principal->nombre, NUEVO_NOMBRE);
	personaje_principal->pokemon = NULL;
	personaje_principal->lista_pokemones_para_combatir = lista_crear();
	if((!personaje_principal->lista_pokemones_para_combatir)){
		free(personaje_principal);
		return NULL;
	}
	personaje_principal->lista_pokemones_obtenidos = lista_crear();
	if((!personaje_principal->lista_pokemones_obtenidos)){
		free(personaje_principal->lista_pokemones_para_combatir);
		free(personaje_principal);
		return NULL;
	}
	
	return personaje_principal;
}

/*
Pre: -
Post: Crea un pokemon y reserva la memoria necesaria para la estructura. 
Devuelve un puntero a un pokemon creado o NULL en caso de error. 
*/

pokemon_t* crear_pokemon() {
	pokemon_t* pokemon = malloc(sizeof(pokemon_t));

	if(pokemon == NULL) {
		return NULL;
	}

	strcpy(pokemon->nombre, NUEVO_NOMBRE);
	pokemon->velocidad = 0;
	pokemon->defensa = 0;
	pokemon->ataque = 0;
	pokemon->puntos_extra = 0;

	return pokemon;
}

/*
Pre: -
Post: Lee la informacion del gimnasio y devuelve una cantidad de variables leidas.
*/

int leer_gimnasio(FILE* arch_gym, gimnasio_t* nuevo_gym) {
	return(fscanf(arch_gym, FORMATO_GIMNASIO ,nuevo_gym->nombre,&(nuevo_gym->dificultad), &(nuevo_gym->id_puntero_funcion)));
}

/*
Pre: -
Post: Lee una letra y devuelve una cantidad de variables leidas.
*/

int leer_inicial(FILE* archivo, char* inicial) {
	return(fscanf(archivo, FORMATO_INICIAL ,inicial));
}

/*
Pre: -
Post: Lee la informacion del lider y devuelve una cantidad de variables leidas.
*/

int leer_lider(FILE* arch_gym, gimnasio_t* nuevo_gym) {
	return(fscanf(arch_gym, FORMATO_LIDER ,nuevo_gym->lider->nombre));
}

/*
Pre: -
Post: Lee la informacion del pokemon del lider y devuelve una cantidad de variables leidas.
*/

int leer_pokemon_lider(FILE* arch_gym, gimnasio_t* nuevo_gym) {
	return(fscanf(arch_gym, FORMATO_POKEMON , nuevo_gym->lider->pokemon->nombre, &(nuevo_gym->lider->pokemon->velocidad), &(nuevo_gym->lider->pokemon->ataque), &(nuevo_gym->lider->pokemon->defensa)));
}

/*
Pre: -
Post: Lee la informacion del pokemon del entrenador y devuelve una cantidad de variables leidas.
*/

int leer_pokemon_entrenador(FILE* arch_gym, gimnasio_t* nuevo_gym) {
	return(fscanf(arch_gym, FORMATO_POKEMON , nuevo_gym->entrenador->pokemon->nombre, &(nuevo_gym->entrenador->pokemon->velocidad), &(nuevo_gym->entrenador->pokemon->ataque), &(nuevo_gym->entrenador->pokemon->defensa)));
}

/*
Pre: -
Post: Lee la informacion del entrenador y devuelve una cantidad de variables leidas.
*/

int leer_entrenador(FILE* arch_gym, gimnasio_t* nuevo_gym) {
	return(fscanf(arch_gym, FORMATO_ENTRENADOR , nuevo_gym->entrenador->nombre));
}

/*
Pre: -
Post: Lee la informacion de los pokemones del personaje principal y devuelve una cantidad de variables leidas.
*/

int leer_pkm_personaje_principal(FILE* arch_personaje, personaje_t* nuevo_personaje) {
	return(fscanf(arch_personaje, FORMATO_POKEMON , nuevo_personaje->pokemon->nombre, &(nuevo_personaje->pokemon->velocidad), &(nuevo_personaje->pokemon->ataque), &(nuevo_personaje->pokemon->defensa)));
}

/*
Pre: -
Post: Lee la informacion del personaje principal y devuelve una cantidad de variables leidas.
*/

int leer_personaje_principal(FILE* arch_personaje, personaje_t* nuevo_personaje) {
	return(fscanf(arch_personaje, FORMATO_ENTRENADOR , nuevo_personaje->nombre));
}

/*
Pre: -
Post: Libera la memoria reservada para las listas de pokemones de un entrenador y para el mismo.
*/

void liberar_entrenador(gimnasio_t* nuevo_gym) {
	free(nuevo_gym->entrenador->lista_pokemones_obtenidos);
	free(nuevo_gym->entrenador->lista_pokemones_para_combatir);
	free(nuevo_gym->entrenador);
}

/*
Pre: -
Post: Libera la memoria reservada para todos un gimnasio.
*/

void liberar_gimnasio_aux(gimnasio_t* gimnasio) {
	if(gimnasio) {
		if(gimnasio->pila_entrenadores) {
			while(lista_elementos(gimnasio->pila_entrenadores) > 0) {
				entrenador_t* entrenador_actual = (entrenador_t*)(lista_tope(gimnasio->pila_entrenadores));
				if(entrenador_actual->lista_pokemones_obtenidos) {
					for(int j = 0 ; j < entrenador_actual->lista_pokemones_obtenidos->cantidad ; j++) {
						free(lista_elemento_en_posicion(entrenador_actual->lista_pokemones_obtenidos,j));
					}
					lista_destruir(entrenador_actual->lista_pokemones_obtenidos);
				}
				if(entrenador_actual->lista_pokemones_para_combatir) {
					lista_destruir(entrenador_actual->lista_pokemones_para_combatir); 
				}
				free(lista_tope(gimnasio->pila_entrenadores));
				lista_desapilar(gimnasio->pila_entrenadores);
			}
			lista_destruir(gimnasio->pila_entrenadores);
		}
		if(gimnasio->lider) {
			lider_t* lider_actual = gimnasio->lider;
			if(lider_actual->lista_pokemones_obtenidos) {
				for(int j = 0 ; j < lider_actual->lista_pokemones_obtenidos->cantidad ; j++) {
					free(lista_elemento_en_posicion(lider_actual->lista_pokemones_obtenidos,j));
				}
				lista_destruir(lider_actual->lista_pokemones_obtenidos);
			}
			if(lider_actual->lista_pokemones_para_combatir) {
			lista_destruir(lider_actual->lista_pokemones_para_combatir);
			}
			free(lider_actual);
		}
	}
	free(gimnasio);
}

/*
Pre: Recibe un archivo de texto y un heap.
Post: Lee la informacion del archivo de texto recibido por parametro y carga el gimnasio completo (con toda su informacion) al heap. Tambien carga los pokemones (tanto del lider como de los entrenadores) a su lista correspondiente. Carga todos los entrenadores a una pila. 
Devuelve 1 si pudo leer exitosamente por lo menos un gimnasio o 0 si no.
*/

int cargar_gimnasio(char arch_gym[MAX_RUTA], heap_t* heap) {
	if(!heap) return 0;
	FILE* gimnasio = fopen(arch_gym, "r");
	if(!gimnasio) {
		printf("El archivo no existe!\n");
		return 0;
	}
	gimnasio_t* nuevo_gym = NULL;
	char inicial = LETRA;
	int i = 0;
	int cant_agregada = 0;
	int resultado = ARCH_NO_ACEPTADO_AUX;
	int leidos = leer_inicial(gimnasio,&inicial);
	if(inicial == LETRA_G_SEC) {
		while(leidos > 0) {
			if(inicial == LETRA_G_SEC) {
				nuevo_gym = crear_gimnasio();
				if(nuevo_gym) {
					leidos = leer_gimnasio(gimnasio,nuevo_gym);
					leidos = leer_inicial(gimnasio,&inicial);
					if(inicial != LETRA_L_SEC) {
						leidos = ERROR_AUX;
					}
				}
				else leidos = ERROR_AUX;
			}
			else if(inicial == LETRA_L_SEC) {
				nuevo_gym->lider = crear_lider();
				if(nuevo_gym->lider) { 
					leidos = leer_lider(gimnasio,nuevo_gym);
					leidos = leer_inicial(gimnasio,&inicial);
					if((inicial == LETRA_P_SEC)) {
						while((inicial == LETRA_P_SEC) && (leidos > 0)) {
							nuevo_gym->lider->pokemon = crear_pokemon();
							leidos = leer_pokemon_lider(gimnasio,nuevo_gym);
							if(i < MAX_PKM_PARA_BATALLA) {
								lista_insertar_en_posicion(nuevo_gym->lider->lista_pokemones_para_combatir, nuevo_gym->lider->pokemon, i);
							}
							lista_insertar_en_posicion(nuevo_gym->lider->lista_pokemones_obtenidos, nuevo_gym->lider->pokemon, i);
							i++;
							leidos = leer_inicial(gimnasio,&inicial);
						}
					}
					else leidos = ERROR_AUX;
				}
				else leidos = ERROR_AUX;
			}
			else if(inicial == LETRA_P_SEC) {
				while((leidos > 0) && (inicial == LETRA_P_SEC)) {
					nuevo_gym->entrenador->pokemon = crear_pokemon();
					if(nuevo_gym->entrenador->pokemon) {
						leidos = leer_pokemon_entrenador(gimnasio,nuevo_gym);
						if(i < MAX_PKM_PARA_BATALLA) {
							lista_insertar_en_posicion(nuevo_gym->entrenador->lista_pokemones_para_combatir, nuevo_gym->entrenador->pokemon, i);
						}
						lista_insertar_en_posicion(nuevo_gym->entrenador->lista_pokemones_obtenidos, nuevo_gym->entrenador->pokemon, i);
						i++;
						leidos = leer_inicial(gimnasio,&inicial);
					}
					else leidos = ERROR_AUX;
				}
				lista_apilar(nuevo_gym->pila_entrenadores, nuevo_gym->entrenador);
				if((leidos > 0) && (inicial == LETRA_G_SEC)) {
					heap_insertar(heap,nuevo_gym);
					(cant_agregada)++;
				}
				else if((leidos > 0) && (inicial != LETRA_E_SEC)) leidos = ERROR;
			}
			else if(inicial == LETRA_E_SEC) {
				nuevo_gym->entrenador = crear_entrenador();
				leidos = leer_entrenador(gimnasio, nuevo_gym);
				i = 0;
				leidos = leer_inicial(gimnasio, &inicial);
				if(inicial != LETRA_P_SEC) {
					liberar_entrenador(nuevo_gym);
					leidos = ERROR_AUX;
				}
			}
			else leidos = ERROR_AUX;
		}
		if(leidos == ERROR_AUX) {
			liberar_gimnasio_aux(nuevo_gym);
		}
		else {
			heap_insertar(heap,nuevo_gym);
			(cant_agregada)++;
		}
		if(cant_agregada > VACIO) resultado = ARCH_ACEPTADO_AUX;
	}
	fclose(gimnasio);
	return resultado;
}

/*
Pre: -
Post: Libera la memoria reservada para todo un personaje principal.
*/

void liberar_personaje(personaje_t* personaje_principal) {
	if(personaje_principal) {
		if(personaje_principal->lista_pokemones_para_combatir) {
			for(int j = 0 ; j < personaje_principal->lista_pokemones_obtenidos->cantidad ; j++) {
				free(lista_elemento_en_posicion(personaje_principal->lista_pokemones_obtenidos,j));
			}
			lista_destruir(personaje_principal->lista_pokemones_obtenidos);
		}
		if(personaje_principal->lista_pokemones_para_combatir) {
			lista_destruir(personaje_principal->lista_pokemones_para_combatir);
		}
		free(personaje_principal);
	}
}

/*
Pre: Recibe un archivo de texto
Post: Lee la informacion del archivo de texto recibido por parametro y carga el personaje principal completo (con toda su informacion)
*/

personaje_t* cargar_personaje_principal(char arch_personaje[MAX_RUTA]) {
	FILE* personaje_principal = fopen(arch_personaje, "r");

	if(!personaje_principal) {
		printf("El archivo no existe!\n");
		return NULL;
	}
	personaje_t* nuevo_personaje = NULL;
	char inicial = LETRA;
	int j = 0;
	int i = 0;
	int leidos = leer_inicial(personaje_principal,&inicial);
	if(inicial == LETRA_E_SEC) {
		nuevo_personaje = crear_personaje();
		while(leidos > 0) {
			if(inicial == LETRA_E_SEC) {
				leidos = leer_personaje_principal(personaje_principal,nuevo_personaje);
			}
			else if(inicial == LETRA_P_SEC) {
				nuevo_personaje->pokemon = crear_pokemon();
				leidos = leer_pkm_personaje_principal(personaje_principal,nuevo_personaje);
				if(i < MAX_PKM_PARA_BATALLA) {
					lista_insertar_en_posicion(nuevo_personaje->lista_pokemones_para_combatir, nuevo_personaje->pokemon, i);
				}
				lista_insertar_en_posicion(nuevo_personaje->lista_pokemones_obtenidos, nuevo_personaje->pokemon, i);
				i++;
			}
			leidos = leer_inicial(personaje_principal,&inicial);
			if((leidos > 0) && (inicial != LETRA_P_SEC)) {
				liberar_personaje(nuevo_personaje);
				fclose(personaje_principal);
				return NULL;
			}
		}
		if(inicial != LETRA_P_SEC) {
			liberar_personaje(nuevo_personaje);
			fclose(personaje_principal);
			return NULL;
		}
	}
	fclose(personaje_principal);
	return nuevo_personaje;
}

/*
Pre: -
Post: Libera la memoria reservada para todo un lider del gimnasio.
*/

void liberar_lider(lider_t* lider_actual) {
	if(lider_actual) {
		if(lider_actual->lista_pokemones_obtenidos) {
			for(int j = 0 ; j < lider_actual->lista_pokemones_obtenidos->cantidad ; j++) {
				free(lista_elemento_en_posicion(lider_actual->lista_pokemones_obtenidos,j));
			}
			lista_destruir(lider_actual->lista_pokemones_obtenidos);
		}
		if(lider_actual->lista_pokemones_para_combatir) {
			lista_destruir(lider_actual->lista_pokemones_para_combatir);
		}
		free(lider_actual);
	}
}

/*
Pre: -
Post: Libera la memoria reservada para los entrenadores.
*/

void liberar_entrenadores(lista_t* pila_actual) { 
	if(pila_actual) {
		while(lista_elementos(pila_actual) > 0) {
			entrenador_t* entrenador_actual = (entrenador_t*)(lista_tope(pila_actual));
			if(entrenador_actual->lista_pokemones_obtenidos) {
				for(int j = 0 ; j < entrenador_actual->lista_pokemones_obtenidos->cantidad ; j++) {
					free(lista_elemento_en_posicion(entrenador_actual->lista_pokemones_obtenidos,j));
				}
				lista_destruir(entrenador_actual->lista_pokemones_obtenidos);
			}
			if(entrenador_actual->lista_pokemones_para_combatir) { 
				lista_destruir(entrenador_actual->lista_pokemones_para_combatir);
			}
			free(lista_tope(pila_actual));
			lista_desapilar(pila_actual);
		}
	lista_destruir(pila_actual);
	}
}

/*
Pre: -
Post: Muestra por pantalla como resulto la modificacion de los pokemones de batalla del personaje principal
*/

void imprimir_modificacion_batalla(personaje_t* personaje) {
	printf(FONDO_AMARILLO NEGRO "------------ MODIFICACION POKEMONES PARA BATALLA ------------" NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "-------------------------------------------------------------" NORMAL "\n");
	for(int i = 0; i < personaje->lista_pokemones_para_combatir->cantidad ; i++) {
		printf(FONDO_GRIS NEGRO "Pokemones de batalla: Posicion % i: %-26s" NORMAL "\n", i, (char*)(lista_elemento_en_posicion(personaje->lista_pokemones_para_combatir, i)));
	}
	printf(FONDO_AMARILLO NEGRO "-------------------------------------------------------------" NORMAL "\n");
	for(int j = 0; j < personaje->lista_pokemones_obtenidos->cantidad ; j++) {
		printf(FONDO_GRIS NEGRO "Pokemones obtenidos: Posicion % i: %-27s" NORMAL "\n", j,(char*)(lista_elemento_en_posicion(personaje->lista_pokemones_obtenidos, j)));
	}
	printf(FONDO_AMARILLO NEGRO "-------------------------------------------------------------" NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "-------------------------------------------------------------" NORMAL "\n");
	printf("\n");
}

/*
Pre: -
Post: Devuelve true si el pokemon seleccionado ya se encuentra en la lista de pokemones de batalla del personaje principal o false si no lo esta.
*/

bool esta_repetido(personaje_t* personaje, int* posicion) {
	bool repetido = false;
	for(int i = 0 ; i < personaje->lista_pokemones_para_combatir->cantidad ; i++) {
		if(lista_elemento_en_posicion(personaje->lista_pokemones_para_combatir, i) == lista_elemento_en_posicion(personaje->lista_pokemones_obtenidos, *posicion)) {
			repetido = true;
		}
	}
	return repetido;
}

/*
Pre: Recibe un entrenador, un lider y un booleano. Sera true si se derrotaron a todos los entrenadores o false si no. 
Post: Determina la lista de pokemones a utilizar para la batalla.
*/

lista_t* determinar_lista(bool* entrenadores_derrotados, entrenador_t* entrenador, lider_t* lider) {
	if(*(entrenadores_derrotados) == false) {
		return entrenador->lista_pokemones_para_combatir;
	}
	return lider->lista_pokemones_para_combatir;
}

/*
Pre: -
Post: Juega el turno con diferentes tipos de batallas segun el id_puntero_funcion del gimnasio actual
*/

int jugar_turno(heap_t* heap_gimnasio,personaje_t* personaje,int* turno_pkm_personaje,int* turno_pkm_entrenador,entrenador_t* entrenador,lider_t* lider, bool* entrenadores_derrotados) {
	lista_t* lista_a_utilizar = determinar_lista(entrenadores_derrotados, entrenador, lider);
	if(((gimnasio_t*)(heap_gimnasio->vector[0]))->id_puntero_funcion == BATALLA_1) {
		((gimnasio_t*)(heap_gimnasio->vector[0]))->batalla = (funcion_batalla)funcion_batalla_1((int*)((((pokemon_t*)(lista_elemento_en_posicion(personaje->lista_pokemones_para_combatir, *turno_pkm_personaje)))->velocidad)),(int*)((((pokemon_t*)(lista_elemento_en_posicion(lista_a_utilizar, *turno_pkm_entrenador)))->velocidad)));
		}
	else if(((gimnasio_t*)(heap_gimnasio->vector[0]))->id_puntero_funcion == BATALLA_2) {
		((gimnasio_t*)(heap_gimnasio->vector[0]))->batalla = (funcion_batalla)funcion_batalla_2((int*)((((pokemon_t*)(lista_elemento_en_posicion(personaje->lista_pokemones_para_combatir, *turno_pkm_personaje)))->defensa)),(int*)((((pokemon_t*)(lista_elemento_en_posicion(lista_a_utilizar, *turno_pkm_entrenador)))->defensa)));
	}
	else if(((gimnasio_t*)(heap_gimnasio->vector[0]))->id_puntero_funcion == BATALLA_3) {
		((gimnasio_t*)(heap_gimnasio->vector[0]))->batalla = (funcion_batalla)funcion_batalla_3((char*)((((pokemon_t*)(lista_elemento_en_posicion(personaje->lista_pokemones_para_combatir, *turno_pkm_personaje)))->nombre)),(char*)((((pokemon_t*)(lista_elemento_en_posicion(lista_a_utilizar, *turno_pkm_entrenador)))->nombre)));
	}
	else if(((gimnasio_t*)(heap_gimnasio->vector[0]))->id_puntero_funcion == BATALLA_4) {
		((gimnasio_t*)(heap_gimnasio->vector[0]))->batalla = (funcion_batalla)funcion_batalla_4((char*)((((pokemon_t*)(lista_elemento_en_posicion(personaje->lista_pokemones_para_combatir, *turno_pkm_personaje)))->nombre)),(char*)((((pokemon_t*)(lista_elemento_en_posicion(lista_a_utilizar, *turno_pkm_entrenador)))->nombre)));
	}
	else {
		((gimnasio_t*)(heap_gimnasio->vector[0]))->batalla = (funcion_batalla)funcion_batalla_5((int*)((((pokemon_t*)(lista_elemento_en_posicion(personaje->lista_pokemones_para_combatir, *turno_pkm_personaje)))->ataque)),(int*)((((pokemon_t*)(lista_elemento_en_posicion(lista_a_utilizar, *turno_pkm_entrenador)))->ataque)));
	}
	return ((int)((gimnasio_t*)(heap_gimnasio->vector[0]))->batalla);
}

/*
Pre: -
Post: Muestra por pantalla el estado de batalla actual
*/

void info_batalla(heap_t* heap_gimnasio,personaje_t* personaje,int* turno_pkm_personaje,int* turno_pkm_entrenador,int* resultado,int* opcion_elegida,entrenador_t* entrenador_actual,lider_t* lider_actual,bool simulacion) {
	char* pokemon_uno = (char*)lista_elemento_en_posicion(personaje->lista_pokemones_para_combatir, *turno_pkm_personaje);
	char* pokemon_dos;
	if(!entrenador_actual) {
		pokemon_dos = (char*)lista_elemento_en_posicion(lider_actual->lista_pokemones_para_combatir, *turno_pkm_entrenador);
	}
	else {
		pokemon_dos = (char*)lista_elemento_en_posicion(entrenador_actual->lista_pokemones_para_combatir,*turno_pkm_entrenador);
	}

	printf(FONDO_AMARILLO NEGRO"=======================================================================" NORMAL "\n");
	printf(FONDO_MAGENTA NEGRO"===========================POKEBALL====================================" NORMAL "\n");
	printf(FONDO_MAGENTA NEGRO"GIMNASIO ACTUAL: %-48s      " NORMAL "\n",((gimnasio_t*)heap_gimnasio->vector[0])->nombre);
	printf(FONDO_MAGENTA NEGRO"DIFICULTAD ACTUAL:%i                                                   " NORMAL "\n" , ((gimnasio_t*)(heap_gimnasio->vector[0]))->dificultad);
	printf(FONDO_AMARILLO NEGRO"=======================================================================" NORMAL "\n");
	printf("%s VS %-55s\n" ,pokemon_uno,pokemon_dos);
	printf(FONDO_AMARILLO NEGRO"=======================================================================" NORMAL "\n");

	char letra = LETRA_N_SEC;
	if(*resultado == TURNO_GANADO) {
		printf(FONDO_CYAN NEGRO "POKEMON GANADOR: %-49s     " NORMAL "\n",pokemon_uno);
		if(simulacion == false) {
			printf(FONDO_CYAN NEGRO "Ganaste el turno! Para ir al proximo, presione la tecla(N):           " NORMAL "\n");
			scanf(" %c", &letra);
		}
		if(letra == LETRA_N_SEC) {
			*opcion_elegida = SIGUIENTE_TURNO;
		}
		else {
			*opcion_elegida = FIN;
		}
	}
	else if(*resultado == TURNO_PERDIDO) {
		printf(FONDO_CYAN NEGRO "POKEMON GANADOR: %-49s     " NORMAL "\n",pokemon_dos);		
		if(simulacion == false) {
			printf(FONDO_CYAN NEGRO "Fuiste derrotado :(. Pelea mas fuerte con tu proximo pokemon!        " NORMAL "\n");
			printf(FONDO_CYAN NEGRO "Para ir al proximo turno, presione la tecla (N):                     " NORMAL "\n");
			scanf(" %c", &letra);
		}
		if(letra == LETRA_N_SEC) {
			*opcion_elegida = SIGUIENTE_TURNO;
		}
		else {
			*opcion_elegida = FIN;
		}
	}
}

/*
Pre: Recibe un pokemon 
Post: Mejora las habilidades del pokemon sumandole 1 punto extra.
Las habilidades se podran mejorar siempre y cuando no hayan superado el maximo 63 puntos agregados. Estos se suman de a uno siempre que el pokemon actual del personaje principal gana una batalla. 
*/

void mejorar_pokemon(pokemon_t* pokemon) {
	if(pokemon->puntos_extra < MAX_MEJORA) {
		(pokemon->velocidad)++;
		(pokemon->defensa)++;
		(pokemon->ataque)++;
		(pokemon->puntos_extra)++;
	}
}

/*
Pre: Recibe un heap de gimnasios
Post: Muestra por pantalla la informacion del lider del gimnasio actual
*/

void mostrar_info_lider(heap_t* heap_gimnasio) {
	printf(FONDO_GRIS NEGRO "Lider: %-38s" NORMAL "\n", ((gimnasio_t*)heap_gimnasio->vector[0])->lider->nombre);
	int k = 0;
	while ((k < MAX_PKM_PARA_BATALLA) && (k < ((gimnasio_t*)heap_gimnasio->vector[0])->lider->lista_pokemones_obtenidos->cantidad)) {
		printf(FONDO_GRIS NEGRO "Pokemon de batalla:%-26s" NORMAL "\n", (char*)(lista_elemento_en_posicion(((gimnasio_t*)heap_gimnasio->vector[0])->lider->lista_pokemones_para_combatir, k)));
			k++;
		}
		k = 0;
	while (k < ((gimnasio_t*)heap_gimnasio->vector[0])->lider->lista_pokemones_obtenidos->cantidad) {
		printf(FONDO_GRIS NEGRO "Pokemon obtenido:%-28s" NORMAL "\n", (char*)(lista_elemento_en_posicion(((gimnasio_t*)heap_gimnasio->vector[0])->lider->lista_pokemones_obtenidos, k)));
		k++;
	}
}

/*
Pre: Recibe un heap de gimnasios
Post: Muestra por pantalla la informacion del gimnasio actual
*/

void mostrar_info_gym(heap_t* heap_gimnasio) {
	printf(FONDO_AMARILLO NEGRO "------------ DATOS GIMNASIO ACTUAL ----------" NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "---------------------------------------------" NORMAL "\n");
	printf(FONDO_GRIS NEGRO "Nombre: %-37s" NORMAL "\n", ((gimnasio_t*)heap_gimnasio->vector[0])->nombre);
	printf(FONDO_GRIS NEGRO "Nivel de dificultad: %-24i" NORMAL "\n", ((gimnasio_t*)heap_gimnasio->vector[0])->dificultad);
}

/*
Pre: Recibe un heap de gimnasios
Post: Muestra por pantalla la informacion de los entrenadores del gimnasio actual
*/

void mostrar_info_entrenadores(heap_t* heap_gimnasio) {
	printf(FONDO_GRIS NEGRO "Entrenadores:                                " NORMAL "\n");
	for(int i = 0; i < ((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores->cantidad ; i++) {
		entrenador_t* entrenador = lista_elemento_en_posicion(((gimnasio_t*)heap_gimnasio->vector[0])->pila_entrenadores, i);
		printf(FONDO_GRIS NEGRO "->%-36s       " NORMAL "\n", (char*)entrenador);
		int j = 0;
		while ((j < MAX_PKM_PARA_BATALLA) && (j < entrenador->lista_pokemones_obtenidos->cantidad)) {
			printf(FONDO_GRIS NEGRO "Pokemon de batalla:%-26s" NORMAL "\n", (char*)(lista_elemento_en_posicion(entrenador->lista_pokemones_para_combatir, j)));
			j++;
		}
		j = 0;
		while (j < entrenador->lista_pokemones_obtenidos->cantidad) {
			printf(FONDO_GRIS NEGRO "Pokemon obtenido:%-28s" NORMAL "\n", (char*)(lista_elemento_en_posicion(entrenador->lista_pokemones_obtenidos, j)));
			j++;
		}
	}
	printf(FONDO_AMARILLO NEGRO "---------------------------------------------" NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "---------------------------------------------" NORMAL "\n");
	printf("\n");
}

/*
Pre: -
Post: devuelve true si esta dentro de las posiciones aceptadas dependiendo del menu o false si no lo esta
*/

void verificar_posicion_uno(personaje_t* personaje, int* posicion_uno) {
	while((*posicion_uno < VACIO) || (*posicion_uno > personaje->lista_pokemones_obtenidos->cantidad) || (esta_repetido(personaje, posicion_uno))) {
		if(!(esta_repetido(personaje, posicion_uno))) { 
			printf("Posicion invalida. Reingrese la posicion del pokemon (de la lista de pokemones obtenidos) que desea para la batalla:\n");
		}
		else {
			printf("¡Ya tienes a ese pokemon en los pokemones de batalla!.Reingrese la posicion del pokemon (de la lista de pokemones obtenidos) que desea para la batalla:\n");
		}
		scanf("%i", posicion_uno);		
	}
}

/*
Pre: -
Post: devuelve true si esta dentro de las posiciones aceptadas dependiendo del menu o false si no lo esta
*/

void verificar_posicion_dos(personaje_t* personaje, int* posicion_dos) {
	while((*posicion_dos < VACIO) || (*posicion_dos > personaje->lista_pokemones_para_combatir->cantidad)) {
		printf("Posicion invalida. Reingrese la posicion del pokemon (de la lista de pokemones de batalla) que desea sacar de la batalla:\n");
		scanf("%i", posicion_dos);		
	}
}

// -----------------------------------------------------------------------------------
// -----------------------------FUNCIONES PUBLICAS------------------------------------
// -----------------------------------------------------------------------------------


int comparador_gimnasios(void* gym_1, void* gym_2) {
	if(((gimnasio_t*)(gym_1))->dificultad < ((gimnasio_t*)(gym_2))->dificultad) {
		return -1;
	}
	else if(((gimnasio_t*)(gym_1))->dificultad > ((gimnasio_t*)(gym_2))->dificultad) {
		return 1;
	}
	return 0;
}

int agregar_arch_gimnasio(heap_t* heap) {
	char arch_gym[100] = ARCH_GYM;
	printf("Introduzca el nombre del nuevo archivo de gimnasios que desea incluir (Aclaracion: debe ser en formato .txt): \n");
	scanf(" %s", arch_gym);
	size_t n = strlen(arch_gym);
	while(strcmp (&(arch_gym[n-4]), ".txt") != 0) {
		printf("Por favor, introduzca un nombre valido. (debe ser formato .txt): \n");
		scanf(" %s", arch_gym);
		n = strlen(arch_gym);
	}
	if(cargar_gimnasio(arch_gym, heap) == ARCH_ACEPTADO_AUX) return ARCH_ACEPTADO_AUX;
	return ARCH_NO_ACEPTADO_AUX;
}

void mostrar_gimnasio(heap_t* heap_gimnasio) { 
	mostrar_info_gym(heap_gimnasio);
	mostrar_info_lider(heap_gimnasio);
	mostrar_info_entrenadores(heap_gimnasio);
}

personaje_t* agregar_arch_personaje_principal() {
	char arch_personaje[100] = ARCH_PERSONAJE;
	printf("Introduzca el nombre del nuevo archivo del personaje principal que desea (Aclaracion: debe ser en formato .txt): \n");
	scanf(" %s", arch_personaje);
	size_t n = strlen(arch_personaje);
	while(strcmp (&(arch_personaje[n-4]), ".txt") != 0) {
		printf("Por favor, introduzca un nombre valido. (debe ser formato .txt): \n");
		scanf(" %s", arch_personaje);
		n = strlen(arch_personaje);
	}
	personaje_t* nuevo_personaje = cargar_personaje_principal(arch_personaje);
	return nuevo_personaje;
}

void mostrar_personaje_principal(personaje_t* personaje) {
	printf(FONDO_AMARILLO NEGRO "--------- DATOS PERSONAJE PRINCIPAL ---------" NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "---------------------------------------------" NORMAL "\n");
	printf(FONDO_GRIS NEGRO "Nombre: %-37s" NORMAL "\n", personaje->nombre);
	for(int i = 0; i < personaje->lista_pokemones_para_combatir->cantidad ; i++) {
		printf(FONDO_GRIS NEGRO "Pokemones de batalla: %-23s" NORMAL "\n", (char*)(lista_elemento_en_posicion(personaje->lista_pokemones_para_combatir, i)));
	}
	for(int j = 0; j < personaje->lista_pokemones_obtenidos->cantidad ; j++) {
		printf(FONDO_GRIS NEGRO "Pokemones obtenidos: %-24s" NORMAL "\n", (char*)(lista_elemento_en_posicion(personaje->lista_pokemones_obtenidos, j)));
	}
	printf(FONDO_AMARILLO NEGRO "---------------------------------------------" NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "---------------------------------------------" NORMAL "\n");
	printf("\n");
}

void cambiar_pokemon_para_batalla(personaje_t* personaje) {
	int posicion_uno = 0;
	int posicion_dos = 0;
	if(personaje->lista_pokemones_obtenidos->cantidad > CANT_MINIMA) { 
		imprimir_modificacion_batalla(personaje);
		printf("--->Ingrese la posicion del pokemon (de la lista de pokemones obtenidos) que desea para la batalla:\n");
		scanf("%i", &posicion_uno);
		verificar_posicion_uno(personaje, &posicion_uno);
		printf("--->Ingrese la posicion del pokemon (de la lista de pokemones de batalla) que desea sacar de la batalla:\n");
		scanf("%i", &posicion_dos);
		verificar_posicion_dos(personaje, &posicion_dos);
		lista_insertar_en_posicion(personaje->lista_pokemones_para_combatir, lista_elemento_en_posicion(personaje->lista_pokemones_obtenidos, posicion_uno), posicion_dos);
		lista_borrar_de_posicion(personaje->lista_pokemones_para_combatir, posicion_dos+1);
		imprimir_modificacion_batalla(personaje);
	}
	else printf(FONDO_NEGRO "AVISO: No tienes los suficientes pokemones para poder intercambiarlos..." NORMAL "\n");
}

int comenzar_batalla(heap_t* heap_gimnasio, personaje_t* personaje, bool simulacion, int* opcion_elegida) {
	bool derrota = false;
	bool entrenadores_derrotados = false;
	int resultado = VACIO;
	*opcion_elegida = SIGUIENTE_TURNO;
	int turno_pkm_personaje = VACIO;
	int turno_pkm_entrenador = VACIO;
	entrenador_t* entrenador_actual = lista_tope(((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores);
	lider_t* lider_actual = ((gimnasio_t*)(heap_gimnasio->vector[0]))->lider;

	while((derrota == false) && (heap_gimnasio->tope > 0) && (*opcion_elegida == SIGUIENTE_TURNO)){
		resultado = jugar_turno(heap_gimnasio,personaje,&turno_pkm_personaje,&turno_pkm_entrenador,entrenador_actual,lider_actual,&entrenadores_derrotados);
		info_batalla(heap_gimnasio,personaje,&turno_pkm_personaje,&turno_pkm_entrenador,&resultado,opcion_elegida,entrenador_actual,lider_actual,simulacion);
		if(resultado == TURNO_PERDIDO) {
			(turno_pkm_personaje)++;
			if((*opcion_elegida == FIN)||(turno_pkm_personaje >= personaje->lista_pokemones_para_combatir->cantidad)) derrota = true;
		}
		else {
			mejorar_pokemon(lista_elemento_en_posicion(personaje->lista_pokemones_para_combatir,turno_pkm_personaje));
			(turno_pkm_entrenador)++;
		}
		if((entrenadores_derrotados) && (lista_elementos(lider_actual->lista_pokemones_para_combatir) == turno_pkm_entrenador)){
			derrota = true;
		}
		if((!entrenadores_derrotados) && ((turno_pkm_entrenador==entrenador_actual->lista_pokemones_para_combatir->cantidad))){
			for(int j = 0 ; j < entrenador_actual->lista_pokemones_obtenidos->cantidad ; j++) {
				free(lista_elemento_en_posicion(entrenador_actual->lista_pokemones_obtenidos,j));
			}
			lista_destruir(entrenador_actual->lista_pokemones_obtenidos);
			lista_destruir(entrenador_actual->lista_pokemones_para_combatir);
			free(lista_tope(((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores));
			lista_desapilar(((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores);
			entrenador_actual = (entrenador_t*)lista_tope(((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores);
			turno_pkm_entrenador = VACIO;
		}
		if((((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores->cantidad == VACIO) && (!entrenadores_derrotados)) {
			entrenadores_derrotados = true;
			turno_pkm_entrenador = VACIO;
		}
	}
	return resultado;
}

void tomar_trofeo_prestado(heap_t* heap_gimnasio, personaje_t* personaje) {
	lider_t* lider_actual = ((gimnasio_t*)heap_gimnasio->vector[0])->lider;
	int posicion;
	printf(FONDO_AMARILLO NEGRO "-------------- LIDER DEL GIMNASIO --------------" NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "------------------------------------------------" NORMAL "\n");
	printf(FONDO_GRIS NEGRO "Nombre: %-40s" NORMAL "\n", lider_actual->nombre);
	for(int i = 0; i < lider_actual->lista_pokemones_para_combatir->cantidad ; i++) {
		printf(FONDO_GRIS NEGRO "Pokemones de batalla: %i) %-23s" NORMAL "\n", i, (char*)(lista_elemento_en_posicion(lider_actual->lista_pokemones_para_combatir, i)));
	}
	printf("Seleccione el numero del pokemon de batalla que quiere llevarse prestado como premio por ganar el gimnasio de %s!\n", lider_actual->nombre);
	scanf("%i", &posicion);
	while(posicion > lider_actual->lista_pokemones_para_combatir->cantidad) {
		printf("La posicion ingresada no es valida. Vuelva a ingresar otra:\n");
		scanf("%i", &posicion);
	}
	lista_insertar(personaje->lista_pokemones_obtenidos,lista_elemento_en_posicion(lider_actual->lista_pokemones_para_combatir, posicion));
	lista_borrar_de_posicion(lider_actual->lista_pokemones_para_combatir, posicion);
	lista_borrar_de_posicion(lider_actual->lista_pokemones_obtenidos, posicion);
}

void liberar_gimnasio(heap_t* heap_gimnasio) {
	if(heap_gimnasio) {
		if(((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores) {
			while(lista_elementos(((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores) > 0) {
				entrenador_t* entrenador_actual = (entrenador_t*)(lista_tope(((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores));
				if(entrenador_actual->lista_pokemones_obtenidos) {
					for(int j = 0 ; j < entrenador_actual->lista_pokemones_obtenidos->cantidad ; j++) {
						free(lista_elemento_en_posicion(entrenador_actual->lista_pokemones_obtenidos,j));
					}
					lista_destruir(entrenador_actual->lista_pokemones_obtenidos);
				}
				if(entrenador_actual->lista_pokemones_para_combatir) {
					lista_destruir(entrenador_actual->lista_pokemones_para_combatir); 
				}
				free(lista_tope(((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores));
				lista_desapilar(((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores);
			}
			lista_destruir(((gimnasio_t*)(heap_gimnasio->vector[0]))->pila_entrenadores);
		}
		lider_t* lider_actual = ((gimnasio_t*)(heap_gimnasio->vector[0]))->lider;
		liberar_lider(lider_actual);
	}
}

void liberar_todo(heap_t* heap_gimnasio, personaje_t* personaje_principal) {
	if(heap_gimnasio) {
		for(int i = 0 ; i < heap_gimnasio->tope ; i++) {
			lista_t* pila_actual = ((gimnasio_t*)(heap_gimnasio->vector[i]))->pila_entrenadores;
			liberar_entrenadores(pila_actual);
			lider_t* lider_actual = ((gimnasio_t*)(heap_gimnasio->vector[i]))->lider;
			liberar_lider(lider_actual);
		}
	}
	liberar_personaje(personaje_principal);
}
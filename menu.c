#include "menu.h"
#include "gimnasio.h"
#include <stdio.h>
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
#define MIN_GIMNASIOS 1
#define TURNO_GANADO 1
#define VACIO 0
#define GIMNASIO_GANADO 1
#define GIMNASIO_NO_GANADO -1
#define NO_SIGUE_PARTIDA -1
#define SIGUE_PARTIDA 1
const int MENU_INICIO = 1;
const int MENU_GIMNASIO = 2;
const int MENU_VICTORIA = 3;
const int MENU_DERROTA = 4;
const char LETRA_E = 'E';
const char LETRA_A = 'A';
const char LETRA_I = 'I';
const char LETRA_S = 'S';
const char LETRA_P = 'P';
const char LETRA_L = 'L';
const char LETRA_G = 'G';
const char LETRA_C = 'C';
const char LETRA_B = 'B';
const char LETRA_T = 'T';
const char LETRA_N = 'N';
const char LETRA_R = 'R';
const char LETRA_F = 'F';
const char LETRA_SALIDA = 'Q';

// -----------------------------------------------------------------------------------
// -----------------------------FUNCIONES PRIVADAS------------------------------------
// -----------------------------------------------------------------------------------

/*
Pre: -
Post: devuelve true si esta dentro de las letras aceptadas dependiendo del menu o false si no lo esta
*/

bool no_esta_en_letras_aceptadas (char letra, int menu_elegido) {
	if(menu_elegido == MENU_INICIO) {
		return ((letra != LETRA_E) && (letra != LETRA_A) && (letra != LETRA_I) && (letra != LETRA_S) && (letra != LETRA_SALIDA));
	}
	else if(menu_elegido == MENU_GIMNASIO) {
		return ((letra != LETRA_E) && (letra != LETRA_G) && (letra != LETRA_C) && (letra != LETRA_B));
	}
	else if(menu_elegido == MENU_VICTORIA) {
		return ((letra != LETRA_T) && (letra != LETRA_C) && (letra != LETRA_N));
	}
	else if(menu_elegido == MENU_DERROTA) {
		return ((letra != LETRA_C) && (letra != LETRA_R) && (letra != LETRA_F));
	}
}

/*
Pre: -
Post: Muestra por pantalla el menu requerido
*/

void preguntar_letra(char* letra, int menu_elegido) { 
	if(menu_elegido == MENU_INICIO) {                    
		printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
		printf(FONDO_GRIS NEGRO "                  MENU DE INICIO                    " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "¡Bienvenido a la simulacion del videojuego PokeBall!" NORMAL "\n");
		printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		printf(FONDO_AMARILLO NEGRO "E: Ingresar archivo del entrenador principal        " NORMAL "\n");
		printf(FONDO_MAGENTA NEGRO "A: Agregar un gimnasio al arbol de gimnasios        " NORMAL "\n");
		printf(FONDO_VERDE NEGRO "I: Comenzar la partida                              " NORMAL "\n");
		printf(FONDO_CYAN NEGRO "S: Simular partida                                  " NORMAL "\n");
		printf(FONDO_ROJO NEGRO "Q: Salir                                            " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		scanf(" %c", letra);
		while (no_esta_en_letras_aceptadas(*letra, menu_elegido) == true) {
			printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
			printf(FONDO_GRIS NEGRO "                  MENU DE INICIO                    " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "         La letra seleccionada no es valida         " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			printf(FONDO_AMARILLO NEGRO "E: Ingresar archivo del entrenador principal        " NORMAL "\n");
			printf(FONDO_MAGENTA NEGRO "A: Agregar un gimnasio al arbol de gimnasios        " NORMAL "\n");
			printf(FONDO_VERDE NEGRO "I: Comenzar la partida                              " NORMAL "\n");
			printf(FONDO_CYAN NEGRO "S: Simular partida                                  " NORMAL "\n");
			printf(FONDO_ROJO NEGRO "Q: Salir                                            " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			scanf(" %c", letra);
		}
	}
	else if(menu_elegido == MENU_GIMNASIO) {
		printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
		printf(FONDO_GRIS NEGRO "                  MENU DE GIMNASIO                  " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		printf(FONDO_AMARILLO NEGRO "E: Mostrar info del entrenador principal            " NORMAL "\n");
		printf(FONDO_MAGENTA NEGRO "G: Mostrar info del gimnasio actual                 " NORMAL "\n");
		printf(FONDO_VERDE NEGRO "C: Cambiar pokemon de batalla                       " NORMAL "\n");
		printf(FONDO_CYAN NEGRO "B: Proxima partida                                  " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		scanf(" %c", letra);
		while (no_esta_en_letras_aceptadas(*letra, menu_elegido) == true) {
			printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
			printf(FONDO_GRIS NEGRO "                  MENU DE GIMNASIO                  " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "         La letra seleccionada no es valida         " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			printf(FONDO_AMARILLO NEGRO "E: Mostrar info del entrenador principal            " NORMAL "\n");
			printf(FONDO_MAGENTA NEGRO "G: Mostrar info del gimnasio actual                 " NORMAL "\n");
			printf(FONDO_VERDE NEGRO "C: Cambiar pokemon de batalla                       " NORMAL "\n");
			printf(FONDO_CYAN NEGRO "B: Proxima partida                                  " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			scanf(" %c", letra);
		}
	}
	else if(menu_elegido == MENU_VICTORIA) {
		printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
		printf(FONDO_GRIS NEGRO "                  MENU DE VICTORIA                  " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		printf(FONDO_AMARILLO NEGRO "T: Tomar prestado un pokemon del lider del gimnasio " NORMAL "\n");
		printf(FONDO_MAGENTA NEGRO "C: Cambiar pokemones de batalla                     " NORMAL "\n");
		printf(FONDO_VERDE NEGRO "N: Proximo gimnasio                                 " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		scanf(" %c", letra);
		while (no_esta_en_letras_aceptadas(*letra, menu_elegido) == true) {
			printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
			printf(FONDO_GRIS NEGRO "                  MENU DE VICTORIA                  " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "         La letra seleccionada no es valida         " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			printf(FONDO_AMARILLO NEGRO "T: Tomar prestado un pokemon del lider del gimnasio " NORMAL "\n");
			printf(FONDO_MAGENTA NEGRO "C: Cambiar pokemones de batalla                     " NORMAL "\n");
			printf(FONDO_VERDE NEGRO "N: Proximo gimnasio                                 " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			scanf(" %c", letra);
		}
	}
	else if(menu_elegido == MENU_DERROTA) {
		printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
		printf(FONDO_GRIS NEGRO "                  MENU DE DERROTA                   " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		printf(FONDO_AMARILLO NEGRO "C: Cambiar pokemones de batalla                     " NORMAL "\n");
		printf(FONDO_MAGENTA NEGRO "R: Repetir ultima batalla                           " NORMAL "\n");
		printf(FONDO_VERDE NEGRO "F: Finalizar partida                                " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		scanf(" %c", letra);
		while (no_esta_en_letras_aceptadas(*letra, menu_elegido) == true) {
			printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
			printf(FONDO_GRIS NEGRO "                  MENU DE DERROTA                   " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "         La letra seleccionada no es valida         " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			printf(FONDO_AMARILLO NEGRO "C: Cambiar pokemones de batalla                     " NORMAL "\n");
			printf(FONDO_MAGENTA NEGRO "R: Repetir ultima batalla                           " NORMAL "\n");
			printf(FONDO_VERDE NEGRO "F: Finalizar partida                                " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			scanf(" %c", letra);
		}
	}
}

/*
Pre: -
Post: Muestra por pantalla el menu requerido
*/

void preguntar_letra_aux(char* letra, int menu_elegido) {
	if(menu_elegido == MENU_INICIO) { 
		printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
		printf(FONDO_GRIS NEGRO "                  MENU DE INICIO                    " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "      ¿Desea seleccionar alguna otra opcion?        " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		printf(FONDO_AMARILLO NEGRO "E: Ingresar archivo del entrenador principal        " NORMAL "\n");
		printf(FONDO_MAGENTA NEGRO "A: Agregar un gimnasio al arbol de gimnasios        " NORMAL "\n");
		printf(FONDO_VERDE NEGRO "I: Comenzar la partida                              " NORMAL "\n");
		printf(FONDO_CYAN NEGRO "S: Simular partida                                  " NORMAL "\n");
		printf(FONDO_ROJO NEGRO "Q: Salir                                            " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		scanf(" %c", letra);
		while (no_esta_en_letras_aceptadas(*letra, MENU_INICIO) == true) {
			printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
			printf(FONDO_GRIS NEGRO "                  MENU DE INICIO                    " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "         La letra seleccionada no es valida         " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			printf(FONDO_AMARILLO NEGRO "E: Ingresar archivo del entrenador principal        " NORMAL "\n");
			printf(FONDO_MAGENTA NEGRO "A: Agregar un gimnasio al arbol de gimnasios        " NORMAL "\n");
			printf(FONDO_VERDE NEGRO "I: Comenzar la partida                              " NORMAL "\n");
			printf(FONDO_CYAN NEGRO "S: Simular partida                                  " NORMAL "\n");
			printf(FONDO_ROJO NEGRO "Q: Salir                                            " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			scanf(" %c", letra);
		}
	}
	else if(menu_elegido == MENU_GIMNASIO) {
		printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
		printf(FONDO_GRIS NEGRO "                  MENU DE GIMNASIO                  " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "      ¿Desea seleccionar alguna otra opcion?        " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		printf(FONDO_AMARILLO NEGRO "E: Mostrar info del entrenador principal            " NORMAL "\n");
		printf(FONDO_MAGENTA NEGRO "G: Mostrar info del gimnasio actual                 " NORMAL "\n");
		printf(FONDO_VERDE NEGRO "C: Cambiar pokemon de batalla                       " NORMAL "\n");
		printf(FONDO_CYAN NEGRO "B: Luchar batalla                                   " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		scanf(" %c", letra);
		while (no_esta_en_letras_aceptadas(*letra, MENU_GIMNASIO) == true) {
			printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
			printf(FONDO_GRIS NEGRO "                  MENU DE GIMNASIO                  " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "         La letra seleccionada no es valida         " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			printf(FONDO_AMARILLO NEGRO "E: Mostrar info del entrenador principal            " NORMAL "\n");
			printf(FONDO_MAGENTA NEGRO "G: Mostrar info del gimnasio actual                 " NORMAL "\n");
			printf(FONDO_VERDE NEGRO "C: Cambiar pokemon de batalla                       " NORMAL "\n");
			printf(FONDO_CYAN NEGRO "B: Luchar batalla                                   " NORMAL "\n");
			printf(FONDO_ROJO NEGRO "Q: Salir del menu gimnasio                          " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			scanf(" %c", letra);
		}
	}
		else if(menu_elegido == MENU_DERROTA) {
			printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
			printf(FONDO_GRIS NEGRO "                  MENU DE DERROTA                   " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "      ¿Desea seleccionar alguna otra opcion?        " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			printf(FONDO_AMARILLO NEGRO "C: Cambiar pokemones de batalla                     " NORMAL "\n");
			printf(FONDO_MAGENTA NEGRO "R: Repetir ultima batalla                           " NORMAL "\n");
			printf(FONDO_VERDE NEGRO "F: Finalizar partida                                " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			scanf(" %c", letra);
		while (no_esta_en_letras_aceptadas(*letra, menu_elegido) == true) {
			printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
			printf(FONDO_GRIS NEGRO "                  MENU DE DERROTA                   " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "         La letra seleccionada no es valida         " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			printf(FONDO_AMARILLO NEGRO "C: Cambiar pokemones de batalla                     " NORMAL "\n");
			printf(FONDO_MAGENTA NEGRO "R: Repetir ultima batalla                           " NORMAL "\n");
			printf(FONDO_VERDE NEGRO "F: Finalizar partida                                " NORMAL "\n");
			printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
			scanf(" %c", letra);
		}
	}
}

/*
Pre: -
Post: Muestra por pantalla el menu de victoria 
*/

void preguntar_letra_aux_victoria(char* letra, bool trofeo_prestado) {
	printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
	printf(FONDO_GRIS NEGRO "                  MENU DE VICTORIA                  " NORMAL "\n");
	printf(FONDO_GRIS NEGRO "      ¿Desea seleccionar alguna otra opcion?        " NORMAL "\n");
	printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
	if(trofeo_prestado != true) {
		printf(FONDO_AMARILLO NEGRO "T: Tomar prestado un pokemon del lider del gimnasio " NORMAL "\n");
		printf(FONDO_MAGENTA NEGRO "C: Cambiar pokemones de batalla                      " NORMAL "\n");
		printf(FONDO_VERDE NEGRO "N: Proximo gimnasio                                 " NORMAL "\n");
	}
	else {
		printf(FONDO_MAGENTA NEGRO "C: Cambiar pokemones de batalla                     " NORMAL "\n");
		printf(FONDO_VERDE NEGRO "N: Proximo gimnasio                                 " NORMAL "\n");			
	}
	printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
	scanf(" %c", letra);
	while (no_esta_en_letras_aceptadas(*letra, MENU_VICTORIA) == true) {
		printf(FONDO_GRIS NEGRO"====================================================" NORMAL "\n");
		printf(FONDO_GRIS NEGRO "                  MENU DE VICTORIA                  " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "         La letra seleccionada no es valida         " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "      Por favor, seleccione la opcion deseada:      " NORMAL "\n");
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		if(trofeo_prestado != true) {
			printf(FONDO_AMARILLO NEGRO "T: Tomar prestado un pokemon del lider del gimnasio " NORMAL "\n");
			printf(FONDO_MAGENTA NEGRO "C: Cambiar pokemones de batalla                      " NORMAL "\n");
			printf(FONDO_VERDE NEGRO "N: Proximo gimnasio                                 " NORMAL "\n");
		}
		else {
			printf(FONDO_MAGENTA NEGRO "C: Cambiar pokemones de batalla                     " NORMAL "\n");
			printf(FONDO_VERDE NEGRO "N: Proximo gimnasio                                 " NORMAL "\n");			
		}
		printf(FONDO_GRIS NEGRO "====================================================" NORMAL "\n");
		scanf(" %c", letra);
	}
}

/*
Pre: -
Post: Muestra por pantalla un aviso en caso de que el usuario gane el juego
*/

void imprimir_aviso_victoria() {
	printf(FONDO_GRIS NEGRO"===============================================================" NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "                   ¡GANASTE EL JUEGO!                          " NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "     ¡Tus pokemones tienen muy buenas habilidades!             " NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "  Pudiste vencer a todos los gimnasios cargados en el juego    " NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "               Ya eres un Maestro Pokemon                      " NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⣠⣤⣶⣶ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⢰⣿⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣀⣀⣾⣿⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⡏⠉⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⠀⠀⠀⠈⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠛⠉⠁⠀⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠙⠿⠿⠿⠻⠿⠿⠟⠿⠛⠉⠀⠀⠀⠀⠀⣸⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣴⣿⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⢰⣹⡆⠀⠀⠀⠀⠀⠀⣭⣷⠀⠀⠀⠸⣿⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠈⠉⠀⠀⠤⠄⠀⠀⠀⠉⠁⠀⠀⠀⠀⢿⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⢾⣿⣷⠀⠀⠀⠀⡠⠤⢄⠀⠀⠀⠠⣿⣿⣷⠀⢸⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⡀⠉⠀⠀⠀⠀⠀⢄⠀⢀⠀⠀⠀⠀⠉⠉⠁⠀⠀⣿⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿ "NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO"		⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿ "NORMAL "\n");
	printf(FONDO_GRIS NEGRO "===============================================================" NORMAL "\n");
}

/*
Pre: -
Post: Muestra por pantalla un aviso en caso de que el usuario pierda el juego
*/

void imprimir_aviso_derrota() {
	printf(FONDO_GRIS NEGRO"===============================================================" NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "                   PERDISTE EL JUEGO                           " NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "       ¡Debes traer a tus pokemones mas entrenados!            " NORMAL "\n");
	printf(FONDO_AMARILLO NEGRO "          Ya te convertiras en un Maestro Pokemon              " NORMAL "\n");
	printf(FONDO_GRIS NEGRO "===============================================================" NORMAL "\n");

}

// -----------------------------------------------------------------------------------
// -----------------------------FUNCIONES PUBLICAS------------------------------------
// -----------------------------------------------------------------------------------

void mostrar_menu_inicio() {
	char letra = LETRA_A;
	heap_t* nuevo_heap = heap_crear(comparador_gimnasios);
	personaje_t* nuevo_personaje = NULL;
	gimnasio_t* nuevo_gimnasio = NULL;
	preguntar_letra(&letra, MENU_INICIO);

	while(letra != LETRA_SALIDA) {
		if(letra == LETRA_E) {
			if(nuevo_personaje == NULL) {
				nuevo_personaje = agregar_arch_personaje_principal();
				if(nuevo_personaje != NULL) printf(FONDO_NEGRO "AVISO: Personaje principal cargado exitosamente :)" NORMAL "\n");
				else printf(FONDO_NEGRO "AVISO: Error al cargar el personaje principal :(" NORMAL "\n");
			}
			else printf(FONDO_NEGRO "Ya cargaste un personaje principal para esta partida..." NORMAL "\n");
		}
		else if(letra == LETRA_A) {
			nuevo_gimnasio = agregar_arch_gimnasio(nuevo_heap);
			if(nuevo_gimnasio != NULL) printf(FONDO_NEGRO "AVISO: Nuevo gimnasio cargado exitosamente :)" NORMAL "\n");
			else printf(FONDO_NEGRO "AVISO: Error al cargar el nuevo gimnasio :(" NORMAL "\n");
		}
		else if(letra == LETRA_I) {
			if ((nuevo_heap->tope >= MIN_GIMNASIOS) && (nuevo_personaje != NULL)) {
				mostrar_menu_gimnasio(nuevo_personaje,nuevo_heap);
				letra = LETRA_SALIDA;
			}
			else if(nuevo_heap->tope < MIN_GIMNASIOS) printf(FONDO_NEGRO "AVISO: No existen suficientes gimnasios cargados para iniciar una partida..." NORMAL "\n");
			else printf(FONDO_NEGRO "AVISO: No existe un personaje principal para iniciar una partida..." NORMAL "\n");
		}
		else if(letra == LETRA_S) {
			bool derrota = false;
			bool simulacion = true;
			int opcion_elegida = VACIO;
			if ((nuevo_heap->tope >= MIN_GIMNASIOS) && (nuevo_personaje != NULL)) {
				while((nuevo_heap->tope > VACIO) && (derrota == false)) {
					int resultado = comenzar_batalla(nuevo_heap,nuevo_personaje,simulacion,&opcion_elegida);
					if(resultado == GIMNASIO_GANADO) {
						liberar_gimnasio(nuevo_heap);
						if(nuevo_heap->vector[0]) free(nuevo_heap->vector[0]);
						heap_extraer_raiz(nuevo_heap);
					} 
					else if(resultado == GIMNASIO_NO_GANADO) {
						derrota = true;
					}
				}
				if((nuevo_heap->tope == VACIO) && (derrota == false)) {
					imprimir_aviso_victoria();
				}
				else {
					imprimir_aviso_derrota();
				}
				letra = LETRA_SALIDA;
			}
			else if(nuevo_heap->tope < MIN_GIMNASIOS) printf(FONDO_NEGRO "AVISO: No existen suficientes gimnasios cargados para simular una partida..." NORMAL "\n");
			else printf(FONDO_NEGRO "AVISO: No existe un personaje principal para simular una partida..." NORMAL "\n");
		}
		if(letra != LETRA_SALIDA) preguntar_letra_aux(&letra,MENU_INICIO);
	}
	liberar_todo(nuevo_heap, nuevo_personaje);
	heap_destruir(nuevo_heap);
}

void mostrar_menu_victoria(personaje_t* personaje, heap_t* heap_gimnasio) {
	char letra;
	preguntar_letra(&letra, MENU_VICTORIA);
	bool trofeo_prestado = false;
	while(letra != LETRA_N) {
		if(letra == LETRA_T) {
			tomar_trofeo_prestado(heap_gimnasio, personaje);
			trofeo_prestado = true;
		}
		else if(letra == LETRA_C) {
			cambiar_pokemon_para_batalla(personaje);
		}
		preguntar_letra_aux_victoria(&letra,trofeo_prestado);
	}
}

int menu_derrota(personaje_t* personaje) {
	char letra;
	preguntar_letra(&letra, MENU_DERROTA);
	while (letra == LETRA_C) {
		cambiar_pokemon_para_batalla(personaje);
		preguntar_letra_aux(&letra,MENU_DERROTA);
	}
	if(letra == LETRA_F) {
		imprimir_aviso_derrota();
		return NO_SIGUE_PARTIDA;
	}
	return SIGUE_PARTIDA;
}

void mostrar_menu_gimnasio(personaje_t* personaje,heap_t* heap_gimnasio) {
	char letra;
	preguntar_letra(&letra, MENU_GIMNASIO);
	bool derrota = false;
	int opcion_elegida = VACIO;
	while(letra != LETRA_B) {
		if(letra == LETRA_E) {
			mostrar_personaje_principal(personaje);
		}
		else if(letra == LETRA_G) {
			mostrar_gimnasio(heap_gimnasio);
		}
		else if(letra == LETRA_C) {
			cambiar_pokemon_para_batalla(personaje);
		}
		preguntar_letra_aux(&letra, MENU_GIMNASIO);
	}
	bool simulacion = false;
	while((heap_gimnasio->tope > VACIO) && (derrota == false)) {
		int resultado = comenzar_batalla(heap_gimnasio,personaje,simulacion, &opcion_elegida);
		if((opcion_elegida == NO_SIGUE_PARTIDA) && (resultado == GIMNASIO_GANADO)) {
			printf(FONDO_NEGRO "Seleccion de otra letra diferente a (N). Partida finalizada." NORMAL "\n");
			derrota = true;
		}
		else if(resultado == GIMNASIO_GANADO) {
			mostrar_menu_victoria(personaje, heap_gimnasio);
			liberar_gimnasio(heap_gimnasio);
			if(heap_gimnasio->vector[0]) free(heap_gimnasio->vector[0]);
			heap_extraer_raiz(heap_gimnasio);
		} 
		else if(resultado == GIMNASIO_NO_GANADO) {
			if(menu_derrota(personaje) == NO_SIGUE_PARTIDA) {
				derrota = true;
			} 
		}
	}
	if(derrota == false) imprimir_aviso_victoria();
}
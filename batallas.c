#include "batallas.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define GANADOR_UNO 1
#define GANADOR_DOS -1
#define NUMERO_ALTO 100
#define NUMERO_BAJO 20
#define PASO_PRUEBA 1
#define NO_PASO_PRUEBA -1
#define NUMERO_CLAVE 5

/*
 * Se deberan implementar las 5 funciones de batalla.
 * Las reglas para decidir al ganador las inventan ustedes
 * 
 * Si el ganador es el primer pokemon, se devolvera 1
 * Si el ganador es el segundo pokemon, se devolvera -1
 * 
 * No habran empates.
 */

// -----------------------------------------------------------------------------------
// -----------------------------FUNCIONES PRIVADAS------------------------------------
// -----------------------------------------------------------------------------------

/*
Pre: -
Post: Devuelve true si el numero que recibe la funcion es par o false si no lo es 
*/

bool es_par(int numero) {
	if ((numero/2) == 0) return true;
	return false;
}

/*
Pre: -
Post: Devuelve 1 si el resultado de la formula es mayor que NUMERO_BAJO o -1 si no.
*/

int formula_defensa(int numero_defensa) {
	if(((numero_defensa*NUMERO_CLAVE)/2) > NUMERO_BAJO) {
		return PASO_PRUEBA;
	}
	return NO_PASO_PRUEBA;
}

/*
Pre: -
Post: Devuelve 1 si el resultado de la formula es mayor que NUMERO_BAJO o -1 si no.
*/

bool es_letra_vocal(char letra) {
	return (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' || letra == 'u' || letra == 'A' || letra == 'E' || letra == 'I' || letra == 'O' || letra == 'U') ;
}
// -----------------------------------------------------------------------------------
// -----------------------------FUNCIONES PUBLICAS------------------------------------
// -----------------------------------------------------------------------------------

int funcion_batalla_1(void* velocidad_pkm_1, void* velocidad_pkm_2) {
	if(((int)velocidad_pkm_1) > ((int)velocidad_pkm_2)) {
		return GANADOR_UNO;
	}
	return GANADOR_DOS;
}

int funcion_batalla_2(void* defensa_pkm_1, void* defensa_pkm_2) {
	if(formula_defensa((int)defensa_pkm_1) == PASO_PRUEBA) {
		return GANADOR_UNO;
	}
	else if((formula_defensa((int)defensa_pkm_2)) == PASO_PRUEBA) {
		return GANADOR_DOS;
	}
	else {
		if((int)defensa_pkm_1 > (int)defensa_pkm_2) {
			return GANADOR_UNO;
		}
		else {
			return GANADOR_DOS;
		}
	}
}

int funcion_batalla_3(void* letras_pkm_1, void* letras_pkm_2) {
	size_t cant_letras_pkm_1 = strlen((char*)letras_pkm_1);
	size_t cant_letras_pkm_2 = strlen((char*)letras_pkm_2);
	int cant_vocales_pkm_1 = 0;
	int cant_vocales_pkm_2 = 0;
	for(int i = 0 ; i < cant_letras_pkm_1 ; i++) {
		if(es_letra_vocal(((char*)letras_pkm_1)[i]) == true) {
			(cant_vocales_pkm_1)++;
		}
	}
	for(int i = 0 ; i < cant_letras_pkm_2 ; i++) {
		if(es_letra_vocal(((char*)letras_pkm_2)[i]) == true) {
			(cant_vocales_pkm_2)++;
		}
	}
	if(cant_vocales_pkm_1 >= cant_vocales_pkm_2) {
		return GANADOR_UNO;
	}
	return GANADOR_DOS;
}

int funcion_batalla_4(void* letras_pkm_1, void* letras_pkm_2) {
	size_t cant_letras_pkm_1 = strlen((char*)letras_pkm_1);
	size_t cant_letras_pkm_2 = strlen((char*)letras_pkm_2);

	if(cant_letras_pkm_1 >= cant_letras_pkm_2) {
		return GANADOR_UNO;
	}
	return GANADOR_DOS;
}

int funcion_batalla_5(void* ataque_pkm_1, void* ataque_pkm_2) {
	if(((int)ataque_pkm_2 > NUMERO_ALTO) && (es_par((int)ataque_pkm_2) == true)) {
		return GANADOR_DOS;
	}
	return GANADOR_UNO;
}
#ifndef __MENU_H__
#define __MENU_H__
#include "gimnasio.h"

/*
Pre: -
Post: Muestra por pantalla el menu de inicio
*/

void mostrar_menu_inicio();

/*
Pre: -
Post: Muestra por pantalla el menu de gimnasio
*/

void mostrar_menu_gimnasio(personaje_t* personaje, heap_t* heap_gimnasio);

/*
Pre: -
Post: Muestra por pantalla el menu de victoria
*/

void mostrar_menu_victoria(personaje_t* personaje, heap_t* heap_gimnasio);

/*
Pre: -
Post: Muestra por pantalla el menu de derrota
*/

int menu_derrota(personaje_t* personaje);


#endif /* __MENU_H__ */
CC= gcc
WFLAGS= -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0

compilar:
	$(CC) batallas.c lista.c heap.c gimnasio.c menu.c main.c -o juego -g $(FLAGS) 

exe_juego: compilar 
	./juego

exe_valgrind: compilar
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./juego

compilar_pruebas_heap:
	$(CC) heap.c pruebas_heap.c -o pruebas_heap -g $(FLAGS) 

exe_pruebas_heap: compilar_pruebas_heap
	./pruebas_heap

exe_pruebas_heap_valgrind: compilar_pruebas_heap
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas_heap

compilar_gdb:
	$(CC) -g batallas.c lista.c heap.c gimnasio.c menu.c main.c  $(FLAGS) -o juego.exe

gdb: compilar_gdb
	gdb juego.exe
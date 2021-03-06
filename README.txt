README: Trabajo Práctico 2: Una Aventura Pokemon.

Facultad de Ingeniería - UBA.

Cátedra Mendez - Camejo.

Alumna: María Pilar Gaddi.

Primera sección: Presentación.

	-Introducción: 
		El presente trabajo consta de los siguientes archivos para poder ser compilado y ejecutado correctamente:
			->menu.c: donde se implementan todas las funciones públicas de la biblioteca menu.h junto con las funciones privadas, todas estas están relacionadas a los variados menues que presenta el juego. 
			->menu.h
			->gimnasio.c: donde se implementan todas las funciones públicas de la biblioteca gimnasio.h junto con las funciones privadas, todas estas están relacionadas a la estructura del juego.
			->gimnasio.h
			->batallas.c: donde se implementan todas las funciones públicas de la biblioteca batallas.h junto con las funciones privadas, todas estas son las funciones de batalla utilizadas en el juego, cada una de estas con diferentes condiciones para determinar al pokemon ganador. 
			->batallas.h 
			->heap.c: donde se implementan todas las funciones públicas de la biblioteca heap.h junto con las funciones privadas, estas están relacionadas con el TDA heap, utilizado en el trabajo práctico.
			->heap.h
			->lista.c: donde se implementan todas las funciones públicas de la biblioteca lista.h junto con las funciones privadas, estas están relacionadas con el TDA lista, utilizado en el trabajo práctico.
			->lista.h
			->pruebas_heap.c: Aquí están todas las funciones de prueba realizadas al heap para lograr un correcto funcionamiento del mismo.
			->pa2mm.h: donde se encuentran algunas de las funciones utilizadas en pruebas_heap.c para realizar las pruebas. Esta biblioteca fue brindada por la cátedra. 
			->makefile: Para facilitar la línea de compilación y de ejecución del programa.
			->main.c: aquí se encuentra el main principal.
			->Están incluídos los archivos 'arch_personaje.txt', 'arch_gym.txt' y 'arch_gym2.txt' que son los que utilicé para jugar el juego. 

	-Linea de compilación y ejecución:

	Para compilar y ejecutar el programa se utilizó un makefile:

	En caso de que se desee correr el programa:
		El programa debe ser compilado bajo la siguiente linea de compilación:
			make compilar
		El programa debe ser ejecutado bajo la siguiente linea de ejecución:
			make exe_juego

	En caso de que se desee chequear que no haya perdida de memoria al correr el programa:
		El programa debe ser compilado bajo la siguiente linea de compilación:
			make compilar
		El programa debe ser ejecutado bajo la siguiente linea de ejecución:
			make exe_valgrind

	En caso de que se desee correr las pruebas del heap:
		El programa debe ser compilado bajo la siguiente linea de compilación:
			make compilar_pruebas_heap
		El programa debe ser ejecutado bajo la siguiente linea de ejecución:
			make exe_pruebas_heap

	En caso de que se desee chequear que no haya perdida de memoria al correr las pruebas del heap:
		El programa debe ser compilado bajo la siguiente linea de compilación:
			make compilar_pruebas_heap
		El programa debe ser ejecutado bajo la siguiente linea de ejecución:
			exe_pruebas_heap_valgrind

Segunda sección: Justificaciones.

	-¿Por qué se eligió el uso de un heap para almacenar todos los gimnasios?
		Todos los gimnasios de cada juego son almacenados en un heap único. En cada nodo del heap hay almacenado toda la estructura de un solo gimnasio.
		El heap se puede representar como un array y resulta muy útil ya que, de esta manera, para poder acceder al gimnasio actual únicamente se necesita acceder a la posición 0 del array (raíz del heap). 
		En el TP se utilizó un heap minimal ya que el juego debía ir desde el gimnasio más sencillo (la menor dificultad) hasta el gimnasio mas difícil (la mayor dificultad). 
		En el caso de la lectura de cada gimnasio, estos podrán ser cargados a partir de un archivo o a partir de múltiples archivos. Decidí cargar al heap únicamente los gimnasios que tengan una lectura exítosa de toda su información. En caso de: que el lider o el entrenador no tenga pokemones, de tener una inicial invalida (es decir, que no esté dentro de las iniciales que pueda llegar a tener el archivo), que la primera inicial leida no sea una "G", o que el archivo este vacio, el gimnasio no será cargado y ahí terminará la lectura de ese archivo. En caso de haberse leído gimnasios bien formateados anteriormente, estos se habrán cargado al heap. 
		Si el usuario quiere ingresar nuevamente un archivo de gimnasios ya cargado, lo podrá ingresar y a la hora de jugar se repetirá ese gimnasio. 

	-¿Por qué se eligió el uso de una pila para almacenar los entrenadores de cada gimnasio?
		La estructura de los entrenadores (de cada gimnasio) son almacenados,cada una,en un nodo de una pila única. Por cada gimnasio, hay una pila de entrenadores. Se eligió el uso de una pila para almacenar a los entrenadores de cada gimnasio ya que el ultimo entrenador del archivo del gimnasio actual es el primero en usarse, de esta manera solo se necesita acceder al la posición tope-1 de la pila. Por lo tanto, a medida que los entrenadores son derrotados se utiliza lista_desapilar para eliminar al último entrenador de la pila y una vez que la misma está vacia (su tope es 0), se combate con el lider del gimnasio actual.
		Aclaración: únicamente recorrí a todos los entrenadores almacenados en una pila cuando sólo se tenía el fin de mostrarlos por pantalla, esto sucede cuando se muestra la información del gimnasio actual.

	-¿Por qué se eligió el uso de una lista para almacenar los pokemones de cada entrenador/lider de cada gimnasio?
		La estructura de los pokemones de cada entrenador/lider (de cada gimnasio) son almacenados,cada uno,en un nodo de la lista lista_pokemones_obtenidos, mientras que la estructura de los primeros seis pokemones también se encuentran almacenados en otra lista, lista_pokemones_para_combatir (estos serían una copia). Por lo tanto, hay dos listas por cada entrenador/lider de cada gimnasio. Se eligió el uso de dos listas para almacenar la estructura de los pokemones de cada entrenador/lider para poder recorrerlos (a todos o a cierta cantidad) cuando sea necesario. Por ejemplo, cuando se quiere enfrentar un pokemon de un entrenador/lider con uno del personaje principal, en una batalla. También cuando se quiere tomar prestado cualquier pokemon de batalla del lider del gimnasio que el personaje principal ganó. 
		En el caso de las batallas, si el gimnasio actual contiene un id_batalla distinto de 1,2,3,4 o 5 se tomará por defecto id_batalla = 5.
		En el caso de los pokemones de los lideres/entrenadores de los gimnasios, los únicos que van a combatir son aquellos que están en la lista lista_pokemones_para_combatir, es decir, los primeros seis. Los demás únicamente estarán presentes a la hora de mostrar la información del lider y de los entrenadores. 

	-¿Por qué se eligió el uso de una lista para almacenar los pokemones del personaje principal?
		La estructura de cada pokemon del personaje principal es almacenada, cada una, en una lista lista_pokemones_obtenidos, mientras que las estruturas de los primeros seis pokemones también se encuentran almacenados en otra lista, lista_pokemones_para_combatir (estos serían una copia). En el juego hay un único personaje principal, con las dos listas de pokemones mencionadas anteriormente. Se eligió el uso de dos listas para almacenar las estructuras de los pokemones del personaje principal para poder recorrerlos y acceder a un determinado pokemon cuando sea necesario. Por ejemplo, cuandos se quiere intercambiar un pokemon de los obtenidos con uno de los de batalla, o cuando se quiere mejorar la habilidad de cierto pokemon de combate. 

	-Lectura del archivo del personaje principal: Solo habrá un único personaje principal hasta terminar el juego. Este no podrá ser cambiado en caso de tener una lectura exitosa del archivo del cual se sacó la información del personaje. Únicamente en caso de haberse leído mal el archivo se podrá ingresar otro.
	La lectura del archivo del personaje NO saldra exítosa si: el jugador no tiene ni un solo pokemon, si la primera inicial al comenzar a leer el archivo no es una "E" o si este está vacio. 


#include "main.h"
#include <stdlib.h>

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
	// Se crea la lista
	Lista lista = crea_lista();
	
	printf("La lista tiene %lu elementos\n", longitud(lista));

	// Se insertan datos de prueba
	inserta_datos_de_prueba(lista);

	// Se remueve un elemento de la lista
	Elemento *borrado = quita_elemento(lista, 0);
	if (borrado != NULL) free(borrado->valor);
	free(borrado);
	printf("La lista tiene %lu elementos después de borrar la cabeza:\n", longitud(lista));
	
	// Se remueve un elemento que no existe en la lista
	quita_elemento(lista, longitud(lista));
	printf("La lista tiene %lu elementos después de borrar algun elemento en una posición erronea\n", longitud(lista));

	//Se imprime la lista antes de ordenar
	printf("Imprimimos la lista antes de ordenar\n");
	imprime_lista_int(lista);
	ordena_lista(lista, &cmp_int);

	//Se imprime la lista después de ordenar
	printf("Imprimimos la lista después de ordenar\n");
	imprime_lista_int(lista);

	//Se libera la memoria ocupada
	borra_lista(lista);
	
}

void inserta_datos_de_prueba(Lista lista){
	srand(time(NULL));
	int *num_a_insertar;
	int indice;
	for (indice = 0; indice < 20; ++indice) {
		num_a_insertar = malloc(sizeof(int));
		*num_a_insertar = rand() % 100;
		inserta_elemento(lista, num_a_insertar);
	};
}

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista*/
int inserta_elemento(Lista lista, void *value){  
		size_t tam= longitud(lista);
		Elemento* new= malloc(sizeof(Elemento)); //Apartamos memoria.
		new -> siguiente= *lista;
		new -> valor= value; //Asignamos el valor, y ponemos el siguiente.
		*lista= new;
		return tam+1;
}

// Función que compara dos enteros.
int cmp_int(const void * a, const void * b){
    int value_a = *((int *)a);
    int value_b = *((int *)b);

    if(value_a < value_b) return -1; //Simple comparación entre 2 enteros.
    else if(value_a > value_b) return 1;
    else return 0;
}

/*Imprime los elementos de la lista como enteros*/
void imprime_lista_int(Lista lista){
	Elemento* next= *lista;
	while(next != NULL){
		printf("%d  ", *(int*)next -> valor); //Vamos iterando sobre la lista imprimiendo cada elemento.
		next= next -> siguiente;
	}
	printf("\n");
}

/*Función que ordena una lista usando una función comparadora*/
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){
	size_t tam= longitud(lista);
	int arreglo[tam]; 
	Elemento* next= *lista;
	for(int i= 0; i < tam; i++){
		arreglo[i]= *(int*)next -> valor; //Hacemos un arreglo con los valores de la lista.
		next= next -> siguiente;
	}
	qsort(arreglo, tam, sizeof(int), cmp_int); //Mandamos a llamar a QSORT para que ordene por nosotros el arreglo, con nuestra función comparadora.
	next= *lista;
	for(int i= 0; i < tam; i++){
		*(int*)next -> valor = arreglo[i]; //Pasamos los valores del arreglo ordenado a la lista.
		next= next -> siguiente;
	}
}

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista lista){
	size_t tam= longitud(lista);
	Elemento* element;
	for(int i= 0; i < tam; i++){
		element= quita_elemento(lista, 0);
		if (element != NULL) free(element -> valor); //Borramos cada elemento de la lista, y nos aseguramos de liberar la memoria.
		free(element);
	}
}

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento* quita_elemento(Lista lista, size_t posicion){
	size_t tam= longitud(lista);
	if(posicion >= tam) return NULL; //Si la posición es ilegal, no hacemos nada.

	if(posicion == 0){ //Si es la cabeza.

		Elemento* next_to_head= (*lista) -> siguiente; //Borramos la cabeza y la nueva cabeza es el siguiente a esta.
		Elemento* head= *lista;
		(*lista) -> siguiente= NULL;
		(*lista) -> valor= NULL;
		*lista= next_to_head;
		return head;

	}else if(posicion == tam-1){ //Si es el último.

		Elemento* prev_to_last= *lista;

		for(int i= 1; i < tam-1; i++){
			prev_to_last= (*lista) -> siguiente;
		}
		Elemento* last= prev_to_last -> siguiente;
		prev_to_last -> siguiente = NULL;
		last -> valor= NULL;
		last -> siguiente= NULL;

		return last;
	}else{	//Si no es ninguno de los anteriores.
	   	int i= 0;
	   	Elemento* next= *lista;
	   	while(next != NULL){
			if(i == posicion-1){
				Elemento* aux= next -> siguiente;
				Elemento* a_borrar= next -> siguiente;
				Elemento* el_sig= a_borrar -> siguiente; //AHHHHHHH, odio acomodar referencias T_T.
				next -> siguiente= el_sig;
				a_borrar -> siguiente = NULL;
				a_borrar -> valor = NULL;
				
				return aux;
			}
			next= next -> siguiente;
		  	i+=1;
		}
	}
}

/*Crea una lista vacía*/
Lista crea_lista(){
	Lista nueva_lista= malloc(sizeof(Lista)); //Apartamos la memoria para crear la nueva lista vacía.
	return nueva_lista;
}

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista){
	if(*lista == NULL) return 0; //Si está vacía.

	size_t tam= 0;
	int i= 0;
	Elemento* next= *lista;

	while(next != NULL){ //Iteramos sobre la lista hasta que el "siguiente sea null", i.e, estemos en el último.
		next= next -> siguiente;							//Para ese momento ya habremos contado los elementos.
		tam+= 1;
		i+= 1;
	}
		
	return tam;
}

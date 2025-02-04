#include "../../inc/push_swap.h"
void	sort_three(t_node **a) //Si tenemos 3 numeros en la pila a
//La lógica emplea identificar el nodo más grande, moverlo a la posición correcta mediante rotaciones o inversiones, y luego asegurar que los dos nodos restantes estén ordenados mediante un intercambio.
{
	t_node	*biggest_node; //puntero al nodo mas grande en la pila a

	biggest_node = find_max(*a);//asignamos el puntero al nodo que nos devuelva la funcion find_max
	if (biggest_node == *a) //comprobamos que el puntero "a" y el puntero al que apunta biggest_node apuntan al mismo nodo. Esto es para saber si "a" ya apunta al nodo que contiene el numero mas grande
		ra(a, false); //si efectivamente a apunta al nodo con el numero mas alto, se llama a la funcion encargada de rotar la pila a, para que "a" apunte al siguiente nodo y el nodo al que apuntaba "a" se mueva al final de la pila
	else if ((*a)->next == biggest_node) //comprobamos si el segundo es el mas grande de la lista
	//lo comprobamos desreferenciando a (*a). Esto es necesario para obtener el nodo al que apunta "a" antes de acceder al campo next de ese nodo
		rra(a, false); //si el segundo nodo es el que tiene el numero mas grande, entonces llamamos a la funcion reverse rotate para que el ultimo nodo del stack pase a ser el primero arrastrando al segundo a la ultima posicion
	if ((*a)->value > (*a)->next->value) //comprueba si el top node es mayor que el segundo node
		sa(a, false); //Si el primer nodo es mayor que el segundo, simplemente haz swap a para cambiar el orden de los nodos
}

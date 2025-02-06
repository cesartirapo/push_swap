#include "../../inc/push_swap.h"
static void	set_target_b(t_node *a, t_node *b) //buscamos el target node para los nodos de b en la pila a
{
	t_node	*current_a; //puntero que nos ayudara a recorrer la pila a
	t_node	*target; //puntero que apunta al target node en a del nodo en b
	long	best_match_index; //variable para almacenar el numero mas grande y cercano al numero del nodo b

	while (b)//siempre que hayas nodos en b
	{
		best_match_index = LONG_MAX; //incializamos la variable con el numero long mas grande
		current_a = a; //hacemos que el punero current_a apunte al primer nodo de la pila a
		while (current_a) //pasamos por todos los nodos de la pila a
		{
			if (current_a->value > b->value 
				&& current_a->value < best_match_index) //si el valor del nodo al que apunta current_a es mayor que el valor del nodo al que apunta b y menor que el valor almacenado en la variable
			{
				best_match_index = current_a->value; //actualizamos el valor de best_match_index con el valor del nodo apuntado por current_a
				target = current_a; //hacemos que el puntero target apunte al nodo de a que tiene el valor mas grande y mas cercano al valor del nodo al que apunta b
			}
			current_a = current_a->next; //nos movemos al siguiente nodo la fila a
		}
		if (best_match_index == LONG_MAX) //si el valor de la variable best_match no ha cambiado (lo cual significaria que no hemos encontrado ningun nodo mayor que el nodo al que apunta b)
			b->target = find_min(a); //actualizamos el campo target del nodo al que apunta b, para que apunta al nodo de a que tenga el valor mas pequeno
		else
			b->target = target; //Si el valor de la variable cambio, es decir, encontramos un numero mas grande que el valor del nodo al que apunta b, actualizamos el campo target del nodo b para que apunte al nodo al que apunta el puntero target (current_a)
		b = b->next; //nos movemos al siguiente nodo de b para hacer la misma comparacion de este con todos los nodos de a
	}
}

void	init_nodes_b(t_node *a, t_node *b) //funcion que prepara los nodos de b para empujarlos a la pila a actualizando indices de nodos en ambas pilas y analizando los a target nodes para los nodos de b
{
	current_index(a);//Asigna índices a los nodos de a para saber su posición actual en la pila y establece el campo above_median de cada nodo como verdadero o falso
	current_index(b);//Asigna índices a los nodos de b para saber su posición actual en la pila y establece el campo above_median de cada nodo como verdadero o falso
	set_target_b(a, b);//cada nodo de b busca su "objetivo" en a, es decir, el nodo en a donde debería colocarse para mantener el orden
}
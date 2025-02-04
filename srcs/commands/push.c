#include "../../inc/push_swap.h"
static void	push(t_node **dst, t_node **src) //Funcion que empuja el primer nodo de una pila a la primera posicion de la otra pila
{
	t_node	*push_node; //creamos un puntero que apuntara a la cabeza de la pila src, es decir, al nodo que queremos mover

	if (!*src) //si la pila desde donde queremos mover esta vacia, es decir si el puntero src apunta a null
		return ;
	push_node = *src; //el puntero push_node apunta al nodo cabeza de la pila src 
	*src = (*src)->next; //ahora el puntero que apunta a la cabeza de la pila src apunta a la direccion que aparece en el campo next del nodo que era cabeza, es decir, al nuevo primer nodo
	if (*src) //si ese campo next apunta a otro nodo, un segundo nodo en esa pila 
		(*src)->prev = NULL; //actualizamos en null em campo prev del nuevo primer nodo de la pila src
	//ATENCION. push_node->prev = NULL; //no creo que haga falta esta linea porque el campo prev de push_node siempre es null, ya que push_node apunta al primer nodo de la pila src
	if (!*dst) //comprobamos si la pila de destino esta vacia
	{
		*dst = push_node; //Si esta vacia, el puntero que apunta a la cabeza de la pila b ahora apunta al primer puntero de la pila a
		push_node->next = NULL; //ademas como es el unico nodo de la lista, su campo next debe apuntar a null
	}
	else //si la pila de destino no esta vacia
	{
		push_node->next = *dst; //el campo next del nodo que vamos a mover ahora apunta al primer nodo de la pila de destino
		push_node->next->prev = push_node; //el campo prev del nuevo segundo nodo de la pila dst ahora apunta al nodo que hemos movido
		*dst = push_node; //el puntero que apunta a la cabeza de la pila dst ahora apunta al nuevo primer nodo de dst
	}
}

void	pa(t_node **a, t_node **b, bool print) //Empuja encima de a el primer nodo de b
{
	push(a, b); 
	if (!print) 
		printf("pa\n");
}

void	pb(t_node **b, t_node **a, bool print) //Empuja encima de b el primer nodo de a
{
	push(b, a);
	if (!print)
		printf("pb\n");
}
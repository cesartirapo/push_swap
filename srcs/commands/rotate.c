#include "../../inc/push_swap.h"
static void	rotate(t_node **stack) //funcion que hace rotar al primer nodo de la pila al final de la pila
{
	t_node	*last_node; //puntero que apuntara al ultimo nodo

	if (!*stack || !(*stack)->next) //comprobamos si stack apunta "a" apunta a null, es decir que la pila esta vacia, o si solo hay un nodo
		return ;
	last_node = find_last(*stack);//enviamos "stack" a find_last para que nos envie un puntero que apunte al ultimo nodo. Lo enviamos con un * porque no queremos modificar el valor de "a" o "stack", solo queremos movernos por la pila
	last_node->next = *stack; //hacemos que el campo next del ultimo nodo ahora apunte al nodo que estamos rotando al final de la pila
	*stack = (*stack)->next; //actualizamos stack para que apunte al segundo nodo. FIJATE EN COMO SE DESREFERENCIA CON (*stack)
	(*stack)->prev = NULL; //stack ahora apunta al que era el segundo nodo, por lo que tenemos que hacer que su campo prev ahora sea null, ya que apuntes apuntaba al primer nodo
	last_node->next->prev = last_node; //hacemos que el campo prev del nuevo ultimo nodo ahora apunte al ultimo nodo
	last_node->next->next = NULL; //terminamos la configuracion del stack haciendo que el campo next del nuevo ultimo nodo apunte a null
}		

void	ra(t_node **a, bool print)//la funcion recibe un puntero doble a la cabeza de la pila que luego lo envia a rotate. Es doble porque hay que modificar el valor de a
{
	rotate(a);
	if (!print)
		printf("ra\n");
}

void	rb(t_node **b, bool print)
{
	rotate(b);
	if (!print)
		printf("rb\n");
}

void	rr(t_node **a, t_node **b, bool print)
{
	rotate(a);
	rotate(b);
	if (!print)
		printf("rr\n");
}
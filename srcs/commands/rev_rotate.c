#include "../../inc/push_swap.h"
static void	rev_rotate(t_node **stack) //funcion que mueve el ultimo nodo al principio de la pila
{
	t_node	*last;

	if (!*stack || !(*stack)->next)//mira la operacion de desreferenciar para acceder al nodo al que apunta stack, y despues a su campo next
		return ;
	last = find_last(*stack);//buscamos el ultimo nodo y hacemos que el puntero last apunte a el
	last->prev->next = NULL; //el campo next del nuevo ultimo nodo ahora apunta a null
	last->next = *stack; //el campo next del nuevo primer nodo tiene que aputnar al nuevo segundo nodo que aun esta apuntado por stack
	last->prev = NULL; //el campo prev del nuevo primer nodo apunta a null
	*stack = last;  //ahora stack apunta al nuevo primer nodo
	last->next->prev = last; //el campo prev del nodo apuntado por el nuevo primer nodo ahora tiene que apuntar al nuevo primer nodo para completar la conexion entre ambos
}

void	rra(t_node **a, bool print)//la funcion recibe un puntero doble a la cabeza de la pila que luego lo envia a rev_rotate. Es doble porque hay que modificar el valor de a
{
	rev_rotate(a);
	if (!print)
		printf("rra\n");
}

void	rrb(t_node **b, bool print)
{
	rev_rotate(b);
	if (!print)
		printf("rrb\n");
}

void	rrr(t_node **a, t_node **b, bool print)
{
	rev_rotate(a);
	rev_rotate(b);
	if (!print)
		printf("rrr\n");
}
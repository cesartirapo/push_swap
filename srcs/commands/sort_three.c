#include "../../inc/push_swap.h"
void	sort_three(t_node **a) //Si tenemos 3 numeros en la pila a
//La lógica emplea identificar el nodo más grande, moverlo a la posición correcta mediante rotaciones o inversiones, y luego asegurar que los dos nodos restantes estén ordenados mediante un intercambio.
{
	t_node	*biggest_node; //To store a pointer to the biggest node in stack `a`

	biggest_node = find_max(*a);
	if (biggest_node == *a) //Check if the current node is the biggest
		ra(a, false); //If so, rotate the top node to the bottom of the stack
	else if ((*a)->next == biggest_node) //Check if the second node is the biggest
		rra(a, false); //If so, reverse rotate the bottom node, to the top of the stack
	if ((*a)->value > (*a)->next->value) //Check if the bottom node is the biggest, but the top node is higher than the second node
		sa(a, false); //If so, simply swap the top and second nodes
}

#include "../../inc/push_swap.h"
int	stack_len(t_node *stack) //Calculamos el numero de nodos que hay en el stack
{
	int	count;

	if (!stack) 
		return (0);
	count = 0;
	while (stack)//iteramos hasta que el puntero stack apunte a NULL, que es donde apuntara el campo next del ultimo nodo
	{
		stack = stack->next;//nos movemos al siguiente nodo
		count++;
	}
	return (count);
}

t_node	*find_last(t_node *stack) //función que devuelve un puntero al último nodo
{
	if (!stack)
		return (NULL);
	while (stack->next) //el campo next contiene un puntero que apunta al siguiente nodo. El loop continua hasta que no siguiente nodo
		stack = stack->next;//stack pasa a apuntar al nodo al que apuntaba stack->next
	return (stack);
}

bool	stack_sorted(t_node *stack) //función que comprueba si la pila está ordenada en ascendente
//Hay en lugar de bool podría ser de tipo int y devolver 1 en lugar de true
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value) //comprobamos que están ordenados de forma ascendente, es decir, que el value del nodo al que apunta stack no sea mayor que el value del nodo que es apuntado por el campo next de stack
			return (false);
		stack = stack->next; //Si el numero anterior no es mayor que el siguiente, actualizamos stack y contiuamos el bucle
	}
	return (true);
}

t_node	*find_min(t_node *stack) //Define a function that searches a stack and returns the node with the smallest number
{
	long			min; //To store the smallest value so far
	t_node	*min_node; //To store a pointer that points to the smallest number

	if (!stack)
		return (NULL);
	min = LONG_MAX; //Assign to the smallest value so far, the max long integer
	while (stack) //Loop until the end of the stack is reached
	{
		if (stack->value < min) //Check if the current node value is smaller than the smallest so far
		{
			min = stack->value; //If so, update the smallest number so far
			min_node = stack; //Set the pointer to point to the node with the smallest number so far
		}
		stack = stack->next; //Move to the next node for processing
	}
	return (min_node); 
}

t_node	*find_max(t_node *stack) //Define a function that searches a stack and returns the node with the biggest number
{
	long			max; //To store the biggest value so far
	t_node	*max_node; //To store a pointer that points to the biggest number

	if (!stack)
		return (NULL);
	max = LONG_MIN; //Assign to the biggest value so far, the max long integer
	while (stack) //Loop until the end of the stack is reached
	{
		if (stack->value > max) //Check if the current node value is smaller than the biggest so far
		{
			max = stack->value; //If so, update the biggest number so far
			max_node = stack; //Set the pointer to point to the node with the biggest number so far
		}
		stack = stack->next; //Move to the next node for processing
	}
	return (max_node);
}

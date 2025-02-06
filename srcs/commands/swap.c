#include "../../inc/push_swap.h"
static void	swap(t_node **head)
{
	if (!*head || !(*head)->next) //head es un puntero que apunta al primer nodo de la lista
		return ;//aqui comprobamos que primero que la lista no esté vacía y segundo que exista un segundo nodo
	*head = (*head)->next; //accedemos al siguiente nodo haciendo que head apunte a este
	//Ahora head apunta al segundo
	(*head)->prev->prev = *head; //accedemos al campo prev del antiguo primer nodo (que ahora es el segundo nodo) y lo actualizamos para que apunte al nuevo primer nodo (que originalmente era el segundo nodo).
	(*head)->prev->next = (*head)->next; //accedemos al campo next del antiguo primer nodo para que apunte donde apunta el puntero next del que era el segundo, es decir al tercer nodo o NULL si no hay un tercer nodo
	if ((*head)->next) //Miramos si hay un tercer nodo, si lo hay...
		(*head)->next->prev = (*head)->prev; //si hay un tercero, su campo prev ahora apuntará al nuevo segundo nodo, que es donde apunta el campo prev del que era segundo
	(*head)->next = (*head)->prev; //Ahora el campo next del nuevo primero nodo apunta donde antes apuntaba su campo prev, es decir al antiguo primero nuevo segundo nodo
	(*head)->prev = NULL; //Se actualiza el campo prev del nuevo primer nodo para que sea NULL
}

void	sa(t_node **a, bool print) //la funcion recibe un puntero doble a la cabeza de la pila que luego lo envia a swap. Es doble porque hay que modificar el valor de a
{
	swap(a);
	if (!print)
		printf("sa\n");
	print_piles(*a, NULL);
}

void	sb(t_node **b, bool print)
{
	swap(b);
	if (!print)
		printf("sb\n");
	print_piles(NULL, *b);
}

void	ss(t_node **a, t_node **b, bool print)
{
	swap(a);
	swap(b);
	if (!print)
		printf("ss\n");
	print_piles(*a, *b);
}

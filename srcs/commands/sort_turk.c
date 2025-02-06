#include "../../inc/push_swap.h"
void	prep_for_push(t_node **stack,
						t_node *top_node,
						char stack_name) //esta funcion es util si el nodo a y su target b estan en diferente posicion con respecto a las medianas de sus pilas, es decir uno por encima de la mediana y otro por debajo

//la funcion recibe un puntero doble cabeza a la pila ( a o b), un puntero que apunta al nodo mas barato en a o a su target en b y un caracter ('a' o 'b')
{
	while (*stack != top_node) //Aqui comprobamos que el nodo mas barato o su target no sean ya los primeros de sus pilas
	{
		if (stack_name == 'a') //En caso de que el nodo barato no sea el primero de la pila a
		{
			if (top_node->above_median)//si esta por encima de la mediana, llamamos a la funcion rotate para empujar el nodo una posicion hacia arriba
				ra(stack, false);
			else
				rra(stack, false);//si esta por debajo de la mediana, llamamos a reverse rotate para que llegue a la primera posicion pero dando la vuelta
		}
		else if (stack_name == 'b') //lo mismo pero para el caso de que el nodo target en b no sea el primero de la pila b
		{
			if (top_node->above_median)
				rb(stack, false);
			else
				rrb(stack, false);
		}	
	}
}

static void	rotate_both(t_node **a,
						t_node **b,
						t_node *cheapest_node) //Funcion que hace rotar los primeros nodos en a y b al final de sus pilas si este es el movimiento mas barato
{
	while (*b != cheapest_node->target
		&& *a != cheapest_node) //por eso enviamos el puntero que apunta al nodo mas barato en a, para comprobar primero que los punteros a y b, que son punteros que apuntan a la cabeza, no apuntan ya a los mas baratos
		rr(a, b, false); //rotamos, y lo hacemos hasta que el nodo mas barato o su target esten en la cima de su pila
	//current_index(*a);//actualizamos los campos indice y above_median de los nodos de las pilas a y b
	//current_index(*b);no creo que hagan falta estas lineas porque las actualizaciones se hacen en init_nodes_a
}

static void	rev_rotate_both(t_node **a,
								t_node **b,
								t_node *cheapest_node) //Esta funcion hace el movimiento contrario
{
	while (*b != cheapest_node->target
		&& *a != cheapest_node)
		rrr(a, b, false);
	//current_index(*a);//actualizamos los campos indice y above_median de los nodos de las pilas a y b
	//current_index(*b);no creo que hagan falta estas lineas porque las actualizaciones se hacen en init_nodes_a
}

t_node	*get_cheapest(t_node *stack) //busca el nodo mas barato, que es basicamente el nodo que en su campo cheapest tiene true
{
	if (!stack)
		return (NULL);
	while (stack)//recorremos toda la pila
	{
		if (stack->cheapest)//si el campo cheapest es true
			return (stack);//devolvemos el puntero que apunta al nodo de a mas barato
		stack = stack->next;//si aun no lo hemos encontrado, actualizamos el puntero stack para seguir recorriendo la pila
	}
	return (NULL);
}

static void	move_a_to_b(t_node **a, t_node **b) //esta funcion prepara los nodos mas baratos para colocarlos en lo alto de sus pilas
//para ello, maneja los nodos según su posición relativa a la mediana. La secuencia de rotate_both, rev_rotate_both, y prep_for_push se asegura de que el nodo más barato y su objetivo estén en la cima antes de hacer el movimiento.
{
	t_node	*cheapest_node; //puntero que apunta al nodo mas barato en a

	cheapest_node = get_cheapest(*a);//actualizamos el puntero cheapest_node para que apunte al nodo en a mas barato
	if (cheapest_node->above_median 
		&& cheapest_node->target->above_median) //Si el nodo mas barato en a es igual a la mediana o mayor y si su target node en b esta tambien igual o por encima de la mediana
		rotate_both(a, b, cheapest_node);//hacemos que los primeros nodos en las pilas a y b roten hacia abajo. Enviamos para eso punteros dobles de a y b y el puntero que apunta al mas barato
	else if (!(cheapest_node->above_median) 
		&& !(cheapest_node->target->above_median)) //Si el nodo en a y su target estan por debajo de la mediana
		rev_rotate_both(a, b, cheapest_node); //hacemos rev rotate para colocar los nodos baratos en la cima de ambas pilas pero dando la vuelta por abajo
	//si el nodo a y su target b estan en diferent posicion con respecto a las medianas de sus pilas, estos se preparan individualmente con prep_for_push
	prep_for_push(a, cheapest_node, 'a'); //colocamos el nodo barato de a arriba de su pila
	prep_for_push(b, cheapest_node->target, 'b'); //colocamos el target node en b arriba de su pila
	pb(b, a, false);//Empujamos encima de b el primer nodo de a
}

static void	move_b_to_a(t_node **a, t_node **b) //Esta funcion prepara Define a function that prepares `b`'s target `a` nodes for pushing all `b` nodes back to stack `a` 
{
	prep_for_push(a, (*b)->target, 'a'); //preparamos el target node en a de b, es decir, lo colocamos encima, en lo alto de la pila a
	pa(a, b, false);//Empujamos encima de a el primer nodo de b
}

static void	min_on_top(t_node **a) //la funcion mueve el nodo con el valor mas pequeno a lo alto de la fila
{
	while ((*a)->value != find_min(*a)->value) //comprobamos que el campo value del primer nodo de la pila a contiene el numero mas pequeno llamando a la funcion find_min que nos devuelve un puntero que apunta al nodo con el numero mas pequeno
	//si ya el primer nodo tuviera el valor mas pequeno entonces este while no se ejecuta
	{
		if (find_min(*a)->above_median) //si el nodo que buscamos esta por encima de la mediana rotamos
			ra(a, false);
		else
			rra(a, false);//si esta por debajo de la mediana, hacemos reverse rotate
	}
}

void	sort_turk(t_node **a, t_node **b, int len_a) //funcion que ordena cuando tenemos mas de 3 numeros en la pila a
{
	if (len_a-- > 3) //si tenemos mas de 3 nodos en la pila a, movemos uno a b
		pb(b, a, false);
	if (len_a-- > 3) //si aun tenemos mas de 3 nodos, volvemos a mover uno a b
		pb(b, a, false);
	while (len_a-- > 3) //Si aun tenemos 3, volvemos a mover uno a b
	{
		init_nodes_a(*a, *b); //pasamos los valores de los punteros, es decir las direccion de memoria del primer nodo de cada pila
		//la funcion init_nodes, va a buscar y preparar los nodos de a mas eficientes (por medio de cost analysis) para ser movidos a b
		move_a_to_b(a, b); //movemos el mas barato de los nodos de la pila a de forma ordenada en la pila `b`, hasta que solo queden 3 nodos en la pila a
		//despues de mover el nodo mas barato tenemos que repetir el proceso (incluido buscar los target nodos de a en b) de encontrar otra vez el nodo mas barato de a para mover en b 
	}
	sort_three(a);//Ordenamos los tres nodos de la pila a
	while (*b) //nos movemos por la fila b
	{
		init_nodes_b(*a, *b); //funcion que prepara los nodos de b para empujarlos a la pila a actualizando indices de nodos en ambas pilas y analizando los a target nodes para los nodos de b
		move_b_to_a(a, b); //Movemos todos los nodos de vuelta desde b hasta a, pero antes tenemos que llevar el b target node en a encima de la pila a, para despues mover el nodo de b
	}
	current_index(*a); //con todos los nodos en a otra vez, refescamos el indice de todos 
	min_on_top(a); //nos aseguramos de que el numero mas pequeno esta arriba de la pila
}
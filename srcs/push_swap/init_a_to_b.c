#include "../../inc/push_swap.h"
void	current_index(t_node *stack)//esta funcion actualiza el campo index y above_median de todos los nodos de la pila a y de la pila b
{
	int	i; //indice del nodo
	int	median; //posicion de la mediana

	i = 0;
	if (!stack)
		return ;
	median = stack_len(stack) / 2; //Calculamos la mediana diviendo la longitud del stack por 2
	while (stack) //hasta que lleguemos al final del stack
	{
		stack->index = i; //actualizamos el campo indice del nodo con i.
		if (i <= median) //comprobamos que el nodo actual esta por encima o debajo de la mediana
			stack->above_median = true; //si coincide con la mediana o esta por encima, campo above_median true
		else
			stack->above_median = false; //si esta por debajo, campo above_median false
		stack = stack->next; //nos movemos hacia el siguiente nodo
		++i; //Incrementamos i que sera el indice del siguiente nodo
	}
}

static void	set_target_a(t_node *a, t_node *b)//buscamos el target node para los nodos de a en la pila b
{
	t_node	*current_b; //puntero que nos ayudara a recorrer la pila b
	t_node	*target; //puntero al target nodo en la pila b
	long		best_match_index; //indice que guarda el valor del numero mas pequeno que se acerca mas

	while (a) //siempre que haya nodos en a
	{
		best_match_index = LONG_MIN; //asignamos el valor mas bajo posible a best_match_index
		current_b = b; //hacemos que current_b apunte al nodo donde apunta b, nodo cabeza de la pila b
		while (current_b) //pasamos por todos los nodos de la pila b
		{
			if (current_b->value < a->value 
				&& current_b->value > best_match_index) //comprobamos que el campo value del nodo al que apunta current_b es mas pequeno que el nodo al que apunta a y que sea mas grande que el numero pequeno mas cercano
			{
				best_match_index = current_b->value; //Si es asi, actualizamos el valor de best_match index, que recuerda que guarda el numero mas pequeno que, y mas cercano al valor del nodo a encontrado hasta el momento
				target = current_b; //actualizamos tambien el puntero target para que apunte al nodo con el numero mas pequeno y cercano al numero de a
			}
			current_b = current_b->next; //pasamos al siguiente nodo de la pila b
		}
		if (best_match_index == LONG_MIN) //Si LONG_MIN no ha cambiado, esto significa que no hemos encontrado un numero mas pequeno
			a->target = find_max(b); //si es asi, entonces hacemos que el campo target del nodo al que apunta a apunte al nodo en b con el numero mas alto
		else
			a->target = target; //Si hemos encontrado un numero mas pequeno y best match ha cambiado, actualizamos el campo target del nodo a para que apunta donde apunta el puntero target, es decir al nodo de b con el numero mas pequeno y cercano al nodo de a
		a = a->next; //Nos movemos al siguiente nodo de la pila a para encontrar su target `b` node
	}
}

static void	cost_analysis_a(t_node *a, t_node *b) //Funcion que calcula el coste de mover los nodos de a y su target b hacia la cima de sus pilas
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);//calculamos longitud de ambas pilas
	len_b = stack_len(b);
	while (a) //nos movemos por la pila a
	{
		if (!(a->above_median)) //si el campo above_median es false, es decir si la posicion del nodo esta por debajo de la mediana (longitud de la pila entre 2)
			a->push_cost = len_a - (a->index); //Si esta por debajo de la mediana, el coste es la longitud de la pila menos la posicion que ocupa el nodo ya que con operaciones de reverse rotate dando la vuelta llegas antes a la cabeza
		else
			a->push_cost = a->index;//Si está por encima de la mediana, el coste es su posición
		// Ahora, ajustamos el coste con respecto al nodo objetivo (target) de la pila b en funcion de su posision con respecto a la mediana de la pila b
		if (a->target->above_median) //Si el nodo target del nodo a en la pila b esta en la mediana o por encima de la mediana
			a->push_cost += a->target->index; //Si esta por encima de la mediana, el coste se actualiza para ser la suma de los indices de ambos nodos en a y b
		else //si el nodo a esta justo en la mediana o encima y su target node en b esta por debajo de su mediana
			a->push_cost += len_b - (a->target->index); //Actualizamos el coste para ser la suma del indice del nodo a mas (longitud de la pila b - el indice del nodo b), ya que en la pila b dariamos la vuelta a la pila
		a = a->next; //Nos movemos al siguiente nodo de la pila a para calcular su coste
	}
}

void	set_cheapest(t_node *stack) //esta funcion actualiza el campo cheapest del nodo mas barato sea true
{
	long		cheapest_value;//variable que almacena el coste del nodo mas barato
	t_node	*cheapest_node; //un puntero que apunta al nodo mas barato

	if (!stack)
		return ;
	cheapest_value = LONG_MAX; //inicializamos la variable con el mayor valor long
	while (stack) //buscamos el nodo mas barato de toda la pila
	{
		if (stack->push_cost < cheapest_value) //comprobamos si el coste del nodo es menor que la variable cheapest_value
		{
			cheapest_value = stack->push_cost; //si es asi, actualizamos esta variable con el coste del nodo mas barato encontrado
			cheapest_node = stack; //hacemos que el puntero cheapest_node apunte al nodo mas barato
		}
		stack = stack->next; //nos movemos al siguiente nodo en la pila para seguir comparando su coste con la variable cheapest_value
	}
	cheapest_node->cheapest = true; //Despues de haber recorrido la pila, actualizamos el campo `cheapest` attribut del nodo con el coste mas bajo a `true`
	//OJO. Creo que en algun momento habra que resetear los campos cheapest para que vuelvan todos a ser false porque cada vez que mueve un nodo de a a b, el campo cheapest de este nodo es True
}

void	init_nodes_a(t_node *a, t_node *b) //funciona que combina las funciones que necesitamos para decidir que nodos de a movemos a b
//la función init_nodes_a está diseñada para trabajar con listas de nodos (t_node *), entonces necesita recibir directamente el primer nodo de cada pila
//recibe punteros simples, no dobles, porque no busca modificar a y b, solo trabajar con sus nodos
{
	current_index(a);//Asigna índices a los nodos de a para saber su posición actual en la pila y establece el campo above_median de cada nodo como verdadero o falso
	current_index(b);//Asigna índices a los nodos de b para saber su posición actual en la pila y establece el campo above_median de cada nodo como verdadero o falso
	set_target_a(a, b);//cada nodo de a busca su "objetivo" en b, es decir, el nodo en b donde debería colocarse para mantener el orden
	cost_analysis_a(a, b);//Calcula el costo de mover cada nodo de a a su posición en b.
	set_cheapest(a);//Identifica el nodo con el movimiento más barato para priorizarlo.
}
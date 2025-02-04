#include "../../inc/push_swap.h"
static void	rotate_both(t_node **a,
						t_node **b,
						t_node *cheapest_node) //Define a function that rotates both the top `a` and `b` nodes to the bottom of their stacks, if it's the cheapest move
{
	while (*b != cheapest_node->target
		&& *a != cheapest_node) //As long as the current `b` node is not `a` cheapest node's target node, and the current top `a` node is not the top node
		rr(a, b, false); //Rotate both `a` and `b` nodes
	current_index(*a);
	current_index(*b);
}

static void	rev_rotate_both(t_node **a,
								t_node **b,
								t_node *cheapest_node) //Define a function that rotates both the bottom `a` and `b` nodes to the top of their stacks, if it's the cheapest move
{
	while (*b != cheapest_node->target
		&& *a != cheapest_node) //As long as the current `b` node is not `a` cheapest node's target node && and the current `a` node is not the cheapest
		rrr(a, b, false); //Reverse rotate both `a` and `b` nodes
	current_index(*a); //Refresh current node positions
	current_index(*b);
}

static void	move_a_to_b(t_node **a, t_node **b) //Define a function that prepares the cheapest nodes on top of the stacks for pushing `a` nodes to stack `b`, until there are three nodes left in `a`
{
	t_node	*cheapest_node; //To store the pointer to the cheapest `a` node

	cheapest_node = get_cheapest(*a); 
	if (cheapest_node->above_median 
		&& cheapest_node->target->above_median) //If both the cheapest `a` node and its target `b` node are above the median
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->above_median) 
		&& !(cheapest_node->target->above_median)) //If both the cheapest `a` node and its target `b` node are below the median
		rev_rotate_both(a, b, cheapest_node); //`rev_rotate_both` will execute if neither nodes are at the top
	prep_for_push(a, cheapest_node, 'a'); //Ensure the cheapest nodes is at the top, ready for pushing
	prep_for_push(b, cheapest_node->target, 'b'); //Ensure the target node is at the top, ready for pushing
	pb(b, a, false);
}

static void	move_b_to_a(t_node **a, t_node **b) //Define a function that prepares `b`'s target `a` nodes for pushing all `b` nodes back to stack `a` 
{
	prep_for_push(a, (*b)->target, 'a'); //Ensure `b`'s target `a` node is on top of the stack
	pa(a, b, false); 
}

static void	min_on_top(t_node **a) //Define a function that moves the smallest number to the top
{
	while ((*a)->value != find_min(*a)->value) //As long as the smallest number is not at the top
	{
		if (find_min(*a)->above_median) //Rotate or reverse rotate according to the position of the node on the median
			ra(a, false);
		else
			rra(a, false);
	}
}

void	sort_turk(t_node **a, t_node **b, int len_a) //funcion que ordena cuando tenemos mas de 3 numeros en la pila a
{
	if (len_a-- > 3 && !stack_sorted(*a)) //If stack `a` has more than three nodes and aren't sorted
		pb(b, a, false);
	if (len_a-- > 3 && !stack_sorted(*a)) //If stack `a` still has more than three nodes and aren't sorted
		pb(b, a, false);
	while (len_a-- > 3 && !stack_sorted(*a)) //If stack `a` still has more than three nodes and aren't sorted
	{
		init_nodes_a(*a, *b); //Iniate all nodes from both stacks
		move_a_to_b(a, b); //Move the cheapest `a` nodes into a sorted stack `b`, until three nodes are left in stack `a`
	}
	sort_three(a);
	while (*b) //Until the end of stack `b` is reached
	{
		init_nodes_b(*a, *b); //Initiate all nodes from both stacks
		move_b_to_a(a, b); //Move all `b` nodes back to a sorted stack `a`
	}
	current_index(*a); //Refresh the current position of stack `a`
	min_on_top(a); //Ensure smallest number is on top
}
/*
void	sort_turk(t_node **a, t_node **b, int len_a) //funcion que ordena cuando tenemos mas de 3 numeros en la pila a
{
	//antigua linea porque esto se comprueba en la main: if (len_a-- > 3 && !stack_sorted(*a)) //If stack `a` has more than three nodes and aren't sorted
	//nueva linea:
	while (len_a-- > 3)//lo hacemos hasta que en a solo queden 3 nodos
		pb(b, a, false);//push b y movemos los nodos desde "a" hasta "b"
	sort_three(a); // Ordena los 3 elementos restantes en 'a'
	
	while (*b) // Mueve los nodos de 'b' de vuelta a 'a'
	{
		init_nodes_b(*a, *b);
		move_b_to_a(a, b);
	}
	
	current_index(*a);
	min_on_top(a);
}
*/

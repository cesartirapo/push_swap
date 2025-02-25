/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirapo- <ctirapo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:59:42 by ctirapo-          #+#    #+#             */
/*   Updated: 2025/02/06 18:19:51 by ctirapo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	struct s_node	*target;	
	int	value;
	int	index;
	int	push_cost;
	bool	above_median;
	bool	cheapest;
} t_node;

//***Handle errors
int				error_syntax(char *str_n); 
int				error_duplicate(t_node *a, int n);
void			free_stack(t_node **stack);
void			free_errors(t_node **a);

//***Stack initiation
void			init_stack_a(t_node **a, char **argv); //Initiate stack `a` before processing
char			**split(char *s, char c); //To handle input of numbers as a string argument, e.g. enclosed in " "

//***Nodes initiation
void			init_nodes_a(t_node *a, t_node *b); //To prep all nodes for pushing `a` to `b`
void			init_nodes_b(t_node *a, t_node *b); //To prep all nodes for pushing `b` back to `a`
void			current_index(t_node *stack); //Set the node's current index
void			set_cheapest(t_node *stack); //Set the stack's cheapest node
t_node			*get_cheapest(t_node *stack); //Get the cheapest node of a stack
void			prep_for_push(t_node **s, t_node *n, char c); //Prep the required nodes on top for pushing

//***Stack utils
void			print_piles(t_node *a, t_node *b);//BORRALA
int				stack_len(t_node *stack); //Calculate the length of a stack
t_node			*find_last(t_node *stack); //Find the last node of a stack
bool			stack_sorted(t_node *stack); //To check whether a stack is sorted
t_node			*find_min(t_node *stack); //Find the smallest number
t_node			*find_max(t_node *stack); //Find the biggest number

//***Commands
void			sa(t_node **a, bool print);
void			sb(t_node **b, bool print);
void			ss(t_node **a, t_node **b, bool print);
void			ra(t_node **a, bool print);
void			rb(t_node **b, bool print);
void			rr(t_node **a, t_node **b, bool print);
void			rra(t_node **a, bool print);
void			rrb(t_node **b, bool print);
void			rrr(t_node **a, t_node **b, bool print);
void			pa(t_node **a, t_node **b, bool print);
void			pb(t_node **b, t_node **a, bool print);

//***Algorithm
void			sort_three(t_node **a);
void			sort_turk(t_node **a, t_node **b, int len_a); //Turk algorithm
#endif
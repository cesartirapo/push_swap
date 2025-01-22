/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirapo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:59:42 by ctirapo-          #+#    #+#             */
/*   Updated: 2025/01/22 17:42:43 by ctirapo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdbool.h>
#include <limits.h>
#include <stdio.h>


typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	struct s_node	*target;	
	int	value;
	int	index;
	bool	above_median;
	bool	cheapest;
}t_node;

//Anade las funciones estaticas o globales, es decir las que deben usarse fuera del archivo donde se implementan:
//handle errors
//stack initiation
//nodes initiation
//satck utils
//commands
//algorithms
#endif

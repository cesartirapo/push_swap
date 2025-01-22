/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirapo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:43:24 by ctirapo-          #+#    #+#             */
/*   Updated: 2025/01/22 18:29:06 by ctirapo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_node	*a;
	t_node	*b;
	//ambos punteros se inician en NULL. Aunque aun no se por que.
	if(ac == 1 || (ac == 2 && !av[1][0]))//no carácter que se encuentre en av[1][0]. Tampoco se para que quiero esta comprobacion. Podria comprobar que efectivamente recibo un numero usando atoi.
		return (1);
	else if(argc == 2)//si recibimos dos argumentos es problable que sea un string que contenga varios numeros. Tendremos por tanto que usar split para separarlos y analizarlos.
	av = split(av[1], " ");//extraemos los numeros
	init_stack_a(&a, av + 1);//le enviamos la direccion de la estructura stack a y la direccion del primer argumento despues del nombre del programa.
				 // Esto es necesario porque quieres modificar el valor de a dentro de la función, es decir, modificar el puntero para que apunte a la pila (stack) que estás inicializando.
	if(!stack_sorted(a))//;primero que queremos comprobar es si el stack esta ordenado. Si no lo esta usamos los algoritmos siguientes.
	{
		if(stack_len(a) == 2)//si tenemos solo dos numeros simplemente los swapeamos
			swap(&a, false);
		else if(stack_len(a) == 3)//si tenemos 3 numeros usamos el sort 3 algoritmo 
			sort_three(&a);
		else
			sort_turk(&a, &b);//si tenemos mas de 3 usamos el algoritmo Turk
	}
	free_stack(&a);//finalmente limpiamos la pila.
	return (0);	
}

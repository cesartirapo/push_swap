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
	/*
	Cuando llamas a split(av[1], " "), el arreglo av (que originalmente contenía el nombre del programa y el primer argumento de la línea de comandos) se reemplaza por el arreglo resultante de split. Entonces, si antes de la llamada a split tenías: av = ["./programa", "3 4"] después de la llamada a split, av ahora apunta al nuevo arreglo retornado por split: av = ["", "3", "4", NULL]. En ese caso, av + 1 sería el puntero que apunta a "3", y av[0] sería la cadena vacía "".
	*/
	init_stack_a(&a, av + 1);//inicializamos el stack a con los numeros. Le enviamos la direccion de la estructura stack a y av + 1, que se traduce como un puntero a av[1]. Es decir, av + 1 es un puntero que apunta al segundo elemento de los argumentos, ya que el primero es el program name.
				 //&a: Esto es necesario porque quieres modificar el valor de a dentro de la función, es decir, modificar el puntero para que apunte a la pila (stack) que estás inicializando.
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

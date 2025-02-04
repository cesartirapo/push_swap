/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirapo- <ctirapo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:43:24 by ctirapo-          #+#    #+#             */
/*   Updated: 2025/02/04 15:04:48 by ctirapo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"
int	main(int ac, char **av)
{
	t_node	*a;//a es un puntero a una estructura de tipo t_node
	t_node	*b;
	int	len_a;
	a = NULL;
	b = NULL;
	//ambos punteros se inician en NULL para que las pilas estén vacías.
	if(ac == 1 || (ac == 2 && !av[1][0]))//no carácter que se encuentre en av[1][0]
		return (1);//se envía mensaje de error
	else if(ac == 2)//si recibimos dos argumentos es problable que sea un string que contenga varios numeros. Tendremos por tanto que usar split para separarlos y analizarlos.
		av = split(av[1], ' ');//extraemos los numeros
	/*
	Cuando llamas a split(av[1], " "), asignas el retorno de split directamenete a av. Entonces, av deja de apuntar al arreglo original con los argumentos del programa, sino que pasa a apuntar al arreglo generado por split. Por tanto, el arreglo av (que originalmente contenía el nombre del programa y el primer argumento de la línea de comandos) se reemplaza por el arreglo resultante de split. Entonces, si antes de la llamada a split tenías: av = ["./programa", "3 4"] después de la llamada a split, av ahora apunta al nuevo arreglo retornado por split: av = ["", "3", "4", NULL]. En ese caso, av + 1 sería el puntero que apunta a "3", y av[0] sería la cadena vacía "".
	Nota además que ahora av no apunta al nombre del programa
	*/
	init_stack_a(&a, av + 1);//inicializamos el stack a con los numeros. Le enviamos la direccion de la estructura stack a y av + 1.
	//av + 1 se traduce como un puntero a av[1]. Es decir, av + 1 es un puntero que apunta al segundo elemento del arreglo
	//El primero es o el nombre del programa o, si se uso split, una cadena vacía.
	//&a: Esto es necesario porque quieres modificar el valor de a dentro de la función, es decir, modificar el puntero para que apunte a la pila (stack) que estás inicializando.
	
	//Una vez creada nuestra pila con todos los numeros comprobamos si éstos están ordenados.
	//stack_sorted está en stack_utils.c
	len_a = stack_len(a);
	if(!stack_sorted(a))//;primero que queremos comprobar es si el stack esta ordenado. Si no lo esta usamos los algoritmos siguientes.
	{
		if(len_a == 2)//si tenemos solo dos numeros simplemente los swapeamos
			sa(&a, false);//Aquí enviamos &a porque no es un puntero doble, como sí lo es por ejemplo en la funcion init_stack_a, que envia "a" a otras funciones sin "&"
		//además, al enviar &a a la función sa, estás pasando la dirección de memoria del puntero a, no el contenido de la pila en sí. Esto es necesario porque quieres que la función swap (y por extensión sa) pueda modificar directamente la cabeza de la pila a.
		else if(len_a == 3)//si tenemos 3 numeros usamos el sort 3 algoritmo 
			sort_three(&a);//enviamos la dirección de a para modificar este puntero fuera de la función
		else
			sort_turk(&a, &b, len_a);//si tenemos mas de 3 usamos el algoritmo Turk. Al ser a y b punteros simples, enviamos &a y &b, es decir, las direcciones de los punteros a y b para que puedan ser modificados por las funciones a las que se envian
	}
	free_stack(&a);//finalmente limpiamos la pila.
	return (0);	
}

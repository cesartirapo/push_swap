#include "../../inc/push_swap.h"
static long ft_atol(const char *str)//"static" hace que la función solo pueda ser usada dentro del archivo donde está definida. Nadie fuera de ese archivo puede usarla, aunque esté dentro del mismo programa.
//long es útil si esperas manejar valores enteros más grandes que los que se pueden almacenar en un int
//atol puede recibir numeros mandar un numero mas grande. Sin embargo, a la funcion init_stack no le gustara porque no quiere numeros mas grandes que int_max
{
    int i;
    int sign;
    int result;
    i = 0;
    sign = 1;
    result = 0;
    while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\r' || str[i] == '\f')
        i++;
    if(str[i] == '-' || str[i] == '+')
        {
            if(str[i] == '-')
                sign *= -1;
            i++;
        }
    while(str[i] >= '0' && str[i] <= '9')
    {
        result = str[i] - '0' + (result * 10);
        i++;
    }
    return result * sign;
}

static void append_node(t_node **stack, int n)//static void: no devuelve y tiene alcance local, es decir, solo puede ser llamada desde este archivo
//t_node **stack: un puntero doble a un nodo, que apunta a la cabeza de la pila (o lista enlazada). Inicialmente, el puntero puede ser NULL si la pila está vacía.
//int n: un número entero, que ha sido convertido de una cadena usando ft_atol (función que convierte una cadena a un número entero largo). Este es el valor que se almacenará en el nuevo nodo.
//El propósito de la función es agregar un nuevo nodo con el valor n a la lista enlazada (pila). Si la pila está vacía (si *stack es NULL), se crea el primer nodo y se convierte en la cabeza de la lista. Si la pila ya tiene elementos, el nuevo nodo se agrega al final de la lista.
{
    t_node  *node;
    //t_node  *last_node; esto lo vamos a cambiar de sitio, más abajo, para que solo se cree este nodo cuando la pila no esté vacía. De lo contrario, consume espacio en la memoria inútilmente

    if(!stack)//stack es un puntero doble (t_node **stack). Se comprueba si stack es NULL, lo que significaría que no se ha pasado un puntero válido a la función
        return ;
    node = malloc(sizeof(t_node));//se reserva memoria dinámica para el nuevo nodo de tipo t_node
    if(!node)
        return ;
    //asignamos valores a los campos del nuevo nodo
    node->next = NULL;//esto indica que este nodo es el ultimo de la lista por ahora, porque no apunta a otro nodo.
    node->value = n;//Asigna el valor n al campo nbr del nuevo nodo. Este valor es el número entero que se pasó a la función
    if(!(*stack))//aquí verificamos si la pila está vacía, recuerda que recibe a, y que cuando declaramos a, éste apunta a NULL
    //cuando hayamos creado el primero nodo, stack apunta a este. Por tanto, en la siguiente llamada a la funcion esta condición no se cumple.
    {
        *stack = node;//si esta vacía, entonces asigna el puntero *stack a node, para que el nuevo nodo se convierta en el primer nodo de la lista (la cabeza)
        //stack es un alias para a en la función append_node, por lo que ahora a (fuera de la función) apunta al nuevo nodo creado.
        node->prev = NULL;//como el nuevo nodo es el primero de la lista, no hay nodo anterior a él, su puntero prev se establece en NULL
    }
    else
    {
        //En last_node = find_last(*stack);, la función find_last(*stack) recorre la lista enlazada hasta encontrar el último nodo (el nodo cuyo puntero next es NULL) y devuelve ese nodo.
        //Así, last_node se convierte en un puntero al último nodo de la pila.
        t_node *last_node = find_last(*stack); // NUEVA LINEA. a la funcion find_last le envío un puntero al primer nodo de la pila, es decir, el valor de *stack.
        //last_node = find_last(*stack);ANTIGUA LINEA.
        last_node->next = node;//Así conseguimos que el ultimo nodo de la fila apunte al ultimo creado
        node->prev = last_node;//Aquí lo que hacemos es que el ultimo creado apunte al que era ultimo de la fila
        //De este modo, ambos nodos se estan apuntando, es decir, están doblemente enlazados.
        //el campo next del ultimo nodo es NULL, de acuerdo con la linea 43 de nuestro codigo.
        //el campo previous de nuestro primer nodo es NULL, de acuerdo con la linea 50 de nuestro codigo.
    }
}

void    init_stack_a(t_node **a, char **av)//void indica que no devuelve un valor y que tiene alcance global, pues puede ser llamada desde cualquier parte del programa
/*
El doble asterisco (t_node **a) significa que estamos pasando un puntero a un puntero. Es decir, un puntero que apunta a otro puntero que, a su vez, apunta a la estructura t_node (en este caso, la pila o lista enlazada). El motivo de usar un puntero doble es que queremos modificar el valor del puntero original dentro de la función. Si usáramos solo un puntero (t_node *a), estaríamos trabajando con una copia del puntero original y no podríamos modificar la dirección de memoria a la que apunta el puntero en la función principal. Con el puntero doble, cualquier cambio que hagamos en *a dentro de la función afectará directamente al puntero original fuera de ella. Esto es útil cuando queremos construir o modificar la lista enlazada de manera dinámica dentro de la función.
En relación a char av**, al llamar a init_stack_a(&a, av + 1), se pasa un puntero que apunta al primer número en el arreglo de cadenas, saltándose el primer elemento que es el puntero a la cadena vacía "" generada por split.
*/
{
    long    n;//es un long porque podra almacenar un numero mas grande y mas pequeño que int max y min. Sera el numero devuelto por la funcion atol
    int i;

    i = 0;
    while(av[i])//nos movemos por todos los punteros que apuntan a numeros hasta llegar al puntero que apunta a null
    //Cuando se usa av + 1 al llamar a init_stack_a, estamos pasando un puntero que apunta al segundo elemento del nuevo arreglo generado por split, es decir, el primer numero.
    {
        if(error_syntax(av[i]))//le enviamos a la función error_syntax un string con el numero para comprobar si el numero está bien escrito
            free_errors(a);//si error_syntax nos devuelve 1 entonces llamamos a free_errors para liberar stack a
        n = ft_atol(av[i]);//se llama a atol para convertir la palabra en un numero
        if(n > INT_MAX || n < INT_MIN)//miramos que no sea ni mas grande ni menos que int max y min
            free_errors (a);
        if(error_duplicate(*a, (int)n))//enviamos a la funcion error_duplicate la pila a y el numero para asegurarnos de que el numero no esta ya en la pila ya que nuestro programa no acepta duplicados
            free_errors(a);
        append_node(a, (int)n);//si todo va bien, creamos un nodo con el numero
        //no enviamos &a porque a ya es un puntero doble, es decir, t_node **a, lo que significa que puede modificar directamente dentro de la funcion append_node.
        i++;//parece que nos movemos al siguiente argumento, siguiente numero
        //Una vez que ejecutamos append_node por primera vez creamos el primero nodo con el primer numero y stack, es decir, a, apunta al nodo.
        //Continuamos con el bucle hasta hasta que se añaden todos los numeros en node a, ya que append_node está diseñada para crear nodos de tipo t_node y añadirlos a la lista enlazada, que es la pila representada por el puntero a.
    }
}
/*
En init_stack_a, cada vez que llamamos a otras funciones y enviamos a, a veces enviamos "a" y otras enviamos "*a". A que se debe?
La diferencia entre enviar a y *a depende de lo que queremos hacer con el puntero dentro de la función.
Enviar a (puntero doble t_node **a): Cuando envías a, estás enviando un puntero a un puntero (es decir, un puntero doble). Esto es útil cuando la función necesita modificar la dirección de memoria a la que apunta el puntero original (*a). Por ejemplo, si queremos cambiar la cabeza de la lista, liberar la lista o reasignar *a a otro nodo, necesitamos acceder al puntero original. Esto ocurre en funciones como free_errors, donde modificamos la dirección de memoria de *a.
Enviar *a (puntero simple t_node *a): Cuando envías *a, estás pasando el puntero al primer nodo de la lista (es decir, el valor al que apunta a). Esto es útil cuando solo necesitamos trabajar con los datos o la estructura a la que apunta el puntero. No estamos modificando la dirección de memoria de a, sino que simplemente accedemos o modificamos los nodos de la lista. Esto ocurre en funciones como error_duplicate, que verifican los elementos de la lista sin cambiar la cabeza de la lista.
*/
//Una vez creada nuestra pila con todos los numeros, volvemos a la función main.
t_node	*get_cheapest(t_node *stack) //Define a function that searches for the cheapest node, that is set by bool
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->cheapest)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

void	prep_for_push(t_node **stack,
						t_node *top_node,
						char stack_name) //Define a function that moves the required node to the top of the stack
{
	while (*stack != top_node) //Check if the required node is not already the first node
	{
		if (stack_name == 'a') //If not, and it is stack `a`, execute the following
		{
			if (top_node->above_median)
				ra(stack, false);
			else
				rra(stack, false);
		}
		else if (stack_name == 'b') //If not, and it is stack `b`, execute the following
		{
			if (top_node->above_median)
				rb(stack, false);
			else
				rrb(stack, false);
		}	
	}
}
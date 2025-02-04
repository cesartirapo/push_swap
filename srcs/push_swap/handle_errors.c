#include "../../inc/push_swap.h"
int	error_syntax(char *str_n)
{
	if (!(*str_n == '+'
			|| *str_n == '-'
			|| (*str_n >= '0' && *str_n <= '9'))) //se comprueba que el primer caracter sea un signo o un numero
		return (1);
	if ((*str_n == '+'
			|| *str_n == '-')
		&& !(str_n[1] >= '0' && str_n[1] <= '9')) //Aquí se comprueba que el segundo caracter sea un numero
		return (1);
	while (*++str_n) //Si pasamos los If error conditions anteriores pre incrementamos para pasar al siguiente caracter e iniciamos un bucle para comprobar los demas
	{
		if (!(*str_n >= '0' && *str_n <= '9')) //Comprueba si el caracter no es un número
			return (1);
	}
	return (0);
}

int	error_duplicate(t_node *a, int n) //Define a function that checks for duplicate input numbers in stack `a`
/*
En esta función, a es un puntero a un nodo (t_node *a), lo que significa que a apunta al primer nodo de la pila. No necesitas un puntero doble (t_node **a) porque solo estás leyendo la pila, no modificando el puntero que apunta a la pila en sí.
En resumen, a se pasa como un puntero simple porque solo se va a iterar a través de los nodos, sin cambiar la referencia a la pila. Si se usara **a, sería necesario si se planea modificar el puntero que apunta al primer nodo de la pila.
*/
{
	if (!a) //Si a no apunta a nada, si apunta a NULL
		return (0);
	while (a) //bucle hasta llegar al ultimo nodo
	{
		if (a->value == n) //Miramos si campo value del nodo es distinto de n
			return (1);
		a = a->next; //hacemos que el puntero a ahora apunte al nodo al que apunta el campo next del nodo al que previamente apuntaba a
	}
	return (0);
}

void	free_stack(t_node **stack) //Define una función que libera la memoria de la pila
{
	t_node	*tmp; //es un puntero de uso temporal que apunta al siguiente nodo en la pila antes de que éste se sea liberado, ya que una vez que se libera no se puede acceder al siguiente al que éste apunta
	t_node	*current;

	if (!stack || !*stack) //Si la pila está vacía o el puntero a la pila es NULL
		return ;
	current = *stack; //si la lista no está vacía hacemos que current apunte al primer nodo
	while (current) //siempre que current apunte a un nodo en la lista
	{
		tmp = current->next; //el puntero tmp ahora apunta al que apuntaba current y lo hacemos antes de liberar al puntero current
		current->value = 0; //Es opcional, pero ayuda a detectar accesos a memoria liberada (uso de memoria no válida) y facilita la depuración al hacer que los valores incorrectos sean más evidentes si se accede a la memoria después de free(). Imagina que tienes una hoja de papel con un número escrito. Cuando "liberas" la memoria (usas free()), es como si te dijeran que ya no puedes usar esa hoja. Pero el número sigue ahí hasta que alguien más lo borre o escriba encima. Si antes de soltar la hoja escribes un 0, entonces si por error intentas leer el número después, verás un 0 en vez de otro número viejo. Esto te hará darte cuenta de que ya no deberías estar mirando esa hoja.
		free(current); //liberamos el puntero current que apuntaba al nodo que se va a eliminar, desalocando memoria que ocupaba el nodo
		current = tmp; //asignamos el siguiente nodo, es decir, al que apunta tmp a current
	}
	*stack = NULL; //de este modo, hacemos que el puntero apunte a NULL. Por eso, pasabamos un puntero doble. Esto es útil cuando la función necesita modificar la dirección de memoria a la que apunta el puntero original (*a)
}

void	free_errors(t_node **a) //Define una función que, al encontrar un error, libera la pila y muestra un mensaje de error
{
	free_stack(a); //Llamamos a free_stack para liberar la memoria de la pila
	printf("Error\n"); //Imprimimos el mensaje de error
	exit(1); //termina la ejecución del programa inmediatamente indicando que hubo un error. exit(0) significa termina el programa indicando que finalizo correctamente
}

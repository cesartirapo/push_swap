
#include "push_swap.h"

static long ft_atol(const char *s)//"static" hace que la función solo pueda ser usada dentro del archivo donde está definida. Nadie fuera de ese archivo puede usarla, aunque esté dentro del mismo programa.
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
            if(s[i] == '-')
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

static void append_node(t_node **stack, int n)
{
    t_node  *node;
    t_node  *last_node;

    if(!stack)
        return ;
    node = malloc(sizeof(t_node));
    if(!node)
        return ;
    node->next = NULL;
    node->nbr = n;
    if(!(*stack))
    {
        *stack = node;
        node->prev = NULL;
    }
    else
    {
        last_node = find_last(*stack);
        last_node->next = node;
        node->prev = last_node;
    }
}

void    init_stack_a(t_node **a, char av**)//ENTIENDE MEJOR ESTO!!!!!!!!!
/*
El doble asterisco (t_node **a) significa que estamos pasando un puntero a un puntero. Es decir, un puntero que apunta a otro puntero que, a su vez, apunta a la estructura t_node (en este caso, la pila o lista enlazada). El motivo de usar un puntero doble es que queremos modificar el valor del puntero original dentro de la función. Si usáramos solo un puntero (t_node *a), estaríamos trabajando con una copia del puntero original y no podríamos modificar la dirección de memoria a la que apunta el puntero en la función principal. Con el puntero doble, cualquier cambio que hagamos en *a dentro de la función afectará directamente al puntero original fuera de ella. Esto es útil cuando queremos construir o modificar la lista enlazada de manera dinámica dentro de la función.
En relación a char av**, al llamar a init_stack_a(&a, av + 1), se pasa un puntero que apunta al primer número en el arreglo de cadenas, saltándose el primer elemento que es el puntero a la cadena vacía "" generada por split.
*/
{
    long    n;//es un long porque podra almacenar un numero mas grande y mas pequeño que int max y min. Sera el numero devuelto por la funcion atol
    int i;

    i = 0;
    while(av[i])//nos movemos por todos los punteros que apuntan a numeros hasta llegar al puntero que apunta a null
    //Cuando se usa av + 1 al llamar a init_stack_a, estamos pasando el arreglo que comienza en av[1], por lo que av[1] sería el primer número (por ejemplo, "3") si dividimos la cadena "3 4". Entonces, dentro de av[1], tendríamos el valor "3", y av[i] empezaría en "3" cuando i = 0.
    {
        if(error_syntax(av[i]))//hay que ver que es esto de error_syntax
            free_errors(a);
        n = ft_atol(av[i]);//se llama a atol para convertir la palabra en un numero
        if(n > INT_MAX || n < INT_MIN)//miramos que no sea ni mas grande ni menos que int max y min
            free_errors (a);
        if(error_duplicate(*a, (int)n))//miraremos tambien que no haya numeros que se repitan ya que nuestro programa no acepta duplicados
            free_errors(a);
        append_node(a, (int)n);//si todo va bien, creamos un nodo con el numero
        i++;//parece que nos movemos al siguiente argumento, siguiente numero
        //De esta mmanera, se añaden todos los numeros en node a, ya que append_node está diseñada para crear nodos de tipo t_node y añadirlos a la lista enlazada, que es la pila representada por el puntero a.
    }
}
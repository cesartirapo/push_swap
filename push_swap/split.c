
#include "push_swap.h"

static int	count_words(char *s, char c)
{
	int	word_count;
	int	i;
	
	word_count = 0;
	i = 0;
	while (s[i])
	{
		while(s[i] == c)
			i++;
		if(s[i] != '\0')
		{
			word_count++;
			while (s[i] && s[i]!= c)
				i++;
		}
	}
	return (word_count)
}

static char	*get_next_word(char *s, char c)
{
	static int	i;
	char	*next_word;
	int	start;
	int	len;
	int	j;

	while(s[i] == c)
		i++;
	if(s[i] != '\0')
	{
		start = i;
		while(s[i] && s[i] != c)
			i++;
		len = i - start;
		next_word = malloc((size_t)len * sizeof(char) + 1);
		if(!next_word)
			return(NULL);
		j = 0;
		while(s[start] != c && s[start])
			next_word[j++] = s[start++];
	}
	next_word[j] = '\0';
	return (next_word);
}

char	**split(char *s, char c)
{
	int	word_count;
	char	**result_array;
	int	i;
	
	i = 0;
	word_count = count_words(s, c);
	if(!word_count)//si no ha contado ninguna palabra
		exit(1);//mensaje de error
	result_array = malloc(sizeof(char *) * (size_t)(word_count + 2));//aqui se crea un array de punteros. Lo que no se es porque sumamos dos al numero total de numeros encontrados
	//La creación de un puntero extra tiene sentido, ya que sirve para marcar el final del array y saber dónde detenerse al recorrerlo
	//puedes investigar mas sobre el uso de (size_t), aunque parece que en este ejercicio solo se escribe por buenas practicas
	if(!result_array)
		return (NULL);
	while(word_count >= 0)
	{
		if(i == 0)
		{
			result_array[i] = malloc(sizeof(char));//aqui reservamos memoria para un solo caracter para el primer puntero
			if(!result_array[i])
				return(NULL);
			result_array[i][0] = '\0'; //Decimos que nuestro primer puntero apunte al caracter nulo. De esta manera se inicializa como una cadena vacia.
			i++;
		}
		else
		{
			result_array[i] = get_next_word(s, c);
			i++;
		}
		word_count--; //se decremena word_count al final de cada iteracion
	}
	result_array[i] = NULL;//Si tuvieramos 2 numeros (dos palabras). El primer puntero hemos dicho que apunta al caracter nulo. El segundo y tercer puntero apuntarias a las dos palabras conseguidas co get_next_word.
	//Y el ultimo puntero apuntaria a NULL, lo que indica el final del array de palabras. Por eso reservamos con malloc words_count + 2
	return(result_array);
}

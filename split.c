/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctirapo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:31:11 by ctirapo-          #+#    #+#             */
/*   Updated: 2025/01/22 17:31:46 by ctirapo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	count_words(char *s, char c)
{
	int	count;
	bool	inside_word;
	
	count = 0;
	while (*s)
	{
		inside_word = false;
		while(*s == c)
			++s;
		while (*s != c && *s)
		{
			if(!inside_word)
			{
				++count;
				inside_word = true;
			}
			++s;
		}
	}
	return (count)
}

static char	*get_next_word(char *s, char c)
{
	static int	cursor = 0;//esta variable nos sirve para que cada vez que llamamemos a la funcion, esta continuara desde la posicion del string donde nos quedamos en la llamada anterior a la funcion
	char	*next_word;
	int	len;
	int	i;
	
	len = 0;
	i = 0;
	while(s[cursor] == c)
		++cursor;
	while((s[cursor + len] != c) && s[cursor + len])
		++len;
	next_word = malloc((size_t)len * sizeof(char) + 1);
	if(!next_word)
		return(NULL);
	while((s[cursor] != c) && s[cursor])
		next_word[i++] = s[cursor++];
	next_word[i] = '\0';
	return (next_word);
}

char	**split(char *s, char c)
{
	int	word_count;
	char	**result_array;
	int	i;
	
	i = 0;
	word_count = count_words(s, c);
	if(!word_count)
		exit(1);
	result_array = malloc(sizeof(char *) * (size_t)(words_count + 2));//aqui se crea un array de punteros que apuntan a nodos. Lo que no se es porque sumamos dos al numero total de numeros encontrados
	if(!result_array)
		return (NULL);
	while(word_count-- >= 0)//word_count se reduce una vez y despues con cada iteracion
	{
		if(i == 0)
		{
			result_array[i] = malloc(sizeof(char));//aqui reservamos memoria para el numero de caracteres que tiene la palabra
			if(!result_array[i]
				return(NULL);
			result_array[i++][0] = '\0';
			continue ;
		}
		result_array[i++] = get_next_word(s, c);
	}
	result_array[i] = NULL;
	return(result_array);
}

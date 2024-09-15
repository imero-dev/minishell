/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_spliter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:08:05 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/14 23:22:59 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	find_next_word(const char **str_ptr, int *word_count)
{
	(*word_count)++;
	while (**str_ptr != ' ' && **str_ptr != '\0')
		(*str_ptr)++;
}

static int	count_words(const char *str)  // FIXME esto no es buena idea, mejor usar ft_realloc dinamicamente
{
	int		word_count;
	bool	in_quotes;

	word_count = 0;
	in_quotes = false;
	while (*str)
	{
		if (*str == '"' || *str == '\'') // TODO comprobar que son las mismas comillas, ahora abre con " y cierra con ' por ejemplo
		{
			if (!in_quotes)
				word_count++;
			in_quotes = !in_quotes;
			str++;
		}
		else if (*str != ' ' && *str != '\0' && !in_quotes)
			find_next_word(&str, &word_count);
		else
			str++;
	}
	if (in_quotes)
	{
		printf("unexpected EOF while looking for matching \"\'\n"); // FIXME no deberia hacer esto
		return (0);
	}
	return (word_count);
}
*/
static void	find_next_word(const char **str_ptr, int *word_count, char quote_char)
{
	(*word_count)++;
	while (**str_ptr != ' ' && **str_ptr != '\0' && **str_ptr != quote_char)
		(*str_ptr)++;
}	

static int	count_words(const char *str)  // FIXME esto no es buena idea, mejor usar ft_realloc dinamicamente
{
	int		word_count;
	bool	in_quotes;
	char	quote_char;

	word_count = 0;
	in_quotes = false;
	quote_char = '\0';
	while (*str)
	{
		if ((*str == '"' || *str == '\'') && quote_char == '\0')
		{
			in_quotes = true;
			quote_char = *str;
			str++;
		}
		else if (*str == quote_char && in_quotes)
		{
			in_quotes = false;
			quote_char = '\0';
			word_count ++;
			str++;
		}
		else if (*str != ' ' && *str != '\0' && !in_quotes)
			find_next_word(&str, &word_count, quote_char);
		else
			str++;
	}
	if (in_quotes)
	{
		ft_perror("minishell: unexpected EOF while looking for matching quotes", 0);
		return (0);
	}
	return (word_count);
}

static int	word_length(const char *str)// TODO recibir quote_char y devolver hasta la siguiente quote_char sino -1 y ¿HEREDOC?
{
	int		len;
	bool	in_quotes;
	char	quote_char;

	len = 0;
	in_quotes = false;
	quote_char = '\0';
	if (*str == '"' || *str == '\'')
	{
		in_quotes = true;
		quote_char = *str;
		str++;
		len++;
	}
	while (*str != '\0' && (in_quotes || *str != ' '))
	{
		if (*str == quote_char && in_quotes)
		{
			in_quotes = false; // ???
			len++;
			str++; // sobra
			break ;
		}
		len++;
		str++;
	}
	return (len);
}

void	expand_env(char **word)
{
	char	*var_name;
	char	*var_value;
	char	buffer[1024]; //  TODO # define MAX_WORD_LENGTH 1024
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	ft_bzero(buffer, 1024);
	while ((*word)[i])
	{
		if ((*word)[i] == '$' && (ft_isalnum((*word)[i + 1]) ||
			(*word)[i + 1] == '_' || (*word)[i + 1] == '?'))
		// && (*word)[i + 1] != '"' && (*word)[i + 1] != '\'')
		{
			j = ++i;
			while ((*word)[i] && (ft_isalnum((*word)[i]) || (*word)[i] == '_'))
				i++;
			if ((*word)[i] == '?')
				i++;
			var_name = ft_substr(*word, j, i - j);
			if (var_name[0] == '?')
				var_value = ft_itoa(get_data()->last_exit_status);
			else
				var_value = env_get(var_name);
			if (var_value)
			{
				j = 0;
				while (var_value[j])
					buffer[k++] = var_value[j++];
				//if (var_name[0] == '?') //not with env_get
					//free(var_value); 
			}
			free(var_name);
		}
		else
			buffer[k++] = (*word)[i++];
	}
	*word = ft_strdup(buffer);
}

// TODO funcion que extraiga el texto entre comillas y lo devuelva

char *extract_quotes(const char *str, char quote_char)
{
	int		len;
	char	*result;

	len = 0;
	while (str[len] != quote_char && str[len] != '\0')
		len++;
	if (str[len] == '\0')
		return (NULL);
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, len + 1);
	return (result);
}
// TODO Preguntar a GPT con "Actua como un programador experto en C, revisa el código y arregla el fallo por el que el programa hace esto y quiero que haga esto otro ....."
static char	*copy_word(const char **str_ptr, int index, char ***result_array)// FIXME comillas pegadas word_length deberia acabar en la comilla y luego si hay comillas seguido repetir
{
	int		len;
	char	quote_char;

	while (**str_ptr == ' ') 
		(*str_ptr)++;
	len = word_length(*str_ptr);
	if (len == 0)
		return (ft_strdup(""));
	quote_char = '\0';
	if (**str_ptr == '"' || **str_ptr == '\'')// FIXME las comillas pueden estar en cualquier parte del string
	{
		quote_char = **str_ptr;
		(*str_ptr)++;
		len -= 2;
	}
	(*result_array)[index] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!(*result_array)[index])
	{
		ft_array_free(*result_array);
		return (NULL);
	}
	// FIXME copiar por partes, primero hasta la comilla, luego el contenido de la comilla y luego lo que queda
	ft_strlcpy((*result_array)[index], *str_ptr, len + 1);
	if (quote_char != '\'')
		expand_env(&(*result_array)[index]);
	*str_ptr += len;
	return ((*result_array)[index]);
}

char	**syntax_spliter(const char *str)
{
	int		index;
	char	*word;
	int		word_count;
	char	**result;

	index = 0;
	word = NULL;
	if (!str)
		return (NULL);
	word_count = count_words(str);
	if (!word_count)
		return (NULL);
	result = (char **)ft_calloc(word_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (index < word_count)
	{
		word = copy_word(&str, index++, &result);
		if (word == NULL)
		{
			ft_array_free(result);
			return (NULL);
		}
/* 		if (word[0] == '\0') // FIXME sobra, las cadenas vacias cuentan como argumentos
			{
				index--;
				word_count--;
				free(word);
				result[index] = NULL;
			} */
	}
	return (result);
}

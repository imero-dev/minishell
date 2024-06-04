/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_spliter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:08:05 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/04 15:16:42 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_next_word(const char **str_ptr, int *word_count)
{
	(*word_count)++;
	while (**str_ptr != ' ' && **str_ptr != '\0')
		(*str_ptr)++;
}

static int	count_words(const char *str)
{
	int		word_count;
	bool	in_quotes;

	word_count = 0;
	in_quotes = false;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
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
		printf("unexpected EOF while looking for matching \"\'\n");
		return (0);
	}
	return (word_count);
}

static int	word_length(const char *str)
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
			in_quotes = false;
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
	char	buffer[1024]; // # define MAX_WORD_LENGTH 1024
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	ft_bzero(buffer, 1024);
	while ((*word)[i])
	{
		if ((*word)[i] == '$' && (*word)[i + 1] != '\0' && (*word)[i
			+ 1] != ' ')
		// && (*word)[i + 1] != '"' && (*word)[i + 1] != '\'')
		{
			j = ++i;
			while ((*word)[i] && ft_isalnum((*word)[i]))
				i++;
			if ((*word)[i] == '?')
				i++;
			var_name = ft_substr(*word, j, i - j);
			if (var_name[0] == '?')
				var_value = ft_itoa(get_data()->last_exit_status);
			else
				var_value = getenv(var_name);
			if (var_value)
			{
				j = 0;
				while (var_value[j])
					buffer[k++] = var_value[j++];
				if (var_name[0] == '?')
					free(var_value);
			}
			free(var_name);
		}
		else
			buffer[k++] = (*word)[i++];
	}
	*word = ft_strdup(buffer);
}

static char	*copy_word(const char **str_ptr, int index, char ***result_array)
{
	int		len;
	char	quote_char;

	while (**str_ptr == ' ')
		(*str_ptr)++;
	len = word_length(*str_ptr);
	if (len == 0)
		return (NULL);
	quote_char = '\0';
	if (**str_ptr == '"' || **str_ptr == '\'')
	{
		quote_char = **str_ptr;
		(*str_ptr)++;
		len -= 2;
	}
	(*result_array)[index] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!(*result_array)[index])
	{
		ft_arrayfree(*result_array);
		return (NULL);
	}
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
			ft_arrayfree(result);
			return (NULL);
		}
		if (word[0] == '\0')
			{
				index--;
				word_count--;
				free(word);
				result[index] = NULL;
			}
	}
	return (result);
}

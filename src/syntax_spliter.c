/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_spliter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:08:05 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/28 01:22:28 by ivromero         ###   ########.fr       */
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

static char	*copy_word(const char **str_ptr, int index, char ***result_array)
{
	int		len;
	//char	quote_char;

	while (**str_ptr == ' ')
		(*str_ptr)++;
	len = word_length(*str_ptr);
	if (len == 0)
		return (NULL);
	//quote_char = '\0';
	if (**str_ptr == '"' || **str_ptr == '\'')
	{
		//quote_char = **str_ptr;
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
/* 	if (quote_char != '\'')
		expand_env(&(*result_array)[index]); */
		// split by "$VAR" and join with the value of var as glue with ft_strjoin_glue()
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
	}
	return (result);
}

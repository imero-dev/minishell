/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_spliter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:08:05 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/28 23:57:09 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	process_quotes(char c, t_spliterdata *data)
{
	if (c == '\'' && !data->in_double_quote)
	{
		data->in_single_quote = !data->in_single_quote;
		data->i++;
		data->expand_env = false;
		data->quoted_token = true;
		return (true);
	}
	else if (c == '\"' && !data->in_single_quote)
	{
		data->in_double_quote = !data->in_double_quote;
		data->i++;
		data->quoted_token = true;
		return (true);
	}
	return (false);
}

static bool	end_token(t_spliterdata *data)
{
	if (data->token_length > 0 || data->quoted_token)
	{
		data->quoted_token = false;
		data->current_token[data->token_length] = '\0';
		if (data->expand_env)
			expand_env(&(data->current_token), 0, 0);
		data->tokens = ft_add_to_array(data->tokens, &(data->tokens_size),
				data->current_token);
		if (!data->tokens)
		{
			free(data->current_token);
			return (false);
		}
		data->token_capacity = 64;
		data->current_token = malloc(data->token_capacity);
		if (!data->current_token)
		{
			ft_array_free(data->tokens);
			return (false);
		}
		data->token_length = 0;
	}
	return (true);
}

static bool	append_char_to_token(char c, t_spliterdata *data)
{
	char	*temp;

	if (data->token_length + 1 >= data->token_capacity)
	{
		data->token_capacity *= 2;
		temp = ft_realloc(data->current_token, data->token_capacity / 2,
				data->token_capacity);
		if (!temp)
		{
			free(data->current_token);
			ft_array_free(data->tokens);
			return (false);
		}
		data->current_token = temp;
	}
	data->current_token[data->token_length++] = c;
	return (true);
}

bool	handle_eof(t_spliterdata *data)
{
	if (data->token_length > 0 || data->tokens == 0 || data->quoted_token)
	{
		data->current_token[data->token_length] = '\0';
		if (data->expand_env)
			expand_env(&(data->current_token), 0, 0);
		data->tokens = ft_add_to_array(data->tokens, &(data->tokens_size),
				data->current_token);
		if (!data->tokens)
		{
			free(data->current_token);
			return (false);
		}
	}
	else
	{
		free(data->current_token);
	}
	return (true);
}

char	**syntax_spliter(const char *str)
{
	t_spliterdata	data;
	char			c;

	if (!initialize_data(&data, str))
		return (NULL);
	while (data.i < data.len)
	{
		c = str[data.i];
		if (process_quotes(c, &data))
			continue ;
		else if (isspace(c) && !data.in_single_quote && !data.in_double_quote)
		{
			if (!end_token(&data))
				return (NULL);
		}
		else
		{
			if (!append_char_to_token(c, &data))
				return (NULL);
		}
		data.i++;
	}
	if (!handle_eof(&data) || !check_unbalanced_quotes(&data))
		return (NULL);
	return (data.tokens);
}

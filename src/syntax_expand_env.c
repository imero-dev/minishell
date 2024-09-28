/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_expand_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:35 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/28 23:07:50 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_var_start(char *token, int i)
{
	return (token[i] == '$' && (ft_isalnum(token[i + 1]) || token[i + 1] == '_'
			|| token[i + 1] == '?'));
}

static char	*get_var_name(char *token, int *i)
{
	int		end;
	char	*var_name;
	int		start;

	start = ++(*i);
	end = start;
	if (token[end] == '?')
	{
		(*i)++;
		return (ft_substr(token, start, 1));
	}
	while (token[end] && (ft_isalnum(token[end]) || token[end] == '_'))
		end++;
	var_name = ft_substr(token, start, end - start);
	*i = end;
	return (var_name);
}

static char	*get_var_value(char *var_name)
{
	char	*var_value;
	char	*env_value;

	if (var_name[0] == '?' && var_name[1] == '\0')
		var_value = ft_itoa(get_data()->last_exit_status);
	else
	{
		env_value = env_get(var_name);
		if (env_value)
			var_value = ft_strdup(env_value);
		else
			var_value = NULL;
	}
	return (var_value);
}

static void	copy_var_value_to_buffer(char *var_value, char *buffer, int *k)
{
	int	j;

	j = 0;
	while (var_value[j])
		buffer[(*k)++] = var_value[j++];
}

void	expand_env(char **token, int i, int k)
{
	char	*var_name;
	char	*var_value;
	char	buffer[MAX_TOKEN_LENGTH];

	ft_bzero(buffer, MAX_TOKEN_LENGTH);
	while ((*token)[i])
	{
		if (is_var_start(*token, i))
		{
			var_name = get_var_name(*token, &i);
			var_value = get_var_value(var_name);
			if (var_value)
			{
				copy_var_value_to_buffer(var_value, buffer, &k);
				free(var_value);
			}
			free(var_name);
		}
		else
			buffer[k++] = (*token)[i++];
	}
	buffer[k] = '\0';
	free(*token);
	*token = ft_strdup(buffer);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_expand_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:43:35 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/27 00:10:44 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prototipos de las funciones auxiliares
static bool	is_var_start(char *token, int i);
static char	*get_var_name(char *token, int *i);
static char	*get_var_value(char *var_name);
static void	copy_var_value_to_buffer(char *var_value, char *buffer, int *k);

void	expand_env(char **token, int i, int k)
{
	char	*var_name;
	char	*var_value;
	char	buffer[MAX_WORD_LENGTH];

	ft_bzero(buffer, MAX_WORD_LENGTH);
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

// OlD CODE
/*
void	expand_env(char **token)
{
	char	*var_name;
	char	*var_value;
	int		i;
	int		j;
	int		k;

	char buffer[1024]; //  TODO # define MAX_WORD_LENGTH 1024
	i = 0;
	j = 0;
	k = 0;
	ft_bzero(buffer, 1024);
	while ((*token)[i])
	{
		if ((*token)[i] == '$' && (ft_isalnum((*token)[i + 1]) || (*token)[i
				+ 1] == '_' || (*token)[i + 1] == '?'))
		// && (*token)[i + 1] != '"' && (*token)[i + 1] != '\'')
		{
			j = ++i;
			while ((*token)[i] && (ft_isalnum((*token)[i])
					|| (*token)[i] == '_'))
				i++;
			if ((*token)[i] == '?')
				i++;
			var_name = ft_substr(*token, j, i - j);
			if (var_name[0] == '?')
				var_value = ft_itoa(get_data()->last_exit_status);
			else
				var_value = env_get(var_name);
			if (var_value)
			{
				j = 0;
				while (var_value[j])
					buffer[k++] = var_value[j++];
				// if (var_name[0] == '?') //not with env_get
				// free(var_value);
			}
			free(var_name);
		}
		else
			buffer[k++] = (*token)[i++];
	}
	*token = ft_strdup(buffer);
}
 */
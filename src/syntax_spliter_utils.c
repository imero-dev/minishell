/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_spliter_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:48:39 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/24 01:02:30 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	initialize_data(t_spliterdata *data, const char *str)
{
	ft_bzero(data, sizeof(t_spliterdata));
	data->len = strlen(str);
	data->token_capacity = 64;
	data->expand_env = true;
	data->current_token = malloc(data->token_capacity);
	if (data->current_token)
		data->current_token[0] = '\0';
	if (!data->current_token)
		return (0);
	return (1);
}

char	**ft_add_to_array(char **tokens, size_t *size, char *new_token)
// TODO LIBFT
{
	char **new_array;

	new_array = realloc(tokens, sizeof(char *) * (*size + 2));
	// FIXME ft_realloc
	if (!new_array)
	{
		free(new_token);
		return (NULL);
	}
	new_array[*size] = new_token;
	new_array[*size + 1] = NULL;
	(*size)++;
	return (new_array);
}

bool	check_unbalanced_quotes(t_spliterdata *data)
{
	if (data->in_single_quote || data->in_double_quote)
	{
		ft_array_free(data->tokens);
		ft_printf("%!minishell: unexpected EOF while looking for matching `%c'\n",
			data->in_single_quote * '\'' + data->in_double_quote * '\"');
		return false;
	}
	return true;
}

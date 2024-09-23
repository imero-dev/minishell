/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_classify_tokens.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 01:11:13 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/23 04:55:03 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect_operator(const char *arg)
{
	if (!arg)
		return (0);
	return (ft_strcmp(arg, "<") == 0 || ft_strcmp(arg, "<<") == 0
		|| ft_strcmp(arg, ">") == 0 || ft_strcmp(arg, ">>") == 0);
}

static void	count_args_and_redirects(t_commandlist *command, int *num_args,
		int *num_redirects)
{
	int	i;

	i = 0;
	*num_args = 0;
	*num_redirects = 0;
	while (command->tokens[i])
	{
		if (is_redirect_operator(command->tokens[i]))
		{
			(*num_redirects)++;
			if (command->tokens[i + 1])
			{
				(*num_redirects)++;
				i++;
			}
			else
			{
				command->syntax_error = 1;
				return ;
			}
		}
		else
			(*num_args)++;
		i++;
	}
}

// Función para asignar memoria para los nuevos arrays
static int	allocate_new_arrays(t_commandlist *command, int num_args,
		int num_redirects)
{
	command->args = ft_calloc((num_args + 1), sizeof(char *));
	if (!command->args)
		return (0);
	command->redirects = ft_calloc((num_redirects + 1), sizeof(char *));
	if (!command->redirects)
	{
		free(command->args);
		return (0);
	}
	return (1);
}

// Función para separar argumentos y redirecciones
static void	separate_args_and_redirects(t_commandlist *command)
{
	int	arg_index;
	int	redirect_index;
	int	i;

	arg_index = 0;
	redirect_index = 0;
	i = 0;
	while (command->tokens[i])
	{
		if (is_redirect_operator(command->tokens[i]))
		{
			command->redirects[redirect_index++]
				= ft_strdup(command->tokens[i]);
			command->redirects[redirect_index++]
				= ft_strdup(command->tokens[i + 1]);
			i++;
		}
		else
			command->args[arg_index++] = ft_strdup(command->tokens[i]);
		i++;
	}
	command->args[arg_index] = NULL;
	command->redirects[redirect_index] = NULL;
	free(command->tokens);
}

// Función principal para encontrar y separar argumentos y redirecciones
void	classify_tokens(t_commandlist *command)
{
	int	num_args;
	int	num_redirects;

	command->syntax_error = 0;
	count_args_and_redirects(command, &num_args, &num_redirects);
	if (command->syntax_error)
	{
		ft_printf("%!minishell: syntax error specting"
			" file name or here document");
		get_data()->last_exit_status = 2;
		return ;
	}
	if (!allocate_new_arrays(command, num_args, num_redirects))
	{
		perror("minishell: malloc failed");
		exit_shell(NULL, 1);
	}
	separate_args_and_redirects(command);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:58:42 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/28 17:25:43 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_empty_command(void)
{
	ft_perror("minishell: command not found\n", 0);
	get_data()->last_exit_status = 127;
	return (NULL);
}

char	*find_command(char *command)
{
	if (!command || command[0] == '\0')
		return (handle_empty_command());
	if (ft_strchr(command, '/'))
		return (handle_absolute_path(command));
	return (search_in_path(command));
}

int	add_command(char **tokens)
{
	t_data			*data;
	t_commandlist	*new_command;
	t_commandlist	*last_command;

	data = get_data();
	new_command = ft_calloc(1, sizeof(t_commandlist));
	if (!new_command)
		return (0);
	new_command->tokens = tokens;
	classify_tokens(new_command);
	if (!data->commandlist)
	{
		data->commandlist = new_command;
		return (1);
	}
	last_command = data->commandlist;
	while (last_command->next)
		last_command = last_command->next;
	last_command->next = new_command;
	return (1);
}

void	free_commandlist(t_commandlist **commandlist)
{
	t_commandlist	*current;
	t_commandlist	*next;

	current = *commandlist;
	while (current)
	{
		next = current->next;
		if (current->command)
			free(current->command);
		//if (current->args && current->args[0])
		//	ft_array_free(current->args);
		if (current->redirects)
			free(current->redirects);
		free(current);
		current = next;
	}
	*commandlist = NULL;
}

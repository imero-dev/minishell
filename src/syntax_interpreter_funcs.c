/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_interpreter_funcs.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:52:20 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/29 00:55:06 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(char **tokens)
{
	int	cmd_count;
	int	i;

	cmd_count = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			cmd_count++;
		i++;
	}
	return (cmd_count + 1);
}

char	***allocate_commands(int cmd_count)
{
	char	***commands;

	commands = malloc(sizeof(char **) * (cmd_count + 1));
	if (!commands)
		return (NULL);
	commands[cmd_count] = NULL;
	return (commands);
}

void	free_commands_on_error(char ***commands, int cmd)
{
	while (cmd > 0)
	{
		cmd--;
		ft_array_free(commands[cmd]);
	}
	free(commands);
}

char	**copy_command_tokens(char **tokens, int cmd_start, int cmd_length)
{
	char	**command_tokens;
	int		j;

	command_tokens = malloc(sizeof(char *) * (cmd_length + 1));
	if (!command_tokens)
		return (NULL);
	j = 0;
	while (j < cmd_length)
	{
		command_tokens[j] = ft_strdup(tokens[cmd_start + j]);
		if (!command_tokens[j])
		{
			ft_array_free(command_tokens);
			return (NULL);
		}
		j++;
	}
	command_tokens[cmd_length] = NULL;
	return (command_tokens);
}

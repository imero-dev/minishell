/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:39:44 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/28 21:21:09 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	***group_tokens_by_pipe(char **tokens)
{
	char	***commands;
	int		cmd_count;
	int		i;
	int		cmd_start;
	int		cmd_length;

	commands = NULL;
	cmd_count = 0;
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			cmd_count++;
		i++;
	}
	cmd_count++;
	commands = malloc(sizeof(char **) * (cmd_count + 1));
	if (!commands)
		return (NULL);
	commands[cmd_count] = NULL;
	i = 0;
	for (int cmd = 0; cmd < cmd_count; cmd++)
	{
		cmd_start = i;
		cmd_length = 0;
		while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
		{
			cmd_length++;
			i++;
		}
		commands[cmd] = malloc(sizeof(char *) * (cmd_length + 1));
		if (!commands[cmd])
		{
			while (cmd > 0)
			{
				cmd--;
				ft_array_free(commands[cmd]);
			}
			free(commands);
			return (NULL);
		}
		for (int j = 0; j < cmd_length; j++)
			commands[cmd][j] = ft_strdup(tokens[cmd_start + j]);
		commands[cmd][cmd_length] = NULL;
		if (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
			i++;
	}
	return (commands);
}

void	interpreter(char *line)
{
	char	**tokens;
	char	***commands;
	int		i;

	if (!line || ft_strlen(line) == 0)
		return ;
	tokens = syntax_spliter(line);
	if (!tokens)
	{
		get_data()->last_exit_status = 2;
		return ;
	}
	commands = group_tokens_by_pipe(tokens);
	if (!commands)
	{
		ft_array_free(tokens);
		get_data()->last_exit_status = 2;
		return ;
	}
	i = 0;
	while (commands[i])
	{
		if (commands[i][0] == NULL)
		{
			get_data()->last_exit_status = 2;
			ft_perror("minishell: syntax error near unexpected token `|'", 0);
			ft_array_free(tokens);
			ft_matrix_free(commands);
			return ;
		}
		if (!add_command(commands[i]))
		{
			ft_perror("minishell: syntax error", 0);
			ft_array_free(tokens);
			ft_matrix_free(commands);
			return ;
		}
		i++;
	}
	ft_array_free(tokens);
	ft_matrix_free(commands);
	run_commands();
}

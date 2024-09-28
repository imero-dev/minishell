/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:39:44 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/29 00:54:16 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	***group_tokens_by_pipe(char **tokens, char ***commands,
		int cmd_count)
{
	int	i;
	int	cmd_start;
	int	cmd_length;
	int	cmd;

	if (!commands)
		return (NULL);
	i = 0;
	cmd = -1;
	while (++cmd < cmd_count)
	{
		cmd_start = i;
		cmd_length = 0;
		while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
		{
			cmd_length++;
			i++;
		}
		commands[cmd] = copy_command_tokens(tokens, cmd_start, cmd_length);
		if (!commands[cmd])
			return (free_commands_on_error(commands, cmd), NULL);
		if (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
			i++;
	}
	return (commands);
}

static int	handle_empty_line(char *line)
{
	if (!line || ft_strlen(line) == 0)
		return (1);
	return (0);
}

static int	handle_syntax_error(char **tokens)
{
	get_data()->last_exit_status = 2;
	ft_array_free(tokens);
	return (1);
}

static int	process_commands(char ***commands, char **tokens)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (commands[i][0] == NULL)
		{
			get_data()->last_exit_status = 2;
			ft_perror("minishell: syntax error near unexpected token `|'", 0);
			ft_array_free(tokens);
			ft_matrix_free(commands);
			return (1);
		}
		if (!add_command(commands[i]))
		{
			ft_perror("minishell: syntax error", 0);
			ft_array_free(tokens);
			ft_matrix_free(commands);
			return (1);
		}
		i++;
	}
	return (0);
}

void	interpreter(char *line)
{
	char	**tokens;
	char	***commands;

	if (handle_empty_line(line))
		return ;
	tokens = syntax_spliter(line);
	if (!tokens)
	{
		get_data()->last_exit_status = 2;
		return ;
	}
	commands = group_tokens_by_pipe(tokens,
			allocate_commands(count_commands(tokens)), count_commands(tokens));
	if (!commands)
	{
		handle_syntax_error(tokens);
		return ;
	}
	if (process_commands(commands, tokens))
		return ;
	ft_array_free(tokens);
	ft_matrix_free(commands);
	run_commands();
}

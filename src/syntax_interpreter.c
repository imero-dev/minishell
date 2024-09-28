/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_interpreter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:39:44 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/28 14:40:37 by ivromero         ###   ########.fr       */
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
	// Contar el número de comandos separados por '|'
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
			cmd_count++;
		i++;
	}
	cmd_count++; // Número de comandos es número de '|' + 1
	// Asignar memoria para los comandos
	commands = malloc(sizeof(char **) * (cmd_count + 1));
	if (!commands)
		return (NULL);
	commands[cmd_count] = NULL;
	// Agrupar los tokens en comandos
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
		// Asignar memoria para los tokens del comando
		commands[cmd] = malloc(sizeof(char *) * (cmd_length + 1));
		if (!commands[cmd])
		{
			// Liberar memoria en caso de error
			while (cmd > 0)
			{
				cmd--;
				ft_array_free(commands[cmd]);
			}
			free(commands);
			return (NULL);
		}
		// Copiar los tokens al comando
		for (int j = 0; j < cmd_length; j++)
			commands[cmd][j] = ft_strdup(tokens[cmd_start + j]);
		commands[cmd][cmd_length] = NULL;
		// Si el token actual es '|', saltarlo
		if (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
			i++;
	}
	return (commands);
}

// Función principal para interpretar la línea de entrada
void	interpreter(char *line)
{
	char **tokens;
	char ***commands;
	int i;

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
			//ft_array_free(commands[i]);
			ft_matrix_free(commands);
			return ;
		}
		if (!add_command(commands[i]))
		{
			ft_perror("minishell: syntax error", 0);
			//ft_array_free(commands[i]);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:50:54 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/28 02:53:14 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	garbage_collector(void)
{
	t_data	*data;

	data = get_data();
	ft_free(&data->last_line);
}

void	interpreter(char *line)
{
	char	**words;

	if (ft_strlen(line) == 0)
		return ;
	words = syntax_spliter(line);
	if (words == NULL || words[0] == NULL || words[0][0] == '\0')
	{
		printf(RED "NULL recieved from syntax_spliter()\n" NC);
		return ;
	}
	if (ft_strcmp(words[0], "exit") == 0)
	{
		ft_arrayfree(words);
		exit_shell(0);
	}
	if (ft_strcmp(words[0], "pwd") == 0)
		com_pwd();
	else if (ft_strcmp(words[0], "cd") == 0)
		com_cd(words[1]);
	else if (ft_strcmp(words[0], "echo") == 0)
		ft_echo(words);
	else
		printf("%s: command not found\n", words[0]);
	if (DEBUG)
	{
		execute_on_bash(line);
		print_words(words);
	}
	ft_arrayfree(words);
}

int	main(void)
{
	t_data	*data;

	data = get_data();
	signal(SIGINT, handle_sigint);   // Ctrl+C
	signal(SIGQUIT, handle_sigquit); // Ctrl+\ (Ctrl+Ç)
	data->last_line = ft_strdup("");
	while (1)
	{
		data->line = readline(ft_strjoinfree1(ft_strjoinfree2(GREEN "user@localhost" NC ":" BLUE,
						get_actual_dir()), NC"$ "));//free
		if (data->line == NULL)       // Ctrl+D
			if (isatty(STDIN_FILENO)) // Solo salir si es terminal interactivo
			{
				rl_free_line_state();
				exit_shell(NULL);
			}
		if (ft_strcmp(data->line, data->last_line) != 0)
			add_history(data->line);
		interpreter(data->line);
		ft_free(&data->last_line);
		data->last_line = data->line;
	}
	return (0);
}

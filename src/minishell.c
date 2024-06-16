/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:50:54 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/15 06:10:59 by ivromero         ###   ########.fr       */
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
	ft_free(&data->line);
	ft_free(&data->prompt);
	free_envlist(data->env_vars);
}

void	interpreter(char *line)
{
	char	**words;

	if (!line || ft_strlen(line) == 0)
		return ;
	words = syntax_spliter(line);
	if (words == NULL || words[0] == NULL || words[0][0] == '\0')
	{
		// printf(RED "NULL recieved from syntax_spliter()\n" NC);
		return ;
	}
	if(!add_command(words, NULL))
		{
			ft_perror("minishell: syntax error", 0);// ? imprimir error 
			ft_array_free(words);
			return;
		}
	run_commands();
	if (DEBUG)
		execute_on_bash(line);
	if (DEBUG)
		print_words(words);
	free_commandlist(&get_data()->commandlist);
}

int	main(int argc, char **argv, char **enviroment)
{
	t_data	*data;

	if (argc > 1 || argv[1])
		ft_perror("To many arguments", 0);
	data = get_data();
	signal(SIGINT, handle_sigint);   // Ctrl+C
	signal(SIGQUIT, handle_sigquit); // Ctrl+\ (Ctrl+Ç)
										//	signal(SIGTERM, handle_sigint); 
												// kill
	data->last_line = ft_strdup("");
	data->env_vars = env_initializer(enviroment);
	data->prompt = ft_strjoinfree1(ft_strjoinfree2(GREEN "user@localhost" NC ":" BLUE,
				get_actual_dir()), NC "$ ");
	while (1)
	{
		//ft_free(&data->prompt);
		//data->prompt = ft_strjoinfree1(ft_strjoinfree2(GREEN "user@localhost" NC ":" BLUE,
		//		get_actual_dir()), NC "$ ");
		data->line = readline(data->prompt); // TODO free
		if (data->line == NULL)              // Ctrl+D
												// if (isatty(STDIN_FILENO))
													// Solo salir si es terminal interactivo
													// TODO revisar
			exit_shell(NULL, 0);
		// printf("%c\n", data->line[0]);
		if (ft_strcmp(data->line, data->last_line) != 0)
			add_history(data->line);
		interpreter(data->line);
		ft_free(&data->last_line);
		data->last_line = data->line;
	}
	return (0);
}

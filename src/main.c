/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:50:54 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/13 17:19:46 by iker_bazo        ###   ########.fr       */
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
}

void	interpreter(char *line, t_envlist *env_vars)
{
	char	**words;
	int		exit_status;// move to exit_func

	if (!line || ft_strlen(line) == 0)
		return ;
	words = syntax_spliter(line);
	if (words == NULL || words[0] == NULL || words[0][0] == '\0')
	{
		//printf(RED "NULL recieved from syntax_spliter()\n" NC);
		return ;
	}
	if (ft_strcmp(words[0], "exit") == 0)
	{
		if (words[1] == NULL)
			exit_status = 0;
		else
			exit_status = ft_atoi(words[1]);
		ft_arrayfree(words);
		free_envlist(env_vars);
		exit_shell("exit", exit_status);
	}
	if (ft_strcmp(words[0], "pwd") == 0)
		com_pwd();
	else if (ft_strcmp(words[0], "cd") == 0)
		com_cd(words[1]);
	else if (ft_strcmp(words[0], "echo") == 0)
		ft_echo(words);
	else if (ft_strcmp(words[0], "env") == 0)
		env_writer(env_vars);
	else if (ft_strchr(words[0],'='))
		add_env(&env_vars,new_env(env_name(words[0]),env_value(words[0]),false));
	else if (ft_strcmp(words[0], "export") == 0)
		export(env_vars,words);
	else if (ft_strcmp(words[0], "unset") == 0)
		unset(env_vars,words);
	else if (ft_strnstr(words[0], "<<",ft_strlen(*words)))
		heredoc(words);
	else
	{
		perror(ft_strjoin(words[0], ": command not found")); //freeeeeee
		get_data()->last_exit_status = 127;
	}
	if (DEBUG)
	{
		execute_on_bash(line);
		print_words(words);
	}
	ft_arrayfree(words);
}

int	main (int ac, char **av, char **enviroment)
{
	t_data	*data;
	t_envlist *env_vars;

	
	if (ac > 1 || av[1])
		perror("To many arguments");
	data = get_data();
	signal(SIGINT, handle_sigint);   // Ctrl+C
	signal(SIGQUIT, handle_sigquit); // Ctrl+\ (Ctrl+Ç)
//	signal(SIGTERM, handle_sigint);  // kill
	data->last_line = ft_strdup("");
	env_vars = env_initializer(enviroment);
	data->prompt = ft_strjoinfree1(ft_strjoinfree2(
				GREEN "user@localhost" NC ":" BLUE, get_actual_dir()), NC"$ ");
	while (1)
	{
		data->line = readline(data->prompt);//free
		if (data->line == NULL)       // Ctrl+D
			//if (isatty(STDIN_FILENO)) // Solo salir si es terminal interactivo
				exit_shell(NULL, 0);
		//printf("%c\n", data->line[0]);
		if (ft_strcmp(data->line, data->last_line) != 0)
			add_history(data->line);
		interpreter(data->line, env_vars);
		ft_free(&data->last_line);
		data->last_line = data->line;
	}
	return (0);
}


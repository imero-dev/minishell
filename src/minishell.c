/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:50:54 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/28 13:40:05 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

static void	init_data(char **enviroment)
{
	t_data	*data;

	data = get_data();
	data->last_exit_status = 0;
	data->commandlist = NULL;
	data->last_line = ft_strdup("");
	data->line = NULL;
	data->prompt = ft_strdup("");
	data->env_vars = env_initializer(enviroment);
	data->orders = NULL;
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
/* 
void	interpreter(char *line)
{
	char	**tokens;
	int		i;

	i = -1;
	if (!line || ft_strlen(line) == 0)
		return ;
	get_data()->orders = ft_split(line, '|');
	while (get_data()->orders[++i])
	{
		tokens = syntax_spliter(get_data()->orders[i]);
		if (tokens == NULL)
		{
			get_data()->last_exit_status = 2;
			return ;
		}
		if (tokens[0] == NULL)
			return ;
		if (!add_command(tokens))
		{
			ft_perror("minishell: syntax error", 0);
			ft_array_free(tokens);
			return ;
		}
	}
	run_commands();
} */

int	main(int argc, char **argv, char **enviroment)
{
	t_data	*data;

	if (argc > 1 || argv[1])
		ft_perror("To many arguments", 0);
	data = get_data();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	init_data(enviroment);
	while (1)
	{
		ft_free(&data->prompt);
		data->prompt = ft_strjoinfree1(ft_strjoinfree2(GREEN
					"42user@localhost" NC ":" BLUE, get_actual_dir()), NC "$ ");
		data->line = readline(data->prompt);
		if (data->line == NULL)
			exit_shell(NULL, 0);
		if (ft_strcmp(data->line, data->last_line) != 0)
			add_history(data->line);
		interpreter(data->line);
		ft_array_free_null(&data->orders);
		ft_free(&data->last_line);
		data->last_line = data->line;
	}
	return (0);
}

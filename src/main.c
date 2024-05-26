/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:50:54 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/26 16:02:28 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*get_data(void)
{
	static t_data data;

	return (&data);
}

void syntax_error(char *msg)
{
	printf("Syntax error: %s\n", msg);
}

void	interpreter(char *line)
{
	char	**words;
	int		i;

	if (line == NULL || ft_strlen(line) == 0)
		return ;
	//expand_env(line); // can split by "$VAR" and join with the value of var, is simple, I guess also need 
	words = ft_split(get_data()->line, ' ');
	//words = syntax_spliter(get_data()->line);

	if (ft_strcmp(words[0], "exit") == 0)
		exit(0) ;
	if (ft_strcmp(words[0], "pwd") == 0)
		com_pwd();
	if (ft_strcmp(words[0], "cd") == 0)
		com_cd(words[1]);
	if (ft_strcmp(words[0], "echo") == 0)
		ft_echo(words);
	printf("--------------------------------------------\n");
	i = 0;
	while (words[i])
	{
		printf("words[%d] = %s\n", i, words[i]);
		i++;
	}
	ft_arrayfree(words);
}

int	main(void)
{
	t_data	*data;

	data = get_data();
	data->last_line = ft_strdup("");
	while (1)
	{
		data->line = readline(GREEN "user@localhost" NC "$ ");
		if (strcmp(data->line, data->last_line) != 0)
			add_history(data->line);
		printf("---BASH-------------------------------------\n");
		system(ft_strjoinmulti("echo \'", data->line, "\\n\' | bash", NULL));
		printf("--------------------------------------------\n");
		printf("---OWN--------------------------------------\n");
		interpreter(data->line);
		printf("--------------------------------------------\n");
		free(data->last_line);
		data->last_line = data->line;
	}
	return (0);
}

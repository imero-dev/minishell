/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:50:54 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/26 03:08:28 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_data

void	interpreter(char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	i = 0;
	while (words[i])
	{
		printf("words[%d] = %s\n", i, words[i]);
		i++;
	}
	if (ft_strncmp(words[0], "exit", 5) == 0)
		exit(0) ;
	if (ft_strncmp(words[0], "pwd", 4) == 0)
		com_pwd();
	if (ft_strncmp(words[0], "cd", 3) == 0)
		com_cd(words[1]);
	ft_arrayfree(words);
}

int	main(void)
{
	char	*line;
	char	*last_line;

	last_line = ft_strdup("");
	while (1)
	{
		line = readline(GREEN "user@localhost" NC "$ ");
		if (strncmp(line, last_line, ft_strlen(line)) != 0)
			add_history(line);
		printf("---BASH-------------------------------------\n");
		system(ft_strjoinmulti("echo \"", line, "\\n\" | bash", NULL));
		printf("--------------------------------------------\n");
		printf("---OWN--------------------------------------\n");
		interpreter(line);
		printf("--------------------------------------------\n");
		free(last_line);
		last_line = line;
	}
	return (0);
}

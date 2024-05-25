/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:50:54 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/25 17:28:30 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("user@localhost: ");
		add_history(line);
		if (ft_strncmp(line, "exit", 5) == 0)
		{
			free(line);
			break ;
		}
		printf("error in command : %s\n", line);
		printf("there is no function to execute comands\n");
		free(line);
	}
	return (0);
}

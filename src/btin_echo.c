/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:59:49 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/13 19:30:08 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	com_echo(char **args)
{
	int		i;
	bool	n_flag;

	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		n_flag = true;
		i = 2;
	}
	else
	{
		n_flag = false;
		i = 1;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}

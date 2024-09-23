/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:59:49 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/23 04:51:07 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	com_echo(char **args)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	while (args[i] && args[i][0] == '-')
	{
		if (ft_strcmp(args[i], "-n") == 0)
			n_flag = true;
		i++;
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
	return (0);
}

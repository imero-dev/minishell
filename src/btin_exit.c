/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:27:53 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/16 04:02:03 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void exit_error(int status, char **args)
{
	if (status == 1)
		ft_perror("bash: exit: too many arguments\n", 0);
	else if (status == 2)
		ft_printf("%!bash: line 1: exit: %s: numeric argument required\n", args[1]);
	exit_shell(NULL, status);
}

void	com_exit(char **args)
{
	int			i;
	bool		is_num;
	long long	status;

	i = 0;
	is_num = false;
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	if (args[1])
	{
		if (args[1][0] == '-' || args[1][0] == '+')
			i++;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]) && !ft_isspace(args[1][i]))
				exit_error(2, args);
			if (ft_isdigit(args[1][i]))
				is_num = true;
			i++;
		}
		if (args[2])
			exit_error(1, args);
		if (!is_num)
			exit_error(2, args);
		status = ft_atoll(args[1]);
		if (status > LONG_MAX || status < LONG_MIN)
			exit_error(2, args);
	}
	else
		status = 0;
	exit_shell(NULL, status);
}

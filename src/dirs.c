/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 02:36:45 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/26 03:12:20 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Print out the current working directory.
*/
int	com_pwd(void)
{
	char	dir[1024];

	//	char	*s;
	getcwd(dir, sizeof(dir) - 1);
	// s = getcwd(dir, sizeof(dir) - 1);
	/*	if (s == 0)
		{
			printf("Error getting pwd: %s\n", dir);
			return (1);
		} */
	printf("%s\n", dir);
	return (0);
}

/*
** Change to the directory ARG.
*/
int	com_cd(char *arg)
{
	if (arg == NULL || arg[0] == '\0' || arg[0] == '~')
	{
		if (chdir(getenv("HOME")) == -1)
		{
			printf("cd: %s: No such file or directory ", arg);
			return (1);
		}
		com_pwd();
		return (0);
	}
	if (chdir(arg) == -1)
	{
		printf("cd: %s: No such file or directory ", arg);
		return (1);
	}
	com_pwd();
	return (0);
}

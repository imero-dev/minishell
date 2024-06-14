/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 02:36:45 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/14 15:36:42 by ivromero         ###   ########.fr       */
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
int	com_cd(char **args) // TODO simplificar en una sola llamada a chdir
{
	if (args[2])
	{
		perror(" too many arguments\n");
		return (1);
	}
	if (args[1] == NULL || args[1][0] == '\0' || args[1][0] == '~')
	{
		if (chdir(env_get("HOME")) == -1) //FIXME use env_get  // test evaluation point
		{
			//printf("cd: %s: No such file or directory\n", args[1]);
			perror("no such file or directory\n");
			return (1);
		}
		return (0);
	}
	if (chdir(args[1]) == -1)
	{
		perror("no such file or directory\n");
		//printf("cd: %s: No such file or directory\n", args[1]);
		return (1);
	}
	return (0);
}

char *get_actual_dir(void)
{
	char	dir[1024];
	char *last_bslash;

	getcwd(dir, sizeof(dir) - 1);
	last_bslash = ft_strrchr(dir, '/');
	if (last_bslash == NULL)
		return (ft_strdup(dir));
	return (ft_strdup(last_bslash + 1));
}

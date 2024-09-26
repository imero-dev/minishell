/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 02:36:45 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/26 23:40:33 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Print out the current working directory.
*/
int	com_pwd(void)
{
	char	dir[1024];

	getcwd(dir, sizeof(dir) - 1);
	printf("%s\n", dir);
	return (0);
}

/*
** Change to the directory ARG.
*/
int	com_cd(char **args)
{
	if (args[2])
	{
		ft_perror("minishell: cd: too many arguments\n", 0);
		return (1);
	}
	if (args[1] == NULL || args[1][0] == '\0' || args[1][0] == '~')
	{
		if (chdir(env_get("HOME")) == -1)
		{
			perror("minishell: cd");
			return (1);
		}
		return (0);
	}
	if (chdir(args[1]) == -1)
	{
		ft_printf("%!minishell: cd: %s: %*", args[1]);
		return (1);
	}
	return (0);
}

char	*get_actual_dir(void)
{
	char	dir[1024];
	char	*last_bslash;

	getcwd(dir, sizeof(dir) - 1);
	last_bslash = ft_strrchr(dir, '/');
	if (last_bslash == NULL)
		return (ft_strdup(dir));
	return (ft_strdup(last_bslash + 1));
}

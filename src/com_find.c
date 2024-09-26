/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:01:07 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/27 00:17:17 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_dir(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

static int	is_executable(char *path)
{
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

static void	print_command_not_found(char *command)
{
	ft_printf("%!%s: command not found\n", command);
	get_data()->last_exit_status = 127;
}

char	*handle_absolute_path(char *command)
{
	if (access(command, F_OK) == 0)
	{
		if (is_dir(command))
		{
			ft_perror("minishell: Is a directory\n", 0);
			get_data()->last_exit_status = 126;
			return (NULL);
		}
		if (is_executable(command))
			return (ft_strdup(command));
		perror("minishell");
		get_data()->last_exit_status = 126;
		return (NULL);
	}
	else
	{
		ft_perror("minishell: No such file or directory\n", 0);
		get_data()->last_exit_status = 127;
		return (NULL);
	}
}

// Busca el comando en las rutas de PATH
char	*search_in_path(char *command)
{
	char	**paths;
	char	*exec_path;
	int		i;

	paths = ft_split(env_get("PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		exec_path = ft_strjoinfree1(ft_strjoin(paths[i], "/"), command);
		if (is_executable(exec_path))
		{
			ft_array_free(paths);
			return (exec_path);
		}
		free(exec_path);
		i++;
	}
	ft_array_free(paths);
	print_command_not_found(command);
	return (NULL);
}

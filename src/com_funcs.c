/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:58:42 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/19 03:29:12 by ivromero         ###   ########.fr       */
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
/* 
static char **find_args(char **args)
{
	int i;
	int len;
	int size;
	char **new_array;
	int j;

	if (args == NULL)
		return NULL;
	j = 0;
	i = 0;
	len = 0;
	while (args[len] && ft_strcmp(args[len], ">>")) 
		len++;
	while (args[i] && ft_strcmp(args[i], "<<") == 0)
		i += 2;
	size = len - i;
	new_array = (char **)malloc((size + 1) * sizeof(char *));
	if (new_array == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	//printf("j=%d, size=%d\n",j,size);
	while (j < size) 
	{
		new_array[j] = strdup(args[i + j]);
		if (new_array[j] == NULL)
		{
			perror("strdup failed");
			exit(EXIT_FAILURE);
		}
		j++;
	}
	new_array[size] = NULL;
	return new_array;
}
 */
static char	*find_command(char *command)
{
	char	**path;
	char	*exec;
	int		i;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
		{
			if (is_dir(command))
				ft_perror("minishell: Is a directory\n", 0);
			else if (access(command, X_OK) == 0)
				return (ft_strdup(command));
			else
				perror("minishell: $(FILE)");
			get_data()->last_exit_status = 126;
			return (NULL);
		} else {
			ft_perror("minishell: No such file or directory\n", 0);
			get_data()->last_exit_status = 127;
			return (NULL);
		}
	}
	path = ft_split(env_get("PATH"), ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		exec = ft_strjoinfree1(ft_strjoin(path[i], "/"), command);
		if (access(exec, X_OK) == 0)
		{
			ft_array_free(path);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_array_free(path);
	ft_printf("%!%s: command not found\n", command);
	get_data()->last_exit_status = 127;
	return (NULL);
}

int	add_command(char **args)
{
	t_data			*data;
	t_commandlist	*new_command;
	t_commandlist	*last_command;

	data = get_data();
	new_command = ft_calloc(1, sizeof(t_commandlist));
	if (!new_command)
		return (0);
	new_command->args = args;
	//new_command->redirects = redirects;
	if (!data->commandlist)
	{
		data->commandlist = new_command;
		return (1);
	}
	last_command = data->commandlist;
	while (last_command->next)
		last_command = last_command->next;
	last_command->next = new_command;
	return (1);
}

void	free_commandlist(t_commandlist **commandlist)
{
	t_commandlist	*current;
	t_commandlist	*next;

	current = *commandlist;
	while (current)
	{
		next = current->next;
		if (current->command)
			free(current->command);
		ft_array_free(current->args);
		if (current->redirects)
			free(current->redirects);
		free(current);
		current = next;
	}
	*commandlist = NULL;
}

void	run_command(t_commandlist *command)
{
	if (ft_strcmp(command->args[0], "exit") == 0)
		com_exit(command->args);
	if (ft_strcmp(command->args[0], "pwd") == 0)
		get_data()->last_exit_status = com_pwd();
	else if (ft_strcmp(command->args[0], "cd") == 0)
		get_data()->last_exit_status = com_cd(command->args);
	else if (ft_strcmp(command->args[0], "echo") == 0)
		get_data()->last_exit_status = com_echo(command->args);
	else if (ft_strcmp(command->args[0], "env") == 0)
		get_data()->last_exit_status = env_writer(get_data()->env_vars);
	else if (ft_strchr(command->args[0], '='))
		get_data()->last_exit_status = save_var(get_data()->env_vars, command->args);
	else if (ft_strcmp(command->args[0], "export") == 0)
		get_data()->last_exit_status = export(get_data()->env_vars,
				command->args);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		get_data()->last_exit_status = unset(get_data()->env_vars,
				command->args);
//	else if (ft_strnstr(command->args[0], "<<", ft_strlen(*command->args)))
//		heredoc(command->args);
	else
	{
		command->command = find_command(command->args[0]);
		get_data()->last_exit_status = exec_command(get_data()->commandlist);
	}
}

int	run_commands(void)
{
	t_commandlist	*current;

	current = get_data()->commandlist;
	while (current)
	{
		run_command(current);
		current = current->next;
	}
	return (0);
}

int	exec_command(t_commandlist *command)
{
	pid_t	pid;
	int		status;

 	if (!command->command)
		return (get_data()->last_exit_status);
/*	{
		ft_perror("minishell: command not found\n", 0);
		return (127);
	} */
	// printf("Running command: %s\n", command->command);
	pid = fork();
	if (pid == 0)
	{
		// printf("fork >>>>\n");
		execve(command->command, command->args, NULL);
		// TODO  - revisar que hice en pipex
		perror("minishell: $(FILE)");
		exit(2);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			//	if (WEXITSTATUS(status) != 0)
			//		printf("Command failed with exit status: %d\n",
			//			WEXITSTATUS(status));
		}
		else
			printf("Command terminated abnormally\n"); // ? imprimir error
	}
	return (WEXITSTATUS(status));
}

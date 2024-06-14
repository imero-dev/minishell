/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:58:42 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/14 03:18:26 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *find_command(char *command)
{
	char	**path;
	char	*exec;
	int		i;

	if(!command)
		return (NULL);
	if(access(command, X_OK) == 0)
		return (command);
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
	return (NULL);
}

int	add_command(char **args, char *redirects)
{
	t_data			*data;
	t_commandlist	*new_command;
	t_commandlist	*last_command;

	data = get_data();
	new_command = malloc(sizeof(t_commandlist));
	if (!new_command)
		return (0);
	new_command->command = find_command(args[0]);
	new_command->args = args;
	new_command->redirects = redirects;
	new_command->next = NULL;
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
		if(current->command)
			free(current->command);
		ft_array_free(current->args);
		if(current->redirects)
			free(current->redirects);
		free(current);
		current = next;
	}
	*commandlist = NULL;
}	

int run_command(t_commandlist *command)
{
    pid_t	pid;
    int		status;

	if (!command->command)
	{
		perror("Command not found: No such file or directory");
		return (127);
	}
	//printf("Running command: %s\n", command->command);
	pid = fork();
    if (pid == 0)
    {
        execve(command->command, command->args, NULL);
        exit(1); // ? como recupero la salida del proceso hijo ¿este da igual?
    }
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				printf("Command failed with exit status: %d\n", WEXITSTATUS(status));
		}
		else
			printf("Command terminated abnormally\n");
	}
return (status);// ? WEXITSTATUS(status)
}

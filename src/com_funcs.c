/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:58:42 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/18 19:04:20 by iker_bazo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 


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
while ((args[len] && ft_strcmp(args[len], ">>") && ft_strcmp(args[len], ">")))
		len ++;
	while ((args[i] && ft_strcmp(args[i], "<<") == 0) || (args[i] && ft_strcmp(args[i], "<") == 0 ))
		i += 2;
	size = len - i;
	new_array = (char **)malloc((size + 1) * sizeof(char *));
	if (new_array == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
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

int	add_command(char **args)
{
	t_data			*data;
	t_commandlist	*new_command;
	t_commandlist	*last_command;

	data = get_data();
	new_command = malloc(sizeof(t_commandlist));
	if (!new_command)
		return (0);
	new_command->command = find_command(args[4]);
	new_command->cmd_args = find_args(args);
	new_command->tokens = args;
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
		if(current->cmd_args)
			ft_array_free(current->cmd_args);
		if(current->tokens)
			ft_array_free(current->tokens);
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
		perror("Command not found\n");
		return (127);
	}
	pid = fork();
    if (pid == 0)
    {
		command->infile = input_redirections(command->tokens);
		command->outfile = output_redirections(command->tokens);
		if(access(".heredoc", R_OK) == 0)
		{
			printf("llego\n");
			command->infile = open(".heredoc", O_RDWR);
			if (dup2(command->infile, STDIN_FILENO) == -1)
				perror("closing standard input: Bad file descriptor");
			close(command->infile);
		}
		else if (command->infile >= 0)
		{
			if (dup2(command->infile, STDIN_FILENO) == -1)
				perror("closing standard input: Bad file descriptor");
			close(command->infile);
		}
		if (command->outfile >= 0)
		{
			if (dup2(command->outfile, STDOUT_FILENO) == -1)
				perror("closing standard output: Bad file descriptor\n");
			close(command->outfile);
		}
        execve(command->command, command->cmd_args, NULL);
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

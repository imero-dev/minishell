/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:58:42 by ivromero          #+#    #+#             */
/*   Updated: 2024/07/11 12:54:23 by iker_bazo        ###   ########.fr       */
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
	heredoc(args);
	new_command->command = find_command(args[2]);
	new_command->outfile = redirections(args);
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
	heredoc(command->tokens);
	printf("Running command: %s\n", command->command);
	pid = fork();
    if (pid == 0)
    {
		if(access(".heredoc", R_OK) == 0)
		{
			command->infile = open(".heredoc", O_RDWR);
			if (dup2(command->infile, STDIN_FILENO) == -1)
				perror("closing standard input: Bad file descriptor");
			close(command->infile);
		}
		// TODO UN ELSE QUE HAGA UN DUP2 DEL PIPE DE LECTURA   
		if	(command->pipefd[FD_OUT])
		{
			dup2(command->pipefd[FD_OUT], STDOUT_FILENO); 
			close(command->pipefd[FD_OUT]);
		}
		// TODO UN ELSE QUE HAGA UN DUP2 DEL PIPE DE ESCRITURA 
		printf("fork >>>>\n");
        execve(command->command, command->cmd_args, NULL);
		printf("<<<< fork\n");
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
		unlink(".heredoc");
	}
return (status);// ? WEXITSTATUS(status)
}

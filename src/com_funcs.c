/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 00:58:42 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/23 04:32:31 by ivromero         ###   ########.fr       */
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
	while (path[i] && command[0] )
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

int	add_command(char **tokens)
{
	t_data			*data;
	t_commandlist	*new_command;
	t_commandlist	*last_command;

	data = get_data();
	new_command = ft_calloc(1, sizeof(t_commandlist));
	if (!new_command)
		return (0);
	new_command->tokens = tokens;
	classify_tokens(new_command);
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
	//FIXME hay que poner el fork aqui esto de abajo es exex_command y lo de exec_command con el fork es el run_comand que tiene que estar aqui y ejecutarse antes
	if (!command->args[0])
		return ;
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
		if(command->command)
			get_data()->last_exit_status = exec_command(get_data()->commandlist);
	}
}

int	run_commands(void)
{
	t_commandlist	*current;

	current = get_data()->commandlist;
	while (current && current->args)
	{
		run_command(current);
		current = current->next;
	}
	free_commandlist(&get_data()->commandlist);
	return (0);
}

int	exec_command(t_commandlist *command)
{
	pid_t	pid;
	int		status;


 	if (!command->command)
		return (get_data()->last_exit_status);
	pid = fork();
	signal(SIGINT, handle_sigint_runing);
	if (pid == 0)
	{
		command->fd_in = input_redirections(command->redirects);
		command->fd_out = output_redirections(command->redirects);
		if(access(".heredoc", R_OK) == 0)
		{
			command->fd_in = open(".heredoc", O_RDWR);
			if (dup2(command->fd_in, STDIN_FILENO) == -1)
				perror("minishell: closing standard input: Bad file descriptor");
			close(command->fd_in);
		}
		else if (command->fd_in)
		{
			if (dup2(command->fd_in, STDIN_FILENO) == -1)
				perror("minishell: closing standard input: Bad file descriptor");
			close(command->fd_in);
		}
		if (command->fd_out)
		{
			printf("%d\n", command->fd_out);
			if (dup2(command->fd_out, STDOUT_FILENO) == -1)
				perror("minishell: closing standard output: Bad file descriptor\n");
			close(command->fd_out);
		}
		execve(command->command, command->args, NULL);
		// TODO  - revisar que hice en pipex
		perror("minishell: fail on execution (execve)"); 
		exit(2);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (access(".heredoc", F_OK) == 0)
			unlink(".heredoc");
		if (WIFEXITED(status))
		{
			//	if (WEXITSTATUS(status) != 0)
			//		printf("Command failed with exit status: %d\n",
			//			WEXITSTATUS(status));
		}
	}
	signal(SIGINT, handle_sigint);
	return (WEXITSTATUS(status));
}

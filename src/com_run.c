/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 03:21:49 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/28 15:07:26 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void run_command(t_commandlist *command)
{
	int		fd[2];
	int		save_fd;
	int		status;
	bool	is_builtin;

	if (!command)
		return ;
	if (command->next)
	{
		pipe(fd);
		save_fd = dup(1);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	exec_command(command);
	if (command->next)
	{
		dup2(save_fd, 1);
		close(save_fd);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		run_command(command->next);
	}
} */
void	run_command(t_commandlist *command, bool first, int pipefd[2],
		int next_pipefd[2])
{
	bool	is_builtin;

	if (!command->args[0])
		return ;
	is_builtin = false;
	if (ft_strcmp(command->args[0], "exit") == 0)
		com_exit(command->args);
	else if (ft_strcmp(command->args[0], "cd") == 0)
		get_data()->last_exit_status = com_cd(command->args);
	else if (ft_strcmp(command->args[0], "export") == 0)
		get_data()->last_exit_status = export(get_data()->env_vars,
				command->args);
	else if (ft_strcmp(command->args[0], "unset") == 0)
		get_data()->last_exit_status = unset(get_data()->env_vars,
				command->args);
	else if (ft_strchr(command->args[0], '='))
		get_data()->last_exit_status = save_var(get_data()->env_vars,
				command->args);
	else if (ft_strcmp(command->args[0], "pwd") == 0
		|| ft_strcmp(command->args[0], "echo") == 0
		|| ft_strcmp(command->args[0], "env") == 0)
	{
		is_builtin = true;
	}
	else
	{
		command->command = find_command(command->args[0]);
		if (command->command)
			get_data()->last_exit_status = fork_exec_command(command, first,
					pipefd, next_pipefd);
	}
	if (is_builtin)
	{
		if (command->next != NULL || !first)
		{
			// Ejecutar en proceso hijo si es parte de una tubería
			command->command = command->args[0];
			get_data()->last_exit_status = fork_exec_command(command, first,
					pipefd, next_pipefd);
		}
		else
		{
			// Ejecutar directamente si no es parte de una tubería
			if (ft_strcmp(command->args[0], "pwd") == 0)
				get_data()->last_exit_status = com_pwd();
			else if (ft_strcmp(command->args[0], "echo") == 0)
				get_data()->last_exit_status = com_echo(command->args);
			else if (ft_strcmp(command->args[0], "env") == 0)
				get_data()->last_exit_status = env_writer(get_data()->env_vars);
		}
	}
}

void	exec_command(t_commandlist *command, bool first, int pipefd[2],
		int next_pipefd[2])
{
	// Configuración de redirecciones y pipes (igual que antes)
	if (access(".heredoc", R_OK) == 0)
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
	else if (!first)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (command->fd_out)
	{
		if (dup2(command->fd_out, STDOUT_FILENO) == -1)
			perror("minishell: closing standard output: Bad file descriptor\n");
		close(command->fd_out);
	}
	else if (command->next != NULL)
	{
		close(next_pipefd[0]);
		dup2(next_pipefd[1], STDOUT_FILENO);
		close(next_pipefd[1]);
	}
	// Ejecutar built-in o comando externo
	if (ft_strcmp(command->args[0], "pwd") == 0)
	{
		com_pwd();
		exit(get_data()->last_exit_status);
	}
	else if (ft_strcmp(command->args[0], "echo") == 0)
	{
		com_echo(command->args);
		exit(get_data()->last_exit_status);
	}
	else if (ft_strcmp(command->args[0], "env") == 0)
	{
		env_writer(get_data()->env_vars);
		exit(get_data()->last_exit_status);
	}
	else
	{
		execvp(command->args[0], command->args);
		perror("execvp");
		exit(1);
	}
}

int	run_commands(void)
{
	t_commandlist	*current;
	int				pipefd[2];
	int				next_pipefd[2];
	bool			first_command;

	first_command = true;
	get_data()->runing_commands = true;
	current = get_data()->commandlist;
	while (current && current->args)
	{
		run_command(current, first_command, pipefd, next_pipefd);
		first_command = false;
		current = current->next;
	}
	free_commandlist(&get_data()->commandlist);
	get_data()->runing_commands = false;
	return (0);
}

void	close_old_advance_pipe(t_commandlist *command, bool first,
		int pipefd[2], int next_pipefd[2])
{
	if (!first)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (command->next != NULL)
	{
		pipefd[0] = next_pipefd[0];
		pipefd[1] = next_pipefd[1];
	}
}

int	fork_exec_command(t_commandlist *command, bool first, int pipefd[2],
		int next_pipefd[2])
{
	pid_t	pid;
	int		status;

	if (!command->command)
		return (get_data()->last_exit_status);
	get_data()->last_exit_status = 0;
	command->fd_in = input_redirections(command->redirects);
	command->fd_out = output_redirections(command->redirects);
	if (command->next != NULL)
	{
		if (pipe(next_pipefd) == -1)
			perror("pipe");
	}
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
		exec_command(command, first, pipefd, next_pipefd);
	else
	{
		close_old_advance_pipe(command, first, pipefd, next_pipefd);
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
	return (WEXITSTATUS(status) + get_data()->last_exit_status);
}

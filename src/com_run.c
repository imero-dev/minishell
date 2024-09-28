/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 03:21:49 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/29 00:34:00 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_command(t_commandlist *command, bool first, int pipefd[2],
			int next_pipefd[2])
{
	handle_input_redirection(command, first, pipefd);
	handle_output_redirection(command, next_pipefd);
	execute_builtins_or_command(command);
}

void	run_command(t_commandlist *command, bool first, int pipefd[2],
			int next_pipefd[2])
{
	if (!command->args[0])
		return ;
	if (handle_direct_builtins(command))
		return ;
	if (is_forked_builtin(command->args[0]))
	{
		command->command = ft_strdup(command->args[0]);
		get_data()->last_exit_status = fork_exec_command(command, first,
			pipefd, next_pipefd);
	}
	else
	{
		command->command = find_command(command->args[0]);
		if (command->command)
			get_data()->last_exit_status = fork_exec_command(command, first,
				pipefd, next_pipefd);
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
		if (pipe(next_pipefd) == -1)
			perror("minishell: pipe");
	pid = fork();
	if (pid == -1)
		perror("minishell: fork");
	if (pid == 0)
		exec_command(command, first, pipefd, next_pipefd);
	else
	{
		close_old_advance_pipe(command, first, pipefd, next_pipefd);
		waitpid(pid, &status, 0);
		if (access(".heredoc", F_OK) == 0)
			unlink(".heredoc");
	}
	return (WEXITSTATUS(status) + get_data()->last_exit_status);
}

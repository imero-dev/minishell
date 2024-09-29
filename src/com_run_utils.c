/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_run_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:29:35 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/29 02:16:19 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_direct_builtins(t_commandlist *command)
{
	if (ft_strcmp(command->args[0], "exit") == 0)
		return (com_exit(command->args), 1);
	if (ft_strcmp(command->args[0], "cd") == 0)
		return (get_data()->last_exit_status = com_cd(command->args), 1);
	if (ft_strcmp(command->args[0], "export") == 0)
	{
		get_data()->last_exit_status = export(get_data()->env_vars,
			command->args);
		return (1);
	}
	if (ft_strcmp(command->args[0], "unset") == 0)
	{
		get_data()->last_exit_status = unset(get_data()->env_vars,
			command->args);
		return (1);
	}
	else if (ft_strchr(command->args[0], '='))
	{
		get_data()->last_exit_status = save_var(get_data()->env_vars,
			command->args);
		return (1);
	}
	return (0);
}

int	is_forked_builtin(const char *cmd)
{
	return (ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0);
}

void	handle_input_redirection(t_commandlist *command, bool first,
		int pipefd[2])
{
	if (access(".heredoc", R_OK) == 0)
	{
		command->fd_in = open(".heredoc", O_RDWR);
		if (dup2(command->fd_in, STDIN_FILENO) == -1)
			perror("minishell: dup2 error");
		close(command->fd_in);
	}
	else if (command->fd_in)
	{
		if (dup2(command->fd_in, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 error");
			return ;
		}
		close(command->fd_in);
	}
	else if (!first)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	handle_output_redirection(t_commandlist *command, int next_pipefd[2])
{
	if (command->fd_out)
	{
		if (dup2(command->fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 error");
			return ;
		}
		close(command->fd_out);
	}
	else if (command->next != NULL)
	{
		close(next_pipefd[0]);
		dup2(next_pipefd[1], STDOUT_FILENO);
		close(next_pipefd[1]);
	}
}

void	execute_builtins_or_command(t_commandlist *command)
{
	if (ft_strcmp(command->args[0], "pwd") == 0)
	{
		com_pwd();
		exit_shell("", get_data()->last_exit_status);
	}
	else if (ft_strcmp(command->args[0], "echo") == 0)
	{
		com_echo(command->args);
		exit_shell("", get_data()->last_exit_status);
	}
	else if (ft_strcmp(command->args[0], "env") == 0)
	{
		env_writer(get_data()->env_vars);
		exit_shell("", get_data()->last_exit_status);
	}
	else
	{
		execve(command->command, command->args, NULL);
		perror("minishell: execve");
		exit_shell("", 1);
	}
}

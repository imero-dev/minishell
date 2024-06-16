/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 03:21:49 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/15 02:20:38 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void run_command(t_commandlist *command)
{
	int		fd[2];
	int		save_fd;
	int		status;

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
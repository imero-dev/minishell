/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:34:16 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/28 13:23:26 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle Ctrl+C interactive
void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	if (get_data()->in_here_doc)
	{
		get_data()->here_doc_stoped = 1;
		rl_replace_line("", 0);
		rl_done = 1;
	}
	if (!get_data()->runing_commands )
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	get_data()->last_exit_status = 130;
}

// Handle Ctrl+\ (Ctrl+Ç)
void	handle_sigquit(int sig)
{
	(void)sig;
	if (get_data()->runing_commands && !get_data()->in_here_doc)
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	else
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  ", STDOUT_FILENO);
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
	get_data()->last_exit_status = 131;
}

void	exit_shell(char *msg, int status)
{
	if (msg)
		printf("%s\n", msg);
	garbage_collector();
	exit(status);
}

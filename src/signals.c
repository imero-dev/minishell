/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:34:16 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/23 04:53:11 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle Ctrl+C interactive
void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Handle Ctrl+C runing command
void	handle_sigint_runing(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

// Handle Ctrl+\ (Ctrl+Ç)
void	handle_sigquit(int sig)
{
	(void)sig;
}

void	exit_shell(char *msg, int status)
{
	if (msg)
		printf("%s\n", msg);
	garbage_collector();
	exit(status);
}

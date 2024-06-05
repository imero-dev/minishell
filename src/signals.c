/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 00:34:16 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/04 13:36:45 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle Ctrl+C
void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Handle Ctrl+\ (Ctrl+Ç)
void	handle_sigquit(int sig)
{
	(void)sig;
	printf("Ctrl+\\ pressed\n");//debug
}

void exit_shell(char *msg, int status)
{
	if (msg)
		printf("%s\n", msg);
	garbage_collector();
	exit(status);
}

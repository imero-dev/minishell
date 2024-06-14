/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 02:30:44 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/27 20:58:05 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_words(char **words)
{
	int	i;

	if(!DEBUG)
		return ;
	printf(YELLOW"------DEBUG-----"NC"\n");
	i = 0;
	while (words[i])
	{
		printf("words[%d] = %s\n", i, words[i]);
		i++;
	}
}

void	execute_on_bash(char *command)
{
	if(!DEBUG)
		return ;
	printf(YELLOW"------BASH------"NC"\n");
	pid_t pid = fork(); 
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		char *args[] = {"/bin/bash", "-c", command, NULL};
		execve(args[0], args, NULL);
		perror("execve");
		exit(1);
	}
	else
	{
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) != 0)
				printf("Command failed with exit status: %d\n", WEXITSTATUS(status));
		}
		else
			printf("Command terminated abnormally\n");
	}
}

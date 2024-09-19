/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_ouput_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:51:50 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/09/19 03:04:22 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int output_files_opener(char *file)
{
	int fd;

	fd = 0;
	if(fd)
	{
		close(fd);
		fd = 0;
	}
	fd = open(file,O_TRUNC | O_RDWR | O_CREAT, 0644);
	return(fd);
}

static int append_opener(char *file)
{
	int fd;

	fd = 0;
	if(fd)
	{
		close(fd);
		fd = 0;
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return(fd);
}

int	output_redirections(char **words)
{
	int		i;
	int		fd;

	fd = 0;
	i = -1;
	while (words[++i])
	{
		if(ft_strcmp(words[i], ">>") == 0 && words[i + 1])
		{
			fd = append_opener(words[1 + i]);
			return (fd);
		}
		else if (ft_strcmp(words[i], ">") == 0 && words[i + 1])
		{
			if(fd)
			{
				close(fd);	
				fd = 0;
			}
			fd = output_files_opener(words[i + 1]);
		}
	}
	return fd;
}

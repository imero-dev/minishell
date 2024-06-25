/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:28:13 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/24 13:39:38 by iker_bazo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_write(int fd, char *line)
{
	int rt;
	if (!fd)
		fd = 1;
	rt = write(fd, line, ft_strlen(line));
	rt += write(fd, "\n", 1);
	return rt;
}

void	free_arr(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	heredoc(char **words)
{
	int		i;
	int		j;
	int		fd;
	char 	*end_of_files;
	char	*line;

	j = -1;
	i = -1;
	while (words[++i])
	{
		if(ft_strcmp(words[i], "<<") == 0 && words[i + 1])
		{
			end_of_files = words[i + 1];
			while (end_of_files[++j])
			{
				fd = open(".heredoc", O_TRUNC | O_RDWR | O_CREAT, 0644);
				while (ft_strcmp(line, end_of_files[j]))
				{
					line = readline("> ");
					ft_write(fd,line);
				}
				close(fd);
			}
		}
	}
}

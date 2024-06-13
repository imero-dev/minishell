/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:28:13 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/13 17:56:36 by iker_bazo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_arr(char **array)
{
	int i;
	
	i = 0;
	if (array == NULL)
		return;
	while(array[i] != NULL)
	{
		free(array[i]);
		i++;	
	}
	free(array);
}


void heredoc(char **words)
{
	int i;
	int j;
	int fd;
	char **end_of_files;
	char *line;
	
	j = -1;
	i = -1;
	while (words[++i])
	{
		end_of_files = ft_split(words[i],'<');
		j = -1;
		while (end_of_files[++j])
		{
			fd = open(".heredoc", O_TRUNC | O_RDWR | O_CREAT, 0644);
			while (ft_strcmp(line,end_of_files[j]))
			{
				line = readline("> ");
				write(fd,line,ft_strlen(line));
				write(fd,"\n",1);
			}
			close(fd);
		}
		free_arr(end_of_files);
	}
}

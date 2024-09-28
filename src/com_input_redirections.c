/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_input_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:28:13 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/09/28 13:08:28 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://www.gnu.org/software/bash/manual/bash.html#Redirections
// https://www.terminaltemple.com

static int	ft_write(int fd, char *line)
{
	int	rt;

	if (!fd)
		fd = 1;
	rt = write(fd, line, ft_strlen(line));
	rt += write(fd, "\n", 1);
	return (rt);
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

static int	input_files_opener(char *file)
{
	int	fd;

	fd = 0;
	if (fd)
	{
		close(fd);
		fd = 0;
	}
	fd = open(file, O_RDWR, 0644);
	return (fd);
}

void	ft_heredoc(char *eof)
{
	int		fd;
	char	*line;

	fd = 0;
	fd = open(".heredoc", O_TRUNC | O_RDWR | O_CREAT, 0644);
	get_data()->in_here_doc = 1;
	get_data()->here_doc_stoped = 0;
	line = ft_strdup("");
	while (ft_strcmp(line, eof) && ! get_data()->here_doc_stoped)
	{
		free(line);
		line = readline("> ");
		if (ft_strcmp(line, eof) == 0)
			break ;
		ft_write(fd, line);
	}
	get_data()->in_here_doc = 0;
	close(fd);
}

int	input_redirections(char **words)
{
	int	i;
	int	fd;

	fd = 0;
	i = -1;
	while (words[++i])
	{
		if (ft_strcmp(words[i], "<<") == 0 && words[i + 1])
		{
			ft_heredoc(words[i + 1]);
			continue ;
		}
		else if (ft_strcmp(words[i], "<") == 0 && words[i + 1])
		{
			if (access(".heredoc", F_OK) == 0)
				unlink(".heredoc");
			if (fd > 0)
			{
				close(fd);
				fd = 0;
			}
			fd = input_files_opener(words[i + 1]);
		}
	}
	return (fd);
}

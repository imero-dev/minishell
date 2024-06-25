/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_ouput_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:51:50 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/24 13:44:50 by iker_bazo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int redirections(char **words)
{
	int i;
	int fd;
	
	i = 0;
	while (words[i])
	{
		if(ft_strcmp(words[i], ">>") == 0 && words[i + 1])
		{
			if(fd)
			{
				close(fd);
				fd = 0;
			}
			i++;
			fd = open(words[i], O_TRUNC | O_RDWR | O_CREAT, 0644);
		}
		i++;
	}
	return(fd);
}
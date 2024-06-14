/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:14 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/14 16:33:35 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envlist(t_envlist *head)
{
	t_envlist	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->name != NULL)
		{
			free(tmp->name);
		}
		if (tmp->value != NULL)
		{
			free(tmp->value);
		}
		free(tmp);
	}
}

int	unset(t_envlist *env, char **words)
{
	t_envlist	*tmp;
	int			i;

	i = 0;
	if (!env)
	{
		perror("No env aviable");
		return(1);
	}
	while (words[i])
	{
		tmp = env;
		while (tmp)
		{
			if (ft_strcmp(tmp->name, words[i]) == 0)
			{
				tmp->export = false;
				tmp->value = "\n";
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

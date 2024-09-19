/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:14 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/09/19 03:00:11 by ivromero         ###   ########.fr       */
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

static int	delete_node(t_envlist *to_delete)
{
	if (!to_delete)
		return (0);
	free(to_delete->name);
	free(to_delete->value);
	free(to_delete);
	return (0);
}

int	unset(t_envlist *env, char **words)
{
	t_envlist	*tmp;
	t_envlist	*to_delete;
	int			i;

	i = -1;
	if (!env)
	{
		perror("No env aviable");
		return (1);
	}
	while (words[++i])
	{
		tmp = env;
		while (tmp)
		{
			if (tmp->next && ft_strcmp(tmp->next->name, words[i]) == 0)
			{
				to_delete = tmp->next;
				tmp->next = tmp->next->next;
				delete_node(to_delete);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

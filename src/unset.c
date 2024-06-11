/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:14 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/11 18:20:21 by iker_bazo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void free_envlist(t_envlist *head) 
{
	t_envlist *tmp;

	while (head != NULL) 
	{
		tmp = head;
		head = head->next;
		if (tmp->name != NULL) {
			free(tmp->name);
		}
		if (tmp->value != NULL) {
			free(tmp->value);
		}
		free(tmp);
	}
}

t_envlist *unset(t_envlist *env, char **words)
{
	t_envlist *tmp;
	int i;
	
	i = 0;
	if(!env)
		perror("No env aviable");
	while (words[i])
	{
		tmp = env;
		while (tmp)
		{
			if (ft_strcmp(tmp->name, words[i]) == 0)
			{
					tmp->export = false;
					tmp->value = "\n";
					break;
			}
			tmp = tmp->next;	
		}
		i++;
	}
	return(env);
}



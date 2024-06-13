/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:10 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/11 18:21:46 by iker_bazo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_env(t_envlist **lst, t_envlist *new)
{
	if (*lst)
		add_env(&(*lst)->next, new);
	else
		*lst = new;
}

t_envlist	*export(t_envlist	*env_vars, char **words)
{
	t_envlist *tmp;
	int i;

	i = 0;
	while(words[i])
	{
		if (ft_strchr(words[i],'='))
			add_env(&env_vars,new_env(env_name(words[i]),env_value(words[i]),true));
		tmp = env_vars;
		while (tmp)
		{
			if (ft_strcmp(tmp->name, words[i]) == 0)
				tmp->export = true;
			tmp = tmp->next;
		}
		i++;
	}
	return env_vars;
}

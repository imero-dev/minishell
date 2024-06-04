/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:10 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/04 16:47:42 by iker_bazo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envlist *export(char *name, char *value, t_envlist **env)
{
	t_envlist	*node;
	
	node = (t_envlist *)malloc(sizeof(t_envlist));
	if (!node)
		return NULL;
	node->name = name;
	node->value = value;
	node->next = NULL;
	ft_add_env_node(&env,node);
	return *env;
}

static void ft_add_env_node(t_envlist **lst, t_envlist *new)
{
	if (*lst)
		ft_add_env_node(&(*lst)->next, new);
	else
		*lst = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:05 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/04 16:48:57 by iker_bazo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *env_name(char *env)
{
	char *name;
	int i;
	
	i=0;
	if(!env)
		return NULL;
	while (env[i]!= '=')
		i++;
	name = ft_strldup(env,i);
	return name;
}
char *env_value(char *env)
{
	char *value;
	int i;
	
	i = 0;
	if(!env)
		return NULL;
	while (env[i]!= '=')
		i++;
	value = ft_strdup(&env[i + 1]);
	return value;
}
static t_envlist *ft_new_env_lst(char *env)
{
	t_envlist	*node;
	
	node = (t_envlist *)malloc(sizeof(t_envlist));
	if (!node)
		return (NULL);
	node->name = env_name(env);
	node->value = env_value(env);
	node->next = NULL;
	return (node);
}

static void ft_add_env_node(t_envlist **lst, t_envlist *new)
{
	if (*lst)
		ft_add_env_node(&(*lst)->next, new);
	else
		*lst = new;
}

t_envlist *env_initializer(char ** env)
{
	t_envlist *enviroments_vars;
	int i;
	
	i = 0;
	while (env[i])
	{
		if (i == 0)
			enviroments_vars = ft_new_env_lst(env[i]);
		else
			ft_add_env_node(&enviroments_vars,ft_new_env_lst(env[i]));
		i++;
	}
	return(enviroments_vars);
}


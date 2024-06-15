/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btin_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:10 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/14 17:23:52 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env(t_envlist **lst, t_envlist *new)
{
	if (*lst)
		add_env(&(*lst)->next, new);
	else
		*lst = new;
	return (0);
}

int	export(t_envlist *env_vars, char **words)
{
	t_envlist	*tmp;
	int			i;

	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '='))
			add_env(&env_vars, new_env(get_name(words[i]), get_value(words[i]),
					true));
		tmp = env_vars;
		while (tmp)
		{
			if (ft_strcmp(tmp->name, words[i]) == 0)
				tmp->export = true;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

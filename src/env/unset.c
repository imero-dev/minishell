/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:14 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/04 16:53:40 by iker_bazo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envlist *unset(t_envlist *env, char *env_name)
{
	t_envlist *header;
	
	header = env;
	if(!env)
		perror("No env aviable");
	while (env)
	{
		if (ft_strcmp(env->next->name,env_name) == 0)
		{
			free(env->next->name);
			free(env->next->value);
			free(env->next);
			env->next = env->next->next;
		}
		else
			env = env->next;	
	}
	if(env == NULL)
		perror("eviroment variable not found");
	return(header);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:05 by ibazo             #+#    #+#             */
/*   Updated: 2024/09/29 01:14:34 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlist	*new_env(char *name, char *value, bool export)
{
	t_envlist	*node;

	node = (t_envlist *)malloc(sizeof(t_envlist));
	if (!node)
		return (NULL);
	node->name = name;
	node->value = value;
	node->export = export;
	node->next = NULL;
	return (node);
}

t_envlist	*env_initializer(char **env)
{
	t_envlist	*env_vars;
	int			i;

	i = 0;
	while (env[i])
	{
		if (i == 0)
			env_vars = new_env(get_name(env[i]), get_value(env[i]), true);
		else
			add_env(&env_vars, new_env(get_name(env[i]), get_value(env[i]),
					true));
		i++;
	}
	return (env_vars);
}

int	env_writer(t_envlist *env_var)
{
	if (!env_var)
	{
		perror("minishell: env not found\n");
		return (1);
	}
	while (env_var && env_var->name)
	{
		if (env_var->export)
			printf("%s=%s\n", env_var->name, env_var->value);
		env_var = env_var->next;
	}
	return (0);
}

char	*env_get(char *name)
{
	t_envlist	*env_var;

	env_var = get_data()->env_vars;
	while (env_var && env_var->name)
	{
		if (ft_strcmp(env_var->name, name) == 0)
			return (env_var->value);
		env_var = env_var->next;
	}
	return (NULL);
}

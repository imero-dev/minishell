/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:05 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/14 02:24:31 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_name(char *env)
{
	char	*name;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] != '=')
		i++;
	name = ft_strldup(env, i);
	if (!name)
		return (NULL);
	return (name);
}
char	*env_value(char *env)
{
	char	*value;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] != '=')
		i++;
	value = ft_strdup(&env[i + 1]);
	if (!value)
		return (NULL);
	return (value);
}
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
			env_vars = new_env(env_name(env[i]), env_value(env[i]), true);
		else
			add_env(&env_vars, new_env(env_name(env[i]), env_value(env[i]),
					true));
		i++;
	}
	return (env_vars);
}

void	env_writer(t_envlist *env_var)
{
	if (!env_var)
		perror("env not found\n");
	while (env_var && env_var->name)
	{
		if (env_var->export)
			printf("%s=%s\n", env_var->name, env_var->value);
		env_var = env_var->next;
	}
}

char	*env_get(char *name)
{
	t_envlist *env_var;

	env_var = get_data()->env_vars;
	while (env_var && env_var->name)
	{
		if (ft_strcmp(env_var->name, name) == 0)
			return (env_var->value);
		env_var = env_var->next;
	}
	return (NULL);
}

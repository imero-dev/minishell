/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:37:27 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/29 02:41:21 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_name(char *input)
{
	if (!input)
		return (NULL);
	if (ft_strchr(input, '='))
		return (get_name(input));
	else
		return (ft_strdup(input));
}

char	*get_name(char *input)
{
	char	*name;
	int		i;

	i = 0;
	if (!input)
		return (NULL);
	while (input[i] != '=')
		i++;
	name = ft_strldup(input, i);
	if (!name)
		return (NULL);
	return (name);
}

char	*get_value(char *input)
{
	char	*value;
	int		i;

	i = 0;
	if (!input)
		return (NULL);
	while (input[i] != '=')
		i++;
	value = ft_strdup(&input[i + 1]);
	if (!value)
		return (NULL);
	return (value);
}

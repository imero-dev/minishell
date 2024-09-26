/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:54:02 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/27 00:38:22 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_array_free_null(char ***array)
{
	if (!array)
		return (0);
	ft_array_free(*array);
	*array = NULL;
	return (0);
}

int	ft_array_free(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		if (array[i])
			ft_free(&array[i++]);
	free(array);
	array = NULL;
	return (0);
}

void	ft_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayfree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:54:02 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/27 13:49:33 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrayfree(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		if (array[i])
			ft_free(&array[i++]);
	free(array);
	array = NULL;
	return (0);
}

void ft_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

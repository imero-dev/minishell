/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayfree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:54:02 by ivromero          #+#    #+#             */
/*   Updated: 2024/05/01 13:43:11 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arrayfree(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		if (array[i])
			free(array[i++]);
	free(array);
	return (0);
}

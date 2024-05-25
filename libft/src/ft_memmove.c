/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.45urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:23:44 by ivromero          #+#    #+#             */
/*   Updated: 2023/04/26 01:12:12 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = -1;
	if (!dst && !src)
		return (NULL);
	if (src < dst)
		while (len--)
			((char *)dst)[len] = ((char *)src)[len];
	else
		while (++i < len)
			((char *)dst)[i] = ((char *)src)[i];
	return (dst);
}

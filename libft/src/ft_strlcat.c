/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.45urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:24:53 by ivromero          #+#    #+#             */
/*   Updated: 2023/04/27 02:32:02 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	i;

	destlen = 0;
	i = -1;
	srclen = 0;
	while (dst[destlen] && destlen < size)
		destlen++;
	while (src[srclen])
		srclen++;
	if (destlen == size)
		return (destlen + srclen);
	while (src[++i] && (destlen + i < size - 1))
		dst[destlen + i] = src[i];
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.45urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:24:44 by ivromero          #+#    #+#             */
/*   Updated: 2023/05/15 00:19:06 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t		i;
	size_t		len;
	char		*dest;

	dest = 0;
	i = -1;
	len = ft_strlen(s);
	dest = (char *)ft_calloc(len + 1, sizeof(*dest));
	if (dest)
		while (++i < len)
			dest[i] = s[i];
	return (dest);
}

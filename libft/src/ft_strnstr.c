/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.45urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:25:19 by ivromero          #+#    #+#             */
/*   Updated: 2023/05/13 16:47:04 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcomp(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	while (needle[i] == haystack[i] && i < len)
		if (!needle[++i])
			return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = -1;
	if (!*needle)
		return ((char *)haystack);
	while (*(haystack + ++i) && len > i)
		if (ft_strcomp(haystack + i, needle, len - i))
			return ((char *)haystack + i);
	return (0);
}

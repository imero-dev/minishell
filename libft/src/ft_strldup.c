/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:01 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/09/27 00:37:13 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strldup(const char *s1, int l)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (l + 1));
	if (!str)
		return (NULL);
	while (i < l)
	{
		str[i] = s1[i];
		i ++;
	}
	str[i] = '\0';
	return (str);
}

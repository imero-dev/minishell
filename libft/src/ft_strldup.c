/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strldup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iker_bazo <iker_bazo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:00:01 by iker_bazo         #+#    #+#             */
/*   Updated: 2024/06/04 16:55:17 by iker_bazo        ###   ########.fr       */
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
		return NULL;
	while (i < l)
	{
		str[i] = s1[i];
		i ++;
	}
	str[i] = '\0';
	return (str);
}

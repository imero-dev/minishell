/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 01:45:08 by ivromero          #+#    #+#             */
/*   Updated: 2023/05/18 17:52:15 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	result = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (s[++i])
		result[i] = (*f)(i, s[i]);
	return (result);
}

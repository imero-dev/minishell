/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.45urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:08:03 by ivromero          #+#    #+#             */
/*   Updated: 2024/04/08 04:21:28 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}

char	*ft_strjoinfree1(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}

char	*ft_strjoinfree2(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s2);
	return (str);
}

char	*ft_strjoinglue(char const *glue, ...)
{
	va_list	args;
	char	*str;
	char	*tmp;

	va_start(args, glue);
	str = va_arg(args, char *);
	if (!str)
		return (va_end(args), ft_strdup(""));
	tmp = va_arg(args, char *);
	if (!tmp)
		return (va_end(args), str);
	while (tmp)
	{
		str = ft_strjoinfree1(str, (char *)glue);
		str = ft_strjoinfree(str, tmp);
		tmp = va_arg(args, char *);
	}
	return (va_end(args), str);
}

char	*ft_strjoinmulti(char const *first, ...)
{
	va_list	args;
	char	*str;
	char	*tmp;

	va_start(args, first);
	str = ft_strdup(first);
	tmp = va_arg(args, char *);
	while (tmp)
	{
		str = ft_strjoinfree(str, tmp);
		tmp = va_arg(args, char *);
	}
	return (va_end(args), str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:57:27 by ivromero          #+#    #+#             */
/*   Updated: 2023/05/02 12:58:21 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strnxtw(char const **s, char c, int *wc)
{
	*wc = *wc + 1;
	while (**s != c && **s)
		*s = *s + 1;
}

static int	ft_strwc(char const *s, char c)
{
	int	wc;

	wc = 0;
	while (*s)
		if (*s != c)
			ft_strnxtw(&s, c, &wc);
	else
		s++;
	return (wc);
}

static int	ft_strwlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s == c)
		s++;
	while (*s != c && *s++)
		len++;
	return (len);
}

static char	*ft_strwcpy(char const **s, char c, int i, char ***ret)
{
	int	malloc_error;

	malloc_error = 0;
	while (**s == c)
		*s = *s + 1;
	(*ret)[i] = (char *)malloc(sizeof(char) * (ft_strwlen(*s, c) + 1));
	if (!(*ret)[i])
		malloc_error = 1;
	if (malloc_error)
		while (i)
			free((*ret)[--i]);
	if (malloc_error)
		return (NULL);
	ft_strlcpy((*ret)[i], *s, ft_strwlen(*s, c) + 1);
	*s += ft_strwlen(*s, c);
	return ((*ret)[i]);
}

char	**ft_split(char const *s, char c)
{
	int		wc;
	char	**ret;
	int		i;

	if (!s)
		return (NULL);
	wc = ft_strwc(s, c);
	ret = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < wc)
		if (!ft_strwcpy(&s, c, i++, &ret))
			return (free(ret), NULL);
	ret[i] = NULL;
	return (ret);
}

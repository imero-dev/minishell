/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:21:12 by ivromero          #+#    #+#             */
/*   Updated: 2023/05/02 20:14:53 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_mem(char *str, long n)
{
	if (n < 0)
		*str = '-';
	if (n < 0)
		n = -n;
	if (n > 9)
		ft_putnbr_mem(str, n / 10);
	while (*str != '\0')
		str++;
	*str = n % 10 + '0';
}

static int	ft_strnbrlen(int n)
{
	size_t	len;

	len = (n <= 0);
	while (n)
		n /= 10 + (int)(0 * ++len);
	return (len);
}

char	*ft_itoa(int n)
{
	char	*nbr;

	nbr = ft_calloc(ft_strnbrlen(n) + 1, sizeof(char));
	if (nbr)
		ft_putnbr_mem(nbr, n);
	return (nbr);
}

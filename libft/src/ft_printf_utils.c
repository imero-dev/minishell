/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:09:31 by ivromero          #+#    #+#             */
/*   Updated: 2024/01/17 17:08:14 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putcharcnt(char c, int *count)
{
	write(1, &c, 1);
	*count += 1;
}

void	ft_putstrcnt(char *s, int *count)
{
	if (s)
		while (*s)
			ft_putcharcnt(*s++, count);
	else
		ft_putstrcnt("(null)", count);
}

void	ft_putnbrcnt(long n, int *count)
{
	if (n < 0)
		ft_putcharcnt('-', count);
	if (n < 0)
		n = -n;
	if (n >= 10)
		ft_putnbrcnt(n / 10, count);
	if (n >= 10)
		ft_putnbrcnt(n % 10, count);
	else
		ft_putcharcnt(n + '0', count);
}

void	ft_puthexcnt(unsigned long int n, int ucase, int prefix,
		int *count)
{
	char	*str;
	char	*str_u;

	str = "0123456789abcdef";
	str_u = "0123456789ABCDEF";
	if (prefix)
		ft_putstrcnt("0x", count);
	if (n >= 16)
		ft_puthexcnt(n / 16, ucase, 0, count);
	if (n >= 16)
		ft_puthexcnt(n % 16, ucase, 0, count);
	else if (ucase)
		ft_putcharcnt(str_u[n], count);
	else
		ft_putcharcnt(str[n], count);
}

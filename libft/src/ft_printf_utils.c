/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:09:31 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/27 00:37:37 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putcharcnt(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putstrcnt(char *s, int fd)
{
	int	count;

	count = 0;
	if (s)
		while (*s)
			count += ft_putcharcnt(*s++, fd);
	else
		count += ft_putstrcnt("(null)", fd);
	return (count);
}

int	ft_putnbrcnt(long n, int fd)
{
	int	count;

	count = 0;
	if (n < 0)
		count += ft_putcharcnt('-', fd);
	if (n < 0)
		n = -n;
	if (n >= 10)
		count += ft_putnbrcnt(n / 10, fd);
	if (n >= 10)
		count += ft_putnbrcnt(n % 10, fd);
	else
		count += ft_putcharcnt(n + '0', fd);
	return (count);
}

int	ft_puthexcnt(unsigned long int n, int ucase, int prefix, int fd)
{
	char	*str;
	char	*str_u;
	int		count;

	count = 0;
	str = "0123456789abcdef";
	str_u = "0123456789ABCDEF";
	if (prefix)
		count += ft_putstrcnt("0x", fd);
	if (n >= 16)
		count += ft_puthexcnt(n / 16, ucase, 0, fd);
	if (n >= 16)
		count += ft_puthexcnt(n % 16, ucase, 0, fd);
	else if (ucase)
		count += ft_putcharcnt(str_u[n], fd);
	else
		count += ft_putcharcnt(str[n], fd);
	return (count);
}

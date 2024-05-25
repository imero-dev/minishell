/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.45urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 00:53:42 by ivromero          #+#    #+#             */
/*   Updated: 2024/04/08 01:33:12 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printconv(char c, va_list args, int *count)
{
	if (c == 'c')
		ft_putcharcnt((char)va_arg(args, int), count);
	if (c == 's')
		ft_putstrcnt(va_arg(args, char *), count);
	if (c == 'd' || c == 'i')
		ft_putnbrcnt(va_arg(args, int), count);
	if (c == 'u')
		ft_putnbrcnt(va_arg(args, unsigned int), count);
	if (c == 'x')
		ft_puthexcnt(va_arg(args, unsigned int), 0, 0, count);
	if (c == 'X')
		ft_puthexcnt(va_arg(args, unsigned int), 1, 0, count);
	if (c == '%')
		ft_putcharcnt('%', count);
	if (c == 'p')
		ft_puthexcnt(va_arg(args, unsigned long int), 0, 1, count);
}

/*
** Función para imprimir en consola solo si debug es verdadero.
** Tambien deberia sacar por stderr los errores. Hay que modificar
*/
int	ft_printf_debug(char const *format, int debug, ...)
{
	va_list		args;
	const char	*p;
	int			count;

	if (!format || !debug)
		return (-1);
	p = format - 1;
	count = 0;
	count += write(1, RED, 5);
	va_start(args, debug);
	while (*++p != '\0')
		if (*p == '%')
			ft_printconv(*++p, args, &count);
	else
		ft_putcharcnt(*p, &count);
	va_end(args);
	count += write(1, RESET, 4);
	return (count);
}

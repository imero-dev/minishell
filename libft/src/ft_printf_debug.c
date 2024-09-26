/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 00:53:42 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/27 00:35:34 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printconv(char c, va_list args, int *fd)
{
	if (c == 'c')
		return (ft_putcharcnt((char)va_arg(args, int), *fd));
	if (c == 's')
		return (ft_putstrcnt(va_arg(args, char *), *fd));
	if (c == 'd' || c == 'i')
		return (ft_putnbrcnt(va_arg(args, int), *fd));
	if (c == 'u')
		return (ft_putnbrcnt(va_arg(args, unsigned int), *fd));
	if (c == 'x')
		return (ft_puthexcnt(va_arg(args, unsigned int), 0, 0, *fd));
	if (c == 'X')
		return (ft_puthexcnt(va_arg(args, unsigned int), 1, 0, *fd));
	if (c == '%')
		return (ft_putcharcnt('%', *fd));
	if (c == 'p')
		return (ft_puthexcnt(va_arg(args, unsigned long int), 0, 1, *fd));
	if (c == '?')
		*fd = va_arg(args, int);
	if (c == '!')
		*fd = STDERR_FILENO;
	if (c == '$')
		*fd = STDOUT_FILENO;
	if (c == '*')
		perror("");
	return (0);
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
	int			fd;

	fd = 1;
	if (!format || !debug)
		return (-1);
	p = format - 1;
	count = 0;
	count += write(1, RED, 5);
	va_start(args, debug);
	while (*++p != '\0')
		if (*p == '%')
			count += ft_printconv(*++p, args, &fd);
	else
		count += ft_putcharcnt(*p, fd);
	va_end(args);
	count += write(1, RESET, 4);
	return (count);
}

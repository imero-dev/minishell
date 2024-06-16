/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:09:31 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/15 23:43:18 by ivromero         ###   ########.fr       */
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

int	ft_printf(char const *format, ...)
{
	va_list		args;
	const char	*p;
	int			count;
	int			fd;

	fd = 1;
	if (!format)
		return (-1);
	p = format - 1;
	count = 0;
	va_start(args, format);
	while (*++p != '\0')
		if (*p == '%')
			count += ft_printconv(*++p, args, &fd);
		else
			count += ft_putcharcnt(*p, fd);
	va_end(args);
	return (count);
}

/*
#include <limits.h>

int	main(void)
{
	int	num;

	ft_printf("\001\002\007\v\010\f\r\n", '1');
	ft_printf("Caracter: %c\n", 'a');
	ft_printf("Cadena: %s\n", "Hola, mundo");
	num = 10;
	ft_printf("Puntero: %p\n", &num);
	ft_printf("Entero: %d\n", num);
	ft_printf("Entero: %i\n", num);
	ft_printf("Entero sin signo: %u\n", 100);
	ft_printf("Entero en hexadecimal (minúsculas): %x\n", 200);
	ft_printf("Entero en hexadecimal (mayúsculas): %X\n", 200);
	ft_printf("Signo de porcentaje: %%\n");
	ft_printf("Entero: %i\n", 0);
	ft_printf("Entero: %i\n", INT_MIN);
	ft_printf("Entero: %i\n", INT_MAX);
	ft_printf("Cadena vacia: %s\n", "");
	ft_printf("Cadena puntero NULL: %s\n", NULL);
	ft_printf("Puntero nulo: %p\n", NULL);
	ft_printf("Varios: %xxx%%__%i %d__%X\n", 101, num, num +1, 100);
	ft_printf("Valor retorno: %d\n", ft_printf("%d\n", 12345678) );
	return (0);
}
*/

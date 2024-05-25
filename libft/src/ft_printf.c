/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 00:09:31 by ivromero          #+#    #+#             */
/*   Updated: 2024/01/17 17:05:52 by ivromero         ###   ########.fr       */
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

int	ft_printf(char const *format, ...)
{
	va_list		args;
	const char	*p;
	int			count;

	if (!format)
		return (-1);
	p = format - 1;
	count = 0;
	va_start(args, format);
	while (*++p != '\0')
		if (*p == '%')
			ft_printconv(*++p, args, &count);
	else
		ft_putcharcnt(*p, &count);
	va_end(args);
	return (count);
}

/*
#include <limits.h>

int	main(void)
{
	ft_printf("\001\002\007\v\010\f\r\n", '1');

	ft_printf("Caracter: %c\n", 'a');
	ft_printf("Cadena: %s\n", "Hola, mundo");

	int num = 10;
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

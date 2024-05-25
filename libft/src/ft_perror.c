/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:34:37 by ivromero          #+#    #+#             */
/*   Updated: 2024/04/30 15:21:07 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** imprime un mensaje de error en la salida estándar de error
** y sale del programa con el código de salida especificado.
** El tercer parametro es un int que se usa para:
** 1 imprimir un mensaje de advertencia
** 0 imprimir un mensaje de error
** -1 imprimir solo "Error" sin color
** puedes meter mas parametros con llamadas a funciones para liberar memoria:
** ft_perror("Error: ", ERR_X , -1, free(ptr), free(ptr2));
*/
void	ft_perror(char *str, int status, ...)
{
	va_list	args;
	int		opt;

	va_start(args, status);
	opt = va_arg(args, int);
	if (opt == -1)
		ft_putstr_fd("Error", STDERR_FILENO);
	else if (va_arg(args, int) == 1)
		ft_putstr_fd(YELLOW "Warning: " RESET, STDERR_FILENO);
	else
		ft_putstr_fd(RED "Error: " RESET, STDERR_FILENO);
	if (opt > 0)
		ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	va_end(args);
	exit(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:34:37 by ivromero          #+#    #+#             */
/*   Updated: 2024/06/16 17:13:39 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** imprime un mensaje de error en la salida estándar de error
** opt:
** 0 imprimir solo el texto sin color
** 1 imprimir un mensaje de advertencia
** 2 imprimir un mensaje de error
** -1 imprimir solo "Error" sin color
*/
void	ft_perror(char *str, int opt)
{
	/* perror(str);
	return ;	 */
	if (opt == -1)
		ft_putstr_fd("Error", STDERR_FILENO);
	else if (opt == 1)
		ft_putstr_fd(YELLOW "Warning: " RESET, STDERR_FILENO);
	else if (opt == 2)
		ft_putstr_fd(RED "Error: " RESET, STDERR_FILENO);
	if (opt >= 0)
		ft_putstr_fd(str, STDERR_FILENO);
	//ft_putstr_fd("\n", STDERR_FILENO);
}

/*
** imprime un mensaje de error en la salida estándar de error
** y sale del programa con el código de salida especificado.
** El tercer parametro es un int que se usa para:
** 0 imprimir solo el texto sin color
** 1 imprimir un mensaje de advertencia
** 2 imprimir un mensaje de error
** -1 imprimir solo "Error" sin color
** puedes meter mas parametros con llamadas a funciones para liberar memoria:
** ft_perror("Error: ", ERR_X , -1, free(ptr), free(ptr2));
*/
void	ft_perror_exit(char *str, int status, ...)
{
	va_list	args;
	int		opt;

	va_start(args, status);
	opt = va_arg(args, int);
	ft_perror(str, opt);
	va_end(args);
	exit(status);
}

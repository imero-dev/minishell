/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:18:59 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/27 00:36:02 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	nb;

	errno = 0;
	sign = 1;
	nb = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (!ft_isdigit(str[i]))
		errno = EINVAL;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb > LLONG_MAX / 10 || (nb == LLONG_MAX / 10 && (str[i++]
					- '0') > LLONG_MAX % 10))
			errno = ERANGE;
		nb = (nb * 10) + (str[i++] - '0') * sign;
	}
	if (!(ft_isdigit(str[i]) || ft_isspace(str[i]) || str[i] == '\0'))
		errno = EINVAL;
	return (nb);
}

long	ft_atol(const char *str)
{
	long long	nb;

	nb = ft_atoll(str);
	if (nb > LONG_MAX || nb < LONG_MIN)
		errno = ERANGE;
	return ((long)nb);
}

int	ft_atoi(const char *str)
{
	long long	nb;

	nb = ft_atoll(str);
	if (nb > INT_MAX || nb < INT_MIN)
		errno = ERANGE;
	return ((int)nb);
}

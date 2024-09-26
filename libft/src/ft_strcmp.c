/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:25:13 by ivromero          #+#    #+#             */
/*   Updated: 2024/09/27 00:35:46 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (0);
	return (ft_strncmp(s1, s2, ft_strlen(s1) + 1));
}

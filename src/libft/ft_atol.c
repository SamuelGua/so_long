/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:42:16 by scely             #+#    #+#             */
/*   Updated: 2024/01/22 18:02:48 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *c)
{
	long	i;
	long	res;
	long	minus;

	i = 0;
	res = 0;
	minus = 1;
	while (c[i] == 32 || (c[i] >= 9 && c[i] <= 13))
		i++;
	if (c[i] == 45)
	{
		i++;
		minus = -1;
	}
	else if (c[i] == 43)
		i++;
	while (c[i] >= 48 && c[i] <= 57)
	{
		res = 10 * res + (c[i] - '0');
		i++;
	}
	return (res * minus);
}

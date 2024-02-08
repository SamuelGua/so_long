/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:24:46 by scely             #+#    #+#             */
/*   Updated: 2024/02/08 20:27:20 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_found2(t_maps *maps, char c)
{
	if (maps->maps[maps->pos_x + 1][maps->pos_y] == c
		|| maps->maps[maps->pos_x - 1][maps->pos_y] == c
		|| maps->maps[maps->pos_x][maps->pos_y + 1] == c
		|| maps->maps[maps->pos_x][maps->pos_y - 1] == c)
		return (0);
	return (1);
}

int	found_posv(t_maps *maps)
{
	maps->pos_x = 0;
	maps->pos_y = 0;
	while (maps->maps[maps->pos_x])
	{
		maps->pos_y = 0;
		while (maps->maps[maps->pos_x][maps->pos_y])
		{
			if (maps->maps[maps->pos_x][maps->pos_y] == 'V')
			{
				if (ft_found2(maps, '0') == 0 || ft_found2(maps, 'C') == 0
					|| ft_found2(maps, 'E') == 0)
					return (0);
			}
			maps->pos_y++;
		}
		maps->pos_x++;
	}
	return (1);
}

int	found_pos(t_maps *maps, char c)
{
	maps->pos_x = 0;
	while (maps->maps[maps->pos_x] && c == 'P')
	{
		maps->pos_y = 0;
		while (maps->maps[maps->pos_x][maps->pos_y])
		{
			if (maps->maps[maps->pos_x][maps->pos_y] == c)
				return (0);
			maps->pos_y++;
		}
		maps->pos_x++;
	}
	maps->exit_x = 0;
	while (maps->maps[maps->exit_x] && c == 'E')
	{
		maps->exit_y = 0;
		while (maps->maps[maps->exit_x][maps->exit_y])
		{
			if (maps->maps[maps->exit_x][maps->exit_y] == c)
				return (0);
			maps->exit_y++;
		}
		maps->exit_x++;
	}
	return (1);
}

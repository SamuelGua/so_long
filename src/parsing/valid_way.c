/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_way.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:59:28 by scely             #+#    #+#             */
/*   Updated: 2024/02/08 20:25:58 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	filling(t_maps *maps, int x, int y)
{
	maps->maps[maps->pos_x][maps->pos_y] = 'V';
	if (maps->maps[maps->pos_x][maps->pos_y] == '1')
		return (0);
	if (maps->maps[maps->pos_x][maps->pos_y + 1] != '1'
		&& maps->maps[maps->pos_x][maps->pos_y + 1] != 'V')
		filling(maps, maps->pos_x, maps->pos_y++);
	if (maps->maps[maps->pos_x + 1][maps->pos_y] != '1'
		&& maps->maps[maps->pos_x + 1][maps->pos_y] != 'V')
		filling(maps, maps->pos_x++, maps->pos_y);
	if (maps->maps[maps->pos_x - 1][maps->pos_y] != '1'
		&& maps->maps[maps->pos_x - 1][maps->pos_y] != 'V')
		filling(maps, maps->pos_x--, maps->pos_y);
	if (maps->maps[maps->pos_x][maps->pos_y - 1] != '1'
		&& maps->maps[maps->pos_x][maps->pos_y - 1] != 'V')
		filling(maps, maps->pos_x, maps->pos_y--);
	return (0);
	(void) x;
	(void) y;
}

int	flood_fill(t_maps *maps)
{
	found_pos(maps, 'P');
	filling(maps, maps->pos_x, maps->pos_y);
	while (found_posv(maps) == 0)
		filling(maps, maps->pos_x, maps->pos_y);
	return (0);
}

int	check_ways(t_maps *maps)
{
	int	i;
	int	j;

	i = 0;
	while (maps->maps[i])
	{
		j = 0;
		while (maps->maps[i][j] && maps->maps[i][j] != '\n')
		{
			if (maps->maps[i][j] == 'E' || maps->maps[i][j] == 'C')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

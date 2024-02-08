/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:36:59 by scely             #+#    #+#             */
/*   Updated: 2024/02/08 17:31:19 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_wall(t_maps *maps)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (maps->maps[i][j] && maps->maps[i][j] == '1')
		j++;
	while (maps->maps[maps->y - 1][k] && maps->maps[maps->y - 1][k] == '1')
		k++;
	if (j == len_line(maps->maps[i]) && k == len_line(maps->maps[i]))
		j = 0;
	else
		return (1);
	while (i + 1 < maps->y)
	{
		if (maps->maps[i][j] != '1' || maps->maps[i][len_line(maps->maps[i])
			- 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_item(t_maps *maps)
{
	int	i;
	int	j;

	i = 0;
	while (maps->maps[i])
	{
		j = 0;
		while (maps->maps[i][j])
		{
			if (maps->maps[i][j] == 'P')
				maps->items.p++;
			if (maps->maps[i][j] == 'C')
				maps->items.c++;
			if (maps->maps[i][j] == 'E')
				maps->items.e++;
			j++;
		}
		i++;
	}
	if (maps->items.p != 1 || maps->items.c < 1 || maps->items.e != 1)
		return (1);
	return (0);
}

int	check_maps(t_maps *maps)
{
	int	y;

	y = 0;
	while (maps->maps[y] != NULL)
	{
		if (check_param(maps->maps[y]) != 0)
			return (1);
		if (len_line(maps->maps[0]) != len_line(maps->maps[y]) && y != 0)
			return (1);
		y++;
	}
	if (check_item(maps) != 0)
		return (1);
	return (0);
}

int	check_final(t_maps *maps)
{
	int	i;
	int	j;

	i = 0;
	while (maps->maps[i])
	{
		j = 0;
		while (maps->maps[i][j])
		{
			if (maps->maps[i][j] == 'P')
				maps->items.p++;
			if (maps->maps[i][j] == 'C')
				maps->items.c++;
			if (maps->maps[i][j] == 'E')
				maps->items.e++;
			j++;
		}
		i++;
	}
	if (maps->items.p != 0 || maps->items.c != 0 || maps->items.e != 0)
		return (1);
	return (0);
}

int	parsing(t_maps *maps_param, char **av)
{
	if (maps_param == NULL)
		return (ft_putstr_fd("Error malloc\n", 2), 1);
	size_map(av, maps_param);
	if (fill_maps(av, maps_param) != 0)
		return (ft_error(maps_param), 1);
	if (check_wall(maps_param) != 0 || check_maps(maps_param) != 0)
		return (ft_error(maps_param), 1);
	if (flood_fill(maps_param) != 0 || check_ways(maps_param) != 0)
		return (ft_error(maps_param), 1);
	ft_free(maps_param->maps);
	fill_maps(av, maps_param);
	found_pos(maps_param, 'E');
	return (0);
}

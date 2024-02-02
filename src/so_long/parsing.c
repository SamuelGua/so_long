/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:36:59 by scely             #+#    #+#             */
/*   Updated: 2024/02/02 14:04:41 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	len_line(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '\n')
		i++;
	return (i);
}

int	check_wall(t_maps *maps)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (maps->maps[i][j] && maps->maps[i][j] == '1')
		j++;
	if (j == len_line(maps->maps[i]))
		j = 0;
	else
		return (1);
	while (maps->maps[maps->y - 1][j] && maps->maps[maps->y - 1][j] == '1')
		j++;
	if (j == len_line(maps->maps[i]))
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

int	size_map(char **av, t_maps **maps)
{
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return (1);
	(*maps)->y = 1;
	(*maps)->x = ft_strlen(line);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			return (1);
		(*maps)->y++;
	}
	free(line);
	close(fd);
	return (0);
}

int	fill_maps(char **av, t_maps **maps)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(av[1], O_RDONLY);
	(*maps)->maps = ft_calloc(sizeof(char *), ((*maps)->y + 1));
	if ((*maps)->maps == NULL)
		return (1);
	(*maps)->maps[(*maps)->y] = NULL;
	while (!(*maps)->maps[i] && i < (*maps)->y + 1)
	{
		(*maps)->maps[i] = get_next_line(fd);
		i++;
	}
	i = 0;
	while ((*maps)->maps[i])
	{
		if (ft_strlen((*maps)->maps[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_param(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != 'C' && str[i] != 'E'
			&& str[i] != 'P' && str[i] != '\n')
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

int	check_maps(t_maps **maps)
{
	int	x;
	int	y;

	y = 0;
	while ((*maps)->maps[y] != NULL)
	{
		if (check_param((*maps)->maps[y]) != 0)
			return (ft_putstr_fd("mauvaise param\n", 1), 1);
		if (len_line((*maps)->maps[0]) != len_line((*maps)->maps[y]) && y != 0)
			return (ft_putstr_fd("mauvaise len\n", 1), 1);
		y++;
	}
	if (check_item((*maps)) != 0)
		return (ft_putstr_fd("mauvaise item\n", 1), 1);
	return (0);
}

int	check_final(t_maps **maps)
{
	int	i;
	int	j;

	i = 0;
	while ((*maps)->maps[i])
	{
		j = 0;
		while ((*maps)->maps[i][j])
		{
			if ((*maps)->maps[i][j] == 'P')
				(*maps)->items.p++;
			if ((*maps)->maps[i][j] == 'C')
				(*maps)->items.c++;
			if ((*maps)->maps[i][j] == 'E')
				(*maps)->items.e++;
			j++;
		}
		i++;
	}
	if ((*maps)->items.p != 0 || (*maps)->items.c != 0 || (*maps)->items.e != 0)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_maps	*maps_param;
	int		i;

	if (av[1] == NULL)
		return (1);
	i = 0;
	maps_param = ft_calloc(sizeof(t_maps), 1);
	if (maps_param == NULL)
		return (ft_putstr_fd("Error\n"), 2);
	size_map(av, &maps_param);
	if (fill_maps(av, &maps_param) != 0)
	{
		if ((*maps_param).maps != NULL)
			ft_free((*maps_param).maps);
		return (ft_putstr_fd("Error\n", 1), 1);
	}
	check_maps(&maps_param);
	i = check_wall(maps_param);
	if (i == 1)
		return (ft_putstr_fd("wall wrong", 1), 1);
	flood_fill(&maps_param);
	i = 0;
	while (maps_param->maps[i] != NULL)
	{
		printf("%d\t%s", i, (maps_param->maps[i]));
		i++;
	}
}

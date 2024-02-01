/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:36:59 by scely             #+#    #+#             */
/*   Updated: 2024/02/01 12:09:30 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int len_line(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '\n')
		i++;
	return (i);
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
	(*maps)->maps[(*maps)->y] = (char *) '\0';
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
		if (str[i] != '0' && str[i] != '1' && str[i] != 'C'
				&& str[i] != 'E' && str[i] != 'P' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	check_item(t_maps *maps)
{
	int i;
	int j;

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
	if (maps->items.p != 1 || maps->items.c < 1 
		|| maps->items.e != 1)
		return (1);
	return (0);
}

int	check_maps(t_maps **maps)
{
	int	x;
	int y;

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
		return (ft_putstr_fd("mauvaise item\n", 1),1); 
	return (0);
}

int	main(int ac, char **av)
{
	t_maps	*maps_param;
	int			i;
	if (av[1] == NULL)
		return (1);
	i = 0;
	maps_param = ft_calloc(sizeof(t_maps), 1);
	size_map(av, &maps_param);	

	if(fill_maps(av, &maps_param) != 0)
	 {
		if ((*maps_param).maps != NULL)
			ft_free((*maps_param).maps);
		return (ft_putstr_fd("Error\n", 1), 1);
	}
	check_maps(&maps_param);
	i = 0;
	flood_fill(&maps_param);
	while (maps_param->maps[i] != NULL)
	{
		printf("%d\t%s", i, (maps_param->maps[i]));
		i++;
	}
}

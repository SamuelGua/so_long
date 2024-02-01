/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meca_971 <meca_971@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:36:59 by scely             #+#    #+#             */
/*   Updated: 2024/01/31 23:07:35 by meca_971         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct maps_items
{
	int p;
	int c;
	int e;
}	t_items;

typedef struct maps_size
{
	int		y; // abscisse | nombres de lignes
	int		x; // ordonne | nombres de colonnes
	char	**maps; // tout mon fichier
	t_items maps_size;
}	t_maps_size;

int len_line(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '\n')
		i++;
	return (i);
}

int	size_map(char **av, t_maps_size **maps)
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

int	fill_maps(char **av, t_maps_size **maps)
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

int	check_item(t_maps_size *maps)
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
				maps->maps_size.p++;
			if (maps->maps[i][j] == 'C')
				maps->maps_size.c++;
			if (maps->maps[i][j] == 'E')
				maps->maps_size.e++;
			j++;
		}
		i++;
	}
	printf("check_item p = %d\t| c = %d\t| e = %d\n", maps->maps_size.p, maps->maps_size.c, maps->maps_size.e);
	if (maps->maps_size.p != 1 || maps->maps_size.c < 1 
		|| maps->maps_size.e != 1)
		return (1);
	return (0);
}

int	check_maps(t_maps_size **maps)
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
		printf("%s", (*maps)->maps[y]);
		y++;
	}
	if (check_item((*maps)) != 0)
		return (ft_putstr_fd("mauvaise item\n", 1),1); 
	return (0);
}

int	main(int ac, char **av)
{
	t_maps_size	*maps_param;
	int			i;
	if (av[1] == NULL)
		return (1);
	i = 0;
	maps_param = ft_calloc(sizeof(t_maps_size), 1);
	size_map(av, &maps_param);	

	if(fill_maps(av, &maps_param) != 0)
	 {
		if ((*maps_param).maps != NULL)
			ft_free((*maps_param).maps);
		return (ft_putstr_fd("Error\n", 1), 1);
	}

	i = check_maps(&maps_param);
	printf("check_maps %d\n", i);
	
	printf("%d\t%d\n", maps_param->x, maps_param->y);
	printf("==============================\n");
	i = 0;
	while (maps_param->maps[i] != NULL)
	{
		printf("strlen %zu\t",ft_strlen(maps_param->maps[i]));
		printf("%d\t%s", i, (maps_param->maps[i]));
		i++;
	}
}

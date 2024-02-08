/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:09:02 by meca_971          #+#    #+#             */
/*   Updated: 2024/02/08 18:00:04 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error(t_maps *maps)
{
	if (maps->maps != NULL)
		ft_free(maps->maps);
	free(maps);
	ft_putstr_fd("Error : invalid maps\n", 2);
}

int	len_line(char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '\n')
		i++;
	return (i);
}

int	size_map(char **av, t_maps *maps)
{
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	if (line == NULL)
		return (1);
	maps->y = 1;
	maps->x = ft_strlen(line);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			return (close(fd), 1);
		maps->y++;
	}
	free(line);
	close(fd);
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

int	fill_maps(char **av, t_maps *maps)
{
	int		fd;
	int		i;

	i = 0;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (1);
	maps->maps = ft_calloc(sizeof(char *), (maps->y + 2));
	if (maps->maps == NULL)
		return (1);
	while (!maps->maps[i] && i < maps->y + 1)
	{
		maps->maps[i] = get_next_line(fd);
		if (i == 0 && maps->maps[i] == NULL)
			return (1);
		i++;
	}
	i = 0;
	while (maps->maps[i])
	{
		if (ft_strlen(maps->maps[i]) == 1)
			return (close(fd), 1);
		i++;
	}
	return (close(fd), 0);
}

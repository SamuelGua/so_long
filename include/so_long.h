/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meca_971 <meca_971@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:51:21 by scely             #+#    #+#             */
/*   Updated: 2024/02/03 22:55:26 by meca_971         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include <fcntl.h>
//# include "../mlx/mlx.h"

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
    int     pos_y;
    int     pos_x;
	char	**maps; // tout mon fichier
	t_items items;
}	t_maps;

//parsing utils
void ft_error(t_maps *maps);
int	len_line(char *av);
int	size_map(char **av, t_maps *maps);
int	check_param(char *str);
int	fill_maps(char **av, t_maps *maps);

//parsing
int	check_wall(t_maps *maps);
int	check_item(t_maps *maps);
int	check_maps(t_maps *maps);
int	check_final(t_maps *maps);
int	parsing(t_maps *maps_param, char **av);

//valid_ways
int	found_posv(t_maps *maps);
int	found_pos(t_maps *maps);
int	filling(t_maps *maps, int x, int y);
int	flood_fill(t_maps *maps);
int check_ways(t_maps *maps);



#endif
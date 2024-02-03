/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meca_971 <meca_971@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:51:21 by scely             #+#    #+#             */
/*   Updated: 2024/02/03 21:44:25 by meca_971         ###   ########.fr       */
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

int	flood_fill(t_maps **maps);
int check_ways(t_maps *maps);

#endif
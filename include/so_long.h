/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:51:21 by scely             #+#    #+#             */
/*   Updated: 2024/02/01 12:11:49 by scely            ###   ########.fr       */
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

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 08:51:21 by scely             #+#    #+#             */
/*   Updated: 2024/02/05 15:09:21 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include <fcntl.h>
# include "../mlx/mlx.h"

typedef struct maps_items
{
	int	p;
	int	c;
	int	e;
}	t_items;

typedef struct maps_size
{
	int		y;
	int		x;
	int		pos_y;
	int		pos_x;
	char	**maps;
	t_items	items;
}	t_maps;

typedef	struct img_maps
{
	void	*wall;
	void	*floor;
	void	*collectible;
	void	*exit;
	void	*character;
}	t_img;

typedef struct mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_win;

typedef struct data_store
{
	t_maps	*maps;
	t_img	*image;
	t_win	*win;
}	t_data;


//parsing utils
void	ft_error(t_maps *maps);
int		len_line(char *av);
int		size_map(char **av, t_maps *maps);
int		check_param(char *str);
int		fill_maps(char **av, t_maps *maps);

//parsing
int		check_wall(t_maps *maps);
int		check_item(t_maps *maps);
int		check_maps(t_maps *maps);
int		check_final(t_maps *maps);
int		parsing(t_maps *maps_param, char **av);

//valid_ways
int		found_posv(t_maps *maps);
int		found_pos(t_maps *maps);
int		filling(t_maps *maps, int x, int y);
int		flood_fill(t_maps *maps);
int		check_ways(t_maps *maps);

//free
void free_maps(t_data *data);
void free_int(t_data *data);
void free_img(t_data *data);
int	close_window(t_data *data);

#endif
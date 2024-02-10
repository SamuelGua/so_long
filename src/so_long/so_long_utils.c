/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:45:58 by scely             #+#    #+#             */
/*   Updated: 2024/02/10 14:55:05 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// printf("x = %d | %d\ty = %d | %d\n", x, (x / 50), y, (y /50));
// printf("x = %d | %d\ty = %d | %d\n", ((data->maps->x) * 50), (data->maps->x),
// ((data->maps->y) * 50), (data->maps->y));
int	check_screen(t_data *data)
{
	int	x;
	int	y;

	mlx_get_screen_size(data->win->mlx_ptr, &x, &y);
	if (x < ((data->maps->x) * 50) || (y - 50) < ((data->maps->y) * 50))
	{
		mlx_destroy_display(data->win->mlx_ptr);
		free_maps(data);
		free(data->win->mlx_ptr);
		free(data->win);
		free(data);
		ft_putstr_fd("Error windows\n", 2);
		exit(1);
	}
	return (0);
}

void	put_img2(t_data *data, int i, int j)
{
	while (data->maps->maps[i][++j])
	{
		if (data->maps->maps[i][j] == '0')
			mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
				data->image->floor, j * 50, i * 50);
		else if (data->maps->maps[i][j] == '1')
			mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
				data->image->wall, j * 50, i * 50);
		else if (data->maps->maps[i][j] == 'C')
			mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
				data->image->collectible, j * 50, i * 50);
		else if (data->maps->maps[i][j] == 'P')
			mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
				data->image->character, j * 50, i * 50);
		else if (data->maps->maps[i][j] == 'E')
			mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr,
				data->image->exit, j * 50, i * 50);
	}
}

int	put_img(void *tmp)
{
	int		i;
	int		j;
	t_data	*data;

	data = (t_data *)tmp;
	i = -1;
	while (data->maps->maps[++i])
	{
		j = -1;
		put_img2(data, i, j);
	}
	return (0);
}

int	init_img(t_data *data)
{
	int	po;
	int	pa;

	data->image = ft_calloc(sizeof(t_img), 1);
	if (data->image == NULL)
		return (1);
	data->image->floor = mlx_xpm_file_to_image(data->win->mlx_ptr,
			"src/sprite/herbe_v2.xpm", &po, &pa);
	data->image->wall = mlx_xpm_file_to_image(data->win->mlx_ptr,
			"src/sprite/barriere.xpm", &po, &pa);
	data->image->character = mlx_xpm_file_to_image(data->win->mlx_ptr,
			"src/sprite/fantome_v-01.xpm", &po, &pa);
	data->image->collectible = mlx_xpm_file_to_image(data->win->mlx_ptr,
			"src/sprite/coins.xpm", &po, &pa);
	data->image->exit = mlx_xpm_file_to_image(data->win->mlx_ptr,
			"src/sprite/exit.xpm", &pa, &pa);
	if (data->image->character == NULL || data->image->collectible == NULL
		|| data->image->wall == NULL || data->image->wall == NULL)
	{
		(free_img(data), free_maps(data));
		mlx_destroy_display(data->win->mlx_ptr);
		(free(data->win->mlx_ptr), free(data->win));
		(free(data), exit(1));
	}
	return (0);
}

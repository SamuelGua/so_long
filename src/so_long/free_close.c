/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:06:38 by scely             #+#    #+#             */
/*   Updated: 2024/02/06 10:51:18 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_maps(t_data *data)
{
	ft_free(data->maps->maps);
	free(data->maps);
}

void free_int(t_data *data)
{
	mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);
	mlx_destroy_display(data->win->mlx_ptr);
	free(data->win->mlx_ptr);
    free(data->win);
}

void free_img(t_data *data)
{
	mlx_destroy_image(data->win->mlx_ptr, data->image->character);
	mlx_destroy_image(data->win->mlx_ptr, data->image->collectible);
	mlx_destroy_image(data->win->mlx_ptr, data->image->floor);
	mlx_destroy_image(data->win->mlx_ptr, data->image->wall);
    free(data->image);
}

int	close_window(t_data *data)
{
	free_img(data);
    free_maps(data);
	free_int(data);
	free(data);
	exit(1);	
}
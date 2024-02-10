/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:06:38 by scely             #+#    #+#             */
/*   Updated: 2024/02/10 15:09:02 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	env_error(t_data *data)
{
	ft_putstr_fd("Error no DISPLAY ENV mlx_init not init\n", 1);
	free(data->win);
	ft_free(data->maps->maps);
	free(data->maps);
	free(data);
	exit(1);
}

void	free_maps(t_data *data)
{
	ft_free(data->maps->maps);
	free(data->maps);
}

void	free_int(t_data *data)
{
	mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);
	mlx_destroy_display(data->win->mlx_ptr);
	free(data->win->mlx_ptr);
	free(data->win);
}

void	free_img(t_data *data)
{	
	if (data->image->character)
		mlx_destroy_image(data->win->mlx_ptr, data->image->character);
	if (data->image->collectible)
		mlx_destroy_image(data->win->mlx_ptr, data->image->collectible);
	if (data->image->floor)
		mlx_destroy_image(data->win->mlx_ptr, data->image->floor);
	if (data->image->wall)
		mlx_destroy_image(data->win->mlx_ptr, data->image->wall);
	if (data->image->exit)
		mlx_destroy_image(data->win->mlx_ptr, data->image->exit);
	free(data->image);
}

int	close_window(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < 4)
		ft_printf("\b\b\b\b\b\b\b\b\b\b\b\b\b");
	ft_printf("Your final score is %d 🤑 ", data->mouv);
	if (data->coins == data->maps->items.c)
		ft_printf("You have collected %d coins 💰\n", data->coins);
	else
		ft_printf("Fail only %d coins 💰\n", data->coins);
	free_img(data);
	free_maps(data);
	free_int(data);
	free(data);
	exit(1);
}

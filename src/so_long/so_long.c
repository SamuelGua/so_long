/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:41:23 by meca_971          #+#    #+#             */
/*   Updated: 2024/02/05 11:46:24 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_img(t_data *data)
{
	int	x;
	int y;
	int	i;
	int	j;

	data->image = ft_calloc(sizeof(t_img), 1);
	if (data->image == NULL)
		return (1);
	i = 0;
	data->image->floor = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/floor.xpm",
						&data->maps->pos_x, &data->maps->pos_y);
	while (data->maps->maps[i])
	{
		j = 0;
		while (data->maps->maps[i][j])
		{
			if (data->maps->maps[i][j] != '1')
			{
				y = i;
				x = j;
				mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr, 
					data->image->floor, x * 50, y * 50);

			}
			j++;
		}
		i++;
	}
	//data->image->character = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/charizard.xpm", &data->maps->pos_x, &data->maps->pos_y);
	//mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr, data->image->character, data->maps->pos_x, data->maps->pos_y);
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->win->mlx_ptr, data->win->win_ptr);
	mlx_destroy_display(data->win->mlx_ptr);
	free(data->win->mlx_ptr);
	
	ft_free(data->maps->maps);
	free(data->maps);
	free(data->win);
	free(data);
	exit(1);	
}

int	key_capt(int keycode, t_data *data)
{
	if (keycode == 65307)
		close_window(data);
	if (keycode == 'a' || keycode == 65361)
		ft_putstr_fd("Left <-\n", 1);
	if (keycode == 'd' || keycode == 65363)
		ft_putstr_fd("Right ->\n", 1);
	if (keycode == 'w' || keycode == 65362)
		ft_putstr_fd("Up ^\n", 1);
	if (keycode == 's' || keycode == 65364)
		ft_putstr_fd("Down V\n", 1);
	printf("the %d key has been pressed \n\n", keycode);
	return (0);
}

void fenetre(t_data *data)
{

	data->win = ft_calloc(sizeof(t_win), 1);
	if (data->win == NULL)
		return ;
	data->win->mlx_ptr = mlx_init();
	data->win->win_ptr = mlx_new_window(data->win->mlx_ptr, data->maps->x * 50, data->maps->y * 50, "so_long !");
	init_img(data);
	mlx_hook(data->win->win_ptr, 2, 1L << 0, key_capt, data);
	mlx_hook(data->win->win_ptr, 17, 1L << 17, close_window, data);
	mlx_loop(data->win->mlx_ptr);
}


int	main(int ac, char **av, char **envp)
{
	t_data *data;

	if (envp[0] == NULL || ac != 2)
		return (1);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	data->maps = ft_calloc(sizeof(t_maps), 1);
	if (data->maps == NULL)
		return (ft_putstr_fd("Error : Malloc\n", 1), 1);
	if (parsing(data->maps, av) != 0)
		return (1);
	fenetre(data);
	ft_free(data->maps->maps);
	free(data->maps);
	free(data);
}

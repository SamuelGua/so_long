/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:41:23 by meca_971          #+#    #+#             */
/*   Updated: 2024/02/10 16:38:03 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_capt(int keycode, t_data *data)
{
	found_pos(data->maps, 'P');
	if (keycode == 65307)
		close_window(data);
	game_exit(data, keycode);
	if ((keycode == 'a' || keycode == 65361)
		&& data->maps->maps[data->maps->pos_x][data->maps->pos_y - 1] != '1')
		made_mouv(data, keycode, 0, -1);
	else if ((keycode == 'd' || keycode == 65363)
		&& data->maps->maps[data->maps->pos_x][data->maps->pos_y + 1] != '1')
		made_mouv(data, keycode, 0, +1);
	else if ((keycode == 'w' || keycode == 65362)
		&& data->maps->maps[data->maps->pos_x - 1][data->maps->pos_y] != '1')
		made_mouv(data, keycode, -1, 0);
	else if ((keycode == 's' || keycode == 65364)
		&& data->maps->maps[data->maps->pos_x + 1][data->maps->pos_y] != '1')
		made_mouv(data, keycode, +1, 0);
	put_img(data);
	return (0);
}

void	protect_windows(t_data *data, char *str)
{
	ft_printf("%s\n", str);
	free(data->win);
	ft_free(data->maps->maps);
	free(data->maps);
	free(data);
	exit(1);
}

void	show_mlx(t_data *data)
{
	data->win = ft_calloc(sizeof(t_win), 1);
	if (data->win == NULL)
		return ;
	data->win->mlx_ptr = mlx_init();
	if (data->win->mlx_ptr == NULL)
		return (protect_windows(data, "Error no DISPLAY ENV"));
	check_screen(data);
	init_img(data);
	data->win->win_ptr = mlx_new_window(data->win->mlx_ptr,
			(data->maps->x - 1) * 50, data->maps->y * 50, "so_long !");
	if (data->win->win_ptr == NULL)
	{
		free(data->win->mlx_ptr);
		return (protect_windows(data, "Windows init"));
	}
	put_img(data);
	found_pos(data->maps, 'P');
	mlx_loop_hook(data->win->win_ptr, put_img, (void *)&data);
	mlx_hook(data->win->win_ptr, 2, 1L << 0, key_capt, data);
	mlx_hook(data->win->win_ptr, 17, 1L << 17, close_window, data);
	mlx_loop(data->win->mlx_ptr);
}

int	check_extension(char **av)
{
	int	i;
	int	x;

	i = ft_strlen(av[1]);
	x = 0;
	if (i > 4)
		if (av[1][i - 5] == '/')
			return (1);
	while (x < i - 4)
		x++;
	if (ft_strnstr(&av[1][x], ".ber", 4) == NULL || i <= 4)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (ft_putstr_fd("Error\n", 1), 1);
	if (check_extension(av) != 0)
		return (ft_putstr_fd("Error : wrong file extension\n", 2), 1);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	data->maps = ft_calloc(sizeof(t_maps), 1);
	if (data->maps == NULL)
		return (ft_putstr_fd("Error : Malloc\n", 1), 1);
	if (parsing(data->maps, av) != 0)
		return (free(data), 1);
	data->mouv = 0;
	data->coins = 0;
	show_mlx(data);
}

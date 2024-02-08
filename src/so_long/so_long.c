/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:41:23 by meca_971          #+#    #+#             */
/*   Updated: 2024/02/08 20:52:12 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	made_mouv(t_data *data, int keycode, int x, int y)
{
	data->maps->maps[data->maps->pos_x][data->maps->pos_y] = '0';
	score(data, keycode);
	if (y != 0 && y == -1)
		data->maps->maps[data->maps->pos_x][data->maps->pos_y - 1] = 'P';
	if (y != 0 && y == +1)
		data->maps->maps[data->maps->pos_x][data->maps->pos_y + 1] = 'P';
	if (x != 0 && x == -1)
		data->maps->maps[data->maps->pos_x - 1][data->maps->pos_y] = 'P';
	if (x != 0 && x == +1)
		data->maps->maps[data->maps->pos_x + 1][data->maps->pos_y] = 'P';
	if (data->maps->maps[data->maps->exit_x][data->maps->exit_y] == '0')
		data->maps->maps[data->maps->exit_x][data->maps->exit_y] = 'E';
}

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

void	fenetre(t_data *data)
{
	data->win = ft_calloc(sizeof(t_win), 1);
	if (data->win == NULL)
		return ;
	data->win->mlx_ptr = mlx_init();
	if (data->win->mlx_ptr == NULL)
	{
		ft_printf("Error no DISPLAY ENV mlx_init not init\n");
		free(data->win);
		ft_free(data->maps->maps);
		free(data->maps);
		free(data);
		exit(1);
	}
	check_screen(data);
	init_img(data);
	data->win->win_ptr = mlx_new_window(data->win->mlx_ptr,
			(data->maps->x - 1) * 50, data->maps->y * 50, "so_long !");
	put_img(data);
	found_pos(data->maps, 'P');
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
	while (x <= i - 4)
		x++;
	if (ft_strnstr(&av[1][x], ".ber", 5) == NULL)
		return (0);
	return (1);
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
	fenetre(data);
}

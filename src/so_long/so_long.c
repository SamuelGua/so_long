/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:41:23 by meca_971          #+#    #+#             */
/*   Updated: 2024/02/08 20:19:20 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_img(t_data *data)
{
	int	i;
	int	j;

	(mlx_clear_window(data->win->mlx_ptr, data->win->win_ptr), i = -1);
	while (data->maps->maps[++i])
	{
		j = -1;
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
}

int	init_img(t_data *data)
{
	int	po;
	int	pa;

	data->image = ft_calloc(sizeof(t_img), 1);
	if (data->image == NULL)
		return (1);
	data->image->floor = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/herbe_v2.xpm", &po, &pa);
	data->image->wall = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/barriere.xpm", &po, &pa);
	data->image->character = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/fantome_v-01.xpm", &po, &pa);
	data->image->collectible = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/coins.xpm", &po, &pa);
	data->image->exit = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/exit.xpm", &pa, &pa);
	if (data->image->character == NULL || data->image->collectible == NULL
		|| data->image->wall == NULL || data->image->wall == NULL)
	{
		free_img(data);
		free_maps(data);
		mlx_destroy_display(data->win->mlx_ptr);
		free(data->win->mlx_ptr);
		free(data->win);
		free(data);
		exit(1);
	}
	return (0);
}

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

void	score(t_data *data, int keycode)
{
	if ((keycode == 'a' || keycode == 65361)
		&& data->maps->maps[data->maps->pos_x][data->maps->pos_y - 1] == 'C')
		data->coins++;
	else if ((keycode == 'd' || keycode == 65363)
		&& data->maps->maps[data->maps->pos_x][data->maps->pos_y + 1] == 'C')
		data->coins++;
	else if ((keycode == 'w' || keycode == 65362)
		&& data->maps->maps[data->maps->pos_x - 1][data->maps->pos_y] == 'C')
		data->coins++;
	else if ((keycode == 's' || keycode == 65364)
		&& data->maps->maps[data->maps->pos_x + 1][data->maps->pos_y] == 'C')
		data->coins++;
	data->mouv++;
	ft_printf("\r\rScore = %d Coins = %d", data->mouv, data->coins);
}

void	game_exit(t_data *data, int keycode)
{
	if ((keycode == 'a' || keycode == 65361)
		&& data->maps->maps[data->maps->pos_x][data->maps->pos_y - 1] == 'E')
	{
		data->maps->maps[data->maps->pos_x][data->maps->pos_y] = '0';
		data->maps->maps[data->maps->pos_x][data->maps->pos_y - 1] = 'P';
		if (data->maps->items.c == data->coins)
			close_window(data);
	}
	else if ((keycode == 'd' || keycode == 65363)
		&& data->maps->maps[data->maps->pos_x][data->maps->pos_y + 1] == 'E')
	{
		data->maps->maps[data->maps->pos_x][data->maps->pos_y] = '0';
		data->maps->maps[data->maps->pos_x][data->maps->pos_y + 1] = 'P';
		if (data->maps->items.c == data->coins)
			close_window(data);
	}
	else if ((keycode == 'w' || keycode == 65362)
		&& data->maps->maps[data->maps->pos_x - 1][data->maps->pos_y] == 'E')
	{
		data->maps->maps[data->maps->pos_x][data->maps->pos_y] = '0';
		data->maps->maps[data->maps->pos_x - 1][data->maps->pos_y] = 'P';
		if (data->maps->items.c == data->coins)
			close_window(data);

	}
	else if ((keycode == 's' || keycode == 65364)
		&& data->maps->maps[data->maps->pos_x + 1][data->maps->pos_y] == 'E')
	{
		data->maps->maps[data->maps->pos_x][data->maps->pos_y] = '0';
		data->maps->maps[data->maps->pos_x + 1][data->maps->pos_y] = 'P';
		if (data->maps->items.c == data->coins)
			close_window(data);
	}

}

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
	data->win->win_ptr = mlx_new_window(data->win->mlx_ptr, (data->maps->x - 1) * 50, data->maps->y * 50, "so_long !");
	put_img(data);
	found_pos(data->maps, 'P');
	mlx_hook(data->win->win_ptr, 2, 1L << 0, key_capt, data);
	mlx_hook(data->win->win_ptr, 17, 1L << 17, close_window, data);
	mlx_loop(data->win->mlx_ptr);
}
int	check_extension(char **av)
{
	int	i;
	int x;

	i = ft_strlen(av[1]);
	x = 0;
	while (x <= i - 4)
		x++;
	if (ft_strnstr(&av[1][x],".ber", 5) == NULL)
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

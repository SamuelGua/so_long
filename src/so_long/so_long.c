/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:41:23 by meca_971          #+#    #+#             */
/*   Updated: 2024/02/07 12:19:20 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void put_img(t_data *data)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	mlx_clear_window(data->win->mlx_ptr,data->win->win_ptr);
	while (data->maps->maps[i])
	{
		j = 0;
		while (data->maps->maps[i][j])
		{
			(x = j);
			if (data->maps->maps[i][j] == '0' && data->maps->maps[i][j] != '\n')
				mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr, data->image->floor, x * 50, i * 50);
			else if (data->maps->maps[i][j] == '1' && data->maps->maps[i][j] != '\n')
				mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr, data->image->wall, x * 50, i * 50);
			else if (data->maps->maps[i][j] == 'C' && data->maps->maps[i][j] != '\n')
				mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr, data->image->collectible, x * 50, i * 50);
			if (data->maps->maps[i][j] == 'P' && data->maps->maps[i][j] != '\n')
				mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr, data->image->character, x * 50, i * 50);
			j++;
		}
		i++;
	}

}

int	init_img(t_data *data)
{
	int po;
	int pa;

	data->image = ft_calloc(sizeof(t_img), 1);
	if (data->image == NULL)
		return (1);
	data->image->floor = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/herbe_v2.xpm",
						&po, &pa);
	data->image->wall = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/barriere.xpm",
						&po, &pa);
	data->image->character = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/fantome_v-01.xpm",
						&po, &pa);
	data->image->collectible = mlx_xpm_file_to_image(data->win->mlx_ptr, "src/sprite/coins.xpm",
						&po, &pa);
	if (data->image->character == NULL || data->image->collectible == NULL
		|| data->image->wall == NULL || data->image->wall == NULL)
	{
		ft_putstr_fd("MERCI FILS\n", 1);
		exit(1);
	}
	put_img(data);
	return (0);

}

int	check_screen(t_data *data)
{
	int	x;
	int y;

	mlx_get_screen_size(data->win->mlx_ptr, &y, &x);
	printf("maps x = %d || y = %d\n", ((data->maps->pos_x - 1) * 50), ((data->maps->pos_y) * 50));
	printf("screen x = %d || y = %d\n", x, y);
	if (x < (data->maps->pos_x - 1) * 50 || y < (data->maps->pos_y) * 50)
	{
		mlx_destroy_display(data->win->mlx_ptr);
		free_maps(data);
		free(data->win->mlx_ptr);
		free(data->win);
		free(data);
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	return (0);
}

int	key_capt(int keycode, t_data *data)
{
	found_pos(data->maps);
	printf("x = %d | y = %d\n", data->maps->pos_x, data->maps->pos_y);
	if (keycode == 65307)
		close_window(data);
	for (int i = 0; data->maps->maps[i]; i++)
		printf("%i\t%s", i,data->maps->maps[i]);
	if ((keycode == 'a' || keycode == 65361) && data->maps->maps[data->maps->pos_x][data->maps->pos_y - 1] != '1')
	{
		ft_putstr_fd("Left <-\n", 1);
		data->maps->maps[data->maps->pos_x][data->maps->pos_y] = '0';
		data->maps->maps[data->maps->pos_x][data->maps->pos_y - 1] = 'P';
	}
	else if ((keycode == 'd' || keycode == 65363) && data->maps->maps[data->maps->pos_x][data->maps->pos_y + 1] != '1')
	{
		ft_putstr_fd("Right ->\n", 1);
		data->maps->maps[data->maps->pos_x][data->maps->pos_y] = '0';
		data->maps->maps[data->maps->pos_x][data->maps->pos_y + 1] = 'P';
	}
	else if ((keycode == 'w' || keycode == 65362) && data->maps->maps[data->maps->pos_x - 1][data->maps->pos_y] != '1')
	{
		ft_putstr_fd("Up ^\n", 1);
		data->maps->maps[data->maps->pos_x][data->maps->pos_y] = '0';
		data->maps->maps[data->maps->pos_x - 1][data->maps->pos_y] = 'P';

	}
	else if ((keycode == 's' || keycode == 65364) && data->maps->maps[data->maps->pos_x + 1][data->maps->pos_y] != '1')
	{
		ft_putstr_fd("Down V\n", 1);
		data->maps->maps[data->maps->pos_x][data->maps->pos_y] = '0';
		data->maps->maps[data->maps->pos_x + 1][data->maps->pos_y] = 'P';
	}
	put_img(data);
	for (int i = 0; data->maps->maps[i]; i++)
		printf("%i\t%s", i,data->maps->maps[i]);
	printf("the %d key has been pressed \n\n", keycode);
	return (0);
}

void fenetre(t_data *data)
{
	data->win = ft_calloc(sizeof(t_win), 1);
	if (data->win == NULL)
		return ;
	data->win->mlx_ptr = mlx_init();
	check_screen(data);
	data->win->win_ptr = mlx_new_window(data->win->mlx_ptr, (data->maps->x - 1) * 50, data->maps->y * 50, "so_long !");
	found_pos(data->maps);
	printf("x = %d | y = %d\n", data->maps->x, data->maps->y);
	printf("x = %d | y = %d\n", data->maps->pos_x, data->maps->pos_y);
	init_img(data);
	mlx_hook(data->win->win_ptr, 2, 1L << 0, key_capt, data);
	mlx_hook(data->win->win_ptr, 17, 1L << 17, close_window, data);
	//mlx_set_font(data->win->mlx_ptr, data->win->win_ptr, "-misc-*-*-*-*-ja-*-*-*-75-*-*-*-*");
	//mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, 25, 25, 0000000, "Wapwap");
	mlx_loop(data->win->mlx_ptr);
}


int	main(int ac, char **av, char **envp)
{
	t_data *data;

	if (!envp || ac != 2)
		return (1);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	data->maps = ft_calloc(sizeof(t_maps), 1);
	if (data->maps == NULL)
		return (ft_putstr_fd("Error : Malloc\n", 1), 1);
	if (parsing(data->maps, av) != 0)
		return (free(data), 1);
	fenetre(data);
}

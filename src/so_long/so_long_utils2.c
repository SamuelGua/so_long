/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:51:10 by scely             #+#    #+#             */
/*   Updated: 2024/02/10 15:27:04 by scely            ###   ########.fr       */
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

void	game_exit1(t_data *data, int keycode)
{
	if ((keycode == 'w' || keycode == 65362)
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
	else
		game_exit1(data, keycode);
}

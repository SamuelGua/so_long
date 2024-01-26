/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:12:50 by scely             #+#    #+#             */
/*   Updated: 2024/01/26 12:16:41 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx_data;

typedef struct img_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	char	*relative_path;
	int		img_width;
	int		img_height;
	int		pos_x;
	int		pos_y;
}	t_img_data;

typedef struct maps_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*floor;
	void	*wall;
	void	*collectible;
	void	*enemis;

}	t_maps_data;

int	key_key(int keycode, t_img_data *dracaufeu, t_mlx_data data)
{	
	if (keycode == 65307)
	{
		printf("the %d key ESC has been pressed\n\n", keycode);
		mlx_destroy_image(dracaufeu->mlx_ptr, dracaufeu->img);
		mlx_destroy_window(dracaufeu->mlx_ptr, dracaufeu->win_ptr);
		mlx_destroy_display(dracaufeu->mlx_ptr);
		free(dracaufeu->mlx_ptr);
		exit(1);
	}
	if ((keycode == 'a' || 65361 == keycode) && dracaufeu->pos_x >= 0)
		dracaufeu->pos_x -= 10;
	if (keycode == 'd' || 65363 == keycode)
		dracaufeu->pos_x += 10;
	if ((keycode == 'w' || 65362 == keycode) && dracaufeu->pos_y >= 0)
		dracaufeu->pos_y -= 10;
	if (keycode == 's' || 65364 == keycode)
		dracaufeu->pos_y += 10;
	mlx_clear_window(dracaufeu->mlx_ptr, dracaufeu->win_ptr);
	mlx_put_image_to_window(dracaufeu->mlx_ptr, dracaufeu->win_ptr,
		dracaufeu->img, dracaufeu->pos_x,
		dracaufeu->pos_y);
	printf("x : %d | y : %d\n\n", dracaufeu->pos_x, dracaufeu->pos_y);
	printf("the %d key has been pressed \n\n", keycode);
	return (0);
}

int	close_window(t_img_data *vars)
{
	mlx_destroy_image(vars->mlx_ptr, vars->img);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->mlx_ptr);
	exit(1);
}

int	mouse_hook(int keycode, t_mlx_data *vars)
{
	printf("the %d key has been pressed \n\n", keycode);
	return (0);
}

int	main(void)
{
	t_mlx_data	data;
	t_img_data	dracaufeu;

	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 192, 108, "Hello world!");
	mlx_hook(data.win_ptr, 17, 1L << 17, close_window, &dracaufeu);
	mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
	dracaufeu.mlx_ptr = data.mlx_ptr;
	dracaufeu.win_ptr = data.win_ptr;
	dracaufeu.pos_x = 150;
	dracaufeu.pos_y = 160;
	dracaufeu.relative_path = "../sprite/charizard.xpm";
	dracaufeu.img = mlx_xpm_file_to_image(data.mlx_ptr,
			dracaufeu.relative_path, &dracaufeu.img_width,
			&dracaufeu.img_height);
	mlx_hook(data.win_ptr, 2, 1L << 0, key_key, &dracaufeu);
	mlx_put_image_to_window(dracaufeu.mlx_ptr, dracaufeu.win_ptr, dracaufeu.img,
		dracaufeu.pos_x, dracaufeu.pos_y);
	printf("avant hook => x : %d, y : %d\n", dracaufeu.pos_x, dracaufeu.pos_y);
	printf("apres hook => x : %d, y : %d\n", dracaufeu.pos_x, dracaufeu.pos_y);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, dracaufeu.img);
	free(data.win_ptr);
}

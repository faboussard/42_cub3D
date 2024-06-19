/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:10:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/03 16:06:21 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_images(t_data *img)
{
	if (img->empty)
		mlx_destroy_image(img->mlx, img->empty);
	if (img->wall)
		mlx_destroy_image(img->mlx, img->wall);
	if (img->coll)
		mlx_destroy_image(img->mlx, img->coll);
	if (img->exit)
		mlx_destroy_image(img->mlx, img->exit);
	if (img->up)
		mlx_destroy_image(img->mlx, img->up);
	if (img->down)
		mlx_destroy_image(img->mlx, img->down);
	if (img->left)
		mlx_destroy_image(img->mlx, img->left);
	if (img->right)
		mlx_destroy_image(img->mlx, img->right);
}

int	close_window(t_data *img)
{
	destroy_images(img);
	if (img->win)
		mlx_destroy_window(img->mlx, img->win);
	if (img->mlx)
	{
		mlx_destroy_display(img->mlx);
		free(img->mlx);
	}
	free_tabs(img->map.grid, img->map.copy);
	exit(1);
	return (0);
}

int	key_hook(int keysym, t_data *img)
{
	if (keysym == XK_Escape)
		close_window(img);
	else if (keysym == XK_W || keysym == XK_w)
		move_up(img);
	else if (keysym == XK_A || keysym == XK_a)
		move_left(img);
	else if (keysym == XK_S || keysym == XK_s)
		move_down(img);
	else if (keysym == XK_D || keysym == XK_d)
		move_right(img);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	img;

	if (ac < 2 || !ends_by_ber(av[1]))
		input_error();
	define_map(&img.map, av[1]);
	if (img.map.status == 0)
		map_error(img.map.grid, img.map.copy);
	init_mlx_win(&img);
	init_screen(&img);
	mlx_hook(img.win, 2, (1L << 0), &key_hook, &img);
	mlx_hook(img.win, DestroyNotify, 0, close_window, &img);
	mlx_loop(img.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:44:28 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/09 13:25:29 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


static void create_walls(t_data *cub, t_ray *ray, int x)
{
	t_render render;

	render = cub->render;
	render.cub = cub;
	ray_tracer(ray);
	get_wallside(cub, ray);
	get_wall_player_dist(cub, ray);
	get_wall_x(cub, ray);
	define_draw_points(&render, cub->wall_player_dist);
	get_texture_x(&render, ray);
	draw(&render, x);
}

static int walls(t_data *cub, t_ray *ray)
{
	int x;

	x = 0;
	while (x < WIDTH_DISPLAY)
	{
		init_ray_info(cub, ray, x);
		create_walls(cub, ray, x);
		x++;
	}
	return (0);
}

static void background(t_data *cub)
{
	int i;
	int j;
	int color;

	i = 0;
	color = cub->map.ceiling_color;
	while (i < (int) cub->my_image.height)
	{
		j = 0;
		while (j < (int) cub->my_image.width)
		{
			if (i > (int) cub->my_image.height / 2)
				color = cub->map.floor_color;
			my_pixel_put(&cub->my_image, j, i, color);
			j++;
		}
		i++;
	}
}


int game_loop(t_data *cub)
{
	t_ray ray;

	background(cub);
	walls(cub, &ray);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->my_image.img, 0, 0);
	if (cub->keys.key_pressed_right == 1)
		rotate_right(cub);
	if (cub->keys.key_pressed_left == 1)
		rotate_left(cub);
	if (cub->keys.key_pressed_w == 1)
		move_forward(cub, &ray);
	if (cub->keys.key_pressed_s == 1)
		move_backward(cub, &ray);
	if (cub->keys.key_pressed_a == 1)
		move_left(cub, &ray);
	if (cub->keys.key_pressed_d == 1)
		move_right(cub, &ray);
	return (0);
}

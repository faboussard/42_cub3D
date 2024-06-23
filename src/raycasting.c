/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:44:28 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/21 15:44:31 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double get_delta_dist(double ray_dir);
static double get_side_dist(double ray_dir, double map, double delta_dist, double pos);
static int get_step(double ray_dir);

static void my_pixel_put(t_data *cub, int x, int y, int color)
{
	char    *dst;
	int     offset_x;
	int     offset_y;

	offset_x = x * (cub->my_image.bits_per_pixel / 8);
	offset_y = y * cub->my_image.line_length;
	if (x >= 0 && x < WIDTH_DISPLAY && y >= 0 && y < HEIGHT_DISPLAY)
	{
		dst = cub->my_image.addr + offset_x + offset_y;
		*(unsigned int *)dst = color;
	}
}


int worldMap[mapWidth][mapHeight]=
		{
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};

static void init_vectors(t_data *cub)
{
	cub->pos_x = 22;
	cub->pos_y = 12;
	cub->dir_x = -1;
	cub->dir_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0.66;
}

static void draw_walls(t_data *cub, int x, double wall_dist)
{
	int line_height;
	int draw_start;
	int draw_end;
	int y;

	line_height = (int)(HEIGHT_DISPLAY / wall_dist);
	draw_start = -line_height / 2 + HEIGHT_DISPLAY / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT_DISPLAY / 2;
	if (draw_end >= HEIGHT_DISPLAY)
		draw_end = HEIGHT_DISPLAY - 1;
	y = draw_start;
	while (y < draw_end)
	{
		my_pixel_put(cub, x, y, 0x00FF0000);
		y++;
	}
}

static void init_raycasting(t_data *cub)
{
	cub->raycast = ft_calloc(sizeof(t_raycasting), 1);
	if (!cub->raycast)
	{
		perror("Failed to allocate memory for raycasting");
		exit(EXIT_FAILURE);
	}
}

static void get_vectors(t_data *cub, double camera_x, int x)
{
	camera_x = 2 * x / (double)WIDTH_DISPLAY - 1; //x-coordinate in camera space
	cub->ray_dir_x = cub->dir_x  + cub->plane_x * camera_x;
	cub->ray_dir_y = cub->dir_y + cub->plane_y * camera_x;
	cub->raycast->map_x = (int)cub->pos_x;
	cub->raycast->map_y = (int)cub->pos_y;
	cub->raycast->delta_dist_x = get_delta_dist(cub->ray_dir_x);
	cub->raycast->delta_dist_y = get_delta_dist(cub->ray_dir_y);
	cub->raycast->side_dist_x = get_side_dist(cub->ray_dir_x, cub->raycast->map_x, cub->raycast->delta_dist_x, cub->pos_x);
	cub->raycast->side_dist_y = get_side_dist(cub->ray_dir_y, cub->raycast->map_y, cub->raycast->delta_dist_y, cub->pos_y);
	cub->raycast->step_x = get_step(cub->ray_dir_x);
	cub->raycast->step_y = get_step(cub->ray_dir_y);
}

static double get_delta_dist(double ray_dir)
{
	double delta_dist;

	if (ray_dir == 0)
		delta_dist = 1e30;
	else
		delta_dist = fabs(1 / ray_dir);
	return delta_dist;
}

static double get_side_dist(double ray_dir, double map, double delta_dist, double pos)
{
	double side_dist;

	if (ray_dir < 0)
		side_dist = (pos - map) * delta_dist;
	else
		side_dist = (map + 1.0 - pos) * delta_dist;
	return (side_dist);
}

static int get_step(double ray_dir)
{
	int step;

	if (ray_dir < 0)
		step = -1;
	else
		step = 1;
	return (step);
}
int ray_tracer(t_data *cub)
{
	int side;
	int hit;

	hit = 0;
	while (hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (cub->raycast->side_dist_x < cub->raycast->side_dist_y)
		{
			cub->raycast->side_dist_x += cub->raycast->delta_dist_x;
			cub->raycast->map_x += cub->raycast->step_x;
			side = 0;
		}
		else
		{
			cub->raycast->side_dist_y += cub->raycast->delta_dist_y;
			cub->raycast->map_y += cub->raycast->step_y;
			side = 1;
		}
		// Check if ray has hit a wall
		if (worldMap[cub->raycast->map_x][cub->raycast->map_y] > 0)
			hit = 1;
	}
	return side;
}

void raycasting(t_data *cub)
{
	double camera_x;
	int x;
	double wall_dist;
	int side;

	init_vectors(cub);
	camera_x = 0;
	x = 0;
	while (x < WIDTH_DISPLAY)
	{
		init_raycasting(cub);
		get_vectors(cub, camera_x, x);
		side = ray_tracer(cub);
		if (side == 0)
			wall_dist = (cub->raycast->map_x - cub->pos_x + (1 - cub->raycast->step_x) / 2) / cub->ray_dir_x;
		else
			wall_dist = (cub->raycast->map_y - cub->pos_y + (1 - cub->raycast->step_y) / 2) / cub->ray_dir_y;
		draw_walls(cub, x, wall_dist);
		x++;
		free(cub->raycast);
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->my_image.img, 0, 0);
}

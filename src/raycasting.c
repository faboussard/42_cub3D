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

//initial direction vector
	cub->dir_x = -1;
	cub->dir_y = 0;

	//the 2d raycaster version of camera plane
	cub->plane_x = 0;
	cub->plane_y = 0.66;
}

static void draw_walls(t_data *cub, int h, int x, double perpWallDist)
{
	int line_height;
	int draw_start;
	int draw_end;
	int y;

	line_height = (int)(h / perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	draw_start = -line_height / 2 + h / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + h / 2;
	if (draw_end >= h)
		draw_end = h - 1;
	y = draw_start;
	//draw the pixels of the stripe as a vertical line
	while (y < draw_end)
	{
		my_pixel_put(cub, x, y, 0x00FF0000);
		y++;// red color for walls
	}
}

static void get_ray_dir(t_data *cub, double camera_x, int w, int x)
{
	camera_x = 2 * x / (double)w - 1; //x-coordinate in camera space
	cub->ray_dir_x = cub->dir_x  + cub->plane_x * camera_x;
	cub->ray_dir_y = cub->dir_y + cub->plane_y * camera_x;
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

void raycasting(t_data *cub)
{
	double camera_x;
	int map_x;
	int map_y;
	int w;
	int h;
	int x;


	int side;
	int hit;


	w = WIDTH_DISPLAY;
	h = HEIGHT_DISPLAY;

//initial position vector
	init_vectors(cub);
	camera_x = 0;
	x = 0;
	while (x < w)
	{
		get_ray_dir(cub, camera_x, w, x);
		double delta_dist_y;
		double delta_dist_x;
		map_x = (int)cub->pos_x;
		map_y = (int)cub->pos_y;
		delta_dist_x = get_delta_dist(cub->ray_dir_x);
		delta_dist_y = get_delta_dist(cub->ray_dir_y);
		hit = 0; //was there a wall hit?
		double side_dist_x;
		double side_dist_y;
		double perpWallDist;
		int step_x;
		int step_y;
		side_dist_x = get_side_dist(cub->ray_dir_x, map_x, delta_dist_x, cub->pos_x);
		side_dist_y = get_side_dist(cub->ray_dir_y, map_y, delta_dist_y, cub->pos_y);
		step_x = get_step(cub->ray_dir_x);
		step_y = get_step(cub->ray_dir_y);
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[map_x][map_y] > 0)
				hit = 1;
		}
		//Calculate distance to the point of impact
		if (side == 0)
			perpWallDist = (map_x - cub->pos_x + (1 - step_x) / 2) / cub->ray_dir_x;
		else
			perpWallDist = (map_y - cub->pos_y + (1 - step_y) / 2) / cub->ray_dir_y;

		//Calculate height of line to draw on screen
		draw_walls(cub, h, x, perpWallDist);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->my_image.img, 0, 0);
}

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

void my_pixel_put(t_data *cub, int x, int y, int color)
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

void init_vectors(t_data *cub)
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

void draw_walls(t_data *cub, int h, int x, double perpWallDist)
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
	x = 0;
	while (x < w)
	{
		//calculate ray position and direction
		camera_x = 2 * x / (double)w - 1; //x-coordinate in camera space
		cub->ray_dir_x = cub->dir_x  + cub->plane_x * camera_x;
		cub->ray_dir_y = cub->dir_y + cub->plane_y * camera_x;
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (cub->ray_dir_x == 0) ? 1e30 : fabs(1 / cub->ray_dir_x);
		double deltaDistY = (cub->ray_dir_y == 0) ? 1e30 : fabs(1 / cub->ray_dir_y);
		double perpWallDist;
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		map_x = (int)cub->pos_x;
		map_y = (int)cub->pos_y;
		hit = 0; //was there a wall hit?
		//calculate step and initial sideDist
		if (cub->ray_dir_x < 0)
		{
			stepX = -1;
			sideDistX = (cub->pos_x - map_x) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (map_x + 1.0 - cub->pos_x) * deltaDistX;
		}
		if (cub->ray_dir_y < 0)
		{
			stepY = -1;
			sideDistY = (cub->pos_y - map_y) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (map_y + 1.0 - cub->pos_y) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				map_x += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				map_y += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[map_x][map_y] > 0)
				hit = 1;
		}
		//Calculate distance to the point of impact
		if (side == 0)
			perpWallDist = (map_x - cub->pos_x + (1 - stepX) / 2) / cub->ray_dir_x;
		else
			perpWallDist = (map_y - cub->pos_y + (1 - stepY) / 2) / cub->ray_dir_y;

		//Calculate height of line to draw on screen
		draw_walls(cub, h, x, perpWallDist);
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->my_image.img, 0, 0);
}

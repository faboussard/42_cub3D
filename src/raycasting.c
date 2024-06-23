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

void raycasting(t_data *cub)
{
	double camera_X;
	int map_X;
	int map_Y;
	int side;
//	double deltaDist_X;
//	double deltaDist_Y;
//	double perp_WallDist;
//	int step_X;
//	int step_Y;
	int hit;
	int w;
	int h;
	int x;

	w = WIDTH_DISPLAY;
	h = HEIGHT_DISPLAY;

//initial position vector
	init_vectors(cub);
	x = 0;
	while (x < w)
	{
		//calculate ray position and direction
		camera_X = 2 * x / (double)w - 1; //x-coordinate in camera space
		cub->ray_dir_x = cub->dir_x  + cub->plane_x * camera_X;
		cub->ray_dir_y = cub->dir_y + cub->plane_y * camera_X;

		//which box of the map we're in
		map_X = (int)cub->pos_x;
		map_Y = (int)cub->pos_y;

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

		hit = 0; //was there a wall hit?

		//calculate step and initial sideDist
		if (cub->ray_dir_x < 0)
		{
			stepX = -1;
			sideDistX = (cub->pos_x - map_X) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (map_X + 1.0 - cub->pos_x) * deltaDistX;
		}
		if (cub->ray_dir_y < 0)
		{
			stepY = -1;
			sideDistY = (cub->pos_y - map_Y) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (map_Y + 1.0 - cub->pos_y) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				map_X += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				map_Y += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[map_X][map_Y] > 0)
				hit = 1;
		}

		//Calculate distance to the point of impact
		if (side == 0)
			perpWallDist = (map_X - cub->pos_x + (1 - stepX) / 2) / cub->ray_dir_x;
		else
			perpWallDist = (map_Y - cub->pos_y + (1 - stepY) / 2) / cub->ray_dir_y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;

		//draw the pixels of the stripe as a vertical line
		for (int y = drawStart; y < drawEnd; y++)
		{
			my_pixel_put(cub, x, y, 0x00FF0000); // red color for walls
		}
		x++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->my_image.img, 0, 0);
}

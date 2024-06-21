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

void raycasting(t_data *img)
{
	double pos_X;
	double pos_Y;
	double dir_X;
	double dir_Y;
	double plane_X;
	double plane_Y;
	double ray_Dir_X;
	double ray_Dir_Y;
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
	pos_X = 22;
	pos_Y = 12;

//initial direction vector
	dir_X = -1;
	dir_Y = 0;

 //the 2d raycaster version of camera plane
	plane_X = 0;
	plane_Y = 0.66;

	x = 0;
	while (x < w)
	{
		//calculate ray position and direction
		camera_X = 2 * x / (double)w - 1; //x-coordinate in camera space
		ray_Dir_X = dir_X + plane_X * camera_X;
		ray_Dir_Y = dir_Y + plane_Y * camera_X;

		//which box of the map we're in
		map_X = (int)pos_X;
		map_Y = (int)pos_Y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (ray_Dir_X == 0) ? 1e30 : fabs(1 / ray_Dir_X);
		double deltaDistY = (ray_Dir_Y == 0) ? 1e30 : fabs(1 / ray_Dir_Y);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		hit = 0; //was there a wall hit?

		//calculate step and initial sideDist
		if (ray_Dir_X < 0)
		{
			stepX = -1;
			sideDistX = (pos_X - map_X) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (map_X + 1.0 - pos_X) * deltaDistX;
		}
		if (ray_Dir_Y < 0)
		{
			stepY = -1;
			sideDistY = (pos_Y - map_Y) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (map_Y + 1.0 - pos_Y) * deltaDistY;
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
			perpWallDist = (map_X - pos_X + (1 - stepX) / 2) / ray_Dir_X;
		else
			perpWallDist = (map_Y - pos_Y + (1 - stepY) / 2) / ray_Dir_Y;

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
			my_pixel_put(img, x, y, 0x00FF0000); // red color for walls
		}
		x++;
	}

	// put the image to the window
	mlx_put_image_to_window(img->mlx, img->win, img->my_image.img, 0, 0);
}


//
//
//void setup_raycasting(t_data *data)
//{
//	data->pos_X = 22;
//	data->pos_Y = 12;
//	data->dir_X = -1;
//	data->dir_Y = 0;
//	data->plane_X = 0;
//	data->plane_Y = 0.66;
//
//	// Allouer de la mémoire pour la carte du monde
//	data->worldMap = malloc(mapWidth * sizeof(int *));
//	for (int i = 0; i < mapWidth; i++)
//		data->worldMap[i] = malloc(mapHeight * sizeof(int));
//
//	// Initialiser la carte du monde
//	int initialMap[mapWidth][mapHeight] = {
//				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//				{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//				{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
//	};
//
//	// Copiez les données initiales dans la carte du monde
//	for (int y = 0; y < mapHeight; y++)
//	{
//		for (int x = 0; x < mapWidth; x++)
//		{
//			data->worldMap[x][y] = initialMap[x][y];
//		}
//	}
//}
//
//void draw_walls(t_data *data, double perpWallDist, int x)
//{
//	// Calcul de la hauteur de la ligne à dessiner sur l'écran
//	int lineHeight = (int)(HEIGHT_DISPLAY / perpWallDist);
//
//	// Calcul des positions de début et de fin de la ligne
//	int drawStart = -lineHeight / 2 + HEIGHT_DISPLAY / 2;
//	if (drawStart < 0)
//		drawStart = 0;
//	int drawEnd = lineHeight / 2 + HEIGHT_DISPLAY / 2;
//	if (drawEnd >= HEIGHT_DISPLAY)
//		drawEnd = HEIGHT_DISPLAY - 1;
//
//	// Couleur du mur en fonction du type dans la carte du monde
//
//	// Dessiner la ligne verticale du mur
//	for (int y = drawStart; y < drawEnd; y++)
//	{
//		my_pixel_put(data, x, y, 0x00FF0000);
//	}
//}
//
//
//void raycasting(t_data *data)
//{
//	setup_raycasting(data);
//	for (int x = 0; x < WIDTH_DISPLAY; x++)
//	{
//		double cameraX = 2 * x / (double)WIDTH_DISPLAY - 1; // Coordonnées x dans l'espace caméra
//		double rayDirX = data->dir_X + data->plane_X * cameraX;
//		double rayDirY = data->dir_Y + data->plane_Y * cameraX;
//
//		// Position de la grille dans le monde
//		int map_X = (int)data->pos_X;
//		int map_Y = (int)data->pos_Y;
//
//		// Longueur de la ligne
//		double sideDistX, sideDistY;
//
//		// Longueur du rayon
//		double deltaDistX = fabs(1 / rayDirX);
//		double deltaDistY = fabs(1 / rayDirY);
//		double perpWallDist;
//
//		// Direction du rayon et pas de grille
//		int stepX, stepY;
//
//		// Calculer les distances des côtés
//		if (rayDirX < 0)
//		{
//			stepX = -1;
//			sideDistX = (data->pos_X - map_X) * deltaDistX;
//		}
//		else
//		{
//			stepX = 1;
//			sideDistX = (map_X + 1.0 - data->pos_X) * deltaDistX;
//		}
//		if (rayDirY < 0)
//		{
//			stepY = -1;
//			sideDistY = (data->pos_Y - map_Y) * deltaDistY;
//		}
//		else
//		{
//			stepY = 1;
//			sideDistY = (map_Y + 1.0 - data->pos_Y) * deltaDistY;
//		}
//		int hit = 0;
//		int side;
//		while (hit == 0)
//		{
//			//jump to next map square, either in x-direction, or in y-direction
//			if (sideDistX < sideDistY)
//			{
//				sideDistX += deltaDistX;
//				map_X += stepX;
//				side = 0;
//			}
//			else
//			{
//				sideDistY += deltaDistY;
//				map_Y += stepY;
//				side = 1;
//			}
//			//Check if ray has hit a wall
//			if (data->worldMap[map_X][map_Y] > 0)
//				hit = 1;
//		}
//
//		// Calcul de la distance perpendiculaire au mur
//// Calcul de la distance perpendiculaire au mur
//		if (side == 0)
//			perpWallDist = fabs((map_X - data->pos_X + (1 - stepX) / 2) / rayDirX);
//		else
//			perpWallDist = fabs((map_Y - data->pos_Y + (1 - stepY) / 2) / rayDirY);
//
//
//
//		// Dessiner les murs
//		draw_walls(data, perpWallDist, x);
//	}
//}
//

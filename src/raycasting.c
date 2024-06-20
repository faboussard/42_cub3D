#include "cub3d.h"

void my_pixel_put(t_data *img, int x, int y, int color)
{
	char    *dst;
	int     offset_x;
	int     offset_y;

	offset_x = x * (img->my_image.bits_per_pixel / 8);
	offset_y = y * img->my_image.line_length;
	if (x >= 0 && x < WIDTH_DISPLAY && y >= 0 && y < HEIGHT_DISPLAY)
	{
		dst = img->my_image.addr + offset_x + offset_y;
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

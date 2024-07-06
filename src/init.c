/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:43:59 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/21 15:44:01 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int create_wall_texture_img(t_data *cub, t_image *wall, int i);


int set_wall_texture(t_data *cub)
{
	cub->wall[0].path = cub->north_img;
	create_wall_texture_img(cub, cub->wall, 0);
	cub->wall[1].path = cub->south_img;
	create_wall_texture_img(cub, cub->wall, 1);
	cub->wall[2].path = cub->east_img;
	create_wall_texture_img(cub, cub->wall, 2);
	cub->wall[3].path = cub->west_img;
	if (create_wall_texture_img(cub, cub->wall, 3) == 1)
		return (1);
	return 0;
}

static int create_wall_texture_img(t_data *cub, t_image *wall, int i)
{
	int	j;

	j = 0;
	printf("Loading texture %d from path: %s\n", i, wall[i].path);
	wall[i].img = mlx_xpm_file_to_image(cub->mlx, wall[i].path, &wall[i].width, &wall[i].height);
	if (wall[i].img == NULL)
	{
		while (j-- > i)
			mlx_destroy_image(cub->mlx, wall[i].img);
		printf("Erreur lors du chargement de l'image de la texture\n");
		return (1);
	}
	wall[i].addr = mlx_get_data_addr(wall[i].img, &wall[i].bits_per_pixel, &wall[i].line_length, &wall[i].endian);
	if (wall[i].addr == NULL)
	{
		j = 0;
		while (j-- > i)
			mlx_destroy_image(cub->mlx, wall[i].img);
		printf("Erreur lors de l'obtention des données de la texture\n");
		return (1);
	}
	return (0);
}


void init_image(t_data *cub)
{
	cub->my_image.width = WIDTH_DISPLAY;
	cub->my_image.height = HEIGHT_DISPLAY;
	cub->my_image.img = mlx_new_image(cub->mlx, cub->my_image.width, cub->my_image.height );
	if (cub->my_image.img == NULL)
	{
//		free_all(cub);
		exit(EXIT_FAILURE);
	}
	cub->my_image.addr = mlx_get_data_addr(cub->my_image.img,
	                                       &cub->my_image.bits_per_pixel, &cub->my_image.line_length,
	                                       &cub->my_image.endian);
}

//static void	init_map(t_data *img, size_t x, size_t y)
//{
//	t_data	*mlx;
//	t_data	*win;
//
//	mlx = img->mlx;
//	win = img->win;
//	while (x <= img->map.rows)
//	{
//		y = 0;
//		while (y <= img->map.cols)
//		{
//			if (img->map.grid[x][y] == '1')
//				mlx_put_image_to_window(mlx, win, img->wall, y * 80, x * 80);
//			else if (img->map.grid[x][y] == '0')
//				mlx_put_image_to_window(mlx, win, img->empty, y * 80, x * 80);
//			else if (img->map.grid[x][y] == 'C')
//				mlx_put_image_to_window(mlx, win, img->coll, y * 80, x * 80);
//			else if (img->map.grid[x][y] == 'E')
//				mlx_put_image_to_window(mlx, win, img->exit, y * 80, x * 80);
//			else if (img->map.grid[x][y] == 'P')
//				mlx_put_image_to_window(mlx, win, img->down, y * 80, x * 80);
//			y++;
//		}
//		x++;
//	}
//}

void init_screen(t_data *cub)
{
	init_mlx_win(cub);

	init_image(cub);
}

void init_mlx_win(t_data *img)
{
	img->mlx = mlx_init();
	if (img->mlx == NULL)
		malloc_error();

	img->win = mlx_new_window(img->mlx, WIDTH_DISPLAY, HEIGHT_DISPLAY, "cub3d");
	if (img->win == NULL)
	{
		mlx_destroy_display(img->mlx);
//		free_tabs(img->map.grid, img->map.copy);
		free(img->mlx);
		malloc_error();
	}
}

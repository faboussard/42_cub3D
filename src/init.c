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

static void create_wall_texture_img(t_data *cub, t_image *wall, int i);

int set_wall_texture(t_data *cub, t_image *wall)
{
	int i;
	int j;

//	char *paths[TEXTURE_NUM] = {
//			"/home/fanny/cub3d/TEST_CUB3D_ESLAMBER/textures/test/west.xpm",
//			"/home/fanny/cub3d/TEST_CUB3D_ESLAMBER/textures/test/north.xpm",
//			"/home/fanny/cub3d/TEST_CUB3D_ESLAMBER/textures/test/east.xpm",
//			"/home/fanny/cub3d/TEST_CUB3D_ESLAMBER/textures/test/south.xpm"
//	};
	char *paths[TEXTURE_NUM] = {
			"/home/juba/cub3d/TEST_CUB3D_ESLAMBER/textures/test/west.xpm",
			"/home/juba/cub3d/TEST_CUB3D_ESLAMBER/textures/test/north.xpm",
			"/home/juba/cub3d/TEST_CUB3D_ESLAMBER/textures/test/east.xpm",
			"/home/juba/cub3d/TEST_CUB3D_ESLAMBER/textures/test/south.xpm"
	};
	i = 0;
	j = 0;
	while (i < TEXTURE_NUM)
	{
		cub->wall[i].path = ft_strdup(paths[i]);
		if (!cub->wall[i].path)
		{
			while (j < i)
			{
				free(cub->wall[j++].path);
				printf("Erreur lors de la duplication du chemin de la texture %d\n", i);
				exit(EXIT_FAILURE);
			}
		}
		create_wall_texture_img(cub, wall, i++);
	}
	return 0;
}


static void create_wall_texture_img(t_data *cub, t_image *wall, int i)
{
	wall[i].img = mlx_xpm_file_to_image(cub->mlx, wall[i].path, &wall[i].width, &wall[i].height);
	if (wall[i].img == NULL)
	{
		while (i-- > 0)
			mlx_destroy_image(cub->mlx, wall[i].img);
		while (++i < TEXTURE_NUM)
			free(wall[i].path);
		printf("Erreur lors du chargement de l'image de la texture\n");
		exit(EXIT_FAILURE);
	}

	wall[i].addr = mlx_get_data_addr(wall[i].img, &wall[i].bits_per_pixel, &wall[i].line_length, &wall[i].endian);
	if (wall[i].addr == NULL)
	{
		while (i-- > 0)
			mlx_destroy_image(cub->mlx, wall[i].img);
		while (++i < TEXTURE_NUM)
			free(wall[i].path);
		printf("Erreur lors de l'obtention des données de la texture\n");
		exit(EXIT_FAILURE);
	}
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

void init_screen(t_data *img)
{
	init_mlx_win(img);

	init_image(img);
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

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

static void create_wall_texture_img(t_data *cub, t_image *wall, int n, int i);

//static void	init_pictures(t_data *img)
//{
//	ft_strlcpy(img->emp_img, "./sprites/empty_80_80.xpm", 26);
//	ft_strlcpy(img->wall_img, "./sprites/wall_80_80.xpm", 25);
//	ft_strlcpy(img->coll_img, "./sprites/coins_80_80.xpm", 26);
//	ft_strlcpy(img->exit_img, "./sprites/chest_80_80.xpm", 26);
//	ft_strlcpy(img->up_img, "./sprites/up_80_80.xpm", 23);
//	ft_strlcpy(img->down_img, "./sprites/down_80_80.xpm", 25);
//	ft_strlcpy(img->left_img, "./sprites/left_80_80.xpm", 25);
//	ft_strlcpy(img->right_img, "./sprites/right_80_80.xpm", 26);
//}
//
//


int set_wall_texture(t_data *cub, t_image *wall)
{
	int i;
	int j;
	int n = TEXTURE_NUM;

	char *paths[TEXTURE_NUM] = {
			"/home/fanny/cub3d/TEST_CUB3D_ESLAMBER/textures/test/west.xpm",
			"/home/fanny/cub3d/TEST_CUB3D_ESLAMBER/textures/test/north.xpm",
			"/home/fanny/cub3d/TEST_CUB3D_ESLAMBER/textures/test/east.xpm",
			"/home/fanny/cub3d/TEST_CUB3D_ESLAMBER/textures/test/south.xpm"
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
		create_wall_texture_img(cub, wall, n, i++);
	}
	return 0;
}


static void create_wall_texture_img(t_data *cub, t_image *wall, int n, int i)
{
	if (n ==
	    32000) // a supprimer une fois que wall[i] sera malloc (parsing). n sert juste a freer les images de textures
		return;
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
	cub->my_image.img = mlx_new_image(cub->mlx, WIDTH_DISPLAY, HEIGHT_DISPLAY);
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
//	init_pictures(img);
	init_image(img);
//	init_map(img, 0, 0);
//	img->map.player.moves = 0;
}

void init_mlx_win(t_data *img)
{
//	size_t	cols;
//	size_t	rows;
//
////	cols = img->map.cols;
////	rows = img->map.rows + 1;
//	if (rows > INT_MAX || rows < 3 || cols > 26843545)
//		map_error(img->map.grid, img->map.copy);
	img->mlx = mlx_init();
	if (img->mlx == NULL)
	{
//		free_tabs(img->map.grid, img->map.copy);
		malloc_error();
	}
//	img->win = mlx_new_window(img->mlx, cols * 80, rows * 80, "cub3d");
	img->win = mlx_new_window(img->mlx, WIDTH_DISPLAY, HEIGHT_DISPLAY, "cub3d");
	if (img->win == NULL)
	{
		mlx_destroy_display(img->mlx);
//		free_tabs(img->map.grid, img->map.copy);
		free(img->mlx);
		malloc_error();
	}
}

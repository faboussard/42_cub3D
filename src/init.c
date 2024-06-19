/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:22:01 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/04 11:11:10 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
//static void	init_images(t_data *img)
//{
//	t_data	*mlx;
//	int		width;
//	int		height;
//
//	mlx = img->mlx;
//	width = 80;
//	height = 80;
//	img->empty = mlx_xpm_file_to_image(mlx, img->emp_img, &width, &height);
//	img->wall = mlx_xpm_file_to_image(mlx, img->wall_img, &width, &height);
//	img->coll = mlx_xpm_file_to_image(mlx, img->coll_img, &width, &height);
//	img->exit = mlx_xpm_file_to_image(mlx, img->exit_img, &width, &height);
//	img->up = mlx_xpm_file_to_image(mlx, img->up_img, &width, &height);
//	img->down = mlx_xpm_file_to_image(mlx, img->down_img, &width, &height);
//	img->left = mlx_xpm_file_to_image(mlx, img->left_img, &width, &height);
//	img->right = mlx_xpm_file_to_image(mlx, img->right_img, &width, &height);
//	if (!img->empty || !img->wall || !img->coll || !img->exit || !img->up
//		|| !img->down || !img->left || !img->right)
//	{
//		ft_putstr_fd("Error\nMalloc error\n", 2);
//		close_window(img);
//	}
//}

void	init_image(t_data *img)
{
	img->my_image.img = mlx_new_image(img->mlx, 1920, 1080);
	if (img->my_image.img == NULL)
	{
//		free_all(fdf);
		exit(EXIT_FAILURE);
	}
	img->my_image.addr = mlx_get_data_addr(img->my_image.img,
										   &img->my_image.bits_per_pixel, &img->my_image.line_length,
										   &img->my_image.endian);
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

void	init_screen(t_data *img)
{
//	init_pictures(img);
	init_image(img);
//	init_map(img, 0, 0);
//	img->map.player.moves = 0;
}

void	init_mlx_win(t_data *img)
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
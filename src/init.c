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

void	init_image(t_data *cub)
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

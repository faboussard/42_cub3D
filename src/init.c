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

static void	init_images(t_data *img)
{
	t_data	*mlx;
	int		width;
	int		height;

	mlx = img->mlx;
	width = 80;
	height = 80;
}

static void	init_map(t_data *img, size_t x, size_t y)
{
	t_data	*mlx;
	t_data	*win;

	mlx = img->mlx;
	win = img->win;
	while (x <= img->map.rows)
	{
		y = 0;
		while (y <= img->map.cols)
		{
			if (img->map.grid[x][y] == '1')
				mlx_put_image_to_window(mlx, win, img->wall, y * 80, x * 80);
			else if (img->map.grid[x][y] == '0')
				mlx_put_image_to_window(mlx, win, img->empty, y * 80, x * 80);
			else if (img->map.grid[x][y] == 'C')
				mlx_put_image_to_window(mlx, win, img->coll, y * 80, x * 80);
			else if (img->map.grid[x][y] == 'E')
				mlx_put_image_to_window(mlx, win, img->exit, y * 80, x * 80);
			else if (img->map.grid[x][y] == 'P')
				mlx_put_image_to_window(mlx, win, img->down, y * 80, x * 80);
			y++;
		}
		x++;
	}
}

void	init_screen(t_data *img)
{
	init_images(img);
	init_map(img, 0, 0);
	img->map.player.moves = 0;
}

void	init_mlx_win(t_data *img)
{
	size_t	cols;
	size_t	rows;

	cols = img->map.cols;
	rows = img->map.rows + 1;
	if (rows > INT_MAX || rows < 3 || cols > 26843545)
		map_error(img->map.grid, img->map.copy);
	img->mlx = mlx_init();
	if (img->mlx == NULL)
	{
		free_tabs(img->map.grid, img->map.copy);
		malloc_error();
	}
	img->win = mlx_new_window(img->mlx, cols * 80, rows * 80, "so_long");
	if (img->win == NULL)
	{
		mlx_destroy_display(img->mlx);
		free_tabs(img->map.grid, img->map.copy);
		free(img->mlx);
		malloc_error();
	}
}

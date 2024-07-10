/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:43:59 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/09 09:37:37 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	create_wall_texture_img(t_data *cub, t_image *wall, int i)
{
	printf("Loading texture %d from path: %s\n", i, wall[i].path);
	wall[i].img = mlx_xpm_file_to_image(cub->mlx, wall[i].path, &wall[i].width, &wall[i].height);
	if (wall[i].img == NULL)
	{
		perror("Error\n");
		perror("Error loading texture's picture");
		close_window(cub);
	}
	wall[i].addr = mlx_get_data_addr(wall[i].img, &wall[i].bits_per_pixel, &wall[i].line_length, &wall[i].endian);
	if (wall[i].addr == NULL)
	{
		perror("Error\n");
		perror("Error obtening texture's data");
		close_window(cub);
	}
}

void set_wall_texture(t_data *cub)
{
	cub->wall[0].path = cub->north_img;
	create_wall_texture_img(cub, cub->wall, 0);
	cub->wall[1].path = cub->south_img;
	create_wall_texture_img(cub, cub->wall, 1);
	cub->wall[2].path = cub->east_img;
	create_wall_texture_img(cub, cub->wall, 2);
	cub->wall[3].path = cub->west_img;
	create_wall_texture_img(cub, cub->wall, 3);
}

void init_image(t_data *cub)
{
	cub->my_image.width = WIDTH_DISPLAY;
	cub->my_image.height = HEIGHT_DISPLAY;
	cub->my_image.img = mlx_new_image(cub->mlx, cub->my_image.width, cub->my_image.height);
	if (cub->my_image.img == NULL)
	{
		perror("Error\n");
		perror("Error init cub->my_image.img");
		close_window(cub);
	}
	cub->my_image.addr = mlx_get_data_addr(cub->my_image.img,
	                                       &cub->my_image.bits_per_pixel, &cub->my_image.line_length,
	                                       &cub->my_image.endian);
	if (cub->my_image.addr == NULL)
	{
		perror("Error\n");
		perror("Error init cub->my_image.addr");
		close_window(cub);
	}
}

void init_mlx_win(t_data *cub)
{
	cub->mlx = mlx_init();
	if (cub->mlx == NULL)
	{
		perror("Error\n");
		perror("Error init cub->mlx");
		close_window(cub);
	}
	cub->win = mlx_new_window(cub->mlx, WIDTH_DISPLAY, HEIGHT_DISPLAY, "cub3D");
	if (cub->win == NULL)
	{
		perror("Error\n");
		perror("Error init cub->win");
		close_window(cub);
	}
}
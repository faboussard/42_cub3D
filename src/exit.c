/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:43:32 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/29 13:47:25 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_images(t_data *img)
{
	if (img->empty)
		mlx_destroy_image(img->mlx, img->empty);
//	if (img->north_wall)
//		mlx_destroy_image(img->mlx, img->north_wall);
//	if (img->south_wall)
//		mlx_destroy_image(img->mlx, img->south_wall);
//	if (img->east_wall)
//		mlx_destroy_image(img->mlx, img->east_wall);
//	if (img->west_wall)
//		mlx_destroy_image(img->mlx, img->west_wall);
}

int	close_window(t_data *img)
{
	destroy_images(img);
	if (img->win)
		mlx_destroy_window(img->mlx, img->win);
	if (img->mlx)
	{
		mlx_destroy_display(img->mlx);
		free(img->mlx);
	}
	free_tabs(img->map.grid, img->map.copy);
	exit(1);
}

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

void	destroy_images(t_data *cub)
{
	int	i;

	i = 0;

	while (i < 4)
	{
		if (cub->wall[i].img)
			mlx_destroy_image(cub->mlx, cub->wall[i].img);
		i++;
	}
	free(cub->my_image.img);
	// if (cub->east_img)
	// 	mlx_destroy_image(cub->mlx, cub->east_img);
	// if (cub->west_img)
	// 	mlx_destroy_image(cub->mlx, cub->west_img);
	// if (cub->north_img)
	// 	mlx_destroy_image(cub->mlx, cub->north_img);
	// if (cub->south_img)
	// 	mlx_destroy_image(cub->mlx, cub->south_img);
	// if (img->empty)
	// 	mlx_destroy_image(img->mlx, img->empty);
//	if (img->north_wall)
//		mlx_destroy_image(img->mlx, img->north_wall);
//	if (img->south_wall)
//		mlx_destroy_image(img->mlx, img->south_wall);
//	if (img->east_wall)
//		mlx_destroy_image(img->mlx, img->east_wall);
//	if (img->west_wall)
//		mlx_destroy_image(img->mlx, img->west_wall);
}

int	close_window(t_data *cub)
{
	destroy_images(cub);
	free(cub->player);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	ft_free_tab(&cub->map.copy);
	// ft_free_tab(&cub->map.copy);
	// free_tabs(img->map.grid, img->map.copy);
	exit(1);
}

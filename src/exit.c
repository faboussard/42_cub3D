/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:43:32 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/11 12:53:25 by mbernard         ###   ########.fr       */
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
	if (cub->my_image.img)
		mlx_destroy_image(cub->mlx, cub->my_image.img);
}

int	close_window(t_data *cub)
{
	destroy_images(cub);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	if (cub->map.copy)
		ft_free_tab(&cub->map.copy);
	if (cub->player)
		free(cub->player);
	exit(EXIT_FAILURE);
}

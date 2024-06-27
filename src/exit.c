/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:43:32 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/21 15:43:35 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_images(t_data *img)
{
	if (img->empty)
		mlx_destroy_image(img->mlx, img->empty);
	if (img->up)
		mlx_destroy_image(img->mlx, img->up);
	if (img->down)
		mlx_destroy_image(img->mlx, img->down);
	if (img->left)
		mlx_destroy_image(img->mlx, img->left);
	if (img->right)
		mlx_destroy_image(img->mlx, img->right);
}

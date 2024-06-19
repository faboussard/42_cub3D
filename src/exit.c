/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:37:40 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/04 11:36:24 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_images(t_data *img)
{
	if (img->empty)
		mlx_destroy_image(img->mlx, img->empty);
	if (img->wall)
		mlx_destroy_image(img->mlx, img->wall);
	if (img->coll)
		mlx_destroy_image(img->mlx, img->coll);
	if (img->exit)
		mlx_destroy_image(img->mlx, img->exit);
	if (img->up)
		mlx_destroy_image(img->mlx, img->up);
	if (img->down)
		mlx_destroy_image(img->mlx, img->down);
	if (img->left)
		mlx_destroy_image(img->mlx, img->left);
	if (img->right)
		mlx_destroy_image(img->mlx, img->right);
}

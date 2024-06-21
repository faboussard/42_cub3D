/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:43:47 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/21 15:43:49 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_data *img)
{
//	destroy_images(img);
	if (img->win)
		mlx_destroy_window(img->mlx, img->win);
	if (img->mlx)
	{
		mlx_destroy_display(img->mlx);
		free(img->mlx);
	}
//	free_tabs(img->map.grid, img->map.copy);
	exit(1);
}

int	key_hook(int keysym, t_data *img)
{
	if (keysym == XK_Escape)
		close_window(img);
//	else if (keysym == XK_W || keysym == XK_w)
//		move_up(img);
//	else if (keysym == XK_A || keysym == XK_a)
//		move_left(img);
//	else if (keysym == XK_S || keysym == XK_s)
//		move_down(img);
//	else if (keysym == XK_D || keysym == XK_d)
//		move_right(img);
	return (0);
}

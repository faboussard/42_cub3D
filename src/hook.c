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

#include "cub3D.h"

int	key_press_hook(int keysym, t_data *cub)
{
	if (keysym == XK_Escape)
		close_window(cub);
	else if (keysym == XK_W || keysym == XK_w)
		cub->keys.key_pressed_w = 1;
	else if (keysym == XK_S || keysym == XK_s)
		cub->keys.key_pressed_s = 1;
//	else if (keysym == XK_A || keysym == XK_a)
//		move_left(cub);
//	else if (keysym == XK_D || keysym == XK_d)
//		move_right(cub);
	return (0);
}


int	key_release_hook(int keysym, t_data *cub)
{
	if (keysym == XK_Escape)
		return (0);
		// close_window(cub); //enlever ?
	else if (cub->keys.key_pressed_w && (keysym == XK_W || keysym == XK_w))
		cub->keys.key_pressed_w = 0;
	else if (cub->keys.key_pressed_s && (keysym == XK_S || keysym == XK_s))
		cub->keys.key_pressed_s = 0;
	return (0);
}

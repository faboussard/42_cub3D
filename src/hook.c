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

int	key_hook(int keysym, t_data *img)
{
	if (keysym == XK_Escape)
		close_window(img);
	else if (keysym == XK_W || keysym == XK_w)
		img->keys.key_pressed_w = 1;
//	else if (keysym == XK_S || keysym == XK_s)
//		move_backward(img);
//	else if (keysym == XK_A || keysym == XK_a)
//		move_left(img);
//	else if (keysym == XK_D || keysym == XK_d)
//		move_right(img);
	return (0);
}

//
//int	keypress(int keysym, t_cub3d *data)
//{
//	if (keysym == XK_Escape)
//		close_window(data);
//	if (keysym == XK_Right)
//		data->keys.key_pressed_right = 1;
//	if (keysym == XK_Left)
//		data->keys.key_pressed_left = 1;
//	if (keysym == XK_w)
//		data->keys.key_pressed_w = 1;
//	if (keysym == XK_a)
//		data->keys.key_pressed_a = 1;
//	if (keysym == XK_s)
//		data->keys.key_pressed_s = 1;
//	if (keysym == XK_d)
//		data->keys.key_pressed_d = 1;
//	if (BONUS)
//	{
//		if (keysym == XK_e)
//			action_event(data);
//		if (keysym == XK_x && data->keys.key_pressed_x == 0)
//			data->keys.key_pressed_x = 1;
//		else if (keysym == XK_x && data->keys.key_pressed_x == 1)
//			data->keys.key_pressed_x = 0;
//	}
//	return (0);
//}
//
//int	keyrelease(int keysym, t_cub3d *data)
//{
//	if (keysym == XK_Right)
//		data->keys.key_pressed_right = 0;
//	if (keysym == XK_Left)
//		data->keys.key_pressed_left = 0;
//	if (keysym == XK_w)
//		data->keys.key_pressed_w = 0;
//	if (keysym == XK_a)
//		data->keys.key_pressed_a = 0;
//	if (keysym == XK_s)
//		data->keys.key_pressed_s = 0;
//	if (keysym == XK_d)
//		data->keys.key_pressed_d = 0;
//	return (0);
//}

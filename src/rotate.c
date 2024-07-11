/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                          	         	    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:44:28 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/02 08:52:20 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3D.h"

void	rotate_left(t_data *cub)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROTATE;
	old_dir_x = cub->player->dir_x;
	old_plane_x = cub->plane_x;
	cub->player->dir_x = cub->player->dir_x * cos(-1.0 * rot_speed) - cub->player->dir_y
		* sin(-1.0 * rot_speed);
	cub->player->dir_y = old_dir_x * sin(-1.0 * rot_speed) + cub->player->dir_y * cos(-1.0
			* rot_speed);
	cub->plane_x = cub->plane_x * cos(-1.0 * rot_speed) - cub->plane_y
		* sin(-1.0 * rot_speed);
	cub->plane_y = old_plane_x * sin(-1.0 * rot_speed) + cub->plane_y
		* cos(-1.0 * rot_speed);
}

void	rotate_right(t_data *cub)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROTATE;
	old_dir_x = cub->player->dir_x;
	old_plane_x = cub->plane_x;
	cub->player->dir_x = cub->player->dir_x * cos(1.0 * rot_speed) - cub->player->dir_y
		* sin(1.0 * rot_speed);
	cub->player->dir_y = old_dir_x * sin(1.0 * rot_speed) + cub->player->dir_y * cos(1.0
			* rot_speed);
	cub->plane_x = cub->plane_x * cos(1.0 * rot_speed) - cub->plane_y
		* sin(1.0 * rot_speed);
	cub->plane_y = old_plane_x * sin(1.0 * rot_speed) + cub->plane_y
		* cos(1.0 * rot_speed);
}
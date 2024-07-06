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

void	rotate_right(t_data *cub)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(-ROTATE) - cub->dir_y * sin(-ROTATE);
	cub->dir_y = old_dir_x * sin(-ROTATE) + cub->dir_y * cos(-ROTATE);
	old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(-ROTATE) - cub->plane_y * sin(-ROTATE);
	cub->plane_y = old_plane_x * sin(-ROTATE) + cub->plane_y * cos(-ROTATE);
}


void	rotate_left(t_data *cub)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = cub->dir_x;
	cub->dir_x = cub->dir_x * cos(ROTATE) - cub->dir_y * sin(ROTATE);
	cub->dir_y = old_dir_x * sin(ROTATE) + cub->dir_y * cos(ROTATE);
	old_plane_x = cub->plane_x;
	cub->plane_x = cub->plane_x * cos(ROTATE) - cub->plane_y * sin(ROTATE);
	cub->plane_y = old_plane_x * sin(ROTATE) + cub->plane_y * cos(ROTATE);
}
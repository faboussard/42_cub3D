/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                          					:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:44:28 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/02 08:52:20 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_forward(t_data *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player->pos_x + cub->player->dir_x * MOVE;
	new_y = cub->player->pos_y + cub->player->dir_y * MOVE;
	if (new_x < cub->map.width && new_y < cub->map.height
		&& cub->map.grid[(int)new_y][(int)new_x] != '1')
		cub->player->pos_x = new_x;
	if (new_x < cub->map.width && new_y < cub->map.height
		&& cub->map.grid[(int)new_y][(int)new_x] != '1')
		cub->player->pos_y = new_y;
}

void	move_backward(t_data *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player->pos_x - cub->player->dir_x * MOVE;
	new_y = cub->player->pos_y - cub->player->dir_y * MOVE;
	if (new_x < cub->map.width && new_y < cub->map.height
		&& cub->map.grid[(int)new_y][(int)new_x] != '1')
		cub->player->pos_x = new_x;
	if (new_x < cub->map.width && new_y < cub->map.height
		&& cub->map.grid[(int)new_y][(int)new_x] != '1')
		cub->player->pos_y = new_y;
}

void	move_left(t_data *cub)
{
	double	new_x;
	double	new_y;
	double	perp_x;
	double	perp_y;

	perp_x = cub->player->dir_y;
	perp_y = -cub->player->dir_x;
	new_x = cub->player->pos_x + perp_x * MOVE;
	new_y = cub->player->pos_y + perp_y * MOVE;
	if (new_x < cub->map.width && new_y < cub->map.height
		&& cub->map.grid[(int)new_y][(int)new_x] != '1')
		cub->player->pos_x = new_x;
	if (new_x < cub->map.width && new_y < cub->map.height
		&& cub->map.grid[(int)new_y][(int)new_x] != '1')
		cub->player->pos_y = new_y;
}

void	move_right(t_data *cub)
{
	double	new_x;
	double	new_y;
	double	perp_x;
	double	perp_y;

	perp_x = -cub->player->dir_y;
	perp_y = cub->player->dir_x;
	new_x = cub->player->pos_x + perp_x * MOVE;
	new_y = cub->player->pos_y + perp_y * MOVE;
	if (new_x < cub->map.width && new_y < cub->map.height
		&& cub->map.grid[(int)new_y][(int)new_x] != '1')
		cub->player->pos_x = new_x;
	if (new_x < cub->map.width && new_y < cub->map.height
		&& cub->map.grid[(int)new_y][(int)new_x] != '1')
		cub->player->pos_y = new_y;
}

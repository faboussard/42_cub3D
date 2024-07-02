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

void	move_forward(t_data *cub, t_player *player, t_map *map)
{
	double	dest_x;
	double	dest_y;

	dest_x = player->pos.x + (player->dir.x * MOVE);
	dest_y = player->pos.y + (player->dir.y * MOVE);
	update_player_position(data, player, dest_x, dest_y);
	map->pos_x = player->pos.x;
	map->pos_y = player->pos.y;
}

void	move_backward(t_cub3d *data, t_player *player, t_map *map)
{
	double	dest_x;
	double	dest_y;

	if (data->anim_close == true || data->anim_open == true)
		return ;
	dest_x = player->pos.x + (player->dir.x * -1 * MOVE);
	dest_y = player->pos.y + (player->dir.y * -1 * MOVE);
	update_player_position(data, player, dest_x, dest_y);
	map->pos_x = player->pos.x;
	map->pos_y = player->pos.y;
}

void	move_left(t_cub3d *data, t_player *player, t_map *map)
{
	double	dest_x;
	double	dest_y;

	if (data->anim_close == true || data->anim_open == true)
		return ;
	dest_x = player->pos.x + (player->dir.y * MOVE);
	dest_y = player->pos.y + (player->dir.x * -1 * MOVE);
	update_player_position(data, player, dest_x, dest_y);
	map->pos_x = player->pos.x;
	map->pos_y = player->pos.y;
}

void	move_right(t_cub3d *data, t_player *player, t_map *map)
{
	double	dest_x;
	double	dest_y;

	if (data->anim_close == true || data->anim_open == true)
		return ;
	dest_x = player->pos.x + (player->dir.y * -1 * MOVE);
	dest_y = player->pos.y + (player->dir.x * MOVE);
	update_player_position(data, player, dest_x, dest_y);
	map->pos_x = player->pos.x;
	map->pos_y = player->pos.y;
}
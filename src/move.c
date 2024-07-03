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

static void	update_player_position(t_player *player, \
double dest_x, double dest_y);

void	move_forward(t_data *cub)
{
	double	dest_x;
	double	dest_y;

	dest_x = cub->player->pos_x + (cub->dir_x * MOVE);
	dest_y = cub->player->pos_y + (cub->dir_y * MOVE);
	//	if (cub->map.grid[dest_x - 1][dest_y] == '1')
//		return ;
	update_player_position(cub->player, dest_x, dest_y);
//	map->pos_x = cub->player->pos_x;
//	map->pos_y = cub->player->pos_y;
}

//void	move_backward(t_data *cub, t_player *player)
//{
//	double	dest_x;
//	double	dest_y;
//
//	dest_x = player->pos_x + (cub->dir_x * -1 * MOVE);
//	dest_y = player->pos_y + (cub->dir_y * -1 * MOVE);
////	if (cub->map.grid[dest_x - 1][dest_y] == '1')
////		return ;
//	update_player_position(player, dest_x, dest_y);
////	map->pos_x = player->pos.x;
////	map->pos_y = player->pos.y;
//}

//void	move_left(t_cub3d *data, t_player *player, //t_map *map)
//{
//	double	dest_x;
//	double	dest_y;
//
//	dest_x = player->pos.x + (cub->dir_y * MOVE);
//	dest_y = player->pos.y + (cub->dir_x * -1 * MOVE);
//	update_player_position(data, player, dest_x, dest_y);
////	map->pos_x = player->pos.x;
////	map->pos_y = player->pos.y;
//}
//
//void	move_right(t_cub3d *data, t_player *player, t_map *map)
//{
//	double	dest_x;
//	double	dest_y;
//
//	if (data->anim_close == true || data->anim_open == true)
//		return ;
//	dest_x = player->pos.x + (player->dir.y * -1 * MOVE);
//	dest_y = player->pos.y + (player->dir.x * MOVE);
//	update_player_position(data, player, dest_x, dest_y);
//	map->pos_x = player->pos.x;
//	map->pos_y = player->pos.y;
//}

//static void	update_player_position(t_data *cub, t_player *player, \
//double dest_x, double dest_y)
static void	update_player_position(t_player *player, \
double dest_x, double dest_y)
{
//	if (data->map.map[(int)player->pos.y][(int)dest_x] != '1'
//	    && data->map.map[(int)player->pos.y][(int)dest_x] != 'D'
//	    && data->map.map[(int)player->pos.y][(int)dest_x] != 'T')
		player->pos_x = dest_x;
//	if (data->map.map[(int)dest_y][(int)player->pos.x] != '1'
//	    && data->map.map[(int)dest_y][(int)player->pos.x] != 'D'
//	    && data->map.map[(int)dest_y][(int)player->pos.x] != 'T')
		player->pos_y = dest_y;
}
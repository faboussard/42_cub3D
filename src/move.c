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

void	move_forward(t_data *cub)
{
	double	dest_x;
	double	dest_y;

	dest_x = cub->player->pos_x + (cub->dir_x * MOVE);
	dest_y = cub->player->pos_y + (cub->dir_y * MOVE);
	//	if (cub->map.grid[dest_x - 1][dest_y] == '1')
//		return ;
	update_player_position(cub->player, dest_x, dest_y);
}

void	move_backward(t_data *cub)
{
	double	dest_x;
	double	dest_y;

	dest_x = cub->player->pos_x + (cub->dir_x * -1 * MOVE);
	dest_y = cub->player->pos_y + (cub->dir_y * -1 * MOVE);
//	if (cub->map.grid[dest_x - 1][dest_y] == '1')
//		return ;
	update_player_position(cub->player, dest_x, dest_y);
}

void	move_left(t_data *cub)
{
	double	dest_x;
	double	dest_y;

	dest_x = cub->player->pos_x + (cub->dir_y * MOVE);
	dest_y = cub->player->pos_y + (cub->dir_x * -1 * MOVE);
	//	if (cub->map.grid[dest_x - 1][dest_y] == '1')
//		return ;
	update_player_position(cub->player, dest_x, dest_y);
}

void	move_right(t_data *cub)
{
	double	dest_x;
	double	dest_y;

	dest_x = cub->player->pos_x  + (cub->dir_y * -1 * MOVE);
	dest_y = cub->player->pos_y + (cub->dir_x * MOVE);
	//	if (cub->map.grid[dest_x - 1][dest_y] == '1')
//		return ;
	update_player_position(cub->player, dest_x, dest_y);
}

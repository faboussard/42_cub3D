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
	int	x;
	int	y;

	x = (int)(cub->player->pos_x + (cub->player->dir_x * MOVE));
	y = (int)cub->player->pos_y;
	if (cub->map.grid[y][x] != '1')
		cub->player->pos_x += cub->player->dir_x * MOVE;
	x = (int)cub->player->pos_x;
	y = (int)(cub->player->pos_y + (cub->player->dir_y * MOVE));
	if (cub->map.grid[y][x] != '1')
		cub->player->pos_y += cub->player->dir_y * MOVE;
}

void	move_backward(t_data *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player->pos_x + (cub->player->dir_x * -1 * MOVE));
	y = (int)cub->player->pos_y;
	if (cub->map.grid[y][x] != '1')
		cub->player->pos_x += cub->player->dir_x * -1 * MOVE;
	x = (int)cub->player->pos_x;
	y = (int)(cub->player->pos_y + (cub->player->dir_y * -1 * MOVE));
	if (cub->map.grid[y][x] != '1')
		cub->player->pos_y += cub->player->dir_y * -1 * MOVE;
}

void move_left(t_data *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player->pos_x + (cub->player->dir_x * MOVE));
	y = (int)cub->player->pos_y;
	if (cub->map.grid[y][x] != '1')
		cub->player->pos_x += cub->player->dir_y * MOVE;
	x = (int)cub->player->pos_x;
	y = (int)(cub->player->pos_y - (cub->player->dir_y * MOVE));
	if (cub->map.grid[y][x] != '1')
		cub->player->pos_y -= cub->player->dir_x * MOVE;
}

void move_right(t_data *cub)
{
	int	x;
	int	y;

	x = (int)(cub->player->pos_x - (cub->player->dir_y * MOVE));
	y = (int)cub->player->pos_y;
	if (cub->map.grid[y][x] != '1')
		cub->player->pos_x -= cub->player->dir_y * MOVE;
	x = (int)cub->player->pos_x;
	y = (int)(cub->player->pos_y + (cub->player->dir_x * MOVE));
	if (cub->map.grid[y][x] != '1')
		cub->player->pos_y += cub->player->dir_x * MOVE;
}


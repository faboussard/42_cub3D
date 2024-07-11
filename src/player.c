/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:20:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/11 12:55:48 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_plane(t_data *cub, char c)
{
	if (c == 'N')
	{
		cub->plane_x = 0.66;
		cub->plane_y = 0.0;
	}
	else if (c == 'S')
	{
		cub->plane_x = -0.66;
		cub->plane_y = 0.0;
	}
	else if (c == 'E')
	{
		cub->plane_x = 0.0;
		cub->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		cub->plane_x = 0.0;
		cub->plane_y = -0.66;
	}
}

static void	init_player_eyes(t_data *cub, char c)
{
	if (c == 'N')
	{
		cub->player->dir_x = 0;
		cub->player->dir_y = -1;
	}
	else if (c == 'S')
	{
		cub->player->dir_x = 0;
		cub->player->dir_y = 1;
	}
	else if (c == 'E')
	{
		cub->player->dir_x = 1;
		cub->player->dir_y = 0;
	}
	else if (c == 'W')
	{
		cub->player->dir_x = -1;
		cub->player->dir_y = 0;
	}
	init_plane(cub, c);
}

static int	search_player_position(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == 'N' || str[x] == 'S' || str[x] == 'E' || str[x] == 'W')
			return (x);
		x++;
	}
	return (0);
}

void	init_player_position(t_data *cub)
{
	int	y;
	int	x;

	cub->player = ft_calloc(sizeof(t_player), 1);
	if (cub->player == NULL)
		close_window(cub);
	y = 0;
	x = search_player_position(cub->map.grid[y]);
	if (x != 0)
		map_error(NULL, cub->map.copy);
	while (cub->map.grid[y] && x == 0)
	{
		x = search_player_position(cub->map.grid[y]);
		if (x != 0)
			break ;
		y++;
	}
	cub->player->pos_y = (double)(y + 0.5);
	cub->player->pos_x = (double)(x + 0.5);
	init_player_eyes(cub, cub->map.grid[y][x]);
}

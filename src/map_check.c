/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:20:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/11 15:45:05 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	wall_or_player(t_data *cub, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (x == 0 || y == 0)
			map_error(NULL, cub->map.copy);
		cub->player_pos[0] = y;
		cub->player_pos[1] = x;
		return (0);
	}
	return (c == '1' || c == ' ');
}

static bool	is_within_the_map(char **map, size_t y, size_t x, size_t max_y)
{
	if (y == 0 || y + 1 == max_y || x == 0
		|| !map[y - 1][x]
		|| !map[y + 1][x]
		|| !map[y][x - 1]
		|| !map[y][x + 1])
		return (0);
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x - 1] == ' '
		|| map[y][x + 1] == ' ')
		return (0);
	return (1);
}

static bool	check_max_size(t_data *cub, size_t y, size_t x)
{
	if (cub->map.width < x)
		cub->map.width = x;
	if (cub->map.height < y)
		cub->map.height = y;
	if (cub->map.width >= MAX_WIDTH)
		return (1);
	if (cub->map.height >= MAX_HEIGHT)
		return (1);
	return (0);
}

bool	check_map_is_closed(t_data *cub, char **map)
{
	size_t	x;
	size_t	y;
	size_t	max_y;

	if (!map[2])
		return (1);
	y = 0;
	max_y = 0;
	while (map[max_y])
		max_y++;
	while (map[y])
	{
		x = -1;
		while (map[y][++x])
		{
			if ((!wall_or_player(cub, map[y][x], y, x)
				&& is_within_the_map(map, y, x, max_y) == 0)
				|| check_max_size(cub, y, x))
				return (1);
		}
		y++;
	}
	return (cub->map.width < 3);
}

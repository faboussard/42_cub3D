/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:20:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/11 14:53:44 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_a_wall(char c)
{
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

bool	check_map_is_closed(char **map)
{
	size_t	y;
	size_t	x;
	size_t	max_x;
	size_t	max_y;

	if (!map[2])
		return (1);
	y = 0;
	max_x = 0;
	max_y = 0;
	while (map[max_y])
		max_y++;
	while (map[y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (!is_a_wall(map[y][x]) && !is_within_the_map(map, y, x, max_y))
				return (1);
		}
		if (max_x < 3 && x > max_x)
			max_x = x;
		y++;
	}
	return (max_x < 3);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:48:53 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/03 13:44:50 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	locate_player(char **map, t_player *player)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'P')
			{
				(*player).x = x;
				(*player).y = y;
				return ;
			}
			y++;
		}
		x++;
	}
}

static bool	is_surrounded_by_zeros(char **copy, size_t x, size_t y)
{
	if (copy[x][y + 1] == '0' || copy[x][y + 1] == 'E' || copy[x][y + 1] == 'C')
		return (1);
	if (copy[x][y - 1] == '0' || copy[x][y - 1] == 'E' || copy[x][y - 1] == 'C')
		return (1);
	if (copy[x + 1][y] == '0' || copy[x + 1][y] == 'E' || copy[x + 1][y] == 'C')
		return (1);
	if (copy[x - 1][y] == '0' || copy[x - 1][y] == 'E' || copy[x - 1][y] == 'C')
		return (1);
	return (0);
}

static void	search_lost_p(t_map map)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (map.copy[x])
	{
		y = 0;
		while (map.copy[x][y])
		{
			if (map.copy[x][y] == 'p')
			{
				if (is_surrounded_by_zeros(map.copy, x, y))
				{
					fill_paths(map, x, y);
					search_lost_p(map);
				}
			}
			y++;
		}
		x++;
	}
}

static void	search_fill_free_path(t_map map, size_t rows, size_t cols)
{
	size_t	x;
	size_t	y;

	x = 1;
	while (x < rows)
	{
		y = 1;
		while (y < cols)
		{
			if (map.copy[x][y] == 'p')
				fill_paths(map, x, y);
			y++;
		}
		x++;
	}
	search_lost_p(map);
}

bool	check_path(t_map *map)
{
	size_t		x;
	size_t		y;

	locate_player(map->copy, &map->player);
	fill_paths(*map, map->player.x, map->player.y);
	search_fill_free_path(*map, map->rows, map->cols);
	x = 1;
	y = 1;
	while (x < map->rows)
	{
		y = 1;
		while (y < map->cols)
		{
			if (map->copy[x][y] == 'C' || map->copy[x][y] == 'E')
				return (0);
			y++;
		}
		x++;
	}
	return (1);
}

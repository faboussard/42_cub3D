/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:57:40 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/03 13:42:40 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	map_contains_0epc(t_map *map, char *tmp_map)
{
	size_t	door;
	size_t	player;
	size_t	x;

	door = 0;
	player = 0;
	x = 0;
	map->coins = 0;
	while (tmp_map[x] && door < 2 && player < 2)
	{
		if (tmp_map[x] == 'C')
			map->coins++;
		if (tmp_map[x] == 'E')
			door++;
		if (tmp_map[x] == 'P')
			player++;
		if (tmp_map[x + 1] && tmp_map[x] == '\n' && tmp_map[x + 1] == '\n')
			return (0);
		x++;
	}
	return ((door == 1 && player == 1 && map->coins != 0));
}

static bool	check_lines(char **map, size_t x, size_t rows)
{
	size_t	y;

	y = 0;
	while (map[x][y])
	{
		if ((x == 0 || x == rows) && map[x][y] != '1')
			return (0);
		y++;
	}
	return (1);
}

static bool	check_walls_and_center(char **map, size_t cols, size_t rows)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (map[x])
	{
		if (!check_lines(map, x, rows))
			return (0);
		if (map[x][0] != '1' || map[x][cols - 1] != '1')
			return (0);
		y = 0;
		while (map[x][y])
		{
			if (!ft_search_char(map[x][y], "01PCE"))
				return (0);
			y++;
		}
		x++;
	}
	x--;
	return (1);
}

static bool	check_map(t_map *map, char *tmp_map)
{
	size_t	x;
	size_t	cols;

	x = 0;
	if (!map->grid[3])
		return (0);
	cols = ft_strlen(map->grid[0]);
	while (map->grid[x + 1])
	{
		if (ft_strlen(map->grid[x + 1]) != cols)
			return (0);
		x++;
	}
	if (!check_walls_and_center(map->grid, cols, x))
		return (0);
	if (!map_contains_0epc(map, tmp_map))
		return (0);
	map->cols = cols;
	map->rows = x;
	map->status = 1;
	return (1);
}

void	launch_checks(t_map *map, char *tmp_map)
{
	(*map).grid = ft_split(tmp_map, '\n');
	(*map).copy = ft_split(tmp_map, '\n');
	if (check_map(map, tmp_map) == 0)
	{
		free(tmp_map);
		map_error(map->grid, map->copy);
	}
	if (check_path(map) == 0)
	{
		free(tmp_map);
		map_error(map->grid, map->copy);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:48:53 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/03 13:06:05 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	fill_down(t_map *map, size_t x, size_t y);
static void	fill_left(t_map *map, size_t x, size_t y);
static void	fill_right(t_map *map, size_t x, size_t y);

static void	fill_up(t_map *map, size_t x, size_t y)
{
	while ((*map).copy[x][y] != '1' && x != 0)
	{
		(*map).copy[x][y] = 'p';
		if ((*map).copy[x][y - 1] != 'p' && (*map).copy[x][y - 1] != '1')
			fill_left(map, x, y);
		if ((*map).copy[x][y + 1] != 'p' && (*map).copy[x][y + 1] != '1')
			fill_right(map, x, y);
		x--;
	}
}

static void	fill_down(t_map *map, size_t x, size_t y)
{
	while ((*map).copy[x][y] != '1' && x != (map->rows))
	{
		(*map).copy[x][y] = 'p';
		x++;
	}
}

static void	fill_left(t_map *map, size_t x, size_t y)
{
	while ((*map).copy[x][y] != '1' && y > 0)
	{
		(*map).copy[x][y] = 'p';
		if ((*map).copy[x + 1][y] != 'p' && (*map).copy[x + 1][y] != '1')
			fill_down(map, x, y);
		y--;
	}
}

static void	fill_right(t_map *map, size_t x, size_t y)
{
	while ((*map).copy[x][y] != '1' && y != (map->cols))
	{
		(*map).copy[x][y] = 'p';
		if ((*map).copy[x + 1][y] != 'p' && (*map).copy[x + 1][y] != '1')
			fill_down(map, x, y);
		y++;
	}
}

void	fill_paths(t_map map, size_t x, size_t y)
{
	while (map.copy[x][y] != '1' && y != (map.cols))
	{
		fill_down(&map, x, y);
		fill_up(&map, x, y);
		fill_left(&map, x, y);
		fill_right(&map, x, y);
		y++;
	}
}

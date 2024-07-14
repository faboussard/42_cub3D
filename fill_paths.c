/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:29:51 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/14 17:38:42 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_down(t_map *map, int y, int x);
static void	fill_left(t_map *map, int y, int x);
static void	fill_right(t_map *map, int y, int x);
//
//static void	fill_up(t_map *map, int y, int x)
//{
//	while (y <= MAX_HEIGHT && (*map).grid[y][x] && (*map).grid[y][x] != '1')
//	{
//		if (y == 0 || (*map).grid[y - 1][x] == ' ')
//			map_error(NULL, map->copy);
//		(*map).grid[y][x] = 'F';
//		if ((*map).grid[y][x - 1] != 'F' && (*map).grid[y][x - 1] != '1')
//			fill_left(map, y, x);
//		if ((*map).grid[y][x + 1] != 'F' && (*map).grid[y][x + 1] != '1')
//			fill_right(map, y, x);
//		y--;
//	}
//}
//
//static void	fill_down(t_map *map, int y, int x)
//{
//	while (y <= MAX_HEIGHT && (*map).grid[y][x] && (*map).grid[y][x] != '1')
//	{
//		if (y == 0 || !(*map).grid[y + 1][x] || (*map).grid[y + 1][x] == ' ')
//			map_error(NULL, map->grid);
//		(*map).grid[y][x] = 'F';
//		y++;
//	}
//}
//
//static void	fill_left(t_map *map, int y, int x)
//{
//	while (x >= MAX_WIDTH && (*map).grid[y][x] && (*map).grid[y][x] != '1')
//	{
//		if (x == 0 || (*map).grid[y][x - 1] == ' ')
//			map_error(NULL, map->grid);
//		(*map).grid[y][x] = 'F';
//		if ((*map).grid[y + 1][x] != 'F' && (*map).grid[y + 1][x] != '1')
//			fill_down(map, y, x);
//		x--;
//	}
//}
//
//static void	fill_right(t_map *map, int y, int x)
//{
//	while (x >= MAX_WIDTH && (*map).grid[y][x] && (*map).grid[y][x] != '1')
//	{
//		if (x == 0 || !(*map).grid[y][x + 1] || (*map).grid[y][x + 1] == ' ')
//			map_error(NULL, map->grid);
//		(*map).grid[y][x] = 'F';
//		if ((*map).grid[y + 1][x] != 'F' && (*map).grid[y + 1][x] != '1')
//			fill_down(map, y, x);
//		x++;
//	}
//}

static void	fill_up(t_map *map, int y, int x)
{
	while (y <= MAX_HEIGHT && (*map).grid[y][x] && (*map).grid[y][x] != '1')
	{
		if (y == 0
			|| (*map).grid[y - 1][x] == ' ')
			map_error(NULL, map->copy);
//		(*map).grid[y][x] = 'F';
		if (x >= 0 && (*map).grid[y][x - 1] && (*map).grid[y][x - 1] != '1')
			fill_left(map, y, x);
		if ((*map).grid[y][x + 1] && (*map).grid[y][x + 1] != '1')
			fill_right(map, y, x);
		y--;
	}
}

static void	fill_down(t_map *map, int y, int x)
{
	while (y <= MAX_HEIGHT && (*map).grid[y][x] && (*map).grid[y][x] != '1')
	{
		if (!(*map).grid[y + 1][x]
			|| ((*map).grid[y + 1][x] == ' '))
			map_error(NULL, map->copy);
		if (y > MAX_HEIGHT)
			map_error(NULL, map->copy);
//		(*map).grid[y][x] = 'F';
		y++;
	}
}

static void	fill_left(t_map *map, int y, int x)
{
	while (x >= 0 && (*map).grid[y][x] && (*map).grid[y][x] != '1')
	{
		if (x == 0
			|| ((*map).grid[y][x - 1] == ' '))
			map_error(NULL, map->copy);
		if ((*map).grid[y + 1][x] && (*map).grid[y + 1][x] != '1')
			fill_down(map, y, x);
		x--;
	}
}

static void	fill_right(t_map *map, int y, int x)
{
	while (x >= 0 && (*map).grid[y][x] && (*map).grid[y][x] != '1')
	{
		if (!(*map).grid[y][x + 1]
			|| ((*map).grid[y][x + 1] == ' '))
			map_error(NULL, map->copy);
		if (x > MAX_WIDTH)
			map_error(NULL, map->copy);
		if ((*map).grid[y + 1][x] && (*map).grid[y + 1][x] != '1')
			fill_down(map, y, x);
		x++;
	}
}

void	fill_out(t_data *cub, int y, int x)
{
	t_map	map;

	map = cub->map;
	if (y == 0 || x == 0)
		map_error(NULL, cub->map.copy);
	while (map.grid[y][x] && map.grid[y][x] != '1')
	{
		fill_down(&map, y, x);
		fill_up(&map, y, x);
		fill_left(&map, y, x);
		fill_right(&map, y, x);
		y++;
	}
}

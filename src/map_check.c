/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:20:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/12 11:09:08 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	is_player(t_data *cub, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (x == 0 || y == 0)
			map_error(NULL, cub->map.copy);
		cub->player_pos[0] = y;
		cub->player_pos[1] = x;
		return (1);
	}
	return (0);
}

static void	fill_in(t_data *cub, const int y, const int x, const int max_y)
{
	if (cub->map.grid[y] && cub->map.grid[y][x]
		&& (cub->map.grid[y][x] == '1' || cub->map.grid[y][x] == 'F'))
		return ;
	if (x <= 0 || y <= 0 || y >= max_y || x > MAX_WIDTH
		|| !cub->map.grid[y][x] || ft_is_space(cub->map.grid[y][x]))
	{
		ft_free_tab(&cub->map.copy);
		(void)write(2, "Error\n: Map isn't closed\n", 25);
		exit(1);
	}
	if (cub->map.grid[y][x] == '0')
		cub->map.grid[y][x] = 'F';
	fill_in(cub, y - 1, x, max_y);
	fill_in(cub, y + 1, x, max_y);
	fill_in(cub, y, x - 1, max_y);
	fill_in(cub, y, x + 1, max_y);
}

static void	check_max_size(t_data *cub, size_t x)
{
	if (x > MAX_WIDTH)
	{
		write(2, "Error\nMap too big\n", 18);
		ft_free_tab(&cub->map.copy);
		exit(EXIT_FAILURE);
	}
	if (cub->map.width < x)
		cub->map.width = x;
}

bool	check_map_is_closed(t_data *cub, char **map)
{
	size_t	x;
	size_t	y;
	size_t	max_y;

	if (!map[2])
		return (1);
	max_y = 0;
	while (map[max_y])
		max_y++;
	if (max_y > MAX_HEIGHT)
		map_error(NULL, cub->map.copy);
	cub->map.width = max_y;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			check_max_size(cub, x);
			if (is_player(cub, map[y][x], y, x))
				fill_in(cub, y, x, max_y);
		}
	}
	return (cub->map.width < 2);
}

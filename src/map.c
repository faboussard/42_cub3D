/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 22:20:55 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/29 13:49:25 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	ft_is_space(const int c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

static bool	map_contains_01nsew(t_map *map, char *tmp_map)
{
	static size_t	player;
	size_t	x;

	(void)map;
	player = 0;
	x = 0;
	if (tmp_map[x] && player < 2)
	{
		if (tmp_map[x] == 'N' || tmp_map[x] == 'S'
			|| tmp_map[x] == 'E' || tmp_map[x] == 'W')
			player++;
		else if (tmp_map[x] != '0' && tmp_map[x] != '1' && tmp_map[x] != '\n'
				&& !ft_is_space(tmp_map[x]))
			return (0);
		if (tmp_map[x + 1] && tmp_map[x] == '\n' && tmp_map[x + 1] == '\n')
			return (0);
		x++;
	}
	return (player < 2);
}

/*
 * Pour configurer CLion pour un projet Makefile, vous pouvez suivre les étapes suivantes :

1. Ouvrez CLion et sélectionnez "File" -> "Open".
2. Naviguez jusqu'à votre projet et sélectionnez le fichier `Makefile`. Cliquez sur "OK".
3. CLion vous demandera si vous voulez ouvrir le projet dans la fenêtre actuelle ou dans une nouvelle fenêtre.
 Choisissez selon vos préférences.
4. Une fois le projet ouvert, allez dans "File" -> "Settings" -> "Build, Execution, Deployment" -> "Makefile".
5. Ici, vous pouvez configurer les options de Makefile selon vos besoins. Par exemple, vous pouvez spécifier
 l'emplacement de l'exécutable `make`, définir les options de la ligne de commande, etc.
6. Cliquez sur "Apply" puis sur "OK" pour enregistrer vos paramètres.

Notez que CLion utilise le plugin Makefile pour fournir le support de Makefile. Si vous ne voyez pas
 l'option Makefile dans les paramètres, assurez-vous que le plugin Makefile est installé et activé.
 Vous pouvez vérifier cela en allant dans "File" -> "Settings" -> "Plugins" et en recherchant "Makefile".
 * No need to check the lines lengths
 *
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
*/

//static bool	map_contains_01nsew(t_map *map, char *tmp_map)
//{
//	static size_t	player;
//	size_t	x;
//
//	player = 0;
//	x = 0;
//	if (tmp_map[x] && player < 2)
//	{
//		if (tmp_map[x] == 'N' || tmp_map[x] == 'S'
//			|| tmp_map[x] == 'E' || tmp_map[x] == 'W')
//			player++;
//		else if (tmp_map[x] != '0' && tmp_map[x] != '1' && tmp_map[x] != '\n')
//			return (0);
//		if (tmp_map[x + 1] && tmp_map[x] == '\n' && tmp_map[x + 1] == '\n')
//			return (0);
//		x++;
//	}
//	return (player < 2);
//}
//
//static bool	check_lines(char **map, size_t x, size_t rows)
//{
//	size_t	y;
//
//	y = 0;
//	while (map[x][y])
//	{
//		if ((x == 0 || x == rows) && map[x][y] != '1')
//			return (0);
//		y++;
//	}
//	return (1);
//}
//
//static bool	check_walls_and_center(char **map, size_t cols, size_t rows)
//{
//	size_t	x;
//	size_t	y;
//
//	x = 0;
//	while (map[x])
//	{
//		if (!check_lines(map, x, rows))
//			return (0);
//		if (map[x][0] != '1' || map[x][cols - 1] != '1')
//			return (0);
//		y = 0;
//		while (map[x][y])
//		{
//			if (!map_contains_01nsew(map, map[x]))
//			if (!ft_search_char(map[x][y], "01PCE"))
//				return (0);
//			y++;
//		}
//		x++;
//	}
//	x--;
//	return (1);
//}

static bool	check_map(t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	if (!map->grid[3])
		return (0);
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (!map_contains_01nsew(map, map->grid[y]))
				return (0);
			x++;
		}
	}
	map->cols = x;
	map->rows = y;
	map->status = 1;
	return (1);
}

void	launch_checks(t_map *map, char *tmp_map)
{
	(*map).grid = ft_split(tmp_map, '\n');
	(*map).copy = ft_split(tmp_map, '\n');
	if (check_map(map) == 0)
	{
		free(tmp_map);
		map_error(map->grid, map->copy);
	}
}

//void	launch_checks(t_map *map, char *tmp_map)
//{
//	(*map).grid = ft_split(tmp_map, '\n');
//	(*map).copy = ft_split(tmp_map, '\n');
//	if (check_map(map, tmp_map) == 0)
//	{
//		free(tmp_map);
//		map_error(map->grid, map->copy);
//	}
//	if (check_path(map) == 0)
//	{
//		free(tmp_map);
//		map_error(map->grid, map->copy);
//	}
//}


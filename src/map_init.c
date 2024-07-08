/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:34:20 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/08 14:40:01 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void	init_map(t_data *cub, char *line)
//{
//	size_t	i;
//	size_t	j;
//
//	i = 0;
//	j = 0;
//	while (line[i])
//	{
//		if (ft_search_char(line[i], "NEWS"))
//		{
//			cub->player->pos_x = i + 0.5;
//			cub->player->pos_y = j + 0.5;
//			cub->player->dir = line[i];
//			line[i] = '0';
//		}
//		if (line[i] == '2')
//			cub->sprite->count++;
//		i++;
//	}
//}

static void	fill_tmp_map(int fd, char **tmp_map)
{
	int		min_line_nb;
	char	*line;

	min_line_nb = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line && min_line_nb == 1)
			empty_file_error();
		if (!line)
			break ;
		*tmp_map = ft_strjoin_free_both(*tmp_map, line);
		if (!*tmp_map)
			malloc_error();
		if (min_line_nb < 9)
			min_line_nb++;
	}
	close(fd);
	if (min_line_nb < 9)
		map_error(*tmp_map, NULL);
}

static char	*get_map_inline(char *ber)
{
	int		fd;
	char	*tmp_map;

	fd = open(ber, O_RDONLY);
	if (fd < 0)
		no_such_file_error();
	tmp_map = NULL;
	fill_tmp_map(fd, &tmp_map);
	return (tmp_map);
}

static bool	check_point_and_color(char *str, bool is_card)
{
	static bool	north = 0;
	static bool	south = 0;
	static bool	west = 0;
	static bool	east = 0;

	if (is_card && (ft_strncmp(str, "NO ", 3) == 0
			|| ft_strncmp(str, "SO ", 3) == 0
			|| ft_strncmp(str, "WE ", 3) == 0
			|| ft_strncmp(str, "EA ", 3) == 0))
	{
		if (ft_strncmp(str, "NO ", 3) == 0 && north == 0)
			north = 1;
		else if (ft_strncmp(str, "SO ", 3) == 0 && south == 0)
			south = 1;
		else if (ft_strncmp(str, "WE ", 3) == 0 && west == 0)
			west = 1;
		else if (ft_strncmp(str, "EA ", 3) == 0 && east == 0)
			east = 1;
		else
			map_error(str, NULL);
		return (1);
	}
	else if (!is_card)
		return ((!ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2)));
	return (0);
}
static void check_textures_and_color(char *str, int *i)
{
	int	cardinal_points;
	int	colors;

	cardinal_points = 0;
	colors = 0;
	if (check_point_and_color(str, 1))
		cardinal_points++;
	else if (check_point_and_color(str, 0))
		colors++;
	while (str[*i] && cardinal_points < 5 && colors < 3)
	{
		if (check_point_and_color(str + *i, 1))
			cardinal_points++;
		else if (check_point_and_color(str + *i, 0))
			colors++;
		++(*i);
	}
	if (cardinal_points != 4 || colors != 2)
		map_error(str, NULL);
}

static void	check_map_lines(char *str)
{
	int	i;

	i = 2;
	check_textures_and_color(str, &i);
	while (str[i] && ft_strncmp(str + i, "\n", 2) != 0)
		i++;
	while (str[i] && ft_strncmp(str + i, "\n", 2) == 0)
		i += 2;
	while (str[i] && str[i + 1])
	{
		if (str[i++] == '\n' && str[i] == '\n')
			map_error(str, NULL);
	}
}

void	define_map(t_map *map, char *file_name)
{
	char	*tmp_map;

	map->status = 0;
	tmp_map = get_map_inline(file_name);
	check_map_lines(tmp_map);
	map->copy = ft_split(tmp_map, '\n');
	map->grid = map->copy + 6;
	dprintf(2, "TMP_MAP\n%s\n\n", tmp_map);
	free(tmp_map);
}

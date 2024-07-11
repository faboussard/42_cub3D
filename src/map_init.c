/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:34:20 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/11 12:52:48 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_map_inline(char *ber, char **tmp_map)
{
	int		fd;
	int		min_line_nb;
	char	*line;

	min_line_nb = 1;
	fd = open(ber, O_RDONLY);
	if (fd < 0)
		no_such_file_error();
	while (1)
	{
		line = get_next_line(fd);
		if (!line && min_line_nb == 1)
			empty_file_error();
		if (!line)
			break ;
		*tmp_map = ft_strjoin_free_both(*tmp_map, line);
		if (!**tmp_map)
			malloc_error();
		if (min_line_nb < 9)
			min_line_nb++;
	}
	close(fd);
	if (min_line_nb < 9)
		map_error(*tmp_map, NULL);
}

static bool	check_point_and_color(char *s, int i, bool is_card)
{
	static bool	north = 0;
	static bool	south = 0;
	static bool	west = 0;
	static bool	east = 0;

	if (is_card && (ft_strncmp(s + i, "NO ", 3) == 0 || ft_strncmp(s + i, "SO ",
				3) == 0 || ft_strncmp(s + i, "WE ", 3) == 0 || ft_strncmp(s + i,
				"EA ", 3) == 0))
	{
		if (ft_strncmp(s + i, "NO ", 3) == 0 && north == 0)
			north = 1;
		else if (ft_strncmp(s + i, "SO ", 3) == 0 && south == 0)
			south = 1;
		else if (ft_strncmp(s + i, "WE ", 3) == 0 && west == 0)
			west = 1;
		else if (ft_strncmp(s + i, "EA ", 3) == 0 && east == 0)
			east = 1;
		else
			map_error(s, NULL);
		return (1);
	}
	else if (!is_card)
		return ((!ft_strncmp(s + i, "F ", 2) || !ft_strncmp(s + i, "C ", 2)));
	return (0);
}

static void	check_textures_and_color(char *str, int *i)
{
	int	cardinal_points;
	int	colors;

	cardinal_points = 0;
	colors = 0;
	if (check_point_and_color(str, *i, 1))
		cardinal_points++;
	else if (check_point_and_color(str, *i, 0))
		colors++;
	while (str[++(*i)] && cardinal_points < 5 && colors < 3)
	{
		if (check_point_and_color(str, *i, 1))
			cardinal_points++;
		else if (check_point_and_color(str, *i, 0))
			colors++;
		if (cardinal_points == 4 && colors == 2)
			break ;
	}
	if (!str[*i] || cardinal_points != 4 || colors != 2)
		map_error(str, NULL);
	while (str[*i] && ft_strncmp(str + *i, "\n", 1) != 0)
		++(*i);
	while (str[*i] && ft_strncmp(str + *i, "\n", 1) == 0)
		++(*i);
}

static void	check_map_lines(char *s)
{
	int		i;
	bool	player_found;

	i = 0;
	player_found = 0;
	check_textures_and_color(s, &i);
	while (s[i] && s[i + 1])
	{
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
		{
			if (!player_found)
				player_found = 1;
			else
				map_error(s, NULL);
		}
		if ((!(s[i] == '0' || s[i] == '1' || s[i] == ' ' || s[i] == '\n'
					|| s[i] == 'N' || s[i] == 'S' || s[i] == 'E'
					|| s[i] == 'W')) || (s[i++] == '\n' && s[i] == '\n'
				&& s[i + 1] && s[i + 1] != '\n') || (!s[i + 1] && !(s[i] == '0'
					|| s[i] == '1' || s[i] == ' ' || s[i] == '\n')))
			map_error(s, NULL);
	}
	if (player_found == 0)
		map_error(s, NULL);
}

void	define_map(t_map *map, char *file_name)
{
	char	*tmp_map;

	tmp_map = NULL;
	get_map_inline(file_name, &tmp_map);
	check_map_lines(tmp_map);
	map->copy = ft_split(tmp_map, '\n');
	map->grid = map->copy + 6;
	dprintf(2, "TMP_MAP\n%s\n\n", tmp_map);
	free(tmp_map);
}

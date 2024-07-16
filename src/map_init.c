/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:34:20 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/12 11:20:23 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*get_map_inline(char *cub, size_t size)
{
	int		fd;
	char	buf[1];
	char	*tmp_map;

	if (size == 0)
		empty_file_error(0);
	if (size < 65)
		map_error(NULL, NULL);
	if (size > 50000)
	{
		write(2, "Error\nMap too big\n", 18);
		exit(EXIT_FAILURE);
	}
	fd = open(cub, O_RDONLY);
	if (fd < 0 || read(fd, buf, 0) < 0)
		no_such_file_error(fd);
	tmp_map = malloc(sizeof(char) * (size + 1));
	if (tmp_map == NULL)
		malloc_error(fd);
	read(fd, tmp_map, size);
	close(fd);
	return (tmp_map);
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
		if ((!ft_search_char(s[i], "01NSWE\n") && !ft_is_space(s[i]))
			|| (s[i++] == '\n' && s[i] == '\n' && s[i + 1] && !(s[i + 1] == '\n'
					|| ft_is_space(s[i + 1]))))
			map_error(s, NULL);
	}
	if (player_found == 0)
		map_error(s, NULL);
}

void	define_map(t_map *map, char *file_name)
{
	char	*tmp_map;
	int		fd;
	char	buf[1024];
	size_t	size;
	size_t	tmp_read;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || read(fd, buf, 0) < 0)
		no_such_file_error(fd);
	size = 0;
	tmp_read = read(fd, buf, 1024);
	while (tmp_read > 0)
	{
		size += tmp_read;
		tmp_read = read(fd, buf, 1024);
	}
	close(fd);
	tmp_map = get_map_inline(file_name, size);
	tmp_map[size] = '\0';
	check_map_lines(tmp_map);
	map->copy = ft_split(tmp_map, '\n');
	free(tmp_map);
	if (!map->copy)
		malloc_error(0);
	map->grid = map->copy + 6;
}

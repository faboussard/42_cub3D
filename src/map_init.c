/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:34:20 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/28 10:34:32 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//static void	init_map(t_data *cub, char *line)
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
	char 	*line;

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
		if (min_line_nb <= 9)
			min_line_nb++;
	}
	close(fd);
	if (min_line_nb < 9)
	{
		free(*tmp_map);
		map_error(NULL, NULL);
	}
}

static char	*get_map_inline(char *ber)
{
	int		fd;
	char 	*tmp_map;

	fd = open(ber, O_RDONLY);
	if (fd < 0)
		no_such_file_error();
//	tmp_map = ft_calloc(1, 1);
//	if (!tmp_map)
//		malloc_error();
	tmp_map = NULL;//ft_strdup("");
	fill_tmp_map(fd, &tmp_map);
	return (tmp_map);
}

void	define_map(t_map *map, char *file_name)
{
//	int		fd;
//	size_t	size;
	char	*tmp_map;

	map->status = 0;
	tmp_map = get_map_inline(file_name);
	dprintf(2, "%s\n", tmp_map);
/*	fd = open(file_name, O_RDONLY);
	if (fd < 0 || read(fd, tmp_map, 0) < 0)
	{
		free(tmp_map);
		no_such_file_error();
	}
	size = read(fd, tmp_map, size);
	if (size > 0)
	{
		tmp_map[size] = '\0';
		launch_checks(map, tmp_map);
	}*/
	free(tmp_map);
	exit(1);
//	close(fd);
}

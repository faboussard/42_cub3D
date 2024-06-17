/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:37:34 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/04 11:34:21 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	ends_by_ber(char *file)
{
	size_t	l;
	size_t	p;
	size_t	b;
	size_t	e;
	size_t	r;

	l = ft_strlen(file);
	if (l < 4)
		return (0);
	p = l - 4;
	b = l - 3;
	e = l - 2;
	r = l - 1;
	if (file[p] == '.' && file[b] == 'b' && file[e] == 'e' && file[r] == 'r')
		return (1);
	return (0);
}

static size_t	get_map_len(char *ber)
{
	int		fd;
	char	buf[1024];
	size_t	size;
	size_t	tmp_read;

	fd = open(ber, O_RDONLY);
	if (fd < 0 || read(fd, buf, 0) < 0)
		no_such_file_error();
	size = 0;
	tmp_read = read(fd, buf, 1024);
	while (tmp_read > 0)
	{
		size += tmp_read;
		tmp_read = read(fd, buf, 1024);
	}
	close(fd);
	if (size == 0)
		empty_file_error();
	return (size);
}

void	define_map(t_map *map, char *ber)
{
	int		fd;
	size_t	size;
	char	*tmp_map;

	map->status = 0;
	size = get_map_len(ber);
	if (size < 17)
		empty_file_error();
	tmp_map = malloc(sizeof(char) * (size + 1));
	if (!tmp_map)
		malloc_error();
	fd = open(ber, O_RDONLY);
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
	}
	free(tmp_map);
	close(fd);
}

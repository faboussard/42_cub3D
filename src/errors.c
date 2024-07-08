/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:43:15 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/08 15:44:14 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	no_such_file_error(void)
{
	write(2, "Error\nNo such file in directory\n", 32);
	exit(EXIT_FAILURE);
}

void	malloc_error(void)
{
	(void)!write(2, "Error\nMallor error\n", 19);
	exit(EXIT_FAILURE);
}

void	map_error(char *tmp_map, char **map)
{
	if (map)
		ft_free_tab(&map);
	if (tmp_map)
		free(tmp_map);
	write(2, "Error\nInvalid map\n", 18);
	exit(EXIT_FAILURE);
}

void	empty_file_error(void)
{
	write(2, "Error\nFile too small\n", 21);
	exit(EXIT_FAILURE);
}

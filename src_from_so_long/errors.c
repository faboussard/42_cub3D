/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:37:40 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/04 11:36:24 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	no_such_file_error(void)
{
	write(2, "Error\nNo such file in directory\n", 32);
	exit(EXIT_FAILURE);
}

void	malloc_error(void)
{
	write(2, "Error\nMallor error\n", 19);
	exit(EXIT_FAILURE);
}

void	input_error(void)
{
	write(2, "Error\nNo file.cub given\n", 24);
	exit(EXIT_FAILURE);
}

void	map_error(char **map, char **copy)
{
	if (map && copy)
		free_tabs(map, copy);
	write(2, "Error\nInvalid map\n", 18);
	exit(EXIT_FAILURE);
}

void	empty_file_error(void)
{
	write(2, "Error\nFile too small\n", 21);
	exit(EXIT_FAILURE);
}

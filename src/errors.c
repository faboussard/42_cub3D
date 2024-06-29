/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:43:15 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/21 15:43:20 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//void	no_such_file_error(void)
//{
//	write(2, "Error\nNo such file in directory\n", 32);
//	exit(EXIT_FAILURE);
//}

void	malloc_error(void)
{
	(void)!write(2, "Error\nMallor error\n", 19);
	exit(EXIT_FAILURE);
}

//void	input_error(void)
//{
//	write(2, "Error\nNo file.ber given\n", 24);
//	exit(EXIT_FAILURE);
//}
//
//void	map_error(char **map, char **copy)
//{
//	if (map && copy)
//		free_tabs(map, copy);
//	write(2, "Error\nInvalid map\n", 18);
//	exit(EXIT_FAILURE);
//}
//
//void	empty_file_error(void)
//{
//	write(2, "Error\nFile too small\n", 21);
//	exit(EXIT_FAILURE);
//}

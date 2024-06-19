/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:10:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/03 16:06:21 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	main(int ac, char **av)
{
	t_data	img;

	(void)av;
	if (ac != 2)
		ft_putendl_fd("Error: Wrong number of arguments", 2);
	//parsing
	init_mlx_win(&img);
	init_screen(&img);
	mlx_hook(img.win, 2, (1L << 0), &key_hook, &img);
	mlx_hook(img.win, DestroyNotify, 0, close_window, &img);
	mlx_hook(img.win, DestroyNotify, 0, close_window, &img);
	raycasting();
	mlx_loop(img.mlx);
	return (EXIT_SUCCESS);
}
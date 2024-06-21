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
	t_data	cub;

	(void)av;
	if (ac != 2)
		ft_putendl_fd("Error: Wrong number of arguments", 2);
	//parsing
	init_mlx_win(&cub);
	init_screen(&cub);
	mlx_hook(cub.win, 2, (1L << 0), &key_hook, &cub);
	mlx_hook(cub.win, DestroyNotify, 0, close_window, &cub);
	mlx_loop_hook(cub.mlx, (void *)raycasting, &cub);
//	raycasting(&cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
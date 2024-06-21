/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/21 15:42:40 by mbernard         ###   ########.fr       */
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

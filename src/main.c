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

#include "cub3D.h"

void init_game_loop(t_data *cub)
{
	(*cub).player = ft_calloc(sizeof (t_player), 1);
	if ((*cub).player == NULL)
		exit(EXIT_FAILURE);
	init_vectors(cub);
}

int	main(int ac, char **av)
{
	t_data	cub;

	ft_bzero(&cub, 1);
	if (ac != 2)
	{
		ft_putendl_fd("Error: Wrong number of arguments", 2);
		exit(1);
	}
	check_file_name(av[1]);
	init_screen(&cub);
	parsing(&cub, av[1]);
	mlx_hook(cub.win, KeyPress, KeyPressMask, key_press_hook, &cub);
	mlx_hook(cub.win, KeyRelease, KeyReleaseMask, key_release_hook, &cub);
	mlx_hook(cub.win, DestroyNotify, 0, close_window, &cub);
	init_game_loop(&cub);
	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}

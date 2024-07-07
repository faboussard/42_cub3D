/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/07 10:36:00 by mbernard         ###   ########.fr       */
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

static void	init_cub_values(t_data *cub)
{
	cub->keys.key_pressed_a = 0;
	cub->keys.key_pressed_d = 0;
	cub->keys.key_pressed_s = 0;
	cub->keys.key_pressed_w = 0;
	cub->keys.key_pressed_m = 0;
	cub->keys.key_pressed_left = 0;
	cub->keys.key_pressed_right = 0;
}

int	main(int ac, char **av)
{
	t_data	cub;

	if (ac != 2)
	{
		(void)write(2, "Error: Wrong number of arguments\n", 33);
		exit(1);
	}
	ft_bzero(&cub, 1);
	check_file_name(av[1]);
	parsing(&cub, av[1]);
	init_screen(&cub);
	if (set_wall_texture(&cub) == 1)
	{
		ft_free_tab(&cub.map.copy);
		// close_window(&cub);
		exit(1);
	}
	init_cub_values(&cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, key_press_hook, &cub);
	mlx_hook(cub.win, KeyRelease, KeyReleaseMask, key_release_hook, &cub);
	mlx_hook(cub.win, DestroyNotify, 0, close_window, &cub);
	init_game_loop(&cub);
	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:42:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/09 13:31:39 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_cub_values(t_data *cub)
{
	cub->keys.key_pressed_a = 0;
	cub->keys.key_pressed_d = 0;
	cub->keys.key_pressed_s = 0;
	cub->keys.key_pressed_w = 0;
	cub->keys.key_pressed_left = 0;
	cub->keys.key_pressed_right = 0;
	cub->wall[0].img = NULL;
	cub->wall[1].img = NULL;
	cub->wall[2].img = NULL;
	cub->wall[3].img = NULL;
	cub->my_image.img = NULL;
}
static void	check_file_name(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 5 || ft_strncmp(&file[len - 4], ".cub", 4))
	{
		(void)write(2, "Error:\nWrong file extension\n", 28);
		exit(1);
	}
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
	init_cub_values(&cub);
	check_file_name(av[1]);
	parsing(&cub, av[1]);
	init_mlx_win(&cub);
	init_image(&cub);
	set_wall_texture(&cub);
	init_player_position(&cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, key_press_hook, &cub);
	mlx_hook(cub.win, KeyRelease, KeyReleaseMask, key_release_hook, &cub);
	mlx_hook(cub.win, DestroyNotify, 0, close_window, &cub);
	mlx_loop_hook(cub.mlx, game_loop, &cub);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}

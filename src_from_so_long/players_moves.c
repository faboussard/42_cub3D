/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_moves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 15:01:07 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/03 15:01:59 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	increment_moves(t_data *img)
{
	img->map.player.moves++;
	ft_putstr_fd("Moves :", 1);
	ft_put_pos_nbr_fd(img->map.player.moves, 1);
	ft_putstr_fd("\n", 1);
}

void	move_player_img(t_data *img, size_t x, size_t y, int direction)
{
	size_t	p_x;
	size_t	p_y;

	p_x = img->map.player.x * 80;
	p_y = img->map.player.y * 80;
	if (img->map.grid[x][y] != 'E')
		mlx_put_image_to_window(img->mlx, img->win, img->empty, y * 80, x * 80);
	else if (img->map.grid[x][y] == 'E' && img->map.coins != 0)
		mlx_put_image_to_window(img->mlx, img->win, img->exit, y * 80, x * 80);
	if (direction == 1)
		mlx_put_image_to_window(img->mlx, img->win, img->up, p_y, p_x);
	else if (direction == 2)
		mlx_put_image_to_window(img->mlx, img->win, img->down, p_y, p_x);
	else if (direction == 3)
		mlx_put_image_to_window(img->mlx, img->win, img->left, p_y, p_x);
	else if (direction == 4)
		mlx_put_image_to_window(img->mlx, img->win, img->right, p_y, p_x);
}

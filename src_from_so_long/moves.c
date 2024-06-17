/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:44:09 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/03 15:08:35 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	collect_or_leave(t_data *img, size_t x, size_t y)
{
	if (img->map.grid[x][y] == 'C' && img->map.coins != 0)
	{
		img->map.coins--;
		img->map.grid[x][y] = '0';
	}
	else if (img->map.grid[x][y] == 'E' && img->map.coins == 0)
	{
		ft_putendl_fd("Congratulations !", 1);
		ft_putendl_fd("You have put every apple in the chest !", 1);
		ft_putendl_fd("Sprites credits to Cub Noodles ;", 1);
		ft_putendl_fd("https://cupnooble.itch.io/", 1);
		close_window(img);
	}
}

void	move_up(t_data *img)
{
	size_t	x;
	size_t	y;

	x = img->map.player.x;
	y = img->map.player.y;
	if (img->map.grid[x - 1][y] == '1')
		return ;
	increment_moves(img);
	img->map.player.x -= 1;
	move_player_img(img, x, y, 1);
	collect_or_leave(img, x - 1, y);
}

void	move_down(t_data *img)
{
	size_t	x;
	size_t	y;

	x = img->map.player.x;
	y = img->map.player.y;
	if (img->map.grid[x + 1][y] == '1')
		return ;
	increment_moves(img);
	img->map.player.x += 1;
	move_player_img(img, x, y, 2);
	collect_or_leave(img, x + 1, y);
}

void	move_left(t_data *img)
{
	size_t	x;
	size_t	y;

	x = img->map.player.x;
	y = img->map.player.y;
	if (img->map.grid[x][y - 1] == '1')
		return ;
	increment_moves(img);
	img->map.player.y -= 1;
	move_player_img(img, x, y, 3);
	collect_or_leave(img, x, y - 1);
}

void	move_right(t_data *img)
{
	size_t	x;
	size_t	y;

	x = img->map.player.x;
	y = img->map.player.y;
	if (img->map.grid[x][y + 1] == '1')
		return ;
	increment_moves(img);
	img->map.player.y += 1;
	move_player_img(img, x, y, 4);
	collect_or_leave(img, x, y + 1);
}

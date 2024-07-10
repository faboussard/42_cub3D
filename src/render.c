/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:44:11 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/21 15:44:21 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void define_draw_points(t_render *render, double wall_player_dist)
{
	render->line_height = (int) (HEIGHT_DISPLAY / wall_player_dist);
	render->draw_start = -render->line_height / 2 + HEIGHT_DISPLAY / 2;
	if (render->draw_start < 0)
		render->draw_start = 0;
	render->draw_end = render->line_height / 2 + HEIGHT_DISPLAY / 2;
	if (render->draw_end >= HEIGHT_DISPLAY)
		render->draw_end = HEIGHT_DISPLAY - 1;
}

void my_pixel_put(t_image *img, int x, int y, int color)
{
	char *dst;
	int offset_x;
	int offset_y;

	offset_x = x * (img->bits_per_pixel / 8);
	offset_y = y * img->line_length;
	if (x >= 0 && x < WIDTH_DISPLAY && y >= 0 && y < HEIGHT_DISPLAY)
	{
		dst = img->addr + offset_x + offset_y;
		*(unsigned int *) dst = color;
	}
}

unsigned int get_texel(t_image *texture, int x, int y)
{
	char *pxl;
	int offset_x;
	int offset_y;

	offset_x = x * (texture->bits_per_pixel / 8);
	offset_y = y * texture->line_length;
	pxl = texture->addr + offset_y + offset_x;
	return (*(unsigned int *) pxl);
}

void draw(t_render *render, int x)
{
	int y;
	int color;

	y = render->draw_start;
	render->text_step = 1.0 * ((double) TEX_H) / (double) render->line_height;
	render->texture_pos = ((double) render->draw_start - ((double) HEIGHT_DISPLAY / 2.0)
	                       + ((double) render->line_height / 2.0)) * render->text_step;
	while (y < render->draw_end)
	{
		render->text_y = (int) render->texture_pos & (TEX_H - 1);
		render->texture_pos += render->text_step;
		color = get_texel(&render->cub->wall[render->cub->wall_side], render->text_x, render->text_y);
		my_pixel_put(&render->cub->my_image, x, y, color);
		y++;
	}
}

// void draw(t_render *render, int x)
// {
// 	int y;
// 	int color;

// 	y = render->draw_start;
// 	render->text_step = 1.0 * ((double) render->cub->wall[render->cub->wall_side].height) / (double) render->line_height;
// 	render->texture_pos = ((double) render->draw_start - ((double) HEIGHT_DISPLAY / 2.0)
// 	                       + ((double) render->line_height / 2.0)) * render->text_step;
// 	while (y < render->draw_end)
// 	{
// 		render->text_y = (int) render->texture_pos & (render->cub->wall[render->cub->wall_side].height - 1);
// 		render->texture_pos += render->text_step;
// 		color = get_texel(&render->cub->wall[render->cub->wall_side], render->text_x, render->text_y);
// 		my_pixel_put(&render->cub->my_image, x, y, color);
// 		y++;
// 	}
// }

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
//	if (x >= 0 && x < 60 && y >= 0 && y < 60) // limiter la map au parsing sinon ca ne fonctionne pas ex / /home/juba/cub3d/TEST_CUB3D_ESLAMBER/textures/wall.xpm
	{
		pxl = texture->addr + offset_y + offset_x;
		return (*(unsigned int *) pxl);
	}
	return 0;
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
		render->text_y = (int) render->texture_pos & (TEX_H -
		                                              1); //sert à calculer l'index vertical (text_y) dans la texture en s'assurant qu'il reste dans les limites de la texture (de 0 à 63)
		render->texture_pos += render->text_step;
		// Obtenir la couleur du texel
		color = get_texel(&render->cub->wall[render->cub->wall_side], render->text_x, render->text_y);

		// Appliquer l'effet d'ombrage si nécessaire
//		if (render->cub->wall_side == NO)
//			color = (color >> 1) & 8355711;
		my_pixel_put(&render->cub->my_image, x, y, color);
		y++;
	}
	// if (render->cub->wall_side == WE)
	// {
	// 	printf(" --------------------- WE ---------------------\n");
	// 	printf("render->cub->wall_side = %d\n", render->cub->wall_side);
	// 	printf("text_x = %d, text_y = %d\n", render->text_x, render->text_y);
	// 	printf("color = %d\n", color);
	// }
	// if (render->cub->wall_side == NO)
	// {
	// 	printf(" --------------------- NO ---------------------\n");
	// 	printf("render->cub->wall_side = %d\n", render->cub->wall_side);
	// 	printf("text_x = %d, text_y = %d\n", render->text_x, render->text_y);
	// 	printf("color = %d\n", color);
	// }
	// if (render->cub->wall_side == SO)
	// {
	// 	printf(" --------------------- SO ---------------------\n");
	// 	printf("render->cub->wall_side = %d\n", render->cub->wall_side);
	// 	printf("text_x = %d, text_y = %d\n", render->text_x, render->text_y);
	// 	printf("color = %d\n", color);
	// }
	// if (render->cub->wall_side == EA)
	// {
	// 	printf(" --------------------- EA ---------------------\n");
	// 	printf("render->cub->wall_side = %d\n", render->cub->wall_side);
	// 	printf("text_x = %d, text_y = %d\n", render->text_x, render->text_y);
	// 	printf("color = %d\n", color);
	// }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:44:28 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/09 13:25:29 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void ray_tracer(t_data *cub, t_ray *ray)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = HORIZONTAL;
		} else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = VERTICAL;
		}
		if (cub->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void get_wall_player_dist(t_data *cub, t_ray *ray)
{
	if (ray->side == HORIZONTAL)
		cub->wall_player_dist = (ray->side_x - ray->delta_x);
	else
		cub->wall_player_dist = (ray->side_y - ray->delta_y);
}

void get_texture_x(t_render *render, t_ray *ray)
{
	render->text_x = (int) (ray->wall_x * (double) TEX_W);
	if (ray->side == HORIZONTAL && ray->dir_x > 0)
	{
		render->text_x = TEX_W - render->text_x - 1;
	}
	if (ray->side == VERTICAL && ray->dir_y < 0)
	{
		render->text_x = TEX_W - render->text_x - 1;
	}
}


void get_wall_x(t_data *cub, t_ray *ray)
{
	if (ray->side == HORIZONTAL)
		ray->wall_x = cub->player->pos_y + cub->wall_player_dist * ray->dir_y;
	else
		ray->wall_x = cub->player->pos_x + cub->wall_player_dist * ray->dir_x;
	if (ray->wall_x < 0.00001)
		ray->wall_x = 0.00001;
	ray->wall_x = 1 - ray->wall_x;
	ray->wall_x -= floor(ray->wall_x);
}

void get_wallside(t_data *cub, t_ray *ray)
{
	if (ray->side == VERTICAL)
	{
		if (ray->dir_y > 0)
			cub->wall_side = NO;
		else
			cub->wall_side = SO;
	}
	else
	{
		if (ray->dir_x > 0)
			cub->wall_side = WE;
		else
			cub->wall_side = EA;
	}
}

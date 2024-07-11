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

static double get_delta(double ray_dir);
static double get_side(double ray_dir, double map, double delta_dist, double pos);
static int get_step(double ray_dir);

void init_ray_info(t_data *cub, t_ray *ray, int x)
{
	double camera_x;

	camera_x = 2 * x / (double) WIDTH_DISPLAY - 1;
	ray->dir_x = cub->player->dir_x + cub->plane_x * camera_x;
	ray->dir_y = cub->player->dir_y + cub->plane_y * camera_x;
	ray->map_x = (int) cub->player->pos_x;
	ray->map_y = (int) cub->player->pos_y;
	ray->step_x = get_step(ray->dir_x);
	ray->step_y = get_step(ray->dir_y);
	ray->delta_x = get_delta(ray->dir_x);
	ray->delta_y = get_delta(ray->dir_y);
	ray->side_x = get_side(ray->dir_x, ray->map_x, ray->delta_x, cub->player->pos_x);
	ray->side_y = get_side(ray->dir_y, ray->map_y, ray->delta_y, cub->player->pos_y);
}

static double get_delta(double ray_dir)
{
	if (ray_dir == 0)
		return 1e30;
	return fabs(1 / ray_dir);
}

static double get_side(double ray_dir, double map, double delta_dist, double pos)
{
	if (ray_dir < 0)
		return (pos - map) * delta_dist;
	return (map + 1.0 - pos) * delta_dist;
}

static int get_step(double ray_dir)
{
	int step;

	if (ray_dir < 0)
		step = -1;
	else
		step = 1;
	return (step);
}

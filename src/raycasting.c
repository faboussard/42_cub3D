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


/*La fonction ray_tracer détermine
 * le chemin d'un rayon à travers une grille jusqu'à ce qu'il frappe un mur.
 * lalgo fait le plus petit pas possible suivant x ou y
 */
void ray_tracer(t_ray *ray)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (ray->side_x < ray->side_y) // la prochaine intersection de grille se produit sur un bord vertical.
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
		if (ray->cub->map.grid[ray->map_x][ray->map_y] == '1')
			hit = 1;
	}
}

//wall_player_dist ligne perpendiculaire a la place camera. same ratio for all walls
void get_wall_player_dist(t_data *cub, t_ray *ray)
{
//trouver le point dimpact

	if (ray->side == HORIZONTAL)
		cub->wall_player_dist = (ray->side_x - ray->delta_x);
	else
		cub->wall_player_dist = (ray->side_y - ray->delta_y);
}

// calcule la position en x sur la texture (text_x) où le rayon frappe.
//ray->wall_x est la position du point d'impact du rayon (entre 0 et 1).
//TEX_W est la largeur de la texture.
//En multipliant ray->wall_x par TEX_W, on obtient la position sur la texture.
//La conversion en entier (int) est effectuée pour obtenir une coordonnée entière.
// inversion si frappe eat ou sud

//N
//-------------
//W |     P     | E
//-------------
//S
void get_texture_x(t_render *render, t_ray *ray)
{
	//faire une fonctin qui definit tex_w en fonction de wall[SO ou EA]
	render->text_x = (int) (ray->wall_x * (double) TEX_W); // pour savoir combien  on a de pixels
//	printf("Initial text_x = %d\n", render->text_x);
	if (ray->side == HORIZONTAL && ray->dir_x > 0)
	{
		render->text_x = TEX_W - render->text_x - 1;
//		printf("Inverted text_x (HORIZONTAL) = %d\n", render->text_x);
	}
	if (ray->side == VERTICAL && ray->dir_y < 0)
	{
		render->text_x = TEX_W - render->text_x - 1;
//		printf("Inverted text_x (VERTICAL) = %d\n", render->text_x);
	}
//	printf("Final text_x = %d\n", render->text_x);
}


//en fonction de la direction du rayon
/*'floor(7.8)' is equal to 7. The ‘floor’ function rounds 7.8 down to the nearest integer, which is 7.

3. Now, we perform the subtraction and assignment operation:

wallX -= floor((wallX)) becomes wallX = 7.8 - 7.

4. We subtract 7 from 7.8:

'7.8 - 7' equals 0.8.*/
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
	// if (cub->wall_side == EA)
	// {
	// 	printf(" --------------------- EA ---------------------\n");
	// 	printf("render->cub->wall_side = %d\n", cub->wall_side);
	// 	printf("pos_y = %f\n", cub->player->pos_y);
	// 	printf("pos_x = %f\n", cub->player->pos_x);
	// 	printf("ray_dir_y = %f\n", ray->dir_y);
	// 	printf("ray_dir_x = %f\n", ray->dir_x);
	// 	printf("dir_y = %f\n", cub->player->dir_y);
	// 	printf("dir_x = %f\n", cub->player->dir_x);
	// 	printf("wall_player_dist = %f\n", cub->wall_player_dist);
	// 	printf("ray->wall_x = %f\n", ray->wall_x);
	// 	printf("ray->side = %d\n", ray->side);
	// }
	
	// if (cub->wall_side == WE)
	// {
	// 	printf(" --------------------- WE ---------------------\n");
	// 	printf("render->cub->wall_side = %d\n", cub->wall_side);
	// 	printf("pos_y = %f\n", cub->player->pos_y);
	// 	printf("pos_x = %f\n", cub->player->pos_x);
	// 	printf("ray_dir_y = %f\n", ray->dir_y);
	// 	printf("ray_dir_x = %f\n", ray->dir_x);
	// 	printf("ray_dir_x = %f\n", ray->dir_x);
	// 	printf("wall_player_dist = %f\n", cub->wall_player_dist);
	// 	printf("ray->wall_x = %f\n", ray->wall_x);
	// 	printf("ray->side = %d\n", ray->side);
	// }
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
		{
			//printf("cub->dir_x = %f\n", cub->dir_x);
			//printf("cub->dir_y = %f\n", cub->dir_y);
			cub->wall_side = WE;
		}
		else
		{
			//printf("cub->dir_x = %f\n",cub->dir_x);
			cub->wall_side = EA;
		}
	}
}

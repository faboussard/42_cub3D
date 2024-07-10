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


/*
 * The step variable determines how much you move in the texture space
 * for each pixel you move down the screen.
 * helps to map a vertical slice of the wall texture to the screen column being drawn.
 */

void init_ray_info(t_data *cub, t_ray *ray, int x)
{
	double camera_x;

	camera_x = 2 * x / (double) WIDTH_DISPLAY -
	           1; // x / width-1 => normalise la valeur de x pour qu elle soit comprise entre 0 et 1. 2 : etend la plage jusqua 2. -1 : recentre la plage pour aller de -1 a 1.
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

/* or slope or gradient.
 * pythagore norme sur 1 car dda fonctionne a partir de ratio.
 * Calcule la distance à parcourir pour traverser une unité de la grille dans la direction du rayon.
 * Si ray_dir est 0, cela signifie que le rayon est parallèle aux axes
 * et ne traverse jamais une unité de la grille dans cette direction,
 * donc la fonction retourne une très grande valeur (1e30) pour éviter une division par zéro.*/
static double get_delta(double ray_dir)
{
	if (ray_dir == 0)
		return 1e30;
	return fabs(1 / ray_dir);
}

/*
get_side are initially the distance the ray has to travel
from its start position to the first x-sideand the first y-side.
Later in the code they will be incremented while steps are taken.

Exemple 1 : Rayon se déplaçant vers la gauche (x négatif)
pos_x = 22.5 : Position x actuelle du joueur.
map_x = 22 : Coordonnée x sur la grille.
ray_dir_x = -1.0 : Direction du rayon vers la gauche.
delta_dist_x = fabs(1 / -1.0) = 1.0 : Distance pour traverser une unité de la grille dans la direction x.
Calcul :
get_side(-1.0, 22, 1.0, 22.5) => (22.5 - 22) * 1.0 => 0.5 * 1.0 => 0.5
 Donc, la distance initiale à la première intersection verticale est 0.5 unités.
 */
static double get_side(double ray_dir, double map, double delta_dist, double pos)
{
	if (ray_dir < 0)
		return (pos - map) * delta_dist;
	return (map + 1.0 - pos) * delta_dist;
}

/*Détermine l'étape (sens du mouvement) à suivre pour avancer le long du rayon dans la grille.*/
static int get_step(double ray_dir)
{
	int step;

	if (ray_dir < 0)
		step = -1;
	else
		step = 1;
	return (step);
}

/*La fonction ray_tracer détermine
 * le chemin d'un rayon à travers une grille jusqu'à ce qu'il frappe un mur.
 * lalgo fait le plus petit pas possible suivant x ou y
 */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:44:28 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/02 08:52:20 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void get_wall_impact_point(t_data *cub, t_ray *ray);

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


static double get_delta(double ray_dir);

static double get_side(double ray_dir, double map, double delta_dist, double pos);

static int get_step(double ray_dir);

static void my_pixel_put(t_image *img, int x, int y, int color)
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
		pxl = texture->addr + (offset_y + offset_x);
		return (*(unsigned int *) pxl);
	}
	return 0;
}


/*
 * If the direction vector and the camera plane vector have the same length, the FOV will be 90°
 * here FOV is  2 * atan(0.66/1.0)=66°
 * */
static void init_vectors(t_data *cub)
{
	cub->player->pos_x = 22;
	cub->player->pos_y = 12;
	cub->dir_x = -1;
	cub->dir_y = 0;
	cub->plane_x = 0;
	cub->plane_y = 0.66; //simplification et arrondi a partir du FOV du jeu de base qui est 2 * atan(0.66/1.0)=66°
}

static void		get_texture_x(t_render *render, t_ray *ray)
{
	render->text_x = (int)(ray->impact_point * (double)TEX_W);
	if (ray->side == HORIZONTAL && render->cub->ray_dir_x > 0)
		render->text_x = TEX_W - render->text_x - 1;
	if (ray->side == VERTICAL && render->cub->ray_dir_y < 0)
		render->text_x  = TEX_H - render->text_x  - 1;
}


static void projection_mapping(t_render *render, int x)
{
	int y;
	unsigned int color;

	y = render->draw_start;
	render->text_step = 1.0 * ((double)TEX_H) / (double) render->line_height;
	render->texture_pos = ((double) render->draw_start - ((double)HEIGHT_DISPLAY / 2.0)
						   + ((double)render->line_height / 2.0)) * render->text_step;
	while (y < render->draw_end)
	{
		render->text_y = (int)render->texture_pos & (TEX_H - 1);
		render->texture_pos += render->text_step;
		// Obtenir la couleur du texel
		color = get_texel(&render->cub->wall[render->cub->wall_side], render->text_x, render->text_y);

		// Appliquer l'effet d'ombrage si nécessaire
		if (render->cub->wall_side == NO || render->cub->wall_side == EA)
			color = (color >> 1) & 8355711;
		my_pixel_put(&render->cub->my_image, x, y, color);
		y++;
	}
}


/*
 * The step variable determines how much you move in the texture space
 * for each pixel you move down the screen.
 * helps to map a vertical slice of the wall texture to the screen column being drawn.
 */
static void draw_walls(t_ray *ray, t_render *render, int x)
{
	get_wall_impact_point(render->cub, ray);
	get_texture_x(render, ray);
	projection_mapping(render, x);
}

static void init_ray_info(t_data *cub, t_ray *ray, int x)
{
    double camera_x;

    camera_x = 2 * x / (double) WIDTH_DISPLAY - 1; // x / width-1 => normalise la valeur de x pour qu elle soit comprise entre 0 et 1. 2 : etend la plage jusqua 2. -1 : recentre la plage pour aller de -1 a 1.
    cub->ray_dir_x = cub->dir_x + cub->plane_x * camera_x;
    cub->ray_dir_y = cub->dir_y + cub->plane_y * camera_x;
    ray->map_x = (int) cub->player->pos_x;
    ray->map_y = (int) cub->player->pos_y;
    ray->step_x = get_step(cub->ray_dir_x);
	ray->step_y = get_step(cub->ray_dir_y);
	ray->delta_x = get_delta(cub->ray_dir_x);
	ray->delta_y = get_delta(cub->ray_dir_y);
	ray->side_x = get_side(cub->ray_dir_x, ray->map_x, ray->delta_x, cub->player->pos_x);
	ray->side_y = get_side(cub->ray_dir_y, ray->map_y, ray->delta_y, cub->player->pos_y);
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
static void ray_tracer(t_ray *ray)
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
        }
        else
        {
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = VERTICAL;
        }
        // Check if ray has hit a wall
        if (worldMap[ray->map_x][ray->map_y] > 0)
            hit = 1;
    }
}

//wall_player_dist ligne perpendiculaire a la place camera. same ratio for all walls
static void get_wall_player_dist(t_data *cub, t_ray *ray)
{
//trouver le point dimpact
	ray_tracer(ray);
	if (ray->side == HORIZONTAL)
//		cub->wall_player_dist = (ray->map_x - cub->player->pos_x
//							+ (1 - ray->step_x) / 2) /
//						   cub->ray_dir_x; //
	cub->wall_player_dist = (ray->side_x - ray->delta_x);
//perpWallDist = (sideDistX — deltaDistX);
	else
//		cub->wall_player_dist = (ray->map_y - cub->player->pos_y
//							+ (1 - ray->step_y) / 2) / cub->ray_dir_y;
		cub->wall_player_dist = (ray->side_y - ray->delta_y);
}

//en fonction de la direction du rayon
static void get_wall_impact_point(t_data *cub, t_ray *ray)
{
	if (ray->side == HORIZONTAL)
	{
		if (cub->dir_y > 0)
		{
			ray->impact_point = cub->player->pos_y + cub->wall_player_dist * cub->dir_y;
			cub->wall_side = SO; // Sud
		}
		else
		{
			ray->impact_point = cub->player->pos_y - cub->wall_player_dist * cub->dir_y;
			cub->wall_side = NO; // Nord
		}
	}
	else
	{
		if (cub->dir_x < 0)
		{
			ray->impact_point = cub->player->pos_x + cub->wall_player_dist * cub->dir_x;
			cub->wall_side = EA; // Est
		}
		else
		{
			ray->impact_point = cub->player->pos_x - cub->wall_player_dist * cub->dir_x;
			cub->wall_side = WE; // Ouest
		}
	}
	if (ray->impact_point  < 0.00001)
		ray->impact_point  = 0.00001;
	ray->impact_point -= floor(ray->impact_point);
}

static void define_draw_points(t_render *render, double wall_player_dist)
{
	render->line_height = (int) (HEIGHT_DISPLAY / wall_player_dist);
	render->draw_start = -render->line_height / 2 + HEIGHT_DISPLAY / 2;
	if (render->draw_start < 0)
		render->draw_start = 0;
	render->draw_end = render->line_height / 2 + HEIGHT_DISPLAY / 2;
	if (render->draw_end >= HEIGHT_DISPLAY)
		render->draw_end = HEIGHT_DISPLAY - 1;
}

/*
 *map : est le point darrivee du rayon quand il a touche le mur
 * pos : position initiale du joueur
 * 1 - setp / 2 : un recentrage
 * ray_di : converti la distance alculee sur la carte 2D en terme de position de grille
 * en une distance reelle dans lespace 3D de jeu
 * ex
 * wall_dist = (3 - 2.5 + (1 - 1) / 2) / (-0.7071);
 * wall_dist = (0.5 + 0.5 / 2) / (-0.7071);
 * wall_dist = (0.5 + 0.25) / (-0.7071);
 * wall_dist = 0.75 / (-0.7071);
 * wall_dist ≈ -1.0607;
 */
static void create_walls(t_data *cub, t_ray *ray, int x)
{
	t_render render;

	render = cub->render;
	render.cub = cub;
	get_wall_player_dist(cub, ray);
   	define_draw_points(&render, cub->wall_player_dist);
    draw_walls(ray, &render, x);
}
static int raycasting(t_data *cub)
{
	int x;
	t_ray	ray;
//	t_player player;

	cub->player = ft_calloc(sizeof (t_player), 1);
	if (cub->player == NULL)
		exit(EXIT_FAILURE);
	ray = cub->ray;
	init_vectors(cub);
	x = 0;
	while (x < WIDTH_DISPLAY)
	{
		init_ray_info(cub, &ray, x);
		create_walls(cub, &ray, x);
		x++;
	}
	return (0);
}


int game_loop(t_data *cub)
{
	raycasting(cub);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->my_image.img, 0, 0);
//	if (cub->keys.key_pressed_right)
//		rotate_clockwise(data);
//	if (cub->keys.key_pressed_left)
//		rotate_counterclockwise(data);
	if (cub->keys.key_pressed_w)
		move_forward(cub);
//	if (cub->keys.key_pressed_s)
//		move_backward(data, &data->player, &data->map);
//	if (cub->keys.key_pressed_a)
//		move_left(data, &data->player, &data->map);
//	if (cub->keys.key_pressed_d)
//		move_right(data, &data->player, &data->map);
	return (0);
}

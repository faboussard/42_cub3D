/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:44:28 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/21 15:44:31 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int worldMap[MAP_WIDTH][MAP_HEIGHT] = {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
									   {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
									   {4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
									   {4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
									   {4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
									   {4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
									   {4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
									   {4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
									   {4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
									   {4, 0, 8, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 8},
									   {4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
									   {4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
									   {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
									   {8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
									   {6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
									   {4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
									   {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
									   {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
									   {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
									   {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
									   {4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
									   {4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
									   {4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
									   {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}};

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
        dst = img->addr + ft_abs(offset_x + offset_y);
        *(unsigned int *) dst = color;
    }
}

unsigned int get_texel(t_image *texture, int x, int y) {
	char *pxl;
	int offset_x;
	int offset_y;

	// Calcul des offsets
	offset_x = x * (texture->bits_per_pixel / 8);
	offset_y = y * texture->line_length;

	// Ajout de messages de débogage pour vérifier les valeurs
	printf("DEBUG: x = %d, y = %d\n", x, y);
	printf("DEBUG: offset_x = %d, offset_y = %d\n", offset_x, offset_y);
	printf("DEBUG: texture width = %d, height = %d\n", TEX_W, TEX_H);

	// Vérification des limites de la texture
	if (x >= 0 && x < texture->width && y >= 0 && y < texture->height) {
		pxl = texture->addr + (offset_y + offset_x);
		printf("DEBUG: pxl = %p\n", pxl); // Affiche l'adresse mémoire du pixel
		return (*(unsigned int *) pxl);
	}

	printf("Erreur : coordonnées (x, y) hors limites (%d, %d)\n", x, y);
	return 0; // Retourne une valeur par défaut ou une couleur d'erreur
}


/*
 * If the direction vector and the camera plane vector have the same length, the FOV will be 90°
 * here FOV is  2 * atan(0.66/1.0)=66°
 * */


static void init_vectors(t_data *cub)
{
    cub->pos_x = 22;
    cub->pos_y = 12;
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
		render->text_y  = TEX_H - render->text_y  - 1;
}

static void create_wall_texture_img(t_data *cub, t_image *wall) {
	wall[0].img = mlx_xpm_file_to_image(cub->mlx, wall[0].path, &wall[0].width, &wall[0].height);
	if (wall[0].img == NULL) {
		printf("Erreur lors du chargement de l'image de la texture\n");
		exit(EXIT_FAILURE);
	}

	wall[0].addr = mlx_get_data_addr(wall[0].img, &wall[0].bits_per_pixel, &wall[0].line_length, &wall[0].endian);
	if (wall[0].addr == NULL) {
		printf("Erreur lors de l'obtention des données de la texture\n");
		exit(EXIT_FAILURE);
	}

	// Ajout de messages de débogage pour vérifier les valeurs
	printf("DEBUG: texture width = %d, height = %d, bits_per_pixel = %d, line_length = %d\n",
		   wall[0].width, wall[0].height, wall[0].bits_per_pixel, wall[0].line_length);
}


/*
 * The step variable determines how much you move in the texture space
 * for each pixel you move down the screen.
 * helps to map a vertical slice of the wall texture to the screen column being drawn.
 */
static void draw_walls(t_ray *ray, t_render *render, int x)
{
    int y;
  	unsigned int color;

	render->cub->wall[0].path = "/home/juba/cub3d/TEST_CUB3D_ESLAMBER/textures/wall.xpm";
	create_wall_texture_img(render->cub, &render->cub->wall[0]);
    get_texture_x(render, ray);
    y = render->draw_start;
	render->text_step = 1.0 * ((double)TEX_H) / (double) render->line_height; // calculates how much to move in the texture for each pixel on the screen.
    render->texture_pos = ((double) render->draw_start - ((double)HEIGHT_DISPLAY / 2.0)
                   + ((double)render->line_height / 2.0)) * render->text_step; // sets the initial position in the texture.
    while (y < render->draw_end)
    {
        render->text_y = (int)render->texture_pos & (TEX_H - 1);
        render->texture_pos += render->text_step;
        color = get_texel(&render->cub->wall[0], render->text_x, render->text_y);
//        my_pixel_put(&render->cub->my_image, x, y, 0x00FF0000);
		my_pixel_put(&render->cub->my_image, x, y, color);
        y++;
    }
}

static void init_ray_info(t_data *cub, t_ray *ray, int x)
{
    double camera_x;

//	ft_bzero(&ray, sizeof(t_ray));
    camera_x = 2 * x / (double) WIDTH_DISPLAY - 1; // x / width-1 => normalise la valeur de x pour qu elle soit comprise entre 0 et 1. 2 : etend la plage jusqua 2. -1 : recentre la plage pour aller de -1 a 1.
    cub->ray_dir_x = cub->dir_x + cub->plane_x * camera_x;
    cub->ray_dir_y = cub->dir_y + cub->plane_y * camera_x;
    ray->map_x = (int) cub->pos_x;
    ray->map_y = (int) cub->pos_y;
    ray->step_x = get_step(cub->ray_dir_x);
	ray->step_y = get_step(cub->ray_dir_y);
	ray->delta_x = get_delta(cub->ray_dir_x);
	ray->delta_y = get_delta(cub->ray_dir_y);
	ray->side_x = get_side(cub->ray_dir_x, ray->map_x, ray->delta_x, cub->pos_x);
	ray->side_y = get_side(cub->ray_dir_y, ray->map_y, ray->delta_y, cub->pos_y);
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

static double get_impact_point(t_data *cub, t_ray *ray)
{
	double wall_player_dist;

//trouver le point dimpact
	ray_tracer(ray);
	if (ray->side == HORIZONTAL)
	{
		wall_player_dist = (ray->map_x - cub->pos_x
							+ (1 - ray->step_x) / 2) /
						   cub->ray_dir_x; //  wall_player_dist ligne perpendiculaire a la place camera. same ratio for all walls
// forumule a revoir
//perpWallDist = (sideDistX — deltaDistX);
		ray->impact_point = cub->pos_y + wall_player_dist * cub->dir_y;
	} else
	{
		wall_player_dist = (ray->map_y - cub->pos_y
							+ (1 - ray->step_y) / 2) / cub->ray_dir_y;
		ray->impact_point = cub->pos_x + wall_player_dist * cub->dir_x;
	}
	ray->impact_point -= floor(ray->impact_point);
	return (wall_player_dist);
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
	double wall_player_dist;
	t_render render;

	render = cub->render;
	render.cub = cub;
	wall_player_dist = get_impact_point(cub, ray);
   	define_draw_points(&render, wall_player_dist);
    draw_walls(ray, &render, x);
}
static int raycasting(t_data *cub)
{
	int x;
	t_ray	ray;

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
	return (0);
}

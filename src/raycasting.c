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

static void get_wall_x(t_data *cub, t_ray *ray);

static double get_delta(double ray_dir);

static double get_side(double ray_dir, double map, double delta_dist, double pos);

static int get_step(double ray_dir);

static void get_texture_x(t_render *render, t_ray *ray);

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
		pxl = texture->addr + offset_y + offset_x;
		return (*(unsigned int *) pxl);
	}
	return 0;
}

static void draw(t_render *render, int x)
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
	if (render->cub->wall_side == WE)
	{
		printf(" --------------------- WE ---------------------\n");
		printf("render->cub->wall_side = %d\n", render->cub->wall_side);
		printf("text_x = %d, text_y = %d\n", render->text_x, render->text_y);
		printf("color = %d\n", color);
	}
	if (render->cub->wall_side == NO)
	{
		printf(" --------------------- NO ---------------------\n");
		printf("render->cub->wall_side = %d\n", render->cub->wall_side);
		printf("text_x = %d, text_y = %d\n", render->text_x, render->text_y);
		printf("color = %d\n", color);
	}
	if (render->cub->wall_side == SO)
	{
		printf(" --------------------- SO ---------------------\n");
		printf("render->cub->wall_side = %d\n", render->cub->wall_side);
		printf("text_x = %d, text_y = %d\n", render->text_x, render->text_y);
		printf("color = %d\n", color);
	}
	if (render->cub->wall_side == EA)
	{
		printf(" --------------------- EA ---------------------\n");
		printf("render->cub->wall_side = %d\n", render->cub->wall_side);
		printf("text_x = %d, text_y = %d\n", render->text_x, render->text_y);
		printf("color = %d\n", color);
	}


}


/*
 * The step variable determines how much you move in the texture space
 * for each pixel you move down the screen.
 * helps to map a vertical slice of the wall texture to the screen column being drawn.
 */

static void init_ray_info(t_data *cub, t_ray *ray, int x)
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
static void get_wall_player_dist(t_data *cub, t_ray *ray)
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
static void get_texture_x(t_render *render, t_ray *ray)
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
static void get_wall_x(t_data *cub, t_ray *ray)
{
	if (ray->side == HORIZONTAL)
		ray->wall_x = cub->player->pos_y + cub->wall_player_dist * ray->dir_y;
	else
		ray->wall_x = cub->player->pos_x + cub->wall_player_dist * ray->dir_x;
	if (ray->wall_x < 0.00001)
		ray->wall_x = 0.00001;
	ray->wall_x = 1 - ray->wall_x;
	ray->wall_x -= floor(ray->wall_x);

	if (cub->wall_side == EA)
	{
		printf(" --------------------- EA ---------------------\n");
		printf("render->cub->wall_side = %d\n", cub->wall_side);
		printf("pos_y = %f\n", cub->player->pos_y);
		printf("pos_x = %f\n", cub->player->pos_x);
		printf("ray_dir_y = %f\n", ray->dir_y);
		printf("ray_dir_x = %f\n", ray->dir_x);
		printf("dir_y = %f\n", cub->player->dir_y);
		printf("dir_x = %f\n", cub->player->dir_x);
		printf("wall_player_dist = %f\n", cub->wall_player_dist);
		printf("ray->wall_x = %f\n", ray->wall_x);
		printf("ray->side = %d\n", ray->side);
	}
	
	if (cub->wall_side == WE)
	{
		printf(" --------------------- WE ---------------------\n");
		printf("render->cub->wall_side = %d\n", cub->wall_side);
		printf("pos_y = %f\n", cub->player->pos_y);
		printf("pos_x = %f\n", cub->player->pos_x);
		printf("ray_dir_y = %f\n", ray->dir_y);
		printf("ray_dir_x = %f\n", ray->dir_x);
		printf("ray_dir_x = %f\n", ray->dir_x);
		printf("wall_player_dist = %f\n", cub->wall_player_dist);
		printf("ray->wall_x = %f\n", ray->wall_x);
		printf("ray->side = %d\n", ray->side);
	}
}

static void get_wallside(t_data *cub, t_ray *ray)
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
	ray_tracer(ray);
	get_wallside(cub, ray);
	get_wall_player_dist(cub, ray);
	get_wall_x(cub, ray);
	define_draw_points(&render, cub->wall_player_dist);
	get_texture_x(&render, ray);
	draw(&render, x);
}

static int draw_walls(t_data *cub)
{
	int x;
	t_ray ray;

	ray = cub->ray;
	ray.cub = cub;
	x = 0;
	while (x < WIDTH_DISPLAY)
	{
		init_ray_info(cub, &ray, x);
		create_walls(cub, &ray, x);
		x++;
	}
	return (0);
}

void draw_background(t_data *cub)
{
	int i;
	int j;
	int color;

	i = 0;
	color = cub->map.ceiling_color;
	while (i < (int) cub->my_image.height)
	{
		j = 0;
		while (j < (int) cub->my_image.width)
		{
			if (i > (int) cub->my_image.height / 2)
				color = cub->map.floor_color;
			my_pixel_put(&cub->my_image, j, i, color);
			j++;
		}
		i++;
	}
}


int game_loop(t_data *cub)
{
	draw_background(cub);
	draw_walls(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->my_image.img, 0, 0);
	if (cub->keys.key_pressed_right == 1)
		rotate_right(cub);
	if (cub->keys.key_pressed_left == 1)
		rotate_left(cub);
	if (cub->keys.key_pressed_w == 1)
		move_forward(cub);
	if (cub->keys.key_pressed_s == 1)
		move_backward(cub);
	if (cub->keys.key_pressed_a == 1)
		move_left(cub);
	if (cub->keys.key_pressed_d == 1)
		move_right(cub);
	return (0);
}

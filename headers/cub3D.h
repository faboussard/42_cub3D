/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.height                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:46:46 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/04 10:47:02 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <bits/stdint-uintn.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

# define TEX_W 64
# define TEX_H 64
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define WIDTH_DISPLAY 960
# define HEIGHT_DISPLAY 720
# define HORIZONTAL 0
# define VERTICAL 1
#  define FOV 90
#define M_PI 3.14159265358979323846


#define NO 0
#define SO 1
#define EA 2
#define WE 3

#define TEXT_NORTH_W render->cub->wall[NO].width
#define TEXT_SOUTH_W render->cub->wall[SO].width
#define TEXT_EAST_W render->cub->wall[EA].width
#define TEXT_WEST_W render->cub->wall[WE].width


#define TEXT_NORTH_H render->cub->wall[NO].height
#define TEXT_SOUTH_H render->cub->wall[SO].height
#define TEXT_EAST_H render->cub->wall[EA].height
#define TEXT_WEST_H render->cub->wall[WE].height



#define TEXTURE_NUM 4

# define MOVE 0.05
# define ROTATE 0.05

typedef struct s_keys
{
	bool			key_pressed_left;
	bool			key_pressed_right;
	bool			key_pressed_w;
	bool			key_pressed_s;
	bool			key_pressed_a;
	bool			key_pressed_d;
}	t_keys;

typedef struct s_image   t_image;
typedef struct s_data   t_data;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	char		*path;
}					t_image;

typedef struct s_player
{
	double      pos_x;
	double      pos_y;
	t_data		*cub;
	int			fov;
	int			plane_length;
}				t_player;


typedef struct s_map
{
	size_t					rows;
	size_t					cols;
	char					**grid;
	char					**copy;
	// bool					status;
	t_player				player;
	int						floor_color;
	int						ceiling_color;
}							t_map;

typedef struct s_ray
{
	int      map_x;
	int      map_y;
	double      delta_x;
	double      delta_y;
	double      side_x;
	double      side_y;
	int      step_x;
	int      step_y;
	double	wall_x;
	int		side;
	t_data 	*cub;
}				t_ray;

typedef struct s_render
{
	int      line_height;
	int      draw_start;
	int      draw_end;
	int 	text_x;
    int 	text_y;
    double	texture_pos;
    double	text_step;
	t_data	*cub;
}				t_render;


typedef struct s_data
{
	int			win_height;
	int			win_width;
	void		*mlx;
	void		*win;
	// void		*empty;
	void		*up;
	void		*down;
	void		*left;
	void		*right;
	// char		emp_img[26];
	char		*north_img;
	char		*south_img;
	char		*east_img;
	char		*west_img;
//	char		exit_img[26];
	t_map		map;
	t_image		my_image;
	double      dir_x;
	double      dir_y;
	double      plane_x;
	double      plane_y;
	double      ray_dir_x;
	double      ray_dir_y;
	double		wall_player_dist;
	t_player    *player;
	t_ray		ray;
	t_render	render;
	t_image		wall[TEXTURE_NUM];
	int			wall_side;
	t_keys		keys;
}				t_data;


////////////////////////////////////////////////////////////////////////
////////     				ERRORS                  			////////
////////////////////////////////////////////////////////////////////////
void						no_such_file_error(void);
void						malloc_error(void);
void						input_error(void);
void						map_error(char *tmp_map, char **map);
void						empty_file_error(void);
////////////////////////////////////////////////////////////////////////
////////     				PARSING								////////
////////////////////////////////////////////////////////////////////////
void						parsing(t_data *cub, char *file);
//////////////////////////////////////////////////////////////////////
/////     				UTILS								////////
/////////////////////////////////////////////////////////////////////
void	ft_free_tab(char ***tab);
bool						ft_search_char(char letter, char *charset);
bool						ft_is_space(const int c);
int							ft_strcmp_skip_spaces(char *s1, char *s2);
int	ft_strncmp_skip_spaces(char *s1, char *s2, size_t n);
// void			ft_put_pos_nbr_fd(size_t n, int fd);
////////////////////////////////////////////////////////////////////////
////////     				INIT								////////
////////////////////////////////////////////////////////////////////////
void						init_mlx_win(t_data *cub);
void						init_screen(t_data *cub);
////////////////////////////////////////////////////////////////////////
////////     				MAP									////////
////////////////////////////////////////////////////////////////////////
void						define_map(t_map *map, char *file_name);
void						launch_checks(t_map *map, char *tmp_map);
void						fill_paths(t_map map, size_t x, size_t y);
bool						check_path(t_map *map);
void						init_player_position(t_data *cub);
////////////////////////////////////////////////////////////////////////
////////     				RAYCASTING							////////
////////////////////////////////////////////////////////////////////////
int				game_loop(t_data *cub);
void			render(t_data *cub);
bool			set_wall_texture(t_data *cub);
void			init_vectors(t_data *cub);
////////////////////////////////////////////////////////////////////////
////////     				MOVE								////////
////////////////////////////////////////////////////////////////////////
void	move_forward(t_data *cub);
void	move_backward(t_data *cub);
void	move_left(t_data *cub);
void	move_right(t_data *cub);
void	update_player_position(t_player *player, \
double dest_x, double dest_y);
void	rotate_right(t_data *cub);
void	rotate_left(t_data *cub);
////////////////////////////////////////////////////////////////////////
////////     				HOOK								////////
////////////////////////////////////////////////////////////////////////
int	key_press_hook(int keysym, t_data *cub);
int	key_release_hook(int keysym, t_data *cub);
////////////////////////////////////////////////////////////////////////
////////     				COLORS								////////
////////////////////////////////////////////////////////////////////////
bool						define_colors(t_data *cub);
////////////////////////////////////////////////////////////////////////
////////     				EXIT								////////
////////////////////////////////////////////////////////////////////////
void						destroy_images(t_data *cub);
int							close_window(t_data *cub);

#endif

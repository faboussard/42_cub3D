/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.height                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 15:46:46 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/21 15:46:50 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/inc/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <bits/stdint-uintn.h>

# define TEX_W 64
# define TEX_H 64
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define WIDTH_DISPLAY 960
# define HEIGHT_DISPLAY 720
# define HORIZONTAL 0
# define VERTICAL 1

enum	e_wallside
{
	NO,
	SO,
	WE,
	EA,
};

typedef struct s_image   t_image;
typedef struct s_data   t_data;


typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int		width;
	int		height;
	char		*path;
}					t_image;

typedef struct s_player
{
	size_t		x;
	size_t		y;
	size_t		moves;
}				t_player;

typedef struct s_map
{
	size_t		rows;
	size_t		cols;
	char		**grid;
	char		**copy;
	bool		status;
	t_player	player;
    int				floor_color;
    int				cealing_color;
}				t_map;

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
	double	impact_point;
	int	side;
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
	void		*empty;
	void		*north_wall;
	void		*south_wall;
	void		*east_wall;
	void		*west_wall;
	void		*up;
	void		*down;
	void		*left;
	void		*right;
	char		emp_img[26];
	char		*north_img;
	char		*south_img;
	char		*east_img;
	char		*west_img;
//	char		exit_img[26];
	t_map		map;
	t_image		my_image;
	double      pos_x;
	double      pos_y;
	double      dir_x;
	double      dir_y;
	double      plane_x;
	double      plane_y;
	double      ray_dir_x;
	double      ray_dir_y;
	double		wall_player_dist;
	int         **worldMap;
	t_ray		ray;
	t_render	render;
	t_image		wall[4];
	enum	e_wallside	wall_side;
}				t_data;


////////////////////////////////////////////////////////////////////////
////////     				ERRORS                  			////////
////////////////////////////////////////////////////////////////////////
void			no_such_file_error(void);
void			malloc_error(void);
void			input_error(void);
void			map_error(char **map, char **copy);
void			empty_file_error(void);
////////////////////////////////////////////////////////////////////////
////////     				PARSING								////////
////////////////////////////////////////////////////////////////////////
void			parsing(t_data *cub, char *file);
void			check_file_name(char *file);
////////////////////////////////////////////////////////////////////////
////////     				UTILS								////////
////////////////////////////////////////////////////////////////////////
void			free_tabs(char **map, char **copy);
bool			ft_search_char(char letter, char *charset);
//void			ft_put_pos_nbr_fd(size_t n, int fd);
////////////////////////////////////////////////////////////////////////
////////     				INIT								////////
////////////////////////////////////////////////////////////////////////
void			init_mlx_win(t_data *img);
void			init_screen(t_data *img);
////////////////////////////////////////////////////////////////////////
////////     				MAP									////////
////////////////////////////////////////////////////////////////////////
void			define_map(t_map *map, char *file_name);
void			launch_checks(t_map *map, char *tmp_map);
void			fill_paths(t_map map, size_t x, size_t y);
bool			check_path(t_map *map);
////////////////////////////////////////////////////////////////////////
////////     				MOVES								////////
////////////////////////////////////////////////////////////////////////
void			move_player_img(t_data *img, size_t x, size_t y, int direction);
void			increment_moves(t_data *img);
void			move_up(t_data *img);
void			move_down(t_data *img);
void			move_left(t_data *img);
void			move_right(t_data *img);
////////////////////////////////////////////////////////////////////////
////////     				RAYCASTING							////////
////////////////////////////////////////////////////////////////////////
int				game_loop(t_data *cub);
void			render(t_data *cub);
////////////////////////////////////////////////////////////////////////
////////     				HOOK								////////
////////////////////////////////////////////////////////////////////////
int				key_hook(int keysym, t_data *cub);
////////////////////////////////////////////////////////////////////////
////////     				EXIT								////////
////////////////////////////////////////////////////////////////////////
void			destroy_images(t_data *cub);
int				close_window(t_data *img);

#endif

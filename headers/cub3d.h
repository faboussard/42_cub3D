/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:44:11 by mbernard          #+#    #+#             */
/*   Updated: 2024/03/04 11:27:30 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/inc/libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdbool.h>

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
	size_t		coins;
	char		**grid;
	char		**copy;
	bool		status;
	t_player	player;
}				t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*empty;
	void		*wall;
	void		*coll;
	void		*exit;
	void		*up;
	void		*down;
	void		*left;
	void		*right;
	char		emp_img[26];
	char		wall_img[25];
	char		coll_img[26];
	char		exit_img[26];
	char		up_img[23];
	char		down_img[25];
	char		left_img[25];
	char		right_img[26];
	t_map		map;
}				t_data;

////////////////////////////////////////////////////////////////////////
////////     				ERRORS                  ////////
////////////////////////////////////////////////////////////////////////
void			no_such_file_error(void);
void			malloc_error(void);
void			input_error(void);
void			map_error(char **map, char **copy);
void			empty_file_error(void);
////////////////////////////////////////////////////////////////////////
////////     				UTILS			////////
////////////////////////////////////////////////////////////////////////
int				close_window(t_data *img);
void			free_tabs(char **map, char **copy);
bool			ends_by_ber(char *file);
bool			ft_search_char(char letter, char *charset);
void			ft_put_pos_nbr_fd(size_t n, int fd);
////////////////////////////////////////////////////////////////////////
////////     				INIT			////////
////////////////////////////////////////////////////////////////////////
void			init_mlx_win(t_data *img);
void			init_screen(t_data *img);
////////////////////////////////////////////////////////////////////////
////////     				MAP			////////
////////////////////////////////////////////////////////////////////////
void			define_map(t_map *map, char *ber);
void			launch_checks(t_map *map, char *tmp_map);
void			fill_paths(t_map map, size_t x, size_t y);
bool			check_path(t_map *map);
////////////////////////////////////////////////////////////////////////
////////     				MOVES			////////
////////////////////////////////////////////////////////////////////////
void			move_player_img(t_data *img, size_t x, size_t y, int direction);
void			increment_moves(t_data *img);
void			move_up(t_data *img);
void			move_down(t_data *img);
void			move_left(t_data *img);
void			move_right(t_data *img);
#endif

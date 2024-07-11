/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:45:56 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/11 15:02:56 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3D.h"

static void	check_if_no_double_textures(t_data *cub)
{
	if (ft_strcmp_skip_spaces(cub->north_img, cub->south_img) == 0
		|| ft_strcmp_skip_spaces(cub->north_img, cub->west_img) == 0
		|| ft_strcmp_skip_spaces(cub->north_img, cub->east_img) == 0
		|| ft_strcmp_skip_spaces(cub->south_img, cub->west_img) == 0
		|| ft_strcmp_skip_spaces(cub->south_img, cub->east_img) == 0
		|| ft_strcmp_skip_spaces(cub->east_img, cub->west_img) == 0)
	{
		(void)write(2, "Error\nSame textures detected\n", 29);
		ft_free_tab(&cub->map.copy);
		exit(EXIT_FAILURE);
	}
}

static void	define_textures_path(t_data *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < 7)
	{
		j = 0;
		while (cub->map.copy[i][j] && ft_is_space(cub->map.copy[i][j]))
			j++;
		j += 3;
		while (cub->map.copy[i][j] && ft_is_space(cub->map.copy[i][j]))
			j++;
		if (ft_strncmp_skip_spaces(cub->map.copy[i], "NO ", 3) == 0)
			cub->north_img = cub->map.copy[i] + j;
		else if (ft_strncmp_skip_spaces(cub->map.copy[i], "SO ", 3) == 0)
			cub->south_img = cub->map.copy[i] + j;
		else if (ft_strncmp_skip_spaces(cub->map.copy[i], "WE ", 3) == 0)
			cub->west_img = cub->map.copy[i] + j;
		else if (ft_strncmp_skip_spaces(cub->map.copy[i], "EA ", 3) == 0)
			cub->east_img = cub->map.copy[i] + j;
		i++;
	}
	check_if_no_double_textures(cub);
}

static void	check_if_textures_exist(t_data *cub, char *path_to_texture)
{
	int	fd;

	fd = open(path_to_texture, O_RDONLY);
	if (fd == -1)
	{
		(void)write(2, "Error:\nTexture path error\n", 26);
		perror(path_to_texture);
		ft_free_tab(&cub->map.copy);
		exit(1);
	}
	close(fd);
}

static void	check_if_texture_is_xpm(t_data *cub, char *path_to_texture)
{
	size_t	len;

	len = ft_strlen(path_to_texture);
	if (len < 5 || ft_strncmp(&path_to_texture[len - 4], ".xpm", 4))
	{
		(void)write(2, "Error:\nNot a xpm texture\n", 25);
		ft_free_tab(&cub->map.copy);
		exit(1);
	}
}

void	parsing(t_data *cub, char *file)
{
	define_map(&cub->map, file);
	define_textures_path(cub);
	if (define_colors(cub) == false || cub->map.ceiling_color == -1
		|| cub->map.floor_color == -1)
	{
		ft_free_tab(&cub->map.copy);
		(void)write(2, "Error\n: Wrong colors\n", 21);
		exit(1);
	}
	check_if_texture_is_xpm(cub, cub->north_img);
	check_if_texture_is_xpm(cub, cub->south_img);
	check_if_texture_is_xpm(cub, cub->west_img);
	check_if_texture_is_xpm(cub, cub->east_img);
	check_if_textures_exist(cub, cub->north_img);
	check_if_textures_exist(cub, cub->south_img);
	check_if_textures_exist(cub, cub->west_img);
	check_if_textures_exist(cub, cub->east_img);
	if (check_map_is_closed(cub->map.grid))
	{
		ft_free_tab(&cub->map.copy);
		(void)write(2, "Error\n: Map isn't closed\n", 25);
		exit(1);
	}
}

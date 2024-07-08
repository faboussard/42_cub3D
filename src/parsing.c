/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:45:56 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/08 14:41:17 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3D.h"

void	check_file_name(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 5 || ft_strncmp(&file[len - 4], ".cub", 4))
	{
		(void)write(2, "Error:\nWrong file extension\n", 28);
		exit(1);
	}
}

static void	define_textures_path(t_data *cub)
{
	int	i;
	int	j;

	i = 0;
	while (i < 6)
	{
		j = 3;
		while (cub->map.copy[i][j] && ft_is_space(cub->map.copy[i][j]))
			j++;
		if (ft_strncmp(cub->map.copy[i], "NO ", 3) == 0)
			cub->north_img = cub->map.copy[i] + j;
		else if (ft_strncmp(cub->map.copy[i], "SO ", 3) == 0)
			cub->south_img = cub->map.copy[i] + j;
		else if (ft_strncmp(cub->map.copy[i], "WE ", 3) == 0)
			cub->west_img = cub->map.copy[i] + j;
		else if (ft_strncmp(cub->map.copy[i], "EA ", 3) == 0)
			cub->east_img = cub->map.copy[i] + j;
		i++;
	}
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

void	parsing(t_data *cub, char *file)
{
	define_map(&cub->map, file);
	define_textures_path(cub);
	if (define_colors(cub) == false || cub->map.ceiling_color == -1
		|| cub->map.floor_color == -1)
	{
		(void)write(2, "Error: Wrong colors\n", 20);
		ft_free_tab(&cub->map.copy);
		exit(1);
	}
	check_if_textures_exist(cub, cub->north_img);
	check_if_textures_exist(cub, cub->south_img);
	check_if_textures_exist(cub, cub->west_img);
	check_if_textures_exist(cub, cub->east_img);
	// ft_free_tab(&cub->map.copy);
	// exit(1);
}

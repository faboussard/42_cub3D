/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:45:56 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/23 15:46:10 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3D.h"

void	check_file_name(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 5 || ft_strncmp(&file[len - 4], ".cub", 4))
	{
		(void)write(2, "Error: Wrong file extension\n", 28);
		exit(1);
	}
}

static void	define_textures_path(t_data *cub)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(cub->map.copy[i], "NO ", 3) == 0)
			cub->north_img = cub->map.copy[i] + 3;
		else if (ft_strncmp(cub->map.copy[i], "SO ", 3) == 0)
			cub->south_img = cub->map.copy[i] + 3;
		else if (ft_strncmp(cub->map.copy[i], "WE ", 3) == 0)
			cub->west_img = cub->map.copy[i] + 3;
		else if (ft_strncmp(cub->map.copy[i], "EA ", 3) == 0)
			cub->east_img = cub->map.copy[i] + 3;
		i++;
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
		(void)write(2, "Error: Wrong colors\n", 20);
		exit(1);
	}
	dprintf(2, "MAPPPPPPPPPPPPPPPPPPPPP \n%s\n", cub->map.grid[0]);
	if (set_wall_texture(cub) == 1)
	{
		ft_free_tab(&cub->map.copy);
		exit(1);
	}
	dprintf(2, "north: %s\n", cub->north_img);
	dprintf(2, "south: %s\n", cub->south_img);
	dprintf(2, "west: %s\n", cub->west_img);
	dprintf(2, "east: %s\n", cub->east_img);
	ft_free_tab(&cub->map.copy);
	// exit(1);
}

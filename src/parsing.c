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

#include "cub3D.h"

void   check_file_name(char *file)
{
	size_t  len;

	len = ft_strlen(file);
	if (len < 5 || ft_strncmp(&file[len - 4], ".cub", 4))
	{
		(void)write(2, "Error: Wrong file extension\n", 28);
		exit(1);
	}
}

static void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

static void	define_colors(t_data *cub)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(cub->map.copy[i], "F ", 2) == 0)
			cub->floor_color = cub->map.copy[i];
		else if (ft_strncmp(cub->map.copy[i], "C ", 2) == 0)
			cub->ceiling_color = cub->map.copy[i];
		i++;
	}
}

static void	define_textures_path(t_data *cub)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(cub->map.copy[i], "NO ", 3) == 0)
			cub->north_img = cub->map.copy[i];
		else if (ft_strncmp(cub->map.copy[i], "SO ", 3) == 0)
			cub->south_img = cub->map.copy[i];
		else if (ft_strncmp(cub->map.copy[i], "WE ", 3) == 0)
			cub->west_img = cub->map.copy[i];
		else if (ft_strncmp(cub->map.copy[i], "EA ", 3) == 0)
			cub->east_img = cub->map.copy[i];
		i++;
	}
}

void	parsing(t_data *cub, char *file)
{
//	int		fd;
//	char	*line;
//	int		ret;

//	ret = 0;
	define_map(&cub->map, file);
	define_textures_path(cub);
	define_colors(cub);
	dprintf(2, "NORTH: %s\n", cub->map.copy[0]);
	dprintf(2, "SOUTH: %s\n", cub->map.copy[1]);
	dprintf(2, "WEST: %s\n", cub->map.copy[2]);
	dprintf(2, "EAST: %s\n", cub->map.copy[3]);
	cub->north_img = cub->map.copy[0];
	cub->south_img = cub->map.copy[1];
	cub->west_img = cub->map.copy[2];
	cub->east_img = cub->map.copy[3];
	dprintf(2, "north: %s\n", cub->north_img);
	dprintf(2, "south: %s\n", cub->south_img);
	dprintf(2, "west: %s\n", cub->west_img);
	dprintf(2, "east: %s\n", cub->east_img);
	ft_free_tab(cub->map.copy);
	exit(1);

	//check_map;

//	fd = open(file, O_RDONLY);
//	if (fd == -1)
//	{
//		(void)write(2, "Error:\n", 7);
//		perror(file);
//		exit(1);
//	}
//	while (1)
//	{
//		ret++;
//		line = get_next_line(fd);
//		if (line == NULL)
//		{
//			if (ret == 1)
//			{
//				(void)write(2, "Error: Empty file\n", 18);
//				exit(1);
//			}
//			else
//				break ;
//		}
//		free(line);
//	}
//	close(fd);
}
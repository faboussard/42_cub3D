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

static bool	check_char_color(char c, int *commas, int *num_nums, bool *num_place)
{
	if (c == ',' && *num_place == false)
	{
		++(*commas);
		*num_place = true;
	}
	else if (ft_isdigit(c) && *num_place == true)
	{
		*num_place = false;
		++(*num_nums);
	}
	else if ((c == ',' && *num_place == true)
		|| (!ft_isdigit(c) && !ft_is_space(c) && c != ','))
		return (0);
	return (1);
}

bool	check_color(char *color)
{
	int		i;
	int		commas;
	bool	num_place;
	int		num_nums;

	i = 0;
	commas = 0;
	num_place = true;
	num_nums = 0;
	color += 1;
	while (color[i])
	{
		if (check_char_color(color[i], &commas, &num_nums, &num_place) == false)
			return (0);
		if (commas > 2 || num_nums > 3)
			return (0);
		i++;
	}
	if (commas != 2 || num_nums != 3 || num_place == true)
		return (0);
	return (1);
}

int	create_trgb(char *color)
{
	int		r;
	int		g;
	int		b;

	color += 2;
	r = ft_atoi(color);
	if (r < 0 || r > 255)
		return (-1);
	while (*color && ft_isdigit(*color))
		color++;
	while (*color && (*color == ',' || ft_is_space(*color)))
		color++;
	g = ft_atoi(color);
	if (g < 0 || g > 255)
		return (-1);
	while (*color && ft_isdigit(*color))
		color++;
	while (*color && (*color == ',' || ft_is_space(*color)))
		color++;
	b = ft_atoi(color);
	if (b < 0 || b > 255)
		return (-1);
	return (0 << 24 | r << 16 | g << 8 | b);
}

static bool	define_colors(t_data *cub)
{
	int		i;
	bool	floor_defined;
	bool	ceiling_defined;

	i = 0;
	floor_defined = false;
	ceiling_defined = false;
	while (i < 6)
	{
		if (floor_defined == false && ft_strncmp(cub->map.copy[i], "F ", 2) == 0)
		{
			cub->map.floor_color = create_trgb(cub->map.copy[i]);
			floor_defined = true;
		}
		else if (floor_defined == true && ft_strncmp(cub->map.copy[i], "F ", 2) == 0)
			return (false);
		else if (ft_strncmp(cub->map.copy[i], "C ", 2) == 0)
		{
			cub->map.ceiling_color = create_trgb(cub->map.copy[i]);
			ceiling_defined = true;
		}
		else if (ceiling_defined == true && ft_strncmp(cub->map.copy[i], "C ", 2) == 0)
			return (false);
		i++;
	}
	return (floor_defined && ceiling_defined);
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
	if(define_colors(cub) == false)
	{
		(void)write(2, "Error: Wrong colors\n", 21);
		ft_free_tab(cub->map.copy);
		exit(1);
	}
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
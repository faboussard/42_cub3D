/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:44:25 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/04 11:03:27 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	check_char_color(char c, int *commas, int *nb_nums, bool *num_place)
{
	if (c == ',' && *num_place == false)
	{
		++(*commas);
		*num_place = true;
	}
	else if (ft_isdigit(c) && *num_place == true)
	{
		*num_place = false;
		++(*nb_nums);
	}
	else if ((c == ',' && *num_place == true) || (!ft_isdigit(c)
			&& !ft_is_space(c) && c != ','))
		return (0);
	return (1);
}

static bool	check_color(char *color)
{
	int		i;
	int		commas;
	bool	num_place;
	int		nb_nums;

	i = 0;
	commas = 0;
	num_place = true;
	nb_nums = 0;
	color += 1;
	while (color[i])
	{
		if (check_char_color(color[i], &commas, &nb_nums, &num_place) == false)
			return (0);
		if (commas > 2 || nb_nums > 3)
			return (0);
		i++;
	}
	if (commas != 2 || nb_nums != 3 || num_place == true)
		return (0);
	return (1);
}

static int	create_trgb(char *color)
{
	int	r;
	int	g;
	int	b;

	color += 2;
	if (check_color(color) == false)
		return (-1);
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

bool	define_colors(t_data *cub)
{
	int		i;
	bool	floor;
	bool	ceiling;

	i = 0;
	floor = false;
	ceiling = false;
	while (i < 6)
	{
		if (floor == false && ft_strncmp(cub->map.copy[i], "F ", 2) == 0)
		{
			cub->map.floor_color = create_trgb(cub->map.copy[i]);
			floor = true;
		}
		else if (ft_strncmp(cub->map.copy[i], "C ", 2) == 0)
		{
			cub->map.ceiling_color = create_trgb(cub->map.copy[i]);
			ceiling = true;
		}
		else if ((ceiling == true && ft_strncmp(cub->map.copy[i], "C ", 2) == 0)
			|| (floor == true && ft_strncmp(cub->map.copy[i], "F ", 2) == 0))
			return (false);
		i++;
	}
	return (floor && ceiling);
}

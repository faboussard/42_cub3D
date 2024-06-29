/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:00:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/06/28 11:00:42 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	ft_search_char(char letter, char *charset)
{
	size_t	c;

	c = 0;
	if (charset)
	{
		while (charset[c])
		{
			if (letter == charset[c])
				return (1);
			c++;
		}
	}
	return (0);
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

void	free_tabs(char **map, char **copy)
{
	ft_free_tab(map);
	ft_free_tab(copy);
}

/*
void	ft_put_pos_nbr_fd(size_t n, int fd)
{
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}
*/

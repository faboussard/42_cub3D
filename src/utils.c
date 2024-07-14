/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:00:35 by mbernard          #+#    #+#             */
/*   Updated: 2024/07/11 12:53:10 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	ft_is_space(const int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

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

void	ft_free_tab(char ***tab)
{
	size_t	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	free(*tab);
	*tab = NULL;
}

int	ft_strncmp_skip_spaces(char *s1, char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (ft_is_space(s1[i]))
		i++;
	while (ft_is_space(s2[j]))
		j++;
	return (ft_strncmp(s1 + i, s2 + j, n));
}

int	ft_strcmp_skip_spaces(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (ft_is_space(s1[i]))
		i++;
	while (ft_is_space(s2[i]))
		j++;
	return (ft_strcmp(s1 + i, s2 + j));
}

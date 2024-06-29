/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 08:46:22 by faboussa          #+#    #+#             */
/*   Updated: 2023/12/12 13:32:24 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	i;
	size_t	j;
	size_t	total_length;

	total_length = ft_strlen(s1) + ft_strlen(s2);
	new_string = malloc(sizeof(char) * total_length + 1);
	if (new_string == NULL)
		return (0);
	i = 0;
	while (i < ft_strlen(s1))
	{
		new_string[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		new_string[i] = s2[j];
		j++;
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

static void	free_both_strjoin_str(char *s1, char *s2)
{
	if (*s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (*s2)
	{
		free(s2);
		s2 = NULL;
	}
}

char	*ft_strjoin_free_both(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*dest;
	int		x;
	int		y;

	if (!s2)
	{
		free_both_strjoin_str((char *)s1, (char *)s2);
		return (NULL);
	}
	if (!s1)
		return (ft_strdup(s2));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!dest)
	{
		free_both_strjoin_str((char *)s1, (char *)s2);
		return (NULL);
	}
	x = -1;
	y = 0;
	while (s1[++x])
		dest[x] = (char)s1[x];
	while (s2[y])
		dest[x++] = (char)s2[y++];
	dest[x] = '\0';
	free_both_strjoin_str((char *)s1, (char *)s2);
	return (dest);
}

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

#include "cub3d.h"

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

void	parsing(t_data *cub, char *file)
{
	int		fd;
	char	*line;
	int		ret;

	ret = 0;
	(void)cub;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		(void)write(2, "Error:\n", 7);
		perror(file);
		exit(1);
	}
	while (1)
	{
		ret++;
		line = get_next_line(fd);
		if (line == NULL)
		{
			if (ret == 1)
			{
				(void)write(2, "Error: Empty file\n", 18);
				exit(1);
			}
			else
				break ;
		}
		free(line);
	}
	close(fd);
}
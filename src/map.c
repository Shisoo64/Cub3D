/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/30 17:58:31 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_dimension(t_vars *vars)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(vars->mapname, 0);
	if (fd == -1)
	{
		ft_printf("Error\nProblem with mapname", "%s");
		exit (0);
	}
	line = get_next_line(fd);
	vars->map_x = ft_strlen(line) - 1;
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i);
}

char	**create_map(t_vars *vars)
{
	char	**map;
	char	*buf;
	int		fd;
	int		y;
	int		x;

	y = -1;
	vars->map_y = get_map_dimension(vars);
	fd = open(vars->mapname, 0);
	map = malloc(sizeof(int *) * (vars->map_y + 1));
	while (++y < vars->map_y)
	{
		buf = get_next_line(fd);
		map[y] = malloc(sizeof(int) * (ft_strlen(buf) + 1));
		if (!buf)
			break;
		x = -1;
		while (++x < vars->map_x - 1)
			map[y][x] = buf[x];
		map[y][x] = '\0';
		free(buf);
	}
	map[y] = NULL;
	close(fd);
	return (map);
}

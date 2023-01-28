/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/28 17:51:21 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_map_height(t_vars *vars)
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
	vars->map_x = ft_strlen(line);
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
	int		fd;
	int		i;

	i = -1;
	vars->map_y = get_map_height(vars);
	fd = open(vars->mapname, 0);
	map = malloc(sizeof(char *) * (vars->map_y + 1));
	while (++i < vars->map_y)
		map[i] = get_next_line(fd);
	map[vars->map_y] = NULL;
	close(fd);
	return (map);
}

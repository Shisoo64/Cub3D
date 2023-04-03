/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/03 14:53:14 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_map_dimension(t_mlx *mlx)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(mlx->mapname, 0);
	if (fd == -1)
	{
		ft_printf("Error\nProblem with mapname", "%s");
		exit (0);
	}
	line = get_next_line(fd);
	mlx->map_x = ft_strlen(line) - 1;
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

void	place_player_on_map(t_mlx *mlx, char **map)
{
	int		y;
	int		x;

	y = -1;
	while (++y < mlx->map_y)
	{
		x = -1;
		while (++x < mlx->map_x - 1)
		{
			if (map[y][x] == 'N')
			{
				mlx->player.dir_x = 1;
				mlx->player.pos_y = y + 0.5f;
				mlx->player.pos_x = x + 0.5f;
			}
		}
	}
	mlx->player.dir_y = 0.0;
}

char	**create_map(t_mlx *mlx)
{
	char	**map;
	char	*buf;
	int		fd;
	int		y;
	int		x;

	y = -1;
	mlx->map_y = get_map_dimension(mlx);
	fd = open(mlx->mapname, 0);
	map = malloc(sizeof(int *) * (mlx->map_y + 1));
	while (++y < mlx->map_y)
	{
		buf = get_next_line(fd);
		map[y] = malloc(sizeof(int) * (ft_strlen(buf) + 1));
		if (!buf)
			break ;
		x = -1;
		while (++x < mlx->map_x - 1)
			map[y][x] = buf[x];
		map[y][x] = '\0';
		free(buf);
	}
	map[y] = NULL;
	close(fd);
	return (map);
}

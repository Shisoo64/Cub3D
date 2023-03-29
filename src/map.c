/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/29 16:10:36 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(char **map)
{
	int	y;

	y = -1;
	ft_printf("map:\n");
	while (map[++y])
		ft_printf("%s\n", map[y]);
	ft_printf("\n\n\n");
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
				mlx->player.dirX = 0.0;
				mlx->player.dirY = -1.0;
				mlx->player.planeX = 0.66;
				mlx->player.planeY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
			}
			else if (map[y][x] == 'S')
			{
				mlx->player.dirX = 0;
				mlx->player.dirY = 1;
				mlx->player.planeX = -0.66;
				mlx->player.planeY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
			}
			else if (map[y][x] == 'E')
			{
				mlx->player.dirX = 1;
				mlx->player.dirY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
			}
			else if (map[y][x] == 'W')
			{
				mlx->player.dirX = -1;
				mlx->player.dirY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
			}
		}
	}
}

void	ft_map_height(t_mlx *mlx)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(mlx->mapname, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("Error\nMap file does not exist or is empty, try again.");
		exit(0);
	}
	mlx->map_x = ft_strlen(line) - 1;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	mlx->map_y = i;
	free(line);
	close(fd);
}

void	ft_fill_map(t_mlx *mlx)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(mlx->mapname, O_RDONLY);
	ft_map_height(mlx);
	mlx->map = malloc(sizeof(char *) * mlx->map_y + 1);
	if (!mlx->map)
		return ;
	while (i < mlx->map_y)
	{
		mlx->map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
}

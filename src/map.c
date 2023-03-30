/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/30 19:02:23 by bchabot          ###   ########.fr       */
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

void	place_player_on_map(t_mlx *mlx)
{
	int		y;
	int		x;

	y = -1;
	while (++y < mlx->map_y)
	{
		x = -1;
		while (++x < mlx->map_x - 1)
		{
			printf("x is : %d\n", x);
			printf("y is : %d\n", y);
			printf("map[y][x] is : %c\n", mlx->map[y][x]);
			if (mlx->map[y][x] == 'N')
			{
				mlx->player.dirX = 0.0;
				mlx->player.dirY = -1.0;
				mlx->player.planeX = 0.66;
				mlx->player.planeY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
			}
			else if (mlx->map[y][x] == 'S')
			{
				mlx->player.dirX = 0;
				mlx->player.dirY = 1;
				mlx->player.planeX = -0.66;
				mlx->player.planeY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
			}
			else if (mlx->map[y][x] == 'E')
			{
				mlx->player.dirX = 1;
				mlx->player.dirY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
			}
			else if (mlx->map[y][x] == 'W')
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
	while (line)
	{
		if (ft_strnstr(line, "111", ft_strlen(line)) || ft_strnstr(line, "000", ft_strlen(line)))
		{
			mlx->map_x = ft_strlen(line) - 1;
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	printf("map x is : %d\n", mlx->map_x);
	mlx->map_y = i;
	printf("map y is : %d\n", mlx->map_y);
	free(line);
	close(fd);
}

int	is_asset(char *line)
{
	char *asset_text;
	char *asset_color;

	asset_text = "NSWE";
	asset_color = "FC";

	while (*asset_text)
	{
		if (ft_strchr(line, *asset_text))
			return (1);
		asset_text++;
	}
	while (*asset_color)
	{
		if (ft_strchr(line, *asset_color))
			return (2);
		asset_color++;
	}
	return (0);
}

void	ft_fill_map(t_mlx *mlx, int fd)
{
	int	i;
	char	*line;

	ft_map_height(mlx);
	mlx->map = malloc(sizeof(char *) * mlx->map_y + 1);
	if (!mlx->map)
		return ;
	line = get_next_line(fd);
	while (line && ft_strcmp(line, "\n"))
		line = get_next_line(fd);
	printf("final line is : %s\n", line);
	i = 0;
	while (i < mlx->map_y)
	{
		if (!line)
			break ;
		mlx->map[i] = ft_substr(line, 0, ft_strlen(line) - 2);
		printf("mlx map[%d] is : %s\n", i, mlx->map[i]);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	printf("mlx map[%d] is : %s\n", i, mlx->map[i]);
//	print_map(mlx->map);
	close(fd);
}

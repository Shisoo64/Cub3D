/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/31 03:14:12 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(char **map)
{
	int	y;

	y = -1;
	ft_printf("map:\n");
	while (map[++y])
		ft_printf("%s", map[y]);
	ft_printf("\n");
}

void	place_player_on_map(t_mlx *mlx)
{
	int		y;
	int		x;

	y = -1;
	printf("x len is : %d\n", mlx->map_x);
	printf("y len is : %d\n", mlx->map_y);
	print_map(mlx->map);
	while (++y < (mlx->map_y - 1))
	{
		x = -1;
		while (++x < (mlx->map_x - 5))
		{
			if (mlx->map[y][x] == 'N')
			{
				mlx->player.dirX = 0.0;
				mlx->player.dirY = -1.0;
				mlx->player.planeX = 0.66;
				mlx->player.planeY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
				break ;
			}
			else if (mlx->map[y][x] == 'S')
			{
				mlx->player.dirX = 0;
				mlx->player.dirY = 1;
				mlx->player.planeX = -0.66;
				mlx->player.planeY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
				break ;
			}
			else if (mlx->map[y][x] == 'E')
			{
				mlx->player.dirX = 1;
				mlx->player.dirY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
				break ;
			}
			else if (mlx->map[y][x] == 'W')
			{
				mlx->player.dirX = -1;
				mlx->player.dirY = 0.0;
				mlx->player.posY = y + 0.5f;
				mlx->player.posX = x + 0.5f;
				break ;
			}
		}
	}
	printf("posx is : %f\n", mlx->player.posY);
	printf("posy is : %f\n", mlx->player.posX);
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

void	ft_map_height(t_mlx *mlx)
{
	int		i;
	int		fd;
	int		len;
	char	*line;

	i = 0;
	fd = open(mlx->mapname, O_RDONLY);
	line = get_next_line(fd);
	len = 0;
	while (line)
	{
		if (*line >= 32 && !is_input(line))
		{
			if (len < ft_strlen(line))
				len = ft_strlen(line);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	mlx->map_y = i;
	mlx->map_x = len - 1;
	printf("map x is : %d\n", mlx->map_x);
	printf("map y is : %d\n", mlx->map_y);
	free(line);
	close(fd);
}

void	ft_fill_map(t_mlx *mlx, int fd)
{
	int	i;
	char	*line;

	//ft_map_height(mlx);
	mlx->map = malloc(sizeof(char *) * mlx->map_y + 1);
	if (!mlx->map)
		return ;
	i = 0;
	while (i < mlx->map_y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line >= 32)
		{
			mlx->map[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	close(fd);
}

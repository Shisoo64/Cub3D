/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/05 15:35:53 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	print_map(char **map)
{
	int	y;

	y = -1;
	ft_printf("map:\n");
	while (map[++y])
		ft_printf("%s", map[y]);
	ft_printf("\n");
}

void	set_player_dir(t_mlx *mlx, int dir[2], double plane[2])
{
	mlx->player.dirX = dir[0];
	mlx->player.dirY = dir[1];
	mlx->player.planeX = plane[0];
	mlx->player.planeY = plane[1];
}

void	place_player_on_map(t_mlx *mlx)
{
	int		y;
	int		x;

	y = -1;
	while (++y < (mlx->map_y - 1))
	{
		x = -1;
		while (++x < (mlx->map_x) - 1)
		{
			if (mlx->map[y][x] == 'N')
			{
				set_player_dir(mlx, (int []){0, -1}, (double []){FOV, 0});
				break ;
			}
			else if (mlx->map[y][x] == 'S')
			{
				set_player_dir(mlx, (int []){0, 1}, (double []){-FOV, 0});
				break ;
			}
			else if (mlx->map[y][x] == 'E')
			{
				set_player_dir(mlx, (int []){1, 0}, (double []){0, FOV});
				break ;
			}
			else if (mlx->map[y][x] == 'W')
			{
				set_player_dir(mlx, (int []){-1, 0}, (double []){0, -FOV});
				break ;
			}
		}
	}
	mlx->player.posY = y + 0.5f;
	mlx->player.posX = x + 0.5f;
}

int	is_asset(char *line)
{
	char	*asset_text;
	char	*asset_color;

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
		if (*line >= 32 && is_input(line))
		{
			if (len < (int)ft_strlen(line))
				len = (int)ft_strlen(line);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	mlx->map_y = i;
	mlx->map_x = len - 1;
	free(line);
	close(fd);
}

void	ft_fill_map(t_mlx *mlx)
{
	char	*line;
	int		i;
	int		fd;

	ft_map_height(mlx);
	fd = open(mlx->mapname, O_RDONLY);
	mlx->map = malloc(sizeof(char *) * mlx->map_y + 1);
	if (!mlx->map)
		return ;
	i = 0;
	while (i < mlx->map_y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line >= 32 && is_input(line))
		{
			mlx->map[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	close(fd);
}

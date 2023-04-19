/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 17:57:54 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D_bonus.h"

void	set_player_dir(t_mlx *mlx, int dir[2], double plane[2], int y)
{
	int	x;

	mlx->player.dir_x = dir[0];
	mlx->player.dir_y = dir[1];
	mlx->player.plane_x = plane[0];
	mlx->player.plane_y = plane[1];
	x = 0;
	while (mlx->map[y][x] && !ft_strchr("NSWE", mlx->map[y][x]))
		x++;
	mlx->player.pos_x = x + 0.5f;
	mlx->player.pos_y = y + 0.5f;
	mlx->player_nb++;
}

void	place_player_on_map(t_mlx *mlx)
{
	int		y;

	y = -1;
	while (++y < mlx->map_y)
	{
		if (ft_strchr(mlx->map[y], 'N'))
			set_player_dir(mlx, (int []){0, -1}, (double []){FOV, 0}, y);
		else if (ft_strchr(mlx->map[y], 'S'))
			set_player_dir(mlx, (int []){0, 1}, (double []){-FOV, 0}, y);
		else if (ft_strchr(mlx->map[y], 'E'))
			set_player_dir(mlx, (int []){1, 0}, (double []){0, FOV}, y);
		else if (ft_strchr(mlx->map[y], 'W'))
			set_player_dir(mlx, (int []){-1, 0}, (double []){0, -FOV}, y);
	}
}

void	ft_map_height(t_mlx *mlx, char **data)
{
	int		i;
	int		len;
	int		row;

	i = 0;
	len = 0;
	row = 0;
	while (data[i])
	{
		if (is_mapline_ok(data[i]))
		{
			if (len < (int)ft_strlen(data[i]))
				len = (int)ft_strlen(data[i]);
			row++;
		}
		i++;
	}
	mlx->map_y = row;
	mlx->map_x = len - 1;
}

void	ft_fill_map(t_mlx *mlx, char **data)
{
	int		i;
	int		y;

	ft_map_height(mlx, data);
	mlx->map = ft_calloc(sizeof(char *), mlx->map_y + 1);
	if (!mlx->map)
		exit_game_light(mlx, data);
	i = 0;
	y = 0;
	while (data[i])
	{
		if (is_mapline_ok(data[i]))
			mlx->map[y++] = ft_strdup(data[i]);
		i++;
	}
	mlx->map[y] = NULL;
}

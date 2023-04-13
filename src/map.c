/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:16:43 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/13 15:55:08 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

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
	mlx->player.dir_x = dir[0];
	mlx->player.dir_y = dir[1];
	mlx->player.plane_x = plane[0];
	mlx->player.plane_y = plane[1];
}

void	set_player_pos(t_mlx *mlx, char *row, int y)
{
	int		x;
	char	*player_orientation;

	player_orientation = "NSWE";
	x = 0;
	while (row[x] && !ft_strchr(player_orientation, row[x]))
		x++;
	mlx->player.pos_y = y + 0.5f;
	mlx->player.pos_x = x + 0.5f;
}

void	place_player_on_map(t_mlx *mlx)
{
	int		y;

	y = -1;
	while (++y < mlx->map_y)
	{
		if (ft_strchr(mlx->map[y], 'N'))
		{
			set_player_dir(mlx, (int []){0, -1}, (double []){FOV, 0});
			break ;
		}
		else if (ft_strchr(mlx->map[y], 'S'))
		{
			set_player_dir(mlx, (int []){0, 1}, (double []){-FOV, 0});
			break ;
		}
		else if (ft_strchr(mlx->map[y], 'E'))
		{
			set_player_dir(mlx, (int []){1, 0}, (double []){0, FOV});
			break ;
		}
		else if (ft_strchr(mlx->map[y], 'W'))
		{
			set_player_dir(mlx, (int []){-1, 0}, (double []){0, -FOV});
			break ;
		}
	}
	set_player_pos(mlx, mlx->map[y], y);
}

int	is_asset(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
			|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (1);
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (2);
	return (0);
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
		if (is_input(data[i]))
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
	int		x;

	ft_map_height(mlx, data);
	mlx->map = ft_calloc(sizeof(char *), mlx->map_y + 1);
	if (!mlx->map)
		exit_game_light(mlx);
	i = 0;
	x = 0;
	while (data[i])
	{
		if (is_input(data[i]))
		{
			mlx->map[x] = ft_strdup(data[i]);
			x++;
		}
		i++;
	}
	mlx->map[x] = NULL;
}

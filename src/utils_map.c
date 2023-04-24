/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:01:28 by bchabot           #+#    #+#             */
/*   Updated: 2023/04/24 16:03:35 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	is_good(char c)
{
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}

char	**copy_map(t_mlx *mlx)
{
	char	**map;
	int		i;
	int		j;

	i = -1;
	j = -1;
	map = ft_calloc(sizeof(char *), mlx->map_y + 5);
	if (!map)
		exit(1);
	while (++i < mlx->map_y + 4)
	{
		map[i] = ft_calloc(sizeof(char), mlx->map_x + 5);
		ft_memset(map[i], ' ', mlx->map_x + 5);
		map[i][mlx->map_x + 4] = '\n';
	}
	while (++j < mlx->map_y)
	{
		i = -1;
		while (++i < mlx->map_x && mlx->map[j][i])
		{
			if (mlx->map[j][i] >= 32)
				map[j + 2][i + 2] = mlx->map[j][i];
		}
	}
	return (map);
}

int	check_surround_cells(char **test_map)
{
	int	i;
	int	j;

	i = -1;
	while (test_map[++i])
	{
		j = -1;
		while (test_map[i][++j])
		{
			if (test_map[i][j] == 32)
			{
				if (!is_good(test_map[i + 1][j]) || !is_good(test_map[i - 1][j])
					|| !is_good(test_map[i][j + 1])
					|| !is_good(test_map[i][j - 1]))
					return (1);
			}
		}
	}
	return (0);
}

void	surround_map(t_mlx *mlx, char **map)
{
	int	i;

	i = -1;
	while (++i <= mlx->map_x + 3)
	{
		map[0][i] = '1';
		map[mlx->map_y + 3][i] = '1';
	}
	i = -1;
	while (++i <= mlx->map_y + 3)
	{
		map[i][0] = '1';
		map[i][mlx->map_x + 3] = '1';
	}
}

void	check_map_borders(t_mlx *mlx, char **data)
{
	char	**test_map;

	test_map = copy_map(mlx);
	surround_map(mlx, test_map);
	if (check_surround_cells(test_map))
	{
		error_message("Map is not closed.\n", NULL);
		free_map(test_map);
		free_map(data);
		exit_game(mlx, mlx->map);
	}
	free_map(test_map);
}

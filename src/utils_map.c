/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:01:28 by bchabot           #+#    #+#             */
/*   Updated: 2023/04/17 16:31:21 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	is_good(char c)
{
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}

void	check_surround_cells(char **test_map)
{
	int	i;
	int	j;

	i = 0;
	while (test_map[i])
	{
		j = 0;
		while (test_map[i][j])
		{
			if (test_map[i][j] == 32)
			{
				if (!is_good(test_map[i + 1][j]) || !is_good(test_map[i - 1][j])
					|| !is_good(test_map[i][j + 1]) || !is_good(test_map[i][j
						- 1]))
				{
					error_message("Map is not closed.", NULL);
					return ;
				}
			}
			j++;
		}
		i++;
	}
}

char	**copy_map(t_mlx *mlx)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	map = ft_calloc(sizeof(char *), mlx->map_y + 5);
	if (!map)
		exit_game_light(mlx, NULL);
	while (i < mlx->map_y + 4)
	{
		map[i] = ft_calloc(sizeof(char), mlx->map_x + 5);
		ft_memset(map[i], ' ', mlx->map_x + 4);
		map[i][mlx->map_x + 3] = '\n';
		i++;
	}
	while (j < mlx->map_y)
	{
		i = 0;
		while (i < mlx->map_x)
		{
			if (mlx->map[j][i] >= 32)
				map[j + 2][i + 2] = mlx->map[j][i];
			i++;
		}
		j++;
	}
	return (map);
}

void	check_map_borders(t_mlx *mlx)
{
	char	**test_map;
	int		l;
	int		m;

	test_map = copy_map(mlx);
	l = 0;
	while (l <= mlx->map_x + 2)
	{
		test_map[0][l] = '1';
		test_map[mlx->map_y + 3][l] = '1';
		l++;
	}
	m = 0;
	while (m <= mlx->map_y + 3)
	{
		test_map[m][0] = '1';
		test_map[m][mlx->map_x + 2] = '1';
		m++;
	}
	print_map(test_map);
	check_surround_cells(test_map);
	free_map(test_map);
}

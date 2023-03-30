/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:08:28 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/30 18:18:57 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
void	check_assets(t_mlx *v)
{
	check_map_ext(v);
	check_items(v);
	check_rectangle(v);
	check_borders(v);
}

int	check_rectangle(char **map, t_mlx *v)
{
	int		y;

	y = -1;
	while (map[++y])
	{
		if (map[y][ft_strlen(map[y]) - 1] == '\n')
		{
			if (ft_strlen(map[y]) != ft_strlen(map[0]))
				ft_error(v, "Error\nMap is not a rectangle.\n");
		}
		else
			if (ft_strlen(map[y]) != ft_strlen(map[0]) - 1)
				ft_error(v, "Error\nMap is not rectangle AND you forgot the\\n, " \
					"u tried to have me, you're a big crazy man, or manette\n");
	}
	return (0);
}

int	check_borders(char **map, t_mlx *v)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] && map[y][x] != '\n')
		{
			if (y == 0 && map[y][x] != '1')
				ft_error(v, "Error\nWrong map border.\n");
			else if (y == v->map_y && map[y][x] != '1')
				ft_error(v, "Error\nWrong map border.\n");
			else if (x == 0 && map[y][x] != '1')
				ft_error(v, "Error\nWrong map border.\n");
			else if (x == v->map_x && map[y][x] != '1')
				ft_error(v, "Error\nWrong map border.\n");
		}
	}
	return (0);
}

void	check_items_ext(int i[3], t_mlx *v)
{
	if (i[0] != 1 || i[2] <= 0 || i[1] != 1)
		ft_error(v, "Error\nProblem with item numbers.\n");
}

void	check_items(char **map, t_mlx *v)
{
	int	x;
	int	y;
	int	i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x] && map[y][x] != '\n')
		{
			if (map[y][x] == 'E')
				i[0]++;
			else if (map[y][x] == 'P')
				i[1]++;
			else if (map[y][x] == 'C')
				i[2]++;
			else if (map[y][x] != '1' && map[y][x] != '0' \
			&& map[y][x] != 'M' && map[y][x] != 'X')
				ft_error(v, "Error\nWrong item on map.\n");
		}
	}
	check_items_ext(i, v);
}

*/

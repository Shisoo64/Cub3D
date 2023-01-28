/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:08:28 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/29 00:37:27 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	check_map(char **map, t_vars *v)
{
	check_map_ext(v);
	check_rectangle(map, v);
	check_borders(map, v);
	check_items(map, v);
}

int	check_rectangle(char **map, t_vars *v)
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

int	check_borders(char **map, t_vars *v)
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

void	check_items_ext(int i[3], t_vars *v)
{
	if (i[0] != 1 || i[2] <= 0 || i[1] != 1)
		ft_error(v, "Error\nProblem with item numbers.\n");
}

void	check_items(char **map, t_vars *v)
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
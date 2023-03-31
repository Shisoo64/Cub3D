/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:08:28 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/31 20:25:07 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*
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
*/

void	error_message(char *msg, char *line)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	if (line)
		ft_putstr_fd(line, 2);

}
int	check_wall_textures(char *line)
{
	char	*str;
	int		fd;

	str = ft_strnstr(line, "./", ft_strlen(line));
	if (!str || !ft_strnstr(str, ".xpm", ft_strlen(str)))
	{
		error_message("Check this wall texture line provided in the map file : ", line);
		return (1);
	}
	str = ft_substr((const char *)str, 0, ft_strlen(str) - 2);
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		free(str);
		error_message("Check this wall texture line provided in the map file : ", line);
		return (1);
	}
	free(str);
	close(fd);
	return (0);
}

int	check_colors(char *line)
{
	int 	i;
	int 	value;
	char	*str;
	char	*buf;

	i = 0;
	str = line;
	while (*str && !ft_isdigit(*str))
		str++;
	while (i < 3)
	{
		buf = ft_strdup(str);
		buf = ft_strtok(buf, ",\n");
		if (!buf)
		{
			printf("Color error.\n");
			return (1);
		}
		while (*str && ft_isdigit(*str))
			str++;
		while (*str && !ft_isdigit(*str))
			str++;
		value = ft_atoi(buf);
		if (value > 255)
		{
			error_message("Error. The value of one of your color is wrong. Check this line : ", line);
			return (1);
		}
		else
			i++;
		//free(buf);
	}
	if (i != 3)
		error_message("Error. Color values seems to be missing. Check this line : ", line);
	free(buf);
	return (0);
}

int	is_input(char *line)
{
	char	*map_input;

	map_input = "10NSWE ";
	while (*line == 32)
		line++;
	while (*line)
	{
		if (!ft_strchr(map_input, *line) && *line > 32)
			return (0);
		line++;
	}
	return (1);
}

int	check_map(char *line, int fd)
{
	while (line)
	{
		if (line && !is_input(line) && !is_asset(line))
		{
			error_message("Check this map row in the map file : ", line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

void	check_items(t_mlx *mlx)
{
	int		fd;
	char	*line;

	fd = open(mlx->mapname, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n' && ft_strnstr(line,"11", ft_strlen(line)) && !is_asset(line))
			break ;
		if (is_asset(line) == 1 && check_wall_textures(line))
			exit_game_light(mlx, fd);
		if (is_asset(line) == 2 && check_colors(line))
			exit_game_light(mlx, fd);
		free(line);
		line = get_next_line(fd);
	}
	if (check_map(line, fd))
		exit_game_light(mlx, fd);
	close(fd);
	// int	x;
	// int	y;
	// int	i[3];

	// i[0] = 0;
	// i[1] = 0;
	// i[2] = 0;
	// y = -1;
	// while (map[++y])
	// {
	// 	x = -1;
	// 	while (map[y][++x] && map[y][x] != '\n')
	// 	{
	// 		if (map[y][x] == 'E')
	// 			i[0]++;
	// 		else if (map[y][x] == 'P')
	// 			i[1]++;
	// 		else if (map[y][x] == 'C')
	// 			i[2]++;
	// 		else if (map[y][x] != '1' && map[y][x] != '0' \
	// 		&& map[y][x] != 'M' && map[y][x] != 'X')
	// 			ft_error(v, "Error\nWrong item on map.\n");
	// 	}
	// }
	// check_items_ext(i, v);
}

void	check_assets(t_mlx *mlx)
{
	check_map_ext(mlx);
	check_items(mlx);
//	check_rectangle(v);
//	check_borders(v);
}

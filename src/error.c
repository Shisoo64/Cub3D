/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:08:28 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/10 11:58:30 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	int		i;
	int		value;
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
			error_message("The value of one of your color is wrong. Check this line : ", line);
			return (1);
		}
		else
			i++;
	}
	if (i != 3)
		error_message("Color values seems to be missing. Check this line : ", line);
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

int	check_map(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] && !is_input(data[i]) && !is_asset(data[i]))
		{
			error_message("Check this map row in the map file : ", data[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	closed_walls(char c)
{
	if (c == '1' || c == '0')
		return (1);
	return (0);
}

int	check_borders(char **data)
{
	int	i;
	int	j;

	i = 0;
	while (data[i] && !is_input(data[i]) && is_asset(data[i]))
		i++;
	while (data[i])
	{
		j = 0;
		while (data[i][j])
		{
			if (data[i][j] != '1' && data[i][j] > 32)
			{
				if (!closed_walls(data[i - 1][j]) || !closed_walls(data[i][j - 1])
				|| !closed_walls(data[i][j + 1]) || !closed_walls(data[i + 1][j]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	check_items(t_mlx *mlx, char **data)
{
	int	i;
	int	text;
	int	color;

	i = 0;
	text = 0;
	color = 0;
	while (data[i])
	{
		if (is_input(data[i]) && !is_asset(data[i]))
			break ;
		if (is_asset(data[i]) == 1)
		{
			if (check_wall_textures(data[i]))
				exit_game_light(mlx);
			else
				text++;
		}
		if (is_asset(data[i]) == 2)
		{
			if (check_colors(data[i]))
				exit_game_light(mlx);
			else
				color++;
		}
		i++;
	}
	if (text != 4 || color != 2)
	{
		error_message("Check this map row in the map file : ", NULL);
		exit_game_light(mlx);
	}
}

void	check_assets(t_mlx *mlx, char **data)
{
	check_items(mlx, data);
	if (check_map(data))// || !check_borders(data))
		exit_game_light(mlx);
}

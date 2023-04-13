/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:08:28 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/13 16:14:03 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	error_message(char *msg, char *line)
{
	ft_putstr_fd("Error.\n", 2);
	ft_putstr_fd(msg, 2);
	if (line)
		ft_putstr_fd(line, 2);
}

int	check_wall_textures(char *line)
{
	char	*str;
	int		fd;

	str = ft_strnstr(line, ".", ft_strlen(line));

	if ((*(str - 1) != ' ' && *(str + 1) != '/') || !str || !ft_strnstr(str, ".xpm", ft_strlen(str)))
	{
		error_message("Check this line provided in the map file : ", line);
		return (1);
	}
	str = ft_substr((const char *)str, 0, ft_strlen(str) - 2);
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		free(str);
		error_message("Check this line provided in the map file : ", line);
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
	str = line + 1;
	while (*str == 32)
		str++;
	while (i < 3)
	{
		buf = ft_strdup(str);
		buf = ft_strtok(buf, ",");
		if (!buf || !ft_isdigit(*buf))
			break ;
		while (*str && ft_isdigit(*str))
			str++;
		str++;
		value = ft_atoi(buf);
		if (value > 255)
			break ;
		else
			i++;
		free(buf);
	}
	free(buf);
	if (i == 3)
			return (0);
	error_message("Color values are erroneous. Check this line : ", line);
	return (1);
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

void	check_items(t_mlx *mlx, char **data)
{
	int	i;
	int	text;
	int	color;

	i = -1;
	text = 0;
	color = 0;
	while (data[++i])
	{
		if (is_asset(data[i]) == 1 && check_wall_textures(data[i]))
			exit_game_light(mlx, data);
		else if (is_asset(data[i]) == 1)
			text++;
		if (is_asset(data[i]) == 2 && check_colors(data[i]))
			exit_game_light(mlx, data);
		else if (is_asset(data[i]) == 2)
			color++;
	}
	if (text != 4 || color != 2)
	{
		error_message("Assets are missing. Check textures and colors.\n", NULL);
		exit_game_light(mlx, data);
	}
}

void	check_assets(t_mlx *mlx, char **data)
{
	check_items(mlx, data);
	if (check_map(data))
		exit_game_light(mlx, data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:08:28 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/24 18:11:04 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	check_wall_textures(char *line)
{
	char	*str;
	int		fd;

	str = ft_strnstr(line, ".", ft_strlen(line));
	if (!str || (*(str - 1) != ' ' && *(str + 1) != '/')
		|| !ft_strnstr(str, ".xpm", ft_strlen(str)))
	{
		error_message("Check this line provided in the map file : ", line);
		return (1);
	}
	str = ft_substr((const char *)str, 0, ft_strlen(str) - 1);
	if (!str)
		return (1);
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

//Check if colors are properly formated
int	check_colors(char *line)
{
	int		i;
	int		value;
	char	*str;

	i = -1;
	str = line + 1;
	while (*str == 32)
		str++;
	if (ft_isdigit(*str) && is_colorline_ok(str) == 2)
	{
		while (++i < 3)
		{
			value = get_next_color(str);
			while (*str && ft_isdigit(*str))
				str++;
			str++;
			if (value > 255 || value < 0)
				break ;
		}
		if (i == 3)
			return (0);
	}
	error_message("Check this line provided in the map file : ", line);
	return (1);
}

//Check if all char in the map are allowed
int	check_map(char **data)
{
	int	i;

	i = -1;
	while (data[++i])
	{
		if (data[i] && !is_mapline_ok(data[i]) && !is_asset(data[i]))
		{
			error_message("Check this map row in the map file : ", data[i]);
			return (1);
		}
	}
	return (0);
}

//Check if colors and textures are valid
int	check_items(char **data)
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
			return (1);
		else if (is_asset(data[i]) == 1)
			text++;
		if (is_asset(data[i]) == 2 && check_colors(data[i]))
			return (1);
		else if (is_asset(data[i]) == 2)
			color++;
	}
	if (text != 4 || color != 2)
	{
		error_message("Check textures and colors.\n", NULL);
		return (1);
	}
	return (0);
}

//Check if map file is properly formated
void	check_assets(char **data)
{
	if (is_mapline_ok(data[0]))
	{
		error_message(NULL, NULL);
		exit_game_light(data);
	}
	if (check_map(data) || check_items(data))
		exit_game_light(data);
}

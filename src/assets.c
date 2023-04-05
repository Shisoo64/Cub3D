/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:20:46 by bchabot           #+#    #+#             */
/*   Updated: 2023/04/05 16:33:56 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	fill_wall_tex(t_mlx *mlx, t_display *texture, char *line)
{
	char	*str;

	str = ft_strnstr(line, "./", ft_strlen(line));
	if (!str || !ft_strnstr(str, ".xpm", ft_strlen(str)))
	{
		error_message("Check this line provided in the map file : ", line);
		exit_game(mlx);
	}
	printf("texture is : %s\n", str);
	str = ft_substr((const char *)str, 0, ft_strlen(str) - 2);
	if (open(str, O_RDONLY) == -1)
		error_message("Check this line provided in the map file : ", line);
	texture->img = mlx_xpm_file_to_image(mlx->mlx, str, &texture->tex_width, &texture->tex_height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
	free(str);
}

void	get_wall_textures(t_mlx *mlx, char *line)
{
	if (is_asset(line) == 1 && ft_strnstr(line, "NO", ft_strlen(line)))
		fill_wall_tex(mlx, &mlx->NO_tex, line);
	else if (is_asset(line) == 1 && ft_strnstr(line, "SO", ft_strlen(line)) != NULL)
		fill_wall_tex(mlx, &mlx->SO_tex, line);
	else if (is_asset(line) == 1 && ft_strnstr(line, "WE", ft_strlen(line)) != NULL)
		fill_wall_tex(mlx, &mlx->WE_tex, line);
	else if (is_asset(line) == 1 && ft_strnstr(line, "EA", ft_strlen(line)) != NULL)
		fill_wall_tex(mlx, &mlx->EA_tex, line);
}

int	fill_color(char *line)
{
	int		i;
	int		color;
	char	*str;
	char	*buf;

	i = 0;
	color = 0;
	str = line;
	while (*str && !ft_isdigit(*str))
		str++;
	while (i < 3)
	{
		i++;
		buf = ft_strdup(str);
		buf = ft_strtok(buf, ",\n");
		while (*str && ft_isdigit(*str))
			str++;
		while (*str && !ft_isdigit(*str))
			str++;
		color |= (ft_atoi(buf) << ((3 - i) * 8));
	}
	return (color);
}

void	get_colors(t_mlx *mlx, char *line)
{
	if (is_asset(line) && ft_strchr(line, 'F'))
	{
		mlx->color_f = fill_color(line);
		printf("color of line %s is %d.\n", line, mlx->color_f);
	}
	else if (is_asset(line) && ft_strchr(line, 'C'))
	{
		mlx->color_c = fill_color(line);
		printf("color of line %s is %d.\n", line, mlx->color_c);
	}
}

void	fetch_assets(t_mlx *mlx)
{
	int		fd;
	char	*line;

	fd = open(mlx->mapname, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n' && ft_strnstr(line,"11", ft_strlen(line)) && !is_asset(line))
			break ;
		if (is_asset(line) == 1)
			get_wall_textures(mlx, line);
		if (is_asset(line) == 2)
			get_colors(mlx, line);
		free(line);
		line = get_next_line(fd);
	}
	ft_fill_map(mlx);
	place_player_on_map(mlx);
	close(fd);
}

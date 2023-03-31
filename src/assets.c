/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:20:46 by bchabot           #+#    #+#             */
/*   Updated: 2023/03/31 16:27:21 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_wall_tex(t_mlx *mlx, t_display *texture, char *line)
{
	char *str;

	str = ft_strnstr(line, "./", ft_strlen(line));
	if (!str || !ft_strnstr(str, ".xpm", ft_strlen(str)))
	{
		printf("Error.\n");
		error_message("Check this line provided in the map file : ", line);
		exit_game(mlx);
	}
	printf("texture is : %s\n", str);
	str = ft_substr((const char *)str, 0, ft_strlen(str) - 2);
	if (open(str, O_RDONLY) == -1)

	texture->img = mlx_xpm_file_to_image(mlx->mlx, str, &texture->tex_width, &texture->tex_height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
	free(str);
}

void	get_wall_textures(t_mlx *mlx)
{
	char	*line;
	int		nbr;
	int		fd;

	nbr = 0;
	fd = open(mlx->mapname, O_RDONLY);
	line = get_next_line(fd);
	while (1)
	{
		if (!line || nbr == 4)
			break ;
		if (is_asset(line) == 1 && ft_strnstr(line, "NO", ft_strlen(line)))
		{
			fill_wall_tex(mlx, &mlx->NO_tex, line);
			nbr++;
		}
		else if (is_asset(line) == 1 && ft_strnstr(line, "SO", ft_strlen(line)) != NULL)
		{
			fill_wall_tex(mlx, &mlx->SO_tex, line);
			nbr++;
		}
		else if (is_asset(line) == 1 && ft_strnstr(line, "WE", ft_strlen(line)) != NULL)
		{
			fill_wall_tex(mlx, &mlx->WE_tex, line);
			nbr++;
		}
		else if (is_asset(line) == 1 && ft_strnstr(line, "EA", ft_strlen(line)) != NULL)
		{
			fill_wall_tex(mlx, &mlx->EA_tex, line);
			nbr++;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (nbr != 4)
	{
		printf("error in wall textures\n");
		exit_game(mlx);
	}
	free(line);
	close(fd);
}

int	fill_color(char *line)
{
	int 	i;
	int		color;
	int 	value;
	char	*str;
	char	*buf;

	i = 0;
	color = 0;
	str = line;
	while (*str && !ft_isdigit(*str))
		str++;
	printf("Color is : %s", str);
	while (i < 3)
	{
		i++;
		buf = ft_strdup(str);
		buf = ft_strtok(buf, ",\n");
		if (!buf)
		{
			printf("Color error.\n");
			exit(0);
		}
		while (*str && ft_isdigit(*str))
			str++;
		while (*str && !ft_isdigit(*str))
			str++;
		value = ft_atoi(buf);
		printf("value is %d\n", value);
		if (value > 255 || value < 0)
		{
			printf("Error. The value of one of your color is wrong.\n");
			exit(0);
		}
		color |= (ft_atoi(buf) << ((3 - i) * 8));
		//free(buf);
	}
	return (color);
}

void	get_colors(t_mlx *mlx)
{
	char	*line;
	int		nbr;
	int		fd;

	nbr = 0;
	fd = open(mlx->mapname, O_RDONLY);
	line = get_next_line(fd);
	printf("line is %s\n", line);
	while (line)
	{
		if (is_asset(line) && ft_strchr(line, 'F'))
		{
			printf("color F is : %s\n", line);
			mlx->color_f = fill_color(line);
			nbr++;
		}
		else if (is_asset(line) && ft_strchr(line, 'C'))
		{
			printf("color C is : %s\n", line);
			mlx->color_c = fill_color(line);
			nbr++;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (nbr != 2)
		printf("Color error\n");
	close(fd);
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
}

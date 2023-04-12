/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 16:20:46 by bchabot           #+#    #+#             */
/*   Updated: 2023/04/12 18:12:18 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	fill_wall_tex(t_mlx *mlx, t_display *texture, char *line)
{
	char	*str;

	str = ft_strnstr(line, "./", ft_strlen(line));
	if (!str || !ft_strnstr(str, ".xpm", ft_strlen(str)))
	{
		error_message("Check this line provided in the map file : ", line);
		exit_game(mlx);
	}
	str = ft_substr((const char *)str, 0, ft_strlen(str) - 2);
	if (open(str, O_RDONLY) == -1)
		error_message("Check this line provided in the map file : ", line);
	texture->img = mlx_xpm_file_to_image(mlx->mlx, str,
			&texture->tex_width, &texture->tex_height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	free(str);
}

void	get_wall_textures(t_mlx *mlx, char *line)
{
	if (is_asset(line) == 1 && ft_strnstr(line, "NO", ft_strlen(line)))
		fill_wall_tex(mlx, &mlx->no_tex, line);
	else if (is_asset(line) == 1
		&& ft_strnstr(line, "SO", ft_strlen(line)) != NULL)
		fill_wall_tex(mlx, &mlx->so_tex, line);
	else if (is_asset(line) == 1
		&& ft_strnstr(line, "WE", ft_strlen(line)) != NULL)
		fill_wall_tex(mlx, &mlx->we_tex, line);
	else if (is_asset(line) == 1
		&& ft_strnstr(line, "EA", ft_strlen(line)) != NULL)
		fill_wall_tex(mlx, &mlx->ea_tex, line);
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
		str++;
		color |= (ft_atoi(buf) << ((3 - i) * 8));
		free(buf);
	}
	return (color);
}

void	get_colors(t_mlx *mlx, char *line)
{
	if (is_asset(line) && ft_strchr(line, 'F'))
		mlx->color_f = fill_color(line);
	else if (is_asset(line) && ft_strchr(line, 'C'))
		mlx->color_c = fill_color(line);
}

#include <string.h>

void	check_map_borders(t_mlx *mlx)
{
	char **test_map;

	printf("y is %d\n", mlx->map_y);
	printf("x is %d\n", mlx->map_x);
	print_map(mlx->map);
	test_map = ft_calloc(sizeof(char *), mlx->map_y + 2);
	if (!test_map)
		exit_game_light(mlx);
	int	i = 0;
	while (i < mlx->map_y + 1)
	{
		test_map[i] = ft_calloc(sizeof(char), mlx->map_x + 2);
		memset(test_map[i], ' ', mlx->map_x + 2);
		test_map[i][mlx->map_x + 2] = '\n';
		i++;
	}
	print_map(test_map);

	// Copy the original map into the new map
    int j = 0;
    while (j < mlx->map_y) {
        int k = 0;
        while (k < mlx->map_x) {
            test_map[j][k] = mlx->map[j][k];
            k++;
        }
        j++;
    }
/*
    // Surround the new map with '1' chars
    int l = 0;
    while (l < mlx->map_x + 2) {
        test_map[0][l] = '1';
        test_map[mlx->map_y + 2][l] = '1';
        l++;
    }
    int m = 1;
    while (m < mlx->map_y + 1) {
        test_map[m][0] = '1';
        test_map[m][mlx->map_x + 1] = '1';
        m++;
    }
	*/
}

void	fetch_assets(t_mlx *mlx, char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (is_asset(data[i]) == 1)
			get_wall_textures(mlx, data[i]);
		if (is_asset(data[i]) == 2)
			get_colors(mlx, data[i]);
		i++;
	}
	ft_fill_map(mlx, data);
	check_map_borders(mlx);
	place_player_on_map(mlx);
}
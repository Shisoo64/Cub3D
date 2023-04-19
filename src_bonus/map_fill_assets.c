/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fill_assets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:43:45 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 17:57:55 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D_bonus.h"

//Assign the wall textures
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
	texture->img = mlx_xpm_file_to_image(mlx->mlx, str, &texture->tex_width,
			&texture->tex_height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	free(str);
}

//Check the texture lines in the map file
void	get_wall_textures(t_mlx *mlx, char *line)
{
	if (is_asset(line) == 1 && ft_strnstr(line, "NO", ft_strlen(line)))
		fill_wall_tex(mlx, &mlx->no_tex, line);
	else if (is_asset(line) == 1 && ft_strnstr(line, "SO",
			ft_strlen(line)) != NULL)
		fill_wall_tex(mlx, &mlx->so_tex, line);
	else if (is_asset(line) == 1 && ft_strnstr(line, "WE",
			ft_strlen(line)) != NULL)
		fill_wall_tex(mlx, &mlx->we_tex, line);
	else if (is_asset(line) == 1 && ft_strnstr(line, "EA",
			ft_strlen(line)) != NULL)
		fill_wall_tex(mlx, &mlx->ea_tex, line);
}

//Assign the sky and ground colors
int	fill_color(char *line)
{
	int		i;
	int		color;
	char	*str;
	int		value;

	i = 0;
	color = 0;
	value = 0;
	str = line;
	while (*str && !ft_isdigit(*str))
		str++;
	while (i < 3)
	{
		i++;
		value = get_next_color(str);
		while (*str && ft_isdigit(*str))
			str++;
		str++;
		color |= (value << ((3 - i) * 8));
	}
	return (color);
}

//Check the colors lines in the map file
void	get_colors(t_mlx *mlx, char *line)
{
	if (is_asset(line) && ft_strchr(line, 'F'))
		mlx->color_f = fill_color(line);
	else if (is_asset(line) && ft_strchr(line, 'C'))
		mlx->color_c = fill_color(line);
}

//Fetch and init the map, color and textures
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
	check_map_borders(mlx, data);
}

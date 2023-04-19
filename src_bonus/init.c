/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:47:59 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 15:00:27 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	init_structs(t_mlx *mlx)
{
	mlx->player.rot_r = 0;
	mlx->player.rot_l = 0;
	mlx->player.up = 0;
	mlx->player.down = 0;
	mlx->player.left = 0;
	mlx->player.right = 0;
	mlx->player.inside = 0;
	mlx->player.using = 0;
	mlx->player.speed = 0;
	mlx->player.use_phone = 0;
	mlx->player.biking = -1;
	mlx->tmaxkeys = 0;
	mlx->bag_status = 0;
	mlx->dialog = 1;
	mlx->wazing = -1;
	mlx->msg = NULL;
	mlx->started = 0;
	mlx->crashed = 0;
}




























int	is_good(char c)
{
	if (c == '1' || c == ' ')
		return (1);
	return (0);
}

char	**copy_map(t_mlx *mlx)
{
	char	**map;
	int		i;
	int		j;

	i = -1;
	j = -1;
	map = ft_calloc(sizeof(char *), mlx->map_y + 5);
	if (!map)
		exit_game_light(mlx, NULL);
	while (++i < mlx->map_y + 4)
	{
		map[i] = ft_calloc(sizeof(char), mlx->map_x + 5);
		ft_memset(map[i], ' ', mlx->map_x + 4);
		map[i][mlx->map_x + 3] = '\n';
	}
	while (++j < mlx->map_y)
	{
		i = -1;
		while (++i < mlx->map_x)
		{
			if (mlx->map[j][i] >= 32)
				map[j + 2][i + 2] = mlx->map[j][i];
		}
	}
	return (map);
}

int	check_surround_cells(char **test_map)
{
	int	i;
	int	j;

	i = -1;
	while (test_map[++i])
	{
		j = -1;
		while (test_map[i][++j])
		{
			if (test_map[i][j] == 32)
			{
				if (!is_good(test_map[i + 1][j]) || !is_good(test_map[i - 1][j])
					|| !is_good(test_map[i][j + 1])
					|| !is_good(test_map[i][j - 1]))
					return (1);
			}
		}
	}
	return (0);
}

void	surround_map(t_mlx *mlx, char **map)
{
	int	i;

	i = -1;
	while (++i <= mlx->map_x + 2)
	{
		map[0][i] = '1';
		map[mlx->map_y + 3][i] = '1';
	}
	i = -1;
	while (++i <= mlx->map_y + 3)
	{
		map[i][0] = '1';
		map[i][mlx->map_x + 2] = '1';
	}
}

void	check_map_borders(t_mlx *mlx, char **data)
{
	char	**test_map;

	test_map = copy_map(mlx);
	surround_map(mlx, test_map);
	if (check_surround_cells(test_map))
	{
		error_message("Map is not closed.\n", NULL);
		free_map(test_map);
		free_map(data);
		exit_game(mlx);
	}
	free_map(test_map);
}













void	set_player_dir(t_mlx *mlx, int dir[2], double plane[2], int y)
{
	int	x;

	mlx->player.dir_x = dir[0];
	mlx->player.dir_y = dir[1];
	mlx->player.plane_x = plane[0];
	mlx->player.plane_y = plane[1];
	x = 0;
	while (mlx->map[y][x] && !ft_strchr("NSWE", mlx->map[y][x]))
		x++;
	mlx->player.pos_x = x + 0.5f;
	mlx->player.pos_y = y + 0.5f;
}

void	place_player_on_map(t_mlx *mlx)
{
	int		y;

	y = -1;
	while (++y < mlx->map_y)
	{
		if (ft_strchr(mlx->map[y], 'N'))
			set_player_dir(mlx, (int []){0, -1}, (double []){FOV, 0}, y);
		else if (ft_strchr(mlx->map[y], 'S'))
			set_player_dir(mlx, (int []){0, 1}, (double []){-FOV, 0}, y);
		else if (ft_strchr(mlx->map[y], 'E'))
			set_player_dir(mlx, (int []){1, 0}, (double []){0, FOV}, y);
		else if (ft_strchr(mlx->map[y], 'W'))
			set_player_dir(mlx, (int []){-1, 0}, (double []){0, -FOV}, y);
	}
}

void	ft_map_height(t_mlx *mlx, char **data)
{
	int		i;
	int		len;
	int		row;

	i = 0;
	len = 0;
	row = 0;
	while (data[i])
	{
		if (is_mapline_ok(data[i]))
		{
			if (len < (int)ft_strlen(data[i]))
				len = (int)ft_strlen(data[i]);
			row++;
		}
		i++;
	}
	mlx->map_y = row;
	mlx->map_x = len - 1;
}

void	ft_fill_map(t_mlx *mlx, char **data)
{
	int		i;
	int		y;

	ft_map_height(mlx, data);
	mlx->map = ft_calloc(sizeof(char *), mlx->map_y + 1);
	if (!mlx->map)
		exit_game_light(mlx, data);
	i = 0;
	y = 0;
	while (data[i])
	{
		if (is_mapline_ok(data[i]))
			mlx->map[y++] = ft_strdup(data[i]);
		i++;
	}
	mlx->map[y] = NULL;
}













void	error_message(char *msg, char *line)
{
	ft_putstr_fd("Error.\n", 2);
	ft_putstr_fd(msg, 2);
	if (line)
		ft_putstr_fd(line, 2);
}

int	get_next_color(char *str)
{
	char	*buf;
	int		value;
	int		i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (i == 0)
		return (-1);
	buf = ft_substr(str, 0, i);
	value = ft_atoi(buf);
	free(buf);
	return (value);
}


//Check if the color line only contain valid chars
int	is_colorline_ok(char *str)
{
	int	i;
	int	nbr;

	i = -1;
	nbr = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			nbr++;
		else if (!ft_isdigit(str[i]) && ft_isprint(str[i]))
			return (-1);
	}
	return (nbr);
}

//Check if the map line only contain valid chars
int	is_mapline_ok(char *line)
{
	while (*line == 32)
		line++;
	while (*line)
	{
		if (!ft_strchr("0123DJANSWE ", *line) && *line > 32)
			return (0);
		line++;
	}
	return (1);
}

int	is_asset(char *line)
{
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		return (1);
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (2);
	return (0);
}











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
		error_message("Assets are missing. Check textures and colors.\n", NULL);
		return (1);
	}
	return (0);
}

//Check if map file is properly formated
void	check_assets(t_mlx *mlx, char **data)
{
	if (check_map(data) || check_items(data))
		exit_game_light(mlx, data);
}










//Check the extension of the map
void	check_map_ext(t_mlx *mlx)
{
	int		i;
	char	*ext;

	i = 1;
	ext = ".cub";
	if (ft_strlen(mlx->mapname) < 5
		|| mlx->mapname[ft_strlen(mlx->mapname) - 5] == '/')
	{
		error_message("Please provide a correct map.\n", NULL);
		exit_game_light(mlx, NULL);
	}
	while (++i < 5)
	{
		if (mlx->mapname[ft_strlen(mlx->mapname) - i] != ext[4 - i])
		{
			error_message("Problem with map extension.\n", NULL);
			exit_game_light(mlx, NULL);
		}
	}
}

//Return the number of useful lines
int	file_size(t_mlx *mlx, int *fd)
{
	char	*line;
	int		i;

	i = 0;
	*fd = open(mlx->mapname, O_RDONLY);
	if (*fd == -1)
	{
		error_message("Check the map file.\n", NULL);
		exit_game_light(mlx, NULL);
	}
	line = get_next_line(*fd);
	while (line)
	{
		if (*line >= 32)
				i++;
		free(line);
		line = get_next_line(*fd);
	}
	close(*fd);
	*fd = open(mlx->mapname, O_RDONLY);
	return (i);
}

//Return the content of the map file
char	**get_data_from_file(t_mlx *mlx)
{
	char	**data;
	char	*line;
	int		fd;
	int		i;

	data = ft_calloc(sizeof(char *), file_size(mlx, &fd) + 1);
	if (!data)
		exit_game_light(mlx, data);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (*line >= 32)
			data[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (data);
}



void	free_map(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		free(map[y++]);
	free(map);
}

void	exit_game_light(t_mlx *mlx, char **data)
{
	(void)mlx;
	if (data)
		free_map(data);
	exit(1);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		error_message("Mlx initialization failed.\n", NULL);
		exit(1);
	}
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	mlx->display.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->display.addr = mlx_get_data_addr(mlx->display.img,
			&mlx->display.bits_per_pixel,
			&mlx->display.line_length, &mlx->display.endian);
}


void	ft_parsing(t_mlx *mlx)
{
	char	**data;

	init_structs(mlx);
	check_map_ext(mlx);
	data = get_data_from_file(mlx);
	check_assets(mlx, data);
	init_mlx(mlx);
	get_textures(mlx);
	fetch_assets(mlx, data);
	place_player_on_map(mlx);
	free_map(data);
}

void	ft_change_map(t_mlx *mlx)
{
	char	**data;

	check_map_ext(mlx);
	data = get_data_from_file(mlx);
	check_assets(mlx, data);
	fetch_assets(mlx, data);
	free_map(data);
}

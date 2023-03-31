/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/31 03:12:25 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	frames(t_mlx *mlx)
{
	ft_display(mlx);
	input_manager(mlx);
	// DISPLAY THE IMG
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->display.img, 0, 0);
	return (0);
}

int	exit_hook(t_mlx *mlx)
{
	exit_game(mlx);
	return (0);
}

void	fill_wall_tex(t_mlx *mlx, t_display *texture, char *line)
{
	char *str;

	str = ft_strnstr(line, "./", ft_strlen(line));
	str = ft_substr((const char *)str, 0, ft_strlen(str) - 2);
	if (!str || !ft_strnstr(str, ".xpm", ft_strlen(str)))
	{
		printf("Error.\n");
		printf("Check this line provided in the map file : %s", line);
		exit_hook(mlx);
	}
	printf("texture is : %s\n", str);
	texture->img = mlx_xpm_file_to_image(mlx->mlx, str, &texture->tex_width, &texture->tex_height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
	free(str);
}

void	get_wall_textures(t_mlx *mlx, int fd)
{
	char	*line;
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line || nbr == 4)
			break ;
		if (ft_strnstr(line, "NO", ft_strlen(line)) != NULL)
		{
			fill_wall_tex(mlx, &mlx->NO_tex, line);
			nbr++;
		}
		else if (ft_strnstr(line, "SO", ft_strlen(line)) != NULL)
		{
			fill_wall_tex(mlx, &mlx->SO_tex, line);
			nbr++;
		}
		else if (ft_strnstr(line, "WE", ft_strlen(line)) != NULL)
		{
			fill_wall_tex(mlx, &mlx->WE_tex, line);
			nbr++;
		}
		else if (ft_strnstr(line, "EA", ft_strlen(line)) != NULL)
		{
			fill_wall_tex(mlx, &mlx->EA_tex, line);
			nbr++;
		}
		free(line);
		i++;
	}
	if (nbr != 4)
	{
		printf("error in wall textures\n");
		exit_hook(mlx);
	}
	printf("final line in wall is : %s\n", line);
	free(line);
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

void	get_colors(t_mlx *mlx, int fd)
{
	char	*line;
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (1)
	{
		if (nbr == 2)
			break ;
		line = get_next_line(fd);
		if (is_asset(line) && ft_strchr(line, 'F'))
		{
			mlx->color_f = fill_color(line);
			nbr++;
		}
		else if (ft_strnstr(line, "C", ft_strlen(line)) != NULL)
		{
			mlx->color_c = fill_color(line);
			nbr++;
		}
		free(line);
		i++;
	}
}

void	ft_parsing(t_mlx *mlx)
{
	int	fd;

	check_assets(mlx);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	mlx->display.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->display.addr = mlx_get_data_addr(mlx->display.img, &mlx->display.bits_per_pixel,
			&mlx->display.line_length, &mlx->display.endian);
	fd = open(mlx->mapname, O_RDONLY);
	ft_map_height(mlx);
	get_wall_textures(mlx, fd);
	get_colors(mlx, fd);
	ft_fill_map(mlx, fd);
	place_player_on_map(mlx);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	mlx.player.planeX = 0;
	mlx.player.planeY = FOV;

	if (ac != 2)
		return (1);
	mlx.mapname = av[1];

	ft_parsing(&mlx);

	// INIT VARS
	mlx.player.rot_r = 0;
	mlx.player.rot_l = 0;
	mlx.player.up = 0;
	mlx.player.down = 0;
	mlx.player.left = 0;
	mlx.player.right = 0;

	printf("Error. The value of one of your color is wrong.\n");
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);

	printf("Error. The value of one of your color is wrong.\n");
	mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);

}

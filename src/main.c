/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/28 19:48:28 by bchabot          ###   ########.fr       */
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

int	mouse_hook(int key, t_mlx *mlx)
{
	(void)mlx;
	//printf("key:%d\n", key);
	if (key == 1)
		printf("\e[2APAN                            \n                                \n");
	return (0);
}

void	fill_wall_tex(t_mlx *mlx, t_display *texture, char *line)
{
	char *str;

	str = ft_strnstr(line, "./", ft_strlen(line));
	str = ft_substr((const char *)str, 0, ft_strlen(str) - 2);
	texture->img = mlx_xpm_file_to_image(mlx->mlx, str, &texture->tex_width, &texture->tex_height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
	free(str);
}

void	get_wall_textures(t_mlx *mlx)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(mlx->mapname, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nMap file does not exist or is empty, try again.");
		exit(0);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strnstr(line, "NO", ft_strlen(line)) != NULL)
			fill_wall_tex(mlx, &mlx->NO_tex, line);
		else if (ft_strnstr(line, "SO", ft_strlen(line)) != NULL)
			fill_wall_tex(mlx, &mlx->SO_tex, line);
		else if (ft_strnstr(line, "WE", ft_strlen(line)) != NULL)
			fill_wall_tex(mlx, &mlx->WE_tex, line);
		else if (ft_strnstr(line, "EA", ft_strlen(line)) != NULL)
			fill_wall_tex(mlx, &mlx->EA_tex, line);
		free(line);
		i++;
	}
	close(fd);
}
/*
int	fill_color(int color, char *line)
{
}

void	get_colors(t_mlx *mlx)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(mlx->mapname, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nMap file does not exist or is empty, try again.");
		exit(0);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strnstr(line, "F", ft_strlen(line)) != NULL)
			mlx->color_f = fill_color(mlx->color_f, line);
		else if (ft_strnstr(line, "C", ft_strlen(line)) != NULL)
			mlx->color_c = fill_color(mlx->color_f, line);
		free(line);
		i++;
	}
	close(fd);
}
*/
void	ft_parsing(t_mlx *mlx)
{
	check_map_ext(mlx);

	ft_fill_map(mlx);
	place_player_on_map(mlx, mlx->map);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	mlx->display.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->display.addr = mlx_get_data_addr(mlx->display.img, &mlx->display.bits_per_pixel,
			&mlx->display.line_length, &mlx->display.endian);

	// GET TEXTURES WALL
	get_wall_textures(mlx);
	//get_colors(mlx);
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

	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);

	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);

}

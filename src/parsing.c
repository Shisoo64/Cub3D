/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 23:37:44 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/03 23:37:44 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	check_map_ext(t_mlx *v)
{
	int		i;
	char	*ext;

	i = 1;
	ext = ".cub";
	if (ft_strlen(v->mapname) < 5
		|| v->mapname[ft_strlen(v->mapname) - 5] == '/')
	{
		ft_printf("Error\nNo map name!\n");
		exit(1);
	}
	while (++i < 5)
		if (v->mapname[ft_strlen(v->mapname) - i] != ext[4 - i])
		{
			ft_printf("Error\nProblem with map extension.\n");
			exit (1);
		}
}

int	file_size(t_mlx *mlx)
{
	char 	*line;
	int		i;
	int		fd;

	i = 0;
	fd = open(mlx->mapname, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (*line >= 32)
				i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

char **get_data_from_file(t_mlx *mlx)
{
	char	**data;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(mlx->mapname, O_RDONLY);
	if (fd == -1)
	{
		error_message("Check the map file.", NULL);
		return (NULL);
	}
	data = malloc(sizeof(char *) * file_size(mlx) + 1);
	line = get_next_line(fd);
	while (line)
	{
		if (*line >= 32)
		{
			data[i] = ft_strdup(line);
			i++;
		}
		line = get_next_line(fd);
	}
	data[i] = NULL;
	close(fd);
	return (data);
}

void	ft_parsing(t_mlx *mlx)
{
	char	**data;

	check_map_ext(mlx);
	data = get_data_from_file(mlx);
	print_map(data);
	check_assets(mlx, data);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	mlx->display.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->display.addr = mlx_get_data_addr(mlx->display.img, &mlx->display.bits_per_pixel,
			&mlx->display.line_length, &mlx->display.endian);
	fetch_assets(mlx);
}

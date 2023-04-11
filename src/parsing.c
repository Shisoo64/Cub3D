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

#include "includes/cub3D.h"

void	check_map_ext(t_mlx *v)
{
	int		i;
	char	*ext;

	i = 1;
	ext = ".cub";
	if (ft_strlen(v->mapname) < 5
		|| v->mapname[ft_strlen(v->mapname) - 5] == '/')
	{
		error_message("Please provide a correct map.", NULL);
		exit_game_light(v);
	}
	while (++i < 5)
	{
		if (v->mapname[ft_strlen(v->mapname) - i] != ext[4 - i])
		{
			error_message("Problem with map extension.", NULL);
			exit_game_light(v);
		}
	}
}

int	file_size(t_mlx *mlx)
{
	char	*line;
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

char	**get_data_from_file(t_mlx *mlx)
{
	char	**data;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(mlx->mapname, O_RDONLY);
	if (fd == -1)
	{
		error_message("Check the map file.\n", NULL);
		exit_game_light(mlx);
	}
	data = ft_calloc(sizeof(char *), file_size(mlx) + 1);
	if (!data)
		exit_game_light(mlx);
	line = get_next_line(fd);
	while (line)
	{
		if (*line >= 32)
		{
			data[i] = ft_strdup(line);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (data);
}

void	ft_parsing(t_mlx *mlx)
{
	char	**data;

	check_map_ext(mlx);
	data = get_data_from_file(mlx);
	check_assets(mlx, data);
	fetch_assets(mlx, data);
	free_map(data);
}

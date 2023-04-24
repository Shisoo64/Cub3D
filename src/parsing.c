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
		exit(1);
	}
	while (++i < 5)
	{
		if (mlx->mapname[ft_strlen(mlx->mapname) - i] != ext[4 - i])
		{
			error_message("Problem with map extension.\n", NULL);
			exit(1);
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
		exit(1);
	}
	line = get_next_line(*fd);
	while (line)
	{
		if (*line >= 32 || *line == 10)
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
		exit_game_light(data);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (*line >= 32 || *line == 10)
			data[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (data);
}

void	ft_parsing(t_mlx *mlx)
{
	char	**data;

	check_map_ext(mlx);
	data = get_data_from_file(mlx);
	check_assets(data);
	init_mlx(mlx);
	fetch_assets(mlx, data);
	free_map(data);
}

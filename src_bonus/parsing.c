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
	if (mlx->player_nb < 1)
	{
		error_message("Player number is erroneous, check map.\n", NULL);
		free_map(data);
		exit_game(mlx);
	}
	free_map(data);
}

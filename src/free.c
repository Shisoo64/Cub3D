/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:52:00 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/24 16:03:00 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	free_map(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		free(map[y++]);
	free(map);
}

void	free_img(t_mlx *mlx)
{
	if (mlx->ea_tex.img)
		mlx_destroy_image(mlx->mlx, mlx->ea_tex.img);
	if (mlx->we_tex.img)
		mlx_destroy_image(mlx->mlx, mlx->we_tex.img);
	if (mlx->no_tex.img)
		mlx_destroy_image(mlx->mlx, mlx->no_tex.img);
	if (mlx->so_tex.img)
		mlx_destroy_image(mlx->mlx, mlx->so_tex.img);
	if (mlx->display.img)
		mlx_destroy_image(mlx->mlx, mlx->display.img);
}

void	exit_game(t_mlx *mlx, char **data)
{
	free_map(data);
	free_img(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

void	exit_game_light(char **data)
{
	if (data)
		free_map(data);
	exit(1);
}

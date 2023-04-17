/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:52:00 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/16 12:39:00 by bchabot          ###   ########.fr       */
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

void	free_img(t_mlx *v)
{
	mlx_destroy_image(v->mlx, v->ea_tex.img);
	mlx_destroy_image(v->mlx, v->we_tex.img);
	mlx_destroy_image(v->mlx, v->no_tex.img);
	mlx_destroy_image(v->mlx, v->so_tex.img);
	mlx_destroy_image(v->mlx, v->display.img);
}

void	exit_game(t_mlx *mlx)
{
	free_map(mlx->map);
	free_img(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}

void	exit_game_light(t_mlx *mlx, char **data)
{
	(void)mlx;
	free_map(data);
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:52:00 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/31 02:53:08 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_map(t_mlx *mlx, char **map)
{
	int	y;

	y = 0;
	while (y < mlx->map_y)
		free(map[y++]);
	free(map);
}

void	free_img(t_mlx *v)
{
	mlx_destroy_image(v->mlx, v->EA_tex.img);
	mlx_destroy_image(v->mlx, v->WE_tex.img);
	mlx_destroy_image(v->mlx, v->NO_tex.img);
	mlx_destroy_image(v->mlx, v->SO_tex.img);
	mlx_destroy_image(v->mlx, v->display.img);
}

void	exit_game_light(t_mlx *mlx, int fd)
{
	close(fd);
	free(mlx->mlx);
	exit(1);
}

void	exit_game(t_mlx *mlx)
{
	free_map(mlx, mlx->map);
	free_img(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(1);
}

/*
void	exit_game_light(t_mlx *mlx, int map)
{
	if (map)
		free_map(mlx, mlx->map);
	free_img(mlx);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}
*/

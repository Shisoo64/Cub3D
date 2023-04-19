/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:52:00 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 16:11:07 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

/*
void	free_map(t_mlx *mlx, char **map)
{
	int	y;

	y = 0;
	while (y < mlx->map_y)
		free(map[y++]);
	free(map);
}
*/

void	free_img(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->in_wall.img);
	mlx_destroy_image(mlx->mlx, mlx->in_wall2.img);
	mlx_destroy_image(mlx->mlx, mlx->in_door_tex.img);
	mlx_destroy_image(mlx->mlx, mlx->handbag.img);
	mlx_destroy_image(mlx->mlx, mlx->bat_tex.img);
	mlx_destroy_image(mlx->mlx, mlx->bat2_tex.img);
	mlx_destroy_image(mlx->mlx, mlx->bat3_tex.img);
	mlx_destroy_image(mlx->mlx, mlx->door_tex.img);
	mlx_destroy_image(mlx->mlx, mlx->hand.img);
	mlx_destroy_image(mlx->mlx, mlx->hand2.img);
	mlx_destroy_image(mlx->mlx, mlx->phone.img);
	mlx_destroy_image(mlx->mlx, mlx->waze.img);
	mlx_destroy_image(mlx->mlx, mlx->bike.img);
	mlx_destroy_image(mlx->mlx, mlx->bike_wheel.img);
	mlx_destroy_image(mlx->mlx, mlx->crash.img);
	mlx_destroy_image(mlx->mlx, mlx->startscreen.img);
}

void	free_sprt(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->jul.tex.img);
	mlx_destroy_image(mlx->mlx, mlx->sch.tex.img);
	mlx_destroy_image(mlx->mlx, mlx->bag.tex.img);
	mlx_destroy_image(mlx->mlx, mlx->tmax.tex.img);
	mlx_destroy_image(mlx->mlx, mlx->no_tex.img);
	mlx_destroy_image(mlx->mlx, mlx->so_tex.img);
	mlx_destroy_image(mlx->mlx, mlx->we_tex.img);
	mlx_destroy_image(mlx->mlx, mlx->ea_tex.img);
	mlx_destroy_image(mlx->mlx, mlx->display.img);
}

void	exit_game(t_mlx *mlx)
{
	system("killall paplay");
	free_map(mlx->map);
	free_img(mlx);
	free_sprt(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	exit(0);
}
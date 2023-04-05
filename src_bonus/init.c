/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:47:59 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/05 16:39:30 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_structs(t_mlx *mlx)
{
	mlx->mapname = "maps/map.cub";
	mlx->player.rot_r = 0;
	mlx->player.rot_l = 0;
	mlx->player.up = 0;
	mlx->player.down = 0;
	mlx->player.left = 0;
	mlx->player.right = 0;
	mlx->player.inside = 0;
	mlx->player.using = 0;
	mlx->player.speed = 0;
	mlx->player.biking = -1;
	mlx->tmaxkeys = 0;
	mlx->bag_status = 0;
	mlx->dialog = 1;
	mlx->message = NULL;
	mlx->started = 0;
	mlx->crashed = 0;
}

void	ft_parsing(t_mlx *mlx)
{
	init_structs(mlx);
	mlx->map = create_map(mlx);
	place_player_on_map(mlx, mlx->map);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	mlx->display.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->display.addr = mlx_get_data_addr(mlx->display.img,
			&mlx->display.bits_per_pixel,
			&mlx->display.line_length, &mlx->display.endian);
	get_textures(mlx);
}

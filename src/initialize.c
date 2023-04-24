/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:21:27 by bchabot           #+#    #+#             */
/*   Updated: 2023/04/24 17:17:14 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	init_mlx(t_mlx *mlx, char **data)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		error_message("Mlx initialization failed.\n", NULL);
		exit_game_light(data);
	}
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	if (mlx->win == NULL)
	{
		error_message("Mlx initialization failed.\n", NULL);
		exit_game_light(data);
	}
	mlx->display.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	if (mlx->display.img == NULL)
	{
		error_message("Mlx initialization failed.\n", NULL);
		exit_game_light(data);
	}
	mlx->display.addr = mlx_get_data_addr(mlx->display.img,
			&mlx->display.bits_per_pixel,
			&mlx->display.line_length, &mlx->display.endian);
}

void	init_data(t_mlx *mlx)
{
	mlx->player.rot_r = 0;
	mlx->player.rot_l = 0;
	mlx->player.up = 0;
	mlx->player.down = 0;
	mlx->player.left = 0;
	mlx->player.right = 0;
	mlx->player_nb = 0;
	mlx->no_tex.img = NULL;
	mlx->so_tex.img = NULL;
	mlx->we_tex.img = NULL;
	mlx->ea_tex.img = NULL;
}

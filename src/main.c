/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/06 23:33:37 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	frames(t_mlx *mlx)
{
	ft_display(mlx);
	input_manager(mlx);
	// DISPLAY THE IMG
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->display.img, 0, 0);
	return (0);
}

void init_data(t_mlx *mlx)
{
	mlx->player.rot_r = 0;
	mlx->player.rot_l = 0;
	mlx->player.up = 0;
	mlx->player.down = 0;
	mlx->player.left = 0;
	mlx->player.right = 0;

	mlx->NO_tex.img = NULL;
	mlx->SO_tex.img = NULL;
	mlx->WE_tex.img = NULL;
	mlx->EA_tex.img = NULL;
}

int	exit_hook(t_mlx *mlx)
{
	exit_game(mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
		return (1);
	mlx.mapname = av[1];
	init_data(&mlx);
	ft_parsing(&mlx);

	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);

	mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);

}

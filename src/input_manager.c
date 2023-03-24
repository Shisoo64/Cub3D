/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:59:47 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/24 15:15:00 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit_game(mlx);
	else if (mlx->started == 0)
		mlx->started = 1;
	else if (mlx->crashed == 1)
		exit_game(mlx);
	else if (key == KEY_ARROW_L || key == KEY_Q)
		mlx->player.rot_l = 1;
	else if (key == KEY_W)
		mlx->player.up = 1;
	else if (key == KEY_S)
		mlx->player.down = 1;
	else if (key == KEY_ARROW_R || key == KEY_E)
		mlx->player.rot_r = 1;
	else if (key == KEY_A)
		mlx->player.left = 1;
	else if (key == KEY_D)
		mlx->player.right = 1;
	else if (key == KEY_F)
		mlx->player.using = 1;

	// Stop biking
	if (mlx->player.biking == 1 && mlx->player.using && mlx->player.speed == 0)
	{
		mlx->player.biking = -1;
		mlx->player.using = 0;
		mlx->tmax.x = mlx->player.posX;
		mlx->tmax.y = mlx->player.posY;
	}

	return (0);
}

int	key_release(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit_game(mlx);
	else if (key == KEY_ARROW_L || key == KEY_Q)
		mlx->player.rot_l = 0;
	else if (key == KEY_W)
		mlx->player.up = 0;
	else if (key == KEY_S)
		mlx->player.down = 0;
	else if (key == KEY_ARROW_R || key == KEY_E)
		mlx->player.rot_r = 0;
	else if (key == KEY_A)
		mlx->player.left = 0;
	else if (key == KEY_D)
		mlx->player.right = 0;
	else if (key == KEY_F)
		mlx->player.using = -1;
	return (0);
}

int	input_manager(t_mlx *mlx)
{
	if (mlx->dialog != 0)
		return (0);
	if (mlx->player.inside != 1 && mlx->player.biking == 1)
		input_manager_bike(mlx);
	else
		input_manager_foot(mlx);
	return (0);
}

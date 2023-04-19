/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:59:47 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 16:22:06 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

int	key_press(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit_game(mlx);
	else if (mlx->started == 0)
	{
		mlx->started = 1;
		ft_playsound(0, NULL);
	}
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
	else if (key == KEY_M)
		mlx->player.use_phone = -1;
	return (0);
}

int	input_manager(t_mlx *mlx)
{
	if (mlx->dialog != 0)
		return (0);
	if (mlx->player.inside == 0 && mlx->player.biking == 1)
		input_manager_bike(mlx);
	else
		input_manager_foot(mlx);
	return (0);
}

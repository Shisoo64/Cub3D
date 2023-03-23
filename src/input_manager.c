/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:59:47 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/23 17:04:23 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int key, t_mlx *mlx)
{
	if (key == ESC)
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
	return (0);
}

int	input_manager(t_mlx *mlx)
{
	input_manager_foot(mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dialog_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:47:24 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 17:58:02 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D_bonus.h"

//draw the black box for dialogs
void	draw_dialog(t_mlx *mlx)
{
	int	y;
	int	x;

	y = WIN_H - (WIN_H / 5);
	while (++y <= WIN_H)
	{
		x = -1;
		while (++x <= WIN_W)
			my_mlx_pixel_put(&mlx->display, x, y, 0);
	}
}

//manage which character you're dialoguing with
void	ft_dialog(t_mlx *mlx)
{
	if (mlx->dialog == 0)
	{
		ft_playsound(0, NULL);
		return ;
	}
	if (mlx->dialog >= 1 && mlx->dialog < 10)
		starting_dialog(mlx);
	else if (mlx->dialog >= 10 && mlx->dialog < 20)
	{
		ft_playsound(1, "paplay ./sounds/dialog1.ogg &");
		jul_dialog(mlx);
	}
	else if (mlx->dialog >= 20 && mlx->dialog < 30)
		sch_dialog(mlx);
	draw_dialog(mlx);
}

//Control the start of the dialogs
void	ft_start_dialog(t_mlx *mlx)
{
	if (mlx->dialog == 0 && mlx->bag_status == 0 && ft_check_prox(mlx, mlx->jul))
	{
		mlx->msg = "Press F to talk to JuL";
		if (mlx->player.using == 1)
			mlx->dialog = 10;
	}
	else if (mlx->dialog == 0 && mlx->bag_status == 1
		&& ft_check_prox(mlx, mlx->sch))
	{
		mlx->msg = "Press F to talk to SCH";
		if (mlx->player.using == 1)
			mlx->dialog = 20;
	}
}

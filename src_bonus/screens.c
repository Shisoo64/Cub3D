/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:45:17 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/17 14:48:46 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_backdrop(t_mlx *mlx)
{
	int	y;
	int	x;
	int	sky;
	int	floor;

	sky = SKYCOLOR;
	floor = FLOORCOLOR;
	if (mlx->player.inside != 0)
	{
		sky = CEILINGCOLOR;
		floor = IN_FLOORCOLOR;
	}
	y = -1;
	while (++y <= WIN_H / 2)
	{
		x = -1;
		while (++x <= WIN_W)
			my_mlx_pixel_put(&mlx->display, x, y, sky);
	}
	while (++y <= WIN_H)
	{
		x = -1;
		while (++x <= WIN_W)
			my_mlx_pixel_put(&mlx->display, x, y, floor);
	}
}

void	start_screen(t_mlx *mlx)
{
	static int	i;

	ft_playsound(1, "paplay ./sounds/ovni.ogg &");
	if (i++ == 0)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->startscreen.img, 0, 0);
		mlx_string_put(mlx->mlx, mlx->win, WIN_W / 2 - 75, WIN_H - 225,
			0xffffff, "Press any key to start");
	}
	else if (i == 50000)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->startscreen.img, 0, 0);
	}
	if (i >= 100000)
		i = -1;
}

void	crash_screen(t_mlx *mlx)
{
	static int	i;

	if (i++ == 0)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->crash.img, 0, 0);
		mlx_string_put(mlx->mlx, mlx->win, WIN_W / 2 - 25, WIN_H - 70,
			0xffffff, "Press any key");
	}
	else if (i == 50000)
	{
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->crash.img, 0, 0);
	}
	if (i >= 100000)
		i = -1;
}

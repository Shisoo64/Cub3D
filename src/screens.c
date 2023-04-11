/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:45:17 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/11 15:22:21 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	draw_backdrop(t_mlx *mlx)
{
	int	y;
	int	x;

	y = -1;
	while (++y <= WIN_H / 2)
	{
		x = -1;
		while (++x <= WIN_W)
			my_mlx_pixel_put(&mlx->display, x, y, mlx->color_c);
	}
	while (++y <= WIN_H)
	{
		x = -1;
		while (++x <= WIN_W)
			my_mlx_pixel_put(&mlx->display, x, y, mlx->color_f);
	}
}

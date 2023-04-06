/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:48:53 by bchabot           #+#    #+#             */
/*   Updated: 2023/04/06 23:48:53 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_background(t_mlx *mlx)
{
	int	y;
	int	x;

	y = -1;
	while (++y <= 300)
	{
		x = -1;
		while (++x <= 300)
            my_mlx_pixel_put(&mlx->display, x, y, 0xbbb8b2);
	}
}

void    draw_minimap(t_mlx *mlx)
{
    draw_background(mlx);
    my_mlx_pixel_put(&mlx->display, mlx->player.posX, mlx->player.posY, 0x000000);
}
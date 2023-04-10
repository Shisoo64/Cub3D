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

void	draw_background(t_mlx *mlx, int pad_x, int pad_y)
{
	int	y;
	int	x;

	y = -1;
	while (++y <= mlx->map_y * 5)//WIN_H / 2)
	{
		x = -1;
		while (++x <= mlx->map_x * 6) //WIN_W / 5)
            my_mlx_pixel_put(&mlx->display, x + pad_x, y + pad_y, 0xbbb8b2);
	}
}

void draw_square(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < 6)
	{
		i = 0;
		while (i < 6)
		{
			my_mlx_pixel_put(&mlx->display, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void fill_minimap(t_mlx *mlx, int pad_x, int pad_y)
{
	int y;
	int x;
    // Loop through each cell in the map matrix*
	y = mlx->player.posY - 10;
	if (y < 0)
		y = 0;
    while (mlx->map[y] && y < mlx->player.posY + 10)
	{
		x = mlx->player.posX - 10;
		if (x < 0)
			x = 0;
        while (mlx->map[y][x] && x < mlx->player.posX + 10)
		{
			if (x > mlx->map_x)
				x = mlx->map_x;
			// Determine the color to use based on the cell value
			if (mlx->map[y][x] == '1')
				draw_square(mlx, x * 6 + pad_x, y * 6 + pad_y, 0x000000);
			else if (mlx->map[y][x] > 32)
				draw_square(mlx, x * 6 + pad_x, y * 6 + pad_y, 0xffffff);
			//my_mlx_pixel_put(&mlx->display, x + pad_x, y + pad_y, color);
			x++;
        }
		y++;
		if (y > mlx->map_y)
			y = mlx->map_y;
    }
}

void	draw_line(t_mlx *mlx, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX; // 10
	double deltaY = endY - beginY; // 0

	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		draw_square(mlx, pixelX, pixelY, color);
		//printf(" pixelX is %f\n", pixelX);
		//printf(" pixelY is %f\n", pixelY);
		//my_mlx_pixel_put(&mlx->display, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

void    draw_minimap(t_mlx *mlx, t_raycast *ray)
{
	int	pad_x;
	int	pad_y;
	
	pad_x = 0;
	pad_y = 0;

	(void)ray;
   	draw_background(mlx, pad_x, pad_y);
	fill_minimap(mlx, pad_x, pad_y);
    draw_square(mlx, (mlx->player.posX * 6) + pad_x, (mlx->player.posY * 6) + pad_y, 0x7EC0EE);
	//draw_line(mlx, (mlx->player.posX * 6) + pad_x, (mlx->player.posY * 6) + pad_y, (mlx->player.posX * 6) + pad_x + ray->sideDistX, (mlx->player.posY * 6) + pad_y + ray->sideDistY, 0x00a000);
	//draw_square(mlx, ray-> * 6 + pad_x, ray->raydirX * 6 + pad_y, 0x000000);
}
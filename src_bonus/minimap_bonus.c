/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:48:53 by bchabot           #+#    #+#             */
/*   Updated: 2023/04/20 12:15:59 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D_bonus.h"

void	draw_square(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	j = -1;
	while (++j < 5)
	{
		i = -1;
		while (++i < 5)
			my_mlx_pixel_put(&mlx->display, x + i, y + j, color);
	}
}

void	draw_background(t_mlx *mlx, int pad_x, int pad_y)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 21 * 5)
	{
		x = -1;
		while (++x < 10 * 5)
			draw_square(mlx, x + pad_x, y + pad_y, 0xbbb8b2);
	}
}

void	reset_coord_minimap(int *y, int *screen)
{
	*screen = 0;
	if (*y <= 0)
	{
		*screen = -*y;
		*y = 0;
	}
}

void	fill_minimap(t_mlx *mlx, int pad_x, int pad_y)
{
	int	y;
	int	x;
	int	screen[2];

	y = mlx->player.pos_y - 10;
	reset_coord_minimap(&y, &screen[1]);
	while (mlx->map[++y] && y < mlx->player.pos_y + 10)
	{
		x = mlx->player.pos_x - 5;
		reset_coord_minimap(&x, &screen[0]);
		while (mlx->map[y][x] && x < mlx->player.pos_x + 5)
		{
			if (x > mlx->map_x)
				x = mlx->map_x;
			if (ft_strchr("123JAD", mlx->map[y][x]))
				draw_square(mlx, screen[0] * 5 + pad_x,
					screen[1] * 5 + pad_y, 0x3c444c);
			else
				draw_square(mlx, screen[0] * 5 + pad_x,
					screen[1] * 5 + pad_y, 0xbbb8b2);
			screen[0]++;
			x++;
		}
		screen[1]++;
	}
}

void	ft_minimap_controller(t_mlx *mlx, int pad_x, int pad_y)
{
	if (mlx->player.use_phone == -1)
		mlx->wazing = -mlx->wazing;
	if (mlx->wazing == 1 && mlx->player.biking == -1)
	{
		draw_background(mlx, pad_x, pad_y);
		fill_minimap(mlx, pad_x, pad_y);
		put_img_transp(mlx, mlx->waze, WIN_W / 2 + 70, WIN_H - 233);
	}
}

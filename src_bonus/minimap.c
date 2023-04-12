/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:48:53 by bchabot           #+#    #+#             */
/*   Updated: 2023/04/12 15:36:13 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

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

/*
void	draw_player(t_mlx *mlx, int x, int y)
{
	int	player_x;
	int	player_y;

	if (x < 0)
		player_x = 4;
	else if (x > 0)
		player_x = 5;
	if (y < 0)
		player_y = 9;
	else if (y > 0)
		player_y = 10;
	draw_square(mlx, player_x * 6, player_y * 6, 0x7EC0EE);
}
*/

void	fill_minimap(t_mlx *mlx, int pad_x, int pad_y)
{
	int	y;
	int	x;
	int	x_screen;
	int	y_screen;
	int	player_x;
	int	player_y;

	player_x = 5;
	player_y = 10;
	y_screen = 0;
	y = mlx->player.pos_y - 10;
	if (y <= 0)
	{
		y_screen = -y;
		player_y = 9;
		y = 0;
	}
	while (mlx->map[y] && y < mlx->player.pos_y + 10)
	{
		x = mlx->player.pos_x - 5;
		//draw_player(mlx, x, y);
		x_screen = 0;
		if (x <= 0)
		{
			x_screen = -x;
			x = 0;
			player_x = 4;
		}
		draw_square(mlx, player_x * 5, player_y * 5, 0x05c8f7);
		while (mlx->map[y][x] && x < mlx->player.pos_x + 5)
		{
			if (x > mlx->map_x)
				x = mlx->map_x;
			// Determine the color to use based on the cell value
			if (ft_strchr("JAD", mlx->map[y][x]))
				draw_square(mlx, x_screen * 5 + pad_x, y_screen * 5 + pad_y, 0x9a40f7);
			else if (ft_strchr("123", mlx->map[y][x]))
				draw_square(mlx, x_screen * 5 + pad_x, y_screen * 5 + pad_y, 0x3c444c);
			else
				draw_square(mlx, x_screen * 5 + pad_x, y_screen * 5 + pad_y, 0xbbb8b2);
			x_screen++;
			x++;
		}
		y_screen++;
		y++;
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
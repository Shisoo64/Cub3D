/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:31 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 16:22:30 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

//	get the color of the pixel on the coordinates of the texture
int	my_mlx_get_color(t_display *texture, int x, int y)
{
	char	*color;

	if (y < 0)
		y = -y;
	color = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(int *)color);
}

void	my_mlx_pixel_put(t_display *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	put_img_transp(t_mlx *mlx, t_display img, int pad_x, int pad_y)
{
	int	y;
	int	x;
	int	color;

	y = -1;
	while (++y <= img.tex_height)
	{
		x = -1;
		while (++x <= img.tex_width)
		{
			color = my_mlx_get_color(&img, x, y);
			if (color != 0x00FF00)
				my_mlx_pixel_put(&mlx->display, x + pad_x, y + pad_y, color);
		}
	}
}

void	ft_playsound(int play, char *filename)
{
	static int	playing;

	if (play && !playing)
	{
		playing = 1;
		system(filename);
	}
	else if (play == 0 && playing)
	{
		playing = 0;
		system("killall paplay");
	}
}

void	ft_walk_anim(t_mlx *mlx)
{
	static int	i;

	if (mlx->player.biking == -1 && mlx->player.down)
	{
		if (i >= 0 && i <= 50)
			put_img_transp(mlx, mlx->hand, WIN_W / 2 - 228, WIN_H - 118);
		else if (mlx->bag_status != 1 && mlx->wazing != 1)
			put_img_transp(mlx, mlx->hand2, WIN_W / 2 + 70, WIN_H - 118);
		if (i++ == 100)
			i = 0;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:31 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/19 14:46:51 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//	get the color of the pixel on the coordinates of the texture
int    my_mlx_get_color(t_display *texture, int x, int y)
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
	int color;

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

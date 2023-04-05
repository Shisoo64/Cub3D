/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:31 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/04 10:04:25 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

//	get the color of the pixel on the coordinates of the texture
int	my_mlx_get_color(t_display *texture, int x, int y)
{
	char	*color;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:55:07 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/20 15:55:07 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line_sprt(t_display *texture, t_raycast *ray, int x, int coord[2])
{
	double	step;
	double	tex_pos;
	int		color;
	int		tex_y;
	int		y;

	step = 1.0 * texture->tex_height / ray->lineheight;
	tex_pos = (coord[0] - WIN_H / 2 + ray->lineheight / 2) * step;
	y = coord[0];
	ray->tex_x = texture->tex_width - ray->tex_x;
	while (y < coord[1])
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = my_mlx_get_color(texture, ray->tex_x, tex_y);
		if (color != 0x00FF00)
			my_mlx_pixel_put(ray->display, x, y, color);
		y++;
	}
}

/*
void    draw_line_sprite(t_display *texture, t_display *display, int x, int lineheight, int coord[2], int tex_x)
{
	double	step;
	double	tex_pos;
	int		color;
	int		tex_y;
	int		y;

	step = 1.0 * texture->tex_height / lineheight;
	tex_pos = (coord[0] - WIN_H / 2 + lineheight / 2) * step;
	y = coord[0];
	tex_x = texture->tex_width - tex_x;
	while (y < coord[1])
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = my_mlx_get_color(texture, tex_x, tex_y);
		if (color != 0x00FF00)
			my_mlx_pixel_put(display, x, y, color);
		y++;
	}
*/

void	ft_render_sprite(t_raycast *ray, t_mlx *mlx, t_sprite texture)
{
	int	stripe;
	int	draw_coord[2];
	double	spriteX;
	double	spriteY;

	spriteX = texture.x - mlx->player.pos_x;
	spriteY = texture.y - mlx->player.pos_y;

	double invDet = 1.0 / (mlx->player.plane_x * mlx->player.dir_y - mlx->player.dir_x * mlx->player.plane_y); //required for correct matrix multiplication

	double transformX = invDet * (mlx->player.dir_y * spriteX - mlx->player.dir_x * spriteY);
	double transformY = invDet * (-mlx->player.plane_y * spriteX + mlx->player.plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

	int spriteScreenX = (int)((WIN_W / 2) * (1 + transformX / transformY));

	//calculate height of the sprite on screen
	ray->lineheight = abs((int)(WIN_H * 1.2 / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
	//calculate lowest and highest pixel to fill in current stripe
	draw_coord[0] = -ray->lineheight / 2 + WIN_H / 2;
	if (draw_coord[0] < 0)
		draw_coord[0] = 0;
	draw_coord[1] = ray->lineheight / 2 + WIN_H / 2;
	if (draw_coord[1] >= WIN_H)
		draw_coord[1] = WIN_H - 1;

	//calculate width of the sprite
	int spriteWidth = abs((int)(WIN_H * 1.2 / (transformY)));
	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	if(drawStartX < 0)
		drawStartX = 0;
	int drawEndX = spriteWidth / 2 + spriteScreenX;
	if(drawEndX >= WIN_W)
		drawEndX = WIN_W - 1;

	//loop through every vertical stripe of the sprite on screen
	stripe = drawStartX;
	while (stripe < drawEndX)
	{
		ray->tex_x = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) *  texture.tex.tex_width / spriteWidth) / 256;
		if (transformY > 0 && stripe > 0 && stripe < WIN_W && transformY - 0.6 < ray->perpwalldists[stripe])
			draw_line_sprt(&texture.tex, ray, stripe, draw_coord);
		stripe++;
	}
}

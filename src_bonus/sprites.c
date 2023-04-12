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

void	display_sprite(t_raycast *ray, double pos[2], int draw_coord[2], t_sprite texture)
{
	int	stripe;
	int	sprt_width;
	int	sprt_screen_x;
	int	draw_start_x;
	int	draw_end_x;

	sprt_width = abs((int)(WIN_H * 1.2 / (pos[1])));
	sprt_screen_x = (int)((WIN_W / 2) * (1 + pos[0] / pos[1]));
	draw_start_x = -sprt_width / 2 + sprt_screen_x;
	draw_end_x = sprt_width / 2 + sprt_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	if (draw_end_x >= WIN_W)
		draw_end_x = WIN_W - 1;
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		ray->tex_x = (int)(256 * (stripe - (-sprt_width / 2 + sprt_screen_x)) \
			* texture.tex.tex_width / sprt_width) / 256;
		if (pos[1] > 0 && stripe > 0
			&& stripe < WIN_W && pos[1] - 0.6 < ray->perpwalldists[stripe])
			draw_line_sprt(&texture.tex, ray, stripe, draw_coord);
		stripe++;
	}
}

void	ft_render_sprite(t_raycast *ray, t_mlx *mlx, t_sprite texture)
{
	int		draw_coord[2];
	double	sprte_x;
	double	sprite_y;
	double	inv_det;
	double	pos[2];

	sprte_x = texture.x - mlx->player.pos_x;
	sprite_y = texture.y - mlx->player.pos_y;
	inv_det = 1.0 / (mlx->player.plane_x * mlx->player.dir_y - mlx->player.dir_x * mlx->player.plane_y);
	pos[0] = inv_det * (mlx->player.dir_y * sprte_x - mlx->player.dir_x * sprite_y);
	pos[1] = inv_det * (-mlx->player.plane_y * sprte_x + mlx->player.plane_x * sprite_y);
	ray->lineheight = abs((int)(WIN_H * 1.2 / (pos[1])));
	draw_coord[0] = -ray->lineheight / 2 + WIN_H / 2;
	if (draw_coord[0] < 0)
		draw_coord[0] = 0;
	draw_coord[1] = ray->lineheight / 2 + WIN_H / 2;
	if (draw_coord[1] >= WIN_H)
		draw_coord[1] = WIN_H - 1;
	display_sprite(ray, pos, draw_coord, texture);
}

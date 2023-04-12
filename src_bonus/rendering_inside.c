/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_inside.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:53:27 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/05 15:53:27 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line_in(t_display *texture, t_raycast *ray, int x, int coord[2])
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
		my_mlx_pixel_put(ray->display, x, y, color);
		y++;
	}
}

//Check wich wall type it hit and show the apropriate texture
void	ft_wall_hit_in(t_raycast *ray, t_mlx *mlx, int draw_coord[2], int x)
{
	if (ray->hit_type == 1)
		draw_line_in(&mlx->in_wall, ray, x, draw_coord);
	else if (ray->hit_type == 2)
		draw_line_in(&mlx->in_wall2, ray, x, draw_coord);
	else if (ray->hit_type == 999)
	{
		if (ray->perpwalldists[x] <= 0.15)
		{
			if (mlx->player.using == 1)
				close_door(mlx);
			else
				mlx->message = "Press F to open door";
		}
		draw_line_in(&mlx->in_door_tex, ray, x, draw_coord);
	}
}

//Get line on texture
void	get_tex_line(t_raycast *ray, t_mlx *mlx, int draw_coord[2], int x)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = mlx->player.pos_y + ray->perpwalldists[x] * ray->raydir_y;
	else
		wall_x = mlx->player.pos_x + ray->perpwalldists[x] * ray->raydir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)mlx->in_wall.tex_width);
	if (ray->side == 0 && ray->raydir_x > 0)
		ray->tex_x = mlx->in_wall.tex_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		ray->tex_x = mlx->in_wall.tex_width - ray->tex_x - 1;
	ft_wall_hit_in(ray, mlx, draw_coord, x);
}

// Draw a vertical line of pixels in the img
void	ft_render_in_vline(t_raycast *ray, t_mlx *mlx, int x)
{
	int	draw_coord[2];

	if (ray->side == 0)
		ray->perpwalldists[x] = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->perpwalldists[x] = (ray->sidedist_y - ray->deltadist_y);
	ray->lineheight = (int)(WIN_H / ray->perpwalldists[x]);
	draw_coord[0] = -ray->lineheight / 2 + WIN_H / 2;
	if (draw_coord[0] < 0)
		draw_coord[0] = 0;
	draw_coord[1] = ray->lineheight / 2 + WIN_H / 2;
	if (draw_coord[1] >= WIN_H)
		draw_coord[1] = WIN_H - 1;
	get_tex_line(ray, mlx, draw_coord, x);
}

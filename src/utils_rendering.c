/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rendering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:24:13 by bchabot           #+#    #+#             */
/*   Updated: 2023/04/18 15:27:16 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	draw_line_tex(t_display *tex, t_raycast *ray, int x, int draw_coord[2])
{
	double	step;
	double	tex_pos;
	int		color;
	int		tex_y;
	int		y;

	step = 1.0 * tex->tex_height / ray->lineheight;
	tex_pos = (draw_coord[0] - WIN_H / 2 + ray->lineheight / 2) * step;
	y = draw_coord[0];
	ray->tex_x = tex->tex_width - ray->tex_x;
	while (y < draw_coord[1])
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = my_mlx_get_color(tex, ray->tex_x, tex_y);
		my_mlx_pixel_put(ray->display, x, y, color);
		y++;
	}
}

//calculate step and initial sideDist
void	ft_sidedist_calc(t_mlx *mlx, t_raycast *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (mlx->player.pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - mlx->player.pos_x)
			* ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (mlx->player.pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - mlx->player.pos_y)
			* ray->deltadist_y;
	}
}

t_display	identify_wall(t_mlx *mlx, t_raycast *ray)
{
	if (ray->side == 1)
	{
		if (ray->step_y > 0)
			return (mlx->no_tex);
		else
			return (mlx->so_tex);
	}
	else
	{
		if (ray->step_x > 0)
			return (mlx->we_tex);
		else
			return (mlx->ea_tex);
	}
}

void	get_tex_line(t_raycast *ray, t_mlx *mlx, int draw_coord[2], int x)
{
	t_display	texture;
	double		wall_x;

	texture = identify_wall(mlx, ray);
	ray->lineheight = (int)(WIN_H / ray->perpwalldists[x]);
	if (ray->side == 0)
		wall_x = mlx->player.pos_y + ray->perpwalldists[x] * ray->raydir_y;
	else
		wall_x = mlx->player.pos_x + ray->perpwalldists[x] * ray->raydir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)texture.tex_width);
	if (ray->side == 0 && ray->raydir_x > 0)
		ray->tex_x = mlx->we_tex.tex_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		ray->tex_x = mlx->so_tex.tex_width - ray->tex_x - 1;
	draw_line_tex(&texture, ray, x, draw_coord);
}

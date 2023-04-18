/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:55:52 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/17 14:55:52 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

// Draw the background colors (floor and ceiling).
void	draw_backdrop(t_mlx *mlx)
{
	int	y;
	int	x;

	y = -1;
	while (++y <= WIN_H / 2)
	{
		x = -1;
		while (++x <= WIN_W)
			my_mlx_pixel_put(&mlx->display, x, y, mlx->color_c);
	}
	while (++y <= WIN_H)
	{
		x = -1;
		while (++x <= WIN_W)
			my_mlx_pixel_put(&mlx->display, x, y, mlx->color_f);
	}
}

// Draw a vertical line of pixels in the img.
void	ft_render_vline(t_raycast *ray, t_mlx *mlx, int x)
{
	int		draw_coord[2];
	double	perpwalldist;

	if (ray->side == 0)
		perpwalldist = (ray->sidedist_x - ray->deltadist_x);
	else
		perpwalldist = (ray->sidedist_y - ray->deltadist_y);
	ray->lineheight = (int)(WIN_H / perpwalldist);
	ray->perpwalldists[x] = perpwalldist;
	draw_coord[0] = -ray->lineheight / 2 + WIN_H / 2;
	if (draw_coord[0] < 0)
		draw_coord[0] = 0;
	draw_coord[1] = ray->lineheight / 2 + WIN_H / 2;
	if (draw_coord[1] >= WIN_H)
		draw_coord[1] = WIN_H - 1;
	get_tex_line(ray, mlx, draw_coord, x);
}

// Digital Differential Analysis
// Iterate through each line in the grid the ray intersect until it hit a wall.
void	ft_dda(t_mlx *mlx, t_raycast *ray)
{
	while (1)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (mlx->map[ray->map_y][ray->map_x]
			&& mlx->map[ray->map_y][ray->map_x] == '1')
			break ;
	}
}

void	ft_raycast(t_mlx *mlx, t_raycast *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_W - 1;
	ray->raydir_x = mlx->player.dir_x + mlx->player.plane_x * camera_x;
	ray->raydir_y = mlx->player.dir_y + mlx->player.plane_y * camera_x;
	ray->map_x = (int)mlx->player.pos_x;
	ray->map_y = (int)mlx->player.pos_y;
	if (ray->raydir_x == 0)
		ray->deltadist_x = 1000;
	else
		ray->deltadist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->deltadist_y = 1000;
	else
		ray->deltadist_y = fabs(1 / ray->raydir_y);
	ft_sidedist_calc(mlx, ray);
	ft_dda(mlx, ray);
	ft_render_vline(ray, mlx, x);
}

void	ft_display(t_mlx *mlx)
{
	t_raycast	ray;
	int			x;

	ray.display = &mlx->display;
	draw_backdrop(mlx);
	x = 0;
	while (x < WIN_W)
		ft_raycast(mlx, &ray, x++);
}

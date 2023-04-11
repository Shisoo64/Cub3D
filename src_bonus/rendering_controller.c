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

#include "rendering.h"

//Check if ray has hit a wall
//and set the type of wall that was hit
int	check_wall_ext(t_mlx *mlx, t_raycast *ray)
{
	if (mlx->map[ray->map_y][ray->map_x]
		&& mlx->map[ray->map_y][ray->map_x] == 'J')
	{
		ray->hit_type = 90;
		return (1);
	}
	else if (mlx->map[ray->map_y][ray->map_x]
		&& mlx->map[ray->map_y][ray->map_x] == 'A')
	{
		ray->hit_type = 91;
		return (1);
	}
	else if (mlx->map[ray->map_y][ray->map_x]
		&& mlx->map[ray->map_y][ray->map_x] == 'D')
	{
		ray->hit_type = 999;
		return (1);
	}
	return (0);
}

int	check_wall(t_mlx *mlx, t_raycast *ray)
{
	if (mlx->map[ray->map_y][ray->map_x]
		&& mlx->map[ray->map_y][ray->map_x] == '1')
	{
		ray->hit_type = 1;
		return (1);
	}
	else if (mlx->map[ray->map_y][ray->map_x]
		&& mlx->map[ray->map_y][ray->map_x] == '2')
	{
		ray->hit_type = 2;
		return (1);
	}
	else if (mlx->map[ray->map_y][ray->map_x]
		&& mlx->map[ray->map_y][ray->map_x] == '3')
	{
		ray->hit_type = 3;
		return (1);
	}
	if (check_wall_ext(mlx, ray))
		return (1);
	return (0);
}

// Digital Differential Analysis
// iterate through each line in the grid the ray intersect until it hit a wall
void	ft_dda(t_mlx *mlx, t_raycast *ray)
{
	while (1)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->DeltaDistX;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->DeltaDistY;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (check_wall(mlx, ray))
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
		ray->DeltaDistX = 1000;
	else
		ray->DeltaDistX = fabs(1 / ray->raydir_x);

	if (ray->raydir_y == 0)
		ray->DeltaDistY = 1000;
	else
		ray->DeltaDistY = fabs(1 / ray->raydir_y);

	//calculate step and initial sideDist
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sideDistX = (mlx->player.pos_x - ray->map_x) * ray->DeltaDistX;
	}
	else
	{
		ray->step_x = 1;
		ray->sideDistX = (ray->map_x + 1.0 - mlx->player.pos_x)
			* ray->DeltaDistX;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sideDistY = (mlx->player.pos_y - ray->map_y) * ray->DeltaDistY;
	}
	else
	{
		ray->step_y = 1;
		ray->sideDistY = (ray->map_y + 1.0 - mlx->player.pos_y)
			* ray->DeltaDistY;
	}
	ft_dda(mlx, ray);
	if (mlx->player.inside == 0)
		ft_render_out_vline(ray, mlx, x);
	else
		ft_render_in_vline(ray, mlx, x);
}

void	ft_sprites_controller(t_mlx *mlx, t_raycast *ray)
{
	if (mlx->player.inside == 1)
	{
		ft_render_sprite(ray, mlx, mlx->jul);
		if (mlx->bag_status == 0)
			ft_render_sprite(ray, mlx, mlx->bag);
	}
	else if (mlx->player.inside == 2)
	{
		ft_render_sprite(ray, mlx, mlx->sch);
		if (mlx->bag_status == 2)
			ft_render_sprite(ray, mlx, mlx->bag);
	}
	else
	{
		ft_render_sprite(ray, mlx, mlx->tmax);
	}
}

// Render the backdrop in the img,
// raycast each vertical lines and render them in the img
void	ft_display(t_mlx *mlx)
{
	t_raycast	ray;
	int			x;

	draw_backdrop(mlx);
	ray.display = &mlx->display;
	x = 0;
	while (x < WIN_W)
		ft_raycast(mlx, &ray, x++);
	ft_sprites_controller(mlx, &ray);
}

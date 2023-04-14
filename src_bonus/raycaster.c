/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:55:52 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/17 14:55:52 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		if (check_wall(mlx, ray))
			break ;
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
	if (mlx->player.inside == 0)
		ft_render_out_vline(ray, mlx, x);
	else
		ft_render_in_vline(ray, mlx, x);
}

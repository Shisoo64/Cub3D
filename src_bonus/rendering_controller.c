/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_controller.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:28:41 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/13 14:28:41 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D_bonus.h"

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
void	ft_rendering(t_mlx *mlx)
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

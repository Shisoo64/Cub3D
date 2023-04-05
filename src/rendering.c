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

#include "../includes/cub3D.h"

void	draw_short_line_texture(t_display *texture, t_display *display, int x, int lineHeight, int draw_start, int draw_end, int tex_x)
{
	double	step;
	double	tex_pos;
	int		color;
	int		tex_y;
	int		y;

	step = 1.0 * texture->tex_height / lineHeight;
	tex_pos = (draw_start - WIN_H / 2 + lineHeight / 2) * step;
	y = draw_start;
	tex_x = texture->tex_width - tex_x;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = my_mlx_get_color(texture, tex_x, tex_y);
		my_mlx_pixel_put(display, x, y, color);
		y++;
	}
}

// Draw a vertical line of pixels in the img
void	ft_render_vline(t_raycast *ray, t_mlx *mlx, int x)
{
	int		draw_start;
	int		draw_end;
	double	perpWallDist;
	int		lineHeight;

	if (ray->side == 0)
		perpWallDist = (ray->sideDistX - ray->DeltaDistX);
	else
		perpWallDist = (ray->sideDistY - ray->DeltaDistY);

	lineHeight = (int)(WIN_H / perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	draw_start = -lineHeight / 2 + WIN_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = lineHeight / 2 + WIN_H / 2;
	if (draw_end >= WIN_H)
		draw_end = WIN_H - 1;


	/// Couper la fonction ici ///
	//Get line on texture
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = mlx->player.posY + perpWallDist * ray->raydirY;
	else
		wall_x = mlx->player.posX + perpWallDist * ray->raydirX;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)mlx->NO_tex.tex_width);
	if (ray->side == 0 && ray->raydirX > 0)
		tex_x = mlx->WE_tex.tex_width - tex_x - 1;
	if (ray->side == 1 && ray->raydirY < 0)
		tex_x = mlx->SO_tex.tex_width - tex_x - 1;
	if (ray->side == 1)
	{
		if (ray->stepY > 0)
			draw_short_line_texture(&mlx->NO_tex, &mlx->display, x, lineHeight, draw_start, draw_end, tex_x);
		else
			draw_short_line_texture(&mlx->SO_tex, &mlx->display, x, lineHeight, draw_start, draw_end, tex_x);
	}
	else
	{
		if (ray->stepX > 0)
			draw_short_line_texture(&mlx->WE_tex, &mlx->display, x, lineHeight, draw_start, draw_end, tex_x);
		else
			draw_short_line_texture(&mlx->EA_tex, &mlx->display, x, lineHeight, draw_start, draw_end, tex_x);
	}
}

// Digital Differential Analysis
// iterate through each line in the grid the ray intersect until it hit a wall
void	ft_dda(t_mlx *mlx, t_raycast *ray)
{
	while (1)
	{
		// ADD LES AUTRES TEXTS DE MUR
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->DeltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->DeltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}

		//Check if ray has hit a wall
		if (mlx->map[ray->mapY][ray->mapX]
			&& mlx->map[ray->mapY][ray->mapX] == '1')
			break ;
	}
}

void	ft_raycast(t_mlx *mlx, t_raycast *ray, int x)
{
	double	cameraX;

	cameraX = 2 * x / (double)WIN_W - 1;

	ray->raydirX = mlx->player.dirX + mlx->player.planeX * cameraX;
	ray->raydirY = mlx->player.dirY + mlx->player.planeY * cameraX;

	ray->mapX = (int)mlx->player.posX;
	ray->mapY = (int)mlx->player.posY;

	if (ray->raydirX == 0)
		ray->DeltaDistX = 1000;
	else
		ray->DeltaDistX = fabs(1 / ray->raydirX);

	if (ray->raydirY == 0)
		ray->DeltaDistY = 1000;
	else
		ray->DeltaDistY = fabs(1 / ray->raydirY);

	//calculate step and initial sideDist
	if (ray->raydirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (mlx->player.posX - ray->mapX) * ray->DeltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - mlx->player.posX) * ray->DeltaDistX;
	}
	if (ray->raydirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (mlx->player.posY - ray->mapY) * ray->DeltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - mlx->player.posY) * ray->DeltaDistY;
	}
	ft_dda(mlx, ray);
	ft_render_vline(ray, mlx, x);
}

// Render the backdrop in the img,
// raycast each vertical lines and render them in the img
void	ft_display(t_mlx *mlx)
{
	t_raycast	ray;
	int			x;

	draw_backdrop(mlx);
	x = 0;
	while (x < WIN_W)
		ft_raycast(mlx, &ray, x++);
}

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

//
//		OUTSIDE
void    draw_line_texture(t_display *texture, t_display *display, int x, int lineHeight, int draw_start, int draw_end, int tex_x)
{
	double	step;
	double	tex_pos;
	int		color;
	int		tex_y;
	int		y;

	step = 0.75 * texture->tex_height / lineHeight;
	tex_pos = (draw_start - WIN_H / 2 + lineHeight / 0.93) * step;
	y = draw_start;
	tex_x = texture->tex_width - tex_x;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = my_mlx_get_color(texture, tex_x, tex_y);

		// CODE POUR FAIRE DE L'OMBRE SUR LES TEXTURES VVVV
		//if (ray->side == 1)
		//	color = color / 2;
		
		my_mlx_pixel_put(display, x, y, color);
		y++;
	}
}

// Draw a vertical line of pixels in the img
void	ft_render_out_vline(t_raycast *ray, t_mlx *mlx, int x)
{
	int 	drawStart;
	int 	drawEnd;
	double	perpWallDist;
	int		lineHeight;

	if (ray->side == 0)
		perpWallDist = (ray->sideDistX - ray->DeltaDistX);
	else
		perpWallDist = (ray->sideDistY - ray->DeltaDistY);

	ray->ZBuffer[x] = perpWallDist;
	lineHeight = (int)(WIN_H / perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	drawStart = -lineHeight * 2.1 + WIN_H / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight * 0.25 + WIN_H / 2;
	if (drawEnd >= WIN_H)
		drawEnd = WIN_H - 1;


	/// Couper la fonction ici ///

	//Get line on texture

	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = mlx->player.posY + perpWallDist * ray->raydirY;
	else
		wall_x = mlx->player.posX + perpWallDist * ray->raydirX;
	wall_x -= floor(wall_x);
	// bat_tex = texture en fonction du wall_type. Pas toujours bat_tex
	tex_x = (int)(wall_x * (double)mlx->bat_tex.tex_width);
	if (ray->side == 0 && ray->raydirX > 0)
		tex_x = mlx->bat_tex.tex_width - tex_x - 1;
	if (ray->side == 1 && ray->raydirY < 0)
		tex_x = mlx->bat_tex.tex_width - tex_x - 1;

	if (ray->wall_type == 1)
		draw_line_texture(&mlx->bat_tex, &mlx->display, x, lineHeight, drawStart, drawEnd, tex_x);
	else if (ray->wall_type == 2)
		draw_line_texture(&mlx->bat2_tex, &mlx->display, x, lineHeight, drawStart, drawEnd, tex_x);
	else if (ray->wall_type == 3)
		draw_line_texture(&mlx->bat3_tex, &mlx->display, x, lineHeight, drawStart, drawEnd, tex_x);
	else if (ray->wall_type == 999)
	{
		if (perpWallDist <= 0.15)
		{
			if (mlx->player.using == 1)
				open_door(mlx);
			else
				mlx->message = "Press F to open door";
		}
		draw_line_texture(&mlx->door_tex, &mlx->display, x, lineHeight, drawStart, drawEnd, tex_x);
	}
}



//		INSIDE
//
void    draw_short_line_texture(t_display *texture, t_display *display, int x, int lineHeight, int draw_start, int draw_end, int tex_x)
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
void	ft_render_in_vline(t_raycast *ray, t_mlx *mlx, int x)
{
	int 	drawStart;
	int 	drawEnd;
	double	perpWallDist;
	int		lineHeight;

	if (ray->side == 0)
		perpWallDist = (ray->sideDistX - ray->DeltaDistX);
	else
		perpWallDist = (ray->sideDistY - ray->DeltaDistY);

	ray->ZBuffer[x] = perpWallDist;

	lineHeight = (int)(WIN_H / perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	drawStart = -lineHeight / 2 + WIN_H / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + WIN_H / 2;
	if (drawEnd >= WIN_H)
		drawEnd = WIN_H - 1;


	/// Couper la fonction ici ///

	//Get line on texture

	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = mlx->player.posY + perpWallDist * ray->raydirY;
	else
		wall_x = mlx->player.posX + perpWallDist * ray->raydirX;
	wall_x -= floor(wall_x);

	// in_wall = texture en fonction du wall_type. Pas toujours in_wall
	tex_x = (int)(wall_x * (double)mlx->in_wall.tex_width);
	if (ray->side == 0 && ray->raydirX > 0)
		tex_x = mlx->in_wall.tex_width - tex_x - 1;
	if (ray->side == 1 && ray->raydirY < 0)
		tex_x = mlx->in_wall.tex_width - tex_x - 1;

	if (ray->wall_type == 1)
		draw_short_line_texture(&mlx->in_wall, &mlx->display, x, lineHeight, drawStart, drawEnd, tex_x);
	else if (ray->wall_type == 2)
		draw_short_line_texture(&mlx->in_wall2, &mlx->display, x, lineHeight, drawStart, drawEnd, tex_x);
	else if (ray->wall_type == 999)
	{
		if (perpWallDist <= 0.15)
		{
			if (mlx->player.using == 1)
				close_door(mlx);
			else
				mlx->message = "Press F to open door";
		}
		draw_short_line_texture(&mlx->in_door_tex, &mlx->display, x, lineHeight, drawStart, drawEnd, tex_x);
	}
}

//Check if ray has hit a wall
//and set the type of wall that was hit 
int	check_wall(t_mlx *mlx, t_raycast *ray)
{
	if (mlx->map[ray->mapY][ray->mapX]
		&& mlx->map[ray->mapY][ray->mapX] == '1')
	{
		ray->wall_type = 1;
		return (1);
	}
	else if (mlx->map[ray->mapY][ray->mapX]
		&& mlx->map[ray->mapY][ray->mapX] == '2')
	{
		ray->wall_type = 2;
		return (1);
	}
	else if (mlx->map[ray->mapY][ray->mapX]
		&& mlx->map[ray->mapY][ray->mapX] == '3')
	{
		ray->wall_type = 3;
		return (1);
	}
	else if (mlx->map[ray->mapY][ray->mapX]
		&& mlx->map[ray->mapY][ray->mapX] == 'D')
	{
		ray->wall_type = 999;
		return (1);
	}
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
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->DeltaDistY;
			ray->mapY += ray->stepY;
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

	ray->raydirX = mlx->player.dirX + mlx->player.planeX * camera_x;
	ray->raydirY = mlx->player.dirY + mlx->player.planeY * camera_x;

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
	if (mlx->player.inside == 0)
		ft_render_out_vline(ray, mlx, x);
	else
		ft_render_in_vline(ray, mlx, x);
}

void	ft_sprites_controller(t_mlx *mlx, t_raycast *ray)
{
	if (mlx->player.inside)
	{
		ft_render_sprite(ray, mlx, mlx->jul);
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
	x = 0;
	while (x < WIN_W)
		ft_raycast(mlx, &ray, x++);
	ft_sprites_controller(mlx, &ray);
}

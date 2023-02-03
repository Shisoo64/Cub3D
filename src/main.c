/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/03 12:58:16 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_backdrop(t_mlx *mlx)
{
	int	y;
	int	x;

	y = -1;
	while (++y <= WIN_H / 2)
	{
		x = -1;
		while (++x <= WIN_W)
			my_mlx_pixel_put(&mlx->display, x, y, SKYCOLOR);
	}
	while (++y <= WIN_H)
	{
		x = -1;
		while (++x <= WIN_W)
			my_mlx_pixel_put(&mlx->display, x, y, FLOORCOLOR);
	}
}

void	ft_init_raycast(t_mlx *mlx)
{
	(void)mlx;
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

		if (ray->mapX > mlx->map_x - 1)
			ray->mapX = mlx->map_x - 1;

		if (ray->mapY > mlx->map_y - 1)
			ray->mapY = mlx->map_y - 1;

		//Check if ray has hit a wall
		if (mlx->map[ray->mapY][ray->mapX] && mlx->map[ray->mapY][ray->mapX] == '1')
			break ;
	}
}

// Draw a vertical line of pixels in the img
void	ft_render_vline(t_raycast *ray, t_display *mlx_display, int x)
{
	int 	drawStart;
	int 	drawEnd;
	double	perpWallDist;
	int		lineHeight;
	int		color;

	color = XCOLOR;
	if (ray->side == 0)
		perpWallDist = (ray->sideDistX - ray->DeltaDistX);
	else
		perpWallDist = (ray->sideDistY - ray->DeltaDistY);

	lineHeight = (int)(WIN_H / perpWallDist);

	//calculate lowest and highest pixel to fill in current stripe
	drawStart = -lineHeight / 2 + WIN_H / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + WIN_H / 2;
	if (drawEnd >= WIN_H)
		drawEnd = WIN_H - 1;

	// Color change on YWall
	if (ray->side == 1)
		color = YCOLOR;

	//draw line
	while (drawStart < drawEnd)
		my_mlx_pixel_put(mlx_display, x, drawStart++, color);
}

void	ft_raycast(t_mlx *mlx, int x)
{
	t_raycast	ray;
	double	cameraX;

	cameraX = 2 * x / (double)WIN_W - 1; //x-coordinate in camera space

	ray.raydirX = mlx->player.dirX + mlx->player.planeX * cameraX;
	ray.raydirY = mlx->player.dirY + mlx->player.planeY * cameraX;

	ray.mapX = (int)mlx->player.posX;
	ray.mapY = (int)mlx->player.posY;

	if (ray.raydirX == 0)
		ray.DeltaDistX = 1000;
	else
		ray.DeltaDistX = fabs(1 / ray.raydirX);

	if (ray.raydirY == 0)
		ray.DeltaDistY = 1000;
	else
		ray.DeltaDistY = fabs(1 / ray.raydirY);

	//calculate step and initial sideDist
	if (ray.raydirX < 0)
	{
		ray.stepX = -1;
		ray.sideDistX = (mlx->player.posX - ray.mapX) * ray.DeltaDistX;
	}
	else
	{
		ray.stepX = 1;
		ray.sideDistX = (ray.mapX + 1.0 - mlx->player.posX) * ray.DeltaDistX;
	}
	if (ray.raydirY < 0)
	{
		ray.stepY = -1;
		ray.sideDistY = (mlx->player.posY - ray.mapY) * ray.DeltaDistY;
	}
	else
	{
		ray.stepY = 1;
		ray.sideDistY = (ray.mapY + 1.0 - mlx->player.posY) * ray.DeltaDistY;
	}
	ft_dda(mlx, &ray);
	ft_render_vline(&ray, &mlx->display, x);
}

// Render the backdrop in the img,
// raycast each vertical lines and render them in the img,
// then display the img
int	ft_display(t_mlx *mlx)
{
	int	x;

	draw_backdrop(mlx);
	x = -1;
	while (++x < WIN_W)
		ft_raycast(mlx, x);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->display.img, 0, 0);
	return (0);
}

int	frames(t_mlx *mlx)
{
	(void)mlx;
	//ft_printf("FRAME\n");
	ft_display(mlx);

	mlx_mouse_hide(mlx->mlx, mlx->win);
	mlx_mouse_move(mlx->mlx, mlx->win, 0, 0);
	return (0);
}

int	exit_hook(t_mlx *mlx)
{
	exit_game(mlx);
	return (0);
}

int	mouse_hook(int key, t_mlx *mlx)
{
	(void)mlx;
	//printf("key:%d\n", key);
	if (key == 1)
		printf("\e[2APAN                            \n                                \n");
	return (0);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	//x and y start position
	mlx.player.posX = 5;
	mlx.player.posY = 5;

	mlx.player.dirX = -1;
	mlx.player.dirY = 0; //initial direction vector
	mlx.player.planeX = 0;
	mlx.player.planeY = 0.66; //the 2d raycaster version of camera plane

	if (ac != 2)
		return (1);
	mlx.mapname = av[1];
	check_map_ext(&mlx);
	mlx.map = create_map(&mlx);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "cub3d");
	mlx.display.img = mlx_new_image(mlx.mlx, WIN_W, WIN_H);
	mlx.display.addr = mlx_get_data_addr(mlx.display.img, &mlx.display.bits_per_pixel,
			&mlx.display.line_length, &mlx.display.endian);

	ft_display(&mlx);
	mlx_hook(mlx.win, 2, 1L<<0, inputs, &mlx);
	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	//mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);
}

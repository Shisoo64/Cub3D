/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/10 18:28:38 by rlaforge         ###   ########.fr       */
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
		if (mlx->map[ray->mapY][ray->mapX]
			&& mlx->map[ray->mapY][ray->mapX] == '1')
			break ;
	}
}


unsigned int    my_mlx_get_color(t_display *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return ((unsigned int) *dst);
}

void    draw_line_texture(t_display *texture,
    t_display *display, int x, int lineHeight, int draw_start, int draw_end, int tex_x)
{
	double	step;
	double	tex_pos;
	int		color;
	int		tex_y;
	int		y;

	step = 1.0 * texHeight / lineHeight;
	tex_pos = (draw_start - WIN_W / 2 + lineHeight / 2) * step;
	y = draw_start;
	tex_x = texWidth - tex_x;
	while (y < draw_end + 1)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = my_mlx_get_color(texture, tex_x - 1, tex_y);
		my_mlx_pixel_put(display, x, y, color);
		y++;
	}
}

// Draw a vertical line of pixels in the img
void	ft_render_vline(t_raycast *ray, t_mlx *mlx, int x)
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
	drawStart = -lineHeight * 2 + WIN_H / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight * 0.25 + WIN_H / 2;
	if (drawEnd >= WIN_H)
		drawEnd = WIN_H;



	// Color change on YWall
	if (ray->side == 1)
		color = YCOLOR;


	//Get line on texture

	int		tex_x;

	double	wall_x;

	if (ray->side == 0)
		wall_x = mlx->player.posY + perpWallDist * ray->raydirY;
	else
		wall_x = mlx->player.posX + perpWallDist * ray->raydirX;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)texWidth);
	if (ray->side == 0 && ray->raydirX > 0)
		tex_x = texWidth - tex_x - 1;
	if (ray->side == 1 && ray->raydirY < 0)
		tex_x = texWidth - tex_x - 1;

	draw_line_texture(mlx->texture, &mlx->display, x, lineHeight, drawStart, drawEnd, tex_x);

	//draw line
	/*
	while (drawStart < drawEnd)
		my_mlx_pixel_put(&mlx->display, x, drawStart++, color);
	*/
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
	ft_render_vline(&ray, mlx, x);
}

// Render the backdrop in the img,
// raycast each vertical lines and render them in the img,
// then display the img
void	ft_display(t_mlx *mlx)
{
	int	x;

	draw_backdrop(mlx);
	x = -1;
	while (++x < WIN_W)
		ft_raycast(mlx, x);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->display.img, 0, 0);
}

int	frames(t_mlx *mlx)
{
	(void)mlx;
	//ft_printf("FRAME\n");
	ft_display(mlx);

	int mouse_x = 0;
	int mouse_y = 0;

	mlx_mouse_get_pos(mlx->mlx, mlx->win, &mouse_x, &mouse_y);
	printf("mX:%d  mY:%d\n", WIN_W / 2 - mouse_x, WIN_H / 2 - mouse_y);
	rotate_player(WIN_W / 2 - mouse_x, &mlx->player);
	mlx_mouse_move(mlx->mlx, mlx->win, WIN_W / 2, WIN_H / 2);
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

void	ft_parsing()
{
	return ;
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	mlx.player.planeX = 0;
	mlx.player.planeY = FOV;

	if (ac != 2)
		return (1);
	mlx.mapname = av[1];
	check_map_ext(&mlx);


	int ix, iy;
	mlx.texture = mlx_xpm_file_to_image(mlx.mlx, "./sprites/wall.xpm", &ix, &iy);


	mlx.map = create_map(&mlx);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "cub3D");
	mlx.display.img = mlx_new_image(mlx.mlx, WIN_W, WIN_H);
	mlx.display.addr = mlx_get_data_addr(mlx.display.img, &mlx.display.bits_per_pixel,
			&mlx.display.line_length, &mlx.display.endian);

	mlx_mouse_hide(mlx.mlx, mlx.win);
	ft_display(&mlx);
	mlx_hook(mlx.win, 2, 1L << 0, inputs, &mlx);
	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);
}

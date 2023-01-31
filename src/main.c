/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/31 18:35:04 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_backdrop(t_vars *vars)
{
	int	yo;
	int	xo;
	yo = -1;
	while (++yo <= WIN_H)
	{
		xo = -1;
		while (++xo <= WIN_W)
			my_mlx_pixel_put(&vars->img, xo, yo, FLOORCOLOR);
	}
}

int	toto(t_vars *vars)
{
	int	x;

	ft_printf("Frame\n");
	draw_backdrop(vars);
	x = -1;
	while (++x < WIN_W)
	{
		int color = 0xffffff;
		//calculate ray position and direction
		double cameraX = 2 * x / (double)WIN_W - 1; //x-coordinate in camera space
		double raydirX = vars->dirX + vars->planeX * cameraX;
		double raydirY = vars->dirY + vars->planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)vars->posX;
		int mapY = (int)vars->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:

		//which can be simplified to abs(|rayDir| / rayvars->dirX) and abs(|rayDir| / rayvars->dirY)
		//where |rayDir| is the length of the vector (rayvars->dirX, rayvars->dirY). Its length,
		//unlike (vars->dirX, vars->dirY) is not 1, however this does not matter, only the
		//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		//stepping further below works. So the values can be computed as below.
		// Division through zero is prevented, even though technically that's not
		// needed in C++ with IEEE 754 floating point values.

		double DeltaDistX;
		double DeltaDistY;

		if (raydirX == 0)
			DeltaDistX = 1000;
		else
			DeltaDistX = fabs(1 / raydirX);
		//	DeltaDistX = sqrt(1 + (rayvars->dirY * rayvars->dirY) / (rayvars->dirX * rayvars->dirX));

		if (raydirY == 0)
			DeltaDistY = 1000;
		else
			DeltaDistY = fabs(1 / raydirY);
		//	DeltaDistY = sqrt(1 + (rayvars->dirX * rayvars->dirX) / (rayvars->dirY * rayvars->dirY));

		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (raydirX < 0)
		{
			stepX = -1;
			sideDistX = (vars->posX - mapX) * DeltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - vars->posX) * DeltaDistX;
		}
		if (raydirY < 0)
		{
			stepY = -1;
			sideDistY = (vars->posY - mapY) * DeltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - vars->posY) * DeltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += DeltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += DeltaDistY;
				mapY += stepY;
				side = 1;
			}

			if (mapX > vars->map_x - 1)
				mapX = vars->map_x - 1;

			if (mapY > vars->map_y - 1)
				mapY = vars->map_y - 1;

			//Check if ray has hit a wall
			if (vars->map[mapY][mapX] && vars->map[mapY][mapX] == '1')
				hit = 1;
    	}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - vars->posX + (1 - stepX) / 2) / rayvars->dirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if (side == 0)
			perpWallDist = (sideDistX - DeltaDistX);
		else
			perpWallDist = (sideDistY - DeltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(WIN_H / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + WIN_H / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_H / 2;
		if (drawEnd >= WIN_H)
			drawEnd = WIN_H - 1;

		// Color change on YWall
    	if (side == 1)
			color = color * 0.75;

		//draw line
		while (drawStart < drawEnd)
			my_mlx_pixel_put(&vars->img, x, drawStart++, color);
	}
	
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	frames(t_vars *vars)
{
	(void)vars;
	//ft_printf("FRAME\n");
	return (0);
}

void	move_player_up(t_vars *vars)
{
	if (vars->map[(int)(vars->posX + vars->dirX * MOVESPEED)][(int)vars->posY] == 0)
		vars->posX += vars->dirX * MOVESPEED;
	if (vars->map[(int)vars->posX][(int)(vars->posY + vars->dirY * MOVESPEED)] == 0)
		vars->posY += vars->dirY * MOVESPEED;
	toto(vars);
}

void	move_player_down(t_vars *vars)
{
	if (vars->map[(int)(vars->posX - vars->dirX * MOVESPEED)][(int)vars->posY] == 0)
		vars->posX -= vars->dirX * MOVESPEED;
	if (vars->map[(int)vars->posX][(int)(vars->posY - vars->dirY * MOVESPEED)] == 0)
		vars->posY -= vars->dirY * MOVESPEED;
	toto(vars);
}

void	rotate_player(int multi, t_vars *vars)
{
	double	olddirX;
	double	oldPlaneX;

	olddirX = vars->dirX;
	oldPlaneX = vars->planeX;
	vars->dirX = vars->dirX * cos(ROTSPEED * multi) - vars->dirY * sin(ROTSPEED * multi);
	vars->dirY = olddirX * sin(ROTSPEED * multi) + vars->dirY * cos(ROTSPEED * multi);
	vars->planeX = vars->planeX * cos(ROTSPEED * multi) - vars->planeY * sin(ROTSPEED * multi);
	vars->planeY = oldPlaneX * sin(ROTSPEED * multi) + vars->planeY * cos(ROTSPEED * multi);
	printf("planeX:%lf\n", vars->planeX);
	printf("planeY:%lf\n", vars->planeY);
	toto(vars);
	
}

int	inputs(int key, t_vars *vars)
{
	if (key == ESC)
		exit_game(vars);
	else if (key == KEY_LEFT)
		rotate_player(1, vars);
	else if (key == KEY_UP)
		move_player_down(vars);
	else if (key == KEY_DOWN)
		move_player_up(vars);
	else if (key == KEY_RIGHT)
		rotate_player(-1, vars);
	return (0);
}

int	exit_hook(t_vars *vars)
{
	exit_game(vars);
	return (0);
}

void	print_map(t_vars *vars)
{
	int	y;

	y = -1;
	while (++y < vars->map_y)
		ft_printf("%s\n", vars->map[y]);
}

int	main(int ac, char **av)
{
	t_vars	vars;


	//x and y start position
	vars.posX = 5;
	vars.posY = 5;

	vars.dirX = -1;
	vars.dirY = 0; //initial direction vector
	vars.planeX = 0;
	vars.planeY = 0.66; //the 2d raycaster version of camera plane
	


	if (ac != 2)
		return (1);
	vars.mapname = av[1];
	check_map_ext(&vars);
	vars.map = create_map(&vars);
	print_map(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_W, WIN_H, "cub3d");

	vars.img.img = mlx_new_image(vars.mlx, WIN_W, WIN_H);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
			&vars.img.line_length, &vars.img.endian);

	mlx_key_hook(vars.win, inputs, &vars);
	mlx_loop_hook(vars.mlx, frames, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	mlx_loop(vars.mlx);
}

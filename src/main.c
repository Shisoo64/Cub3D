/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/01 18:53:51 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_raycast(t_mlx *mlx, int x)
{
	int	color = XCOLOR;


	double perpWallDist;

	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;

	int drawStart;
	int drawEnd;





	//calculate ray position and direction
	double cameraX = 2 * x / (double)WIN_W - 1; //x-coordinate in camera space
	double raydirX = mlx->player.dirX + mlx->player.planeX * cameraX;
	double raydirY = mlx->player.dirY + mlx->player.planeY * cameraX;
	//which box of the map we're in
	int mapX = (int)mlx->player.posX;
	int mapY = (int)mlx->player.posY;

	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;

	//length of ray from one x or y-side to next x or y-side
	//these are derived as:

	//which can be simplified to abs(|rayDir| / raymlx->player->dirX) and abs(|rayDir| / raymlx->player->dirY)
	//where |rayDir| is the length of the vector (raymlx->player->dirX, raymlx->player->dirY). Its length,
	//unlike (mlx->player->dirX, mlx->player->dirY) is not 1, however this does not matter, only the
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
	//	DeltaDistX = sqrt(1 + (raymlx->player->dirY * raymlx->player->dirY) / (raymlx->player->dirX * raymlx->player->dirX));

	if (raydirY == 0)
		DeltaDistY = 1000;
	else
		DeltaDistY = fabs(1 / raydirY);
	//	DeltaDistY = sqrt(1 + (raymlx->player->dirX * raymlx->player->dirX) / (raymlx->player->dirY * raymlx->player->dirY));

	int hit = 0; //was there a wall hit?
	int side; //was a NS or a EW wall hit?
	//calculate step and initial sideDist
	if (raydirX < 0)
	{
		stepX = -1;
		sideDistX = (mlx->player.posX - mapX) * DeltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - mlx->player.posX) * DeltaDistX;
	}
	if (raydirY < 0)
	{
		stepY = -1;
		sideDistY = (mlx->player.posY - mapY) * DeltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - mlx->player.posY) * DeltaDistY;
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

		if (mapX > mlx->map_x - 1)
			mapX = mlx->map_x - 1;

		if (mapY > mlx->map_y - 1)
			mapY = mlx->map_y - 1;

		//Check if ray has hit a wall
		if (mlx->map[mapY][mapX] && mlx->map[mapY][mapX] == '1')
			hit = 1;
	}
	//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
	//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
	//This can be computed as (mapX - mlx->player->posX + (1 - stepX) / 2) / raymlx->player->dirX for side == 0, or same formula with Y
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
	drawStart = -lineHeight / 2 + WIN_H / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + WIN_H / 2;
	if (drawEnd >= WIN_H)
		drawEnd = WIN_H - 1;

	// Color change on YWall
	if (side == 1)
		color = YCOLOR;

	//draw line
	while (drawStart < drawEnd)
		my_mlx_pixel_put(&mlx->display, x, drawStart++, color);
}

int	ft_display(t_mlx *mlx)
{
	int	x;

	ft_printf("Frame\n");
	draw_backdrop(mlx);
	x = -1;
	while (++x < WIN_W)
	{
		ft_raycast(mlx, x);
	}

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->display.img, 0, 0);
	return (0);
}

int	frames(t_mlx *mlx)
{
	(void)mlx;
	//ft_printf("FRAME\n");
	return (0);
}

void	move_player_up(t_player *player, char **map)
{
	if (map[(int)player->posY][(int)(player->posX + player->dirX * MOVESPEED)] != '1')
		player->posX += player->dirX * MOVESPEED;
	if (map[(int)(player->posY + player->dirY * MOVESPEED)][(int)player->posX] != '1')
		player->posY += player->dirY * MOVESPEED;
	printf("posX:%lf\n", player->posX);
	printf("posY:%lf\n", player->posY);
}

void	move_player_down(t_player *player, char **map)
{
	if (map[(int)player->posY][(int)(player->posX - player->dirX * MOVESPEED)] != '1')
		player->posX -= player->dirX * MOVESPEED;
	if (map[(int)(player->posY - player->dirY * MOVESPEED)][(int)player->posX] != '1')
		player->posY -= player->dirY * MOVESPEED;
	printf("posX:%lf\n", player->posX);
	printf("posY:%lf\n", player->posY);
}


void	rotate_player(int multi, t_player *player)
{
	double	olddirX;
	double	oldPlaneX;

	olddirX = player->dirX;
	oldPlaneX = player->planeX;
	player->dirX = player->dirX * cos(ROTSPEED * multi) - player->dirY * sin(ROTSPEED * multi);
	player->dirY = olddirX * sin(ROTSPEED * multi) + player->dirY * cos(ROTSPEED * multi);
	player->planeX = player->planeX * cos(ROTSPEED * multi) - player->planeY * sin(ROTSPEED * multi);
	player->planeY = oldPlaneX * sin(ROTSPEED * multi) + player->planeY * cos(ROTSPEED * multi);
	printf("planeX:%lf\n", player->planeX);
	printf("planeY:%lf\n", player->planeY);
}

int	inputs(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit_game(mlx);
	else if (key == KEY_LEFT)
		rotate_player(1, &mlx->player);
	else if (key == KEY_UP)
		move_player_down(&mlx->player, mlx->map);
	else if (key == KEY_DOWN)
		move_player_up(&mlx->player, mlx->map);
	else if (key == KEY_RIGHT)
		rotate_player(-1, &mlx->player);
	ft_display(mlx);
	return (0);
}

int	exit_hook(t_mlx *mlx)
{
	exit_game(mlx);
	return (0);
}

void	print_map(t_mlx *mlx)
{
	int	y;

	y = -1;
	while (++y < mlx->map_y)
		ft_printf("%s\n", mlx->map[y]);
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
	print_map(&mlx);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WIN_W, WIN_H, "cub3d");
	mlx.display.img = mlx_new_image(mlx.mlx, WIN_W, WIN_H);
	mlx.display.addr = mlx_get_data_addr(mlx.display.img, &mlx.display.bits_per_pixel,
			&mlx.display.line_length, &mlx.display.endian);

	ft_display(&mlx);
	mlx_hook(mlx.win, 2, 1L<<0, inputs, &mlx);
	mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:59:47 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/02 15:06:57 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(int multi, t_player *player, char **map)
{
	if (map[(int)player->posY]
		[(int)(player->posX + (player->dirX * MOVESPEED * multi))] != '1')
		player->posX += (player->dirX * MOVESPEED) * multi;
	if (map[(int)(player->posY + (player->dirY * MOVESPEED * multi))]
		[(int)player->posX] != '1')
		player->posY += (player->dirY * MOVESPEED) * multi;
	printf("\e[2AposX:%lf             \n", player->posX);
	printf("posY:%lf              \n", player->posY);
}

void	strafe_player(int multi, t_player *player, char **map)
{
	if (map[(int)player->posY]
		[(int)(player->posX + (player->planeX * MOVESPEED * multi))] != '1')
		player->posX += (player->planeX * MOVESPEED) * multi;
	if (map[(int)(player->posY + (player->planeY * MOVESPEED * multi))]
		[(int)player->posX] != '1')
		player->posY += (player->planeY * MOVESPEED) * multi;
	printf("\e[2AposX:%lf             \n", player->posX);
	printf("posY:%lf              \n", player->posY);
}

void	rotate_player(int multi, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dirX;
	old_plane_x = player->planeX;
	player->dirX = player->dirX * cos(ROTSPEED * multi)
		- player->dirY * sin(ROTSPEED * multi);
	player->dirY = old_dir_x * sin(ROTSPEED * multi)
		+ player->dirY * cos(ROTSPEED * multi);
	player->planeX = player->planeX * cos(ROTSPEED * multi)
		- player->planeY * sin(ROTSPEED * multi);
	player->planeY = old_plane_x * sin(ROTSPEED * multi)
		+ player->planeY * cos(ROTSPEED * multi);
}










// BIKE


void	input_manager_foot(t_mlx *mlx)
{

	if (mlx->player.up == 1)
		move_player(-500, &mlx->player, mlx->map);
	if (mlx->player.down == 1)
		move_player(500, &mlx->player, mlx->map);

	if (mlx->player.rot_r == 1)
		rotate_player(-3000, &mlx->player);
	if (mlx->player.rot_l == 1)
		rotate_player(3000, &mlx->player);

	if (mlx->player.left == 1)
		strafe_player(-300, &mlx->player, mlx->map);
	if (mlx->player.right == 1)
		strafe_player(300, &mlx->player, mlx->map);


	int mouse_x = 0;
	int mouse_y = 0;

	mlx_mouse_get_pos(mlx->mlx, mlx->win, &mouse_x, &mouse_y);
	rotate_player((WIN_W / 2 - mouse_x) * 100, &mlx->player);
	mlx_mouse_move(mlx->mlx, mlx->win, WIN_W / 2, WIN_H / 2);
}


void	move_player_bike(t_mlx *mlx, int speed, t_player *player)
{
	if (mlx->map[(int)player->posY]
		[(int)(player->posX + (player->dirX * MOVESPEED * speed))] != '1')
		player->posX += (player->dirX * MOVESPEED) * speed;
	if (mlx->map[(int)(player->posY + (player->dirY * MOVESPEED * speed))]
		[(int)player->posX] != '1')
		player->posY += (player->dirY * MOVESPEED) * speed;


	// CHECK WALL CRASH
	if (mlx->map[(int)player->posY]
		[(int)(player->posX + (player->dirX * MOVESPEED * speed))] == '1' && speed >= CRASH_SPEED)
		exit_game(mlx);
	if (mlx->map[(int)(player->posY + (player->dirY * MOVESPEED * speed))]
		[(int)player->posX] == '1' && speed >= CRASH_SPEED)
		exit_game(mlx);

	printf("posX:%lf\n", player->posX);
	printf("posY:%lf\n", player->posY);
}

void	input_manager_bike(t_mlx *mlx)
{
	static double coef;

	if (mlx->player.speed > 6000)
		mlx->player.speed = 6000;
	else if (mlx->player.speed >= 4000)
	{
		coef = 0.1;
		put_img_transp(mlx, mlx->bike_wheel, WIN_W / 2 - 250, WIN_H - 262);
	}
	else if (mlx->player.speed >= 2600)
	{
		coef = 0.25;
		put_img_transp(mlx, mlx->bike_wheel, WIN_W / 2 - 250, WIN_H - 262);
	}
	else
		put_img_transp(mlx, mlx->bike, WIN_W / 2 - 250, WIN_H - 262);

	if (mlx->player.speed >= 250)
		coef = 0.5;
	else
		coef = 1;

	if (mlx->player.speed < -250)
		mlx->player.speed = -250;

	mlx_string_put(mlx->mlx, mlx->win, WIN_W / 2 - 12, WIN_H - 70, 0xffffff, ft_itoa(mlx->player.speed / 30));

	// Frein
	if (mlx->player.up == 1)
		mlx->player.speed -= 15;


	// Reculer avec les pieds
	if (mlx->player.up == 1 && mlx->player.speed <= 0)
		mlx->player.speed -= 20;
	
	// Accelerer
	if (mlx->player.down == 1 && mlx->player.speed >= 0)
		mlx->player.speed += 12 * coef;

	// Frein moteur
	if (mlx->player.down == 0 && mlx->player.speed >= 0)
		mlx->player.speed -= 12 * (1.15 - coef);
	// Frein moteur en marche arriere
	if (mlx->player.up == 0 && mlx->player.speed <= 0)
		mlx->player.speed += 20 * (1.3 - coef);

	if (mlx->player.rot_l == 1)
		rotate_player((5000 - mlx->player.speed) * coef, &mlx->player);
	if (mlx->player.rot_r == 1)
		rotate_player((-5000 + mlx->player.speed) * coef, &mlx->player);

	if (mlx->player.speed <= 10 && mlx->player.speed >= -10)
		mlx->player.speed = 0;


	printf("\e[1A\e[2K\e[1A\e[2K\e[1A\e[2Kspeed:%fkmh	(%f)\n", mlx->player.speed / 30, mlx->player.speed);
	move_player_bike(mlx, mlx->player.speed, &mlx->player);
}

int	key_press(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit_game(mlx);
	else if (key == KEY_ARROW_L || key == KEY_Q)
		mlx->player.rot_l = 1;
	else if (key == KEY_W)
		mlx->player.up = 1;
	else if (key == KEY_S)
		mlx->player.down = 1;
	else if (key == KEY_ARROW_R || key == KEY_E)
		mlx->player.rot_r = 1;
	else if (key == KEY_A)
		mlx->player.left = 1;
	else if (key == KEY_D)
		mlx->player.right = 1;
	else if (key == KEY_F && mlx->player.speed == 0)
		mlx->player.biking = -mlx->player.biking;
	return (0);
}

int	key_release(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit_game(mlx);
	else if (key == KEY_ARROW_L || key == KEY_Q)
		mlx->player.rot_l = 0;
	else if (key == KEY_W)
		mlx->player.up = 0;
	else if (key == KEY_S)
		mlx->player.down = 0;
	else if (key == KEY_ARROW_R || key == KEY_E)
		mlx->player.rot_r = 0;
	else if (key == KEY_A)
		mlx->player.left = 0;
	else if (key == KEY_D)
		mlx->player.right = 0;
	return (0);
}






int	input_manager(t_mlx *mlx)
{
	if (mlx->player.biking == 1)
		input_manager_bike(mlx);
	else
		input_manager_foot(mlx);
	return (0);
}

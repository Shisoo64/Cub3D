/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bike_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:05:19 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/14 16:21:48 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
		mlx->crashed = 1;
	if (mlx->map[(int)(player->posY + (player->dirY * MOVESPEED * speed))]
		[(int)player->posX] == '1' && speed >= CRASH_SPEED)
		mlx->crashed = 1;
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

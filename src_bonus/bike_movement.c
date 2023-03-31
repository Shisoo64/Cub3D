/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bike_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:05:19 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/31 16:14:27 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player_bike(t_mlx *mlx, int speed, t_player *player)
{
	if (!ft_strchr("123JAD", mlx->map[(int)player->pos_y]
			[(int)(player->pos_x + (player->dir_x * MOVESPEED * speed))]))
		player->pos_x += (player->dir_x * MOVESPEED) * speed;
	if (!ft_strchr("123JAD",
			mlx->map[(int)(player->pos_y + (player->dir_y * MOVESPEED * speed))]
		[(int)player->pos_x]))
		player->pos_y += (player->dir_y * MOVESPEED) * speed;


	// CHECK WALL CRASH
	if (ft_strchr("123JAD", mlx->map[(int)player->pos_y]
			[(int)(player->pos_x + (player->dir_x * MOVESPEED * speed))])
		&& speed >= CRASH_SPEED)
		mlx->crashed = 1;
	if (ft_strchr("123JAD",
			mlx->map[(int)(player->pos_y + (player->dir_y * MOVESPEED * speed))]
		[(int)player->pos_x]) && speed >= CRASH_SPEED)
		mlx->crashed = 1;
}

void	input_manager_bike(t_mlx *mlx)
{
	static double	coef;

	if (mlx->player.speed > 6000)
		mlx->player.speed = 6000;
	if (mlx->player.speed >= 4000)
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

	if (mlx->player.rot_r == 1)
		rotate_player((5000 - mlx->player.speed) * coef, &mlx->player);
	if (mlx->player.rot_l == 1)
		rotate_player((-5000 + mlx->player.speed) * coef, &mlx->player);

	if (mlx->player.speed <= 10 && mlx->player.speed >= -10)
		mlx->player.speed = 0;

	printf("\e[1A\e[2K\e[1A\e[2K\e[1A\e[2Kspeed:%fkmh - (%f)\n", mlx->player.speed / 30, mlx->player.speed);
	move_player_bike(mlx, mlx->player.speed, &mlx->player);
}

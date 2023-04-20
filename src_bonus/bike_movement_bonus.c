/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bike_movement_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:05:19 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/20 12:14:42 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D_bonus.h"

//apply speed to the player and wall detection
void	move_player_bike(t_mlx *mlx, int speed, t_player *player)
{
	if (!ft_strchr("123JAD", mlx->map[(int)player->pos_y]
			[(int)(player->pos_x + (player->dir_x * MOVESPEED * speed))]))
		player->pos_x += (player->dir_x * MOVESPEED) * speed;
	if (!ft_strchr("123JAD",
			mlx->map[(int)(player->pos_y + (player->dir_y * MOVESPEED * speed))]
		[(int)player->pos_x]))
		player->pos_y += (player->dir_y * MOVESPEED) * speed;
	if (ft_strchr("123JAD", mlx->map[(int)player->pos_y]
			[(int)(player->pos_x + (player->dir_x * MOVESPEED * speed))])
		&& speed >= CRASH_SPEED)
		mlx->crashed = 1;
	if (ft_strchr("123JAD",
			mlx->map[(int)(player->pos_y + (player->dir_y * MOVESPEED * speed))]
		[(int)player->pos_x]) && speed >= CRASH_SPEED)
		mlx->crashed = 1;
}

//passive speed modifications,
//like engine braking and acceleration diminishing with speed
void	bike_speed(t_mlx *mlx, double *coef)
{
	if (mlx->player.speed > 6000)
		mlx->player.speed = 6000;
	if (mlx->player.speed >= 4000)
	{
		*coef = 0.1;
		put_img_transp(mlx, mlx->bike_wheel, WIN_W / 2 - 250, WIN_H - 262);
	}
	else if (mlx->player.speed >= 2600)
	{
		*coef = 0.25;
		put_img_transp(mlx, mlx->bike_wheel, WIN_W / 2 - 250, WIN_H - 262);
	}
	else
		put_img_transp(mlx, mlx->bike, WIN_W / 2 - 250, WIN_H - 262);
	if (mlx->player.speed >= 250)
		*coef = 0.5;
	else
		*coef = 1;
	if (mlx->player.speed < -250)
		mlx->player.speed = -250;
}

//change the speed and rotation in fuction of the inputs
void	input_manager_bike(t_mlx *mlx)
{
	static double	coef;

	bike_speed(mlx, &coef);
	if (mlx->player.up == 1)
		mlx->player.speed -= 15;
	if (mlx->player.up == 1 && mlx->player.speed <= 0)
		mlx->player.speed -= 20;
	if (mlx->player.down == 1 && mlx->player.speed >= 0)
		mlx->player.speed += 12 * coef;
	if (mlx->player.down == 0 && mlx->player.speed >= 0)
		mlx->player.speed -= 12 * (1.15 - coef);
	if (mlx->player.up == 0 && mlx->player.speed <= 0)
		mlx->player.speed += 20 * (1.3 - coef);
	if (mlx->player.rot_r == 1)
		rotate_player((5000 - mlx->player.speed) * coef, &mlx->player);
	if (mlx->player.rot_l == 1)
		rotate_player((-5000 + mlx->player.speed) * coef, &mlx->player);
	if (mlx->player.speed <= 10 && mlx->player.speed >= -10)
		mlx->player.speed = 0;
	ft_printf("\e[1A\e[2K\e[1A\e[2K\e[1A\e[2Kspeed:%fkmh\n",
		mlx->player.speed / 30, mlx->player.speed);
	move_player_bike(mlx, mlx->player.speed, &mlx->player);
}

//Get on and off the bike
void	ft_bike_action(t_mlx *mlx)
{
	if (ft_check_prox(mlx, mlx->tmax))
	{
		if (mlx->tmaxkeys)
			mlx->msg = "Press F to ride the T-MAX";
		else
			mlx->msg = "You don't have the keys!";
		if (mlx->player.using == -1 && mlx->tmaxkeys)
		{
			mlx->tmax.x = 0;
			mlx->tmax.y = 0;
			mlx->player.biking = 1;
		}
	}
	else if (mlx->player.biking == 1
		&& mlx->player.using == -1 && mlx->player.speed == 0)
	{
		mlx->player.biking = -1;
		mlx->player.using = 0;
		mlx->tmax.x = mlx->player.pos_x;
		mlx->tmax.y = mlx->player.pos_y;
	}
}

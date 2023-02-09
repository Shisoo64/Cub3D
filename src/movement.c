/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 23:59:47 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/09 13:59:10 by rlaforge         ###   ########.fr       */
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
	printf("\e[2AplaneX:%lf             \n", player->planeX);
	printf("planeY:%lf              \n", player->planeY);
}

int	inputs(int key, t_mlx *mlx)
{
	//printf("key:%d\n", key);

	if (key == ESC)
		exit_game(mlx);
	else if (key == KEY_ARROW_L || key == KEY_Q)
		rotate_player(1, &mlx->player);
	else if (key == KEY_W)
		move_player(-1, &mlx->player, mlx->map);
	else if (key == KEY_S)
		move_player(1, &mlx->player, mlx->map);
	else if (key == KEY_ARROW_R || key == KEY_E)
		rotate_player(-1, &mlx->player);
	else if (key == KEY_A)
		strafe_player(-1, &mlx->player, mlx->map);
	else if (key == KEY_D)
		strafe_player(1, &mlx->player, mlx->map);
	ft_display(mlx);
	return (0);
}

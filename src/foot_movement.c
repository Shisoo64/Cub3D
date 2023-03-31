/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foot_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:06:29 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/31 02:43:01 by bchabot          ###   ########.fr       */
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
	//printf("\e[2AposX:%lf             \n", player->posX);
	//printf("posY:%lf              \n", player->posY);
}

void	strafe_player(int multi, t_player *player, char **map)
{
	if (map[(int)player->posY]
		[(int)(player->posX + (player->planeX * MOVESPEED * multi))] != '1')
		player->posX += (player->planeX * MOVESPEED) * multi;
	if (map[(int)(player->posY + (player->planeY * MOVESPEED * multi))]
		[(int)player->posX] != '1')
		player->posY += (player->planeY * MOVESPEED) * multi;
	//printf("\e[2AposX:%lf             \n", player->posX);
	//printf("posY:%lf              \n", player->posY);
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

void	input_manager_foot(t_mlx *mlx)
{
	if (mlx->player.up == 1)
		move_player(-750, &mlx->player, mlx->map);
	if (mlx->player.down == 1)
		move_player(500, &mlx->player, mlx->map);

	if (mlx->player.rot_r == 1)
		rotate_player(4200, &mlx->player);
	if (mlx->player.rot_l == 1)
		rotate_player(-4200, &mlx->player);

	if (mlx->player.left == 1)
		strafe_player(-300, &mlx->player, mlx->map);
	if (mlx->player.right == 1)
		strafe_player(300, &mlx->player, mlx->map);
}

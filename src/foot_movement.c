/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foot_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:06:29 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/11 17:03:16 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D.h"

void	move_player(int multi, t_player *player, char **map)
{
	if (map[(int)player->pos_y]
		[(int)(player->pos_x + (player->dir_x * MOVESPEED * multi))] != '1')
		player->pos_x += (player->dir_x * MOVESPEED) * multi;
	if (map[(int)(player->pos_y + (player->dir_y * MOVESPEED * multi))]
		[(int)player->pos_x] != '1')
		player->pos_y += (player->dir_y * MOVESPEED) * multi;
}

void	strafe_player(int multi, t_player *player, char **map)
{
	if (map[(int)player->pos_y]
		[(int)(player->pos_x + (player->plane_x * MOVESPEED * multi))] != '1')
		player->pos_x += (player->plane_x * MOVESPEED) * multi;
	if (map[(int)(player->pos_y + (player->plane_y * MOVESPEED * multi))]
		[(int)player->pos_x] != '1')
		player->pos_y += (player->plane_y * MOVESPEED) * multi;
}

void	rotate_player(int multi, t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(ROTSPEED * multi)
		- player->dir_y * sin(ROTSPEED * multi);
	player->dir_y = old_dir_x * sin(ROTSPEED * multi)
		+ player->dir_y * cos(ROTSPEED * multi);
	player->plane_x = player->plane_x * cos(ROTSPEED * multi)
		- player->plane_y * sin(ROTSPEED * multi);
	player->plane_y = old_plane_x * sin(ROTSPEED * multi)
		+ player->plane_y * cos(ROTSPEED * multi);
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

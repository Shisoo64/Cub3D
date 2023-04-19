/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foot_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:06:29 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 17:57:59 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D_bonus.h"

void	move_player(int multi, t_player *player, char **map)
{
	if (!ft_strchr("123JAD", map[(int)player->pos_y]
			[(int)(player->pos_x + (player->dir_x * MOVESPEED * multi))]))
		player->pos_x += (player->dir_x * MOVESPEED) * multi;
	if (!ft_strchr("123JAD",
			map[(int)(player->pos_y + (player->dir_y * MOVESPEED * multi))]
		[(int)player->pos_x]))
		player->pos_y += (player->dir_y * MOVESPEED) * multi;
}

void	strafe_player(int multi, t_player *player, char **map)
{
	if (!ft_strchr("123JAD", map[(int)player->pos_y]
			[(int)(player->pos_x + (player->plane_x * MOVESPEED * multi))]))
		player->pos_x += (player->plane_x * MOVESPEED) * multi;
	if (!ft_strchr("123JAD",
			map[(int)(player->pos_y + (player->plane_y * MOVESPEED * multi))]
		[(int)player->pos_x]))
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
	int	mult;
	int	mouse_x;
	int	mouse_y;

	mult = 1;
	if (mlx->player.inside != 0)
		mult = 2;
	if (mlx->player.up == 1)
		move_player(-500 * mult, &mlx->player, mlx->map);
	if (mlx->player.down == 1)
		move_player(750 * mult, &mlx->player, mlx->map);
	if (mlx->player.rot_l == 1)
		rotate_player(-5000, &mlx->player);
	if (mlx->player.rot_r == 1)
		rotate_player(5000, &mlx->player);
	if (mlx->player.left == 1)
		strafe_player(-300 * mult, &mlx->player, mlx->map);
	if (mlx->player.right == 1)
		strafe_player(300 * mult, &mlx->player, mlx->map);
	mlx_mouse_get_pos(mlx->mlx, mlx->win, &mouse_x, &mouse_y);
	rotate_player(-(WIN_W / 2 - mouse_x) * 100, &mlx->player);
	mlx_mouse_move(mlx->mlx, mlx->win, WIN_W / 2, WIN_H / 2);
}

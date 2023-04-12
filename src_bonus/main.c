/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/12 17:21:28 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_walk_anim(t_mlx *mlx)
{
	static int	i;

	if (mlx->player.biking == -1 && mlx->player.down)
	{
		if (i >= 0 && i <= 50)
			put_img_transp(mlx, mlx->hand, WIN_W / 2 - 228, WIN_H - 118);
		else if (mlx->bag_status != 1 && mlx->wazing != 1)
			put_img_transp(mlx, mlx->hand2, WIN_W / 2 + 70, WIN_H - 118);
		if (i++ == 100)
			i = 0;
	}
}

//If player press the Use key, enter the building
//else display the message
void	open_door(t_mlx *mlx, char *mapname, int batnbr)
{
	if (mlx->player.using == 1)
	{
		mlx->mapname = mapname;
		mlx->player.dir_x_save = -mlx->player.dir_x;
		mlx->player.dir_y_save = -mlx->player.dir_y;
		mlx->player.pos_x_save = mlx->player.pos_x;
		mlx->player.pos_y_save = mlx->player.pos_y;
		mlx->player.plane_x_save = -mlx->player.plane_x;
		mlx->player.plane_y_save = -mlx->player.plane_y;
		mlx->player.inside = batnbr;
		mlx->player.biking = -1;
		mlx->player.plane_x = 0;
		mlx->player.plane_y = FOV;
		free_map(mlx, mlx->map);
		mlx->map = create_map(mlx);
		place_player_on_map(mlx, mlx->map);
	}
	else
		mlx->message = "Press F to open door";
}

//If player press the Use key, go back to the main map
//else display the message
void	close_door(t_mlx *mlx)
{
	if (mlx->player.using == 1)
	{
		mlx->mapname = "maps/map.cub";
		mlx->player.pos_x = mlx->player.pos_x_save;
		mlx->player.pos_y = mlx->player.pos_y_save;
		mlx->player.plane_x = mlx->player.plane_x_save;
		mlx->player.plane_y = mlx->player.plane_y_save;
		mlx->player.dir_x = mlx->player.dir_x_save;
		mlx->player.dir_y = mlx->player.dir_y_save;
		mlx->player.inside = 0;
		mlx->player.using = 0;
		free_map(mlx, mlx->map);
		mlx->map = create_map(mlx);
	}
	else
		mlx->message = "Press F to open door";
}

//Check if the sprite is reachable by the player
int	ft_check_prox(t_mlx *mlx, t_sprite tex)
{
	if (mlx->player.pos_x - tex.x <= 0.5
		&& mlx->player.pos_x - tex.x >= -0.5
		&& mlx->player.pos_y - tex.y <= 0.5
		&& mlx->player.pos_y - tex.y >= -0.5)
		return (1);
	return (0);
}

//Control the start of the dialogs
void	ft_start_dialog(t_mlx *mlx)
{
	if (mlx->dialog == 0 && ft_check_prox(mlx, mlx->jul))
	{
		mlx->message = "Press F to talk to JuL";
		if (mlx->player.using == 1)
			mlx->dialog = 10;
	}
	else if (mlx->dialog == 0 && mlx->bag_status == 1
		&& ft_check_prox(mlx, mlx->sch))
	{
		mlx->message = "Press F to talk to SCH";
		if (mlx->player.using == 1)
			mlx->dialog = 20;
	}
}

//Get on and off the bike
void	ft_bike_action(t_mlx *mlx)
{
	if (ft_check_prox(mlx, mlx->tmax))
	{
		if (mlx->tmaxkeys)
			mlx->message = "Press F to ride the T-MAX";
		else
			mlx->message = "You don't have the keys!";
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

//This function is called at every frames
int	frames(t_mlx *mlx)
{
	if (mlx->started == 0)
		start_screen(mlx);
	else if (mlx->crashed == 1)
		crash_screen(mlx);
	else
	{
		ft_rendering(mlx);
		input_manager(mlx);
		ft_walk_anim(mlx);
		ft_bike_action(mlx);
		ft_minimap_controller(mlx, WIN_W / 2 + 100, WIN_H - 230);
		if (mlx->bag_status == 1)
			put_img_transp(mlx, mlx->handbag, WIN_W - 366, WIN_H - 240);
		if (mlx->dialog != 0)
			ft_dialog(mlx);
		if (mlx->player.biking == -1)
			ft_start_dialog(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->display.img, 0, 0);
		if (mlx->message)
		{
			mlx_string_put(mlx->mlx, mlx->win, 342, 717, 0xffffff, mlx->message);
			mlx->message = NULL;
		}
		mlx->player.use_phone = 0;
		mlx->player.using = 0;
	}
	return (0);
}

int	exit_hook(t_mlx *mlx)
{
	exit_game(mlx);
	return (0);
}

int	main(void)
{
	t_mlx	mlx;

	mlx.player.plane_x = 0;
	mlx.player.plane_y = FOV;
	ft_parsing(&mlx);
	mlx_mouse_hide(mlx.mlx, mlx.win);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);
	mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}

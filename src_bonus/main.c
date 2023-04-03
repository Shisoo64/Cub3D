/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/03 19:30:20 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_door(t_mlx *mlx, char *mapname, int batnbr)
{

	printf("\nENTERING THE BAT\n");

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

void	close_door(t_mlx *mlx)
{
	printf("\nJE ME BARRE OF THE BAT\n");

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


int	ft_check_prox(t_mlx *mlx, t_sprite tex)
{
	if (mlx->player.pos_x - tex.x <= 0.5 && mlx->player.pos_x - tex.x >= -0.5
		&& mlx->player.pos_y - tex.y <= 0.5 && mlx->player.pos_y - tex.y >= -0.5)
		return (1);
	return (0);
}

void	ft_start_dialog_check(t_mlx *mlx)
{
	if (ft_check_prox(mlx, mlx->tmax))
	{
		if (mlx->tmaxkeys)
			mlx->message = "Press F to ride the T-MAX";
		else
			mlx->message = "You don't have the keys!";
		if (mlx->player.using == 1 && mlx->tmaxkeys)
		{
			mlx->tmax.x = 0;
			mlx->tmax.y = 0;
			mlx->player.biking = 1;
		}
	}
	else if (mlx->dialog == 0 && ft_check_prox(mlx, mlx->jul))
	{
		mlx->message = "Press F to talk";
		if (mlx->player.using == 1)
			mlx->dialog = 10;
	}
	else if (mlx->dialog == 0 && mlx->bag_status == 1
		&& ft_check_prox(mlx, mlx->sch))
	{
		mlx->message = "Press F to talk";
		if (mlx->player.using == 1)
			mlx->dialog = 20;
	}
}

int	frames(t_mlx *mlx)
{
	if (mlx->started == 0)
	{
		start_screen(mlx);
		return (0);
	}
	else if (mlx->crashed == 1)
	{
		crash_screen(mlx);
		return (0);
	}
	else
	{
		ft_display(mlx);
		input_manager(mlx);
	}


	// WALK ANIM
	// DOWN PARCE QUE LES CONTROLES SONT INVERSÉS
	if (mlx->player.biking == -1 && mlx->player.down)
	{
		static int i;

		if (i >= 0 && i <= 50)
			put_img_transp(mlx, mlx->hand, WIN_W / 2 - 228, WIN_H - 118);
		else if (mlx->bag_status != 1)
			put_img_transp(mlx, mlx->hand2, WIN_W / 2 + 70, WIN_H - 118);
		if (i++ == 100)
			i = 0;
	}

	if (mlx->bag_status == 1)
		put_img_transp(mlx, mlx->handbag, WIN_W - 366, WIN_H - 240);

	if (mlx->dialog != 0)
		ft_dialog(mlx);

	// DISPLAY THE IMG
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->display.img, 0, 0);

	// MESSAGES
	if (mlx->player.biking == -1)
		ft_start_dialog_check(mlx);

	// DISPLAY MESSAGE
	if (mlx->message)
	{
		mlx_string_put(mlx->mlx, mlx->win, WIN_W / 3, WIN_H - 50, 0xffffff, mlx->message);
		mlx->message = NULL;
	}


	mlx->player.using = 0;

	return (0);
}

int	exit_hook(t_mlx *mlx)
{
	exit_game(mlx);
	return (0);
}

void	ft_parsing(t_mlx *mlx)
{
	mlx->map = create_map(mlx);
	place_player_on_map(mlx, mlx->map);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	mlx->display.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->display.addr = mlx_get_data_addr(mlx->display.img,
			&mlx->display.bits_per_pixel,
			&mlx->display.line_length, &mlx->display.endian);
	get_textures(mlx);
}

int	main()
{
	t_mlx	mlx;

	mlx.player.plane_x = 0;
	mlx.player.plane_y = FOV;
	mlx.mapname = "maps/map.cub";

	ft_parsing(&mlx);
	mlx_mouse_hide(mlx.mlx, mlx.win);

	// INIT VARS
	mlx.player.rot_r = 0;
	mlx.player.rot_l = 0;
	mlx.player.up = 0;
	mlx.player.down = 0;
	mlx.player.left = 0;
	mlx.player.right = 0;
	mlx.player.inside = 0;
	mlx.player.using = 0;


	mlx.player.speed = 0;
	mlx.player.biking = -1;

	mlx.tmaxkeys = 0;
	mlx.bag_status = 0;

	mlx.dialog = 1;
	mlx.message = NULL;
	mlx.started = 0;
	mlx.crashed = 0;

	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);


	mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);
}
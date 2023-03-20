/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/20 17:53:21 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	open_door(t_mlx *mlx)
{

	printf("\nENTERING THE BAT\n");

	mlx->mapname = "maps/julbat.cub";

	mlx->player.dirX_save = -mlx->player.dirX;
	mlx->player.dirY_save = -mlx->player.dirY;
	mlx->player.posX_save = mlx->player.posX;
	mlx->player.posY_save = mlx->player.posY;
	mlx->player.planeX_save = -mlx->player.planeX;
	mlx->player.planeY_save = -mlx->player.planeY;

	mlx->player.inside = 1;
	mlx->player.biking = -1;

	mlx->player.planeX = 0;
	mlx->player.planeY = FOV;
	free_map(mlx, mlx->map);
	mlx->map = create_map(mlx);
	place_player_on_map(mlx, mlx->map);
}

void	close_door(t_mlx *mlx)
{
	printf("\nJE ME BARRE OF THE BAT\n");

	mlx->mapname = "maps/map.cub";

	mlx->player.posX = mlx->player.posX_save;
	mlx->player.posY = mlx->player.posY_save;
	mlx->player.planeX = mlx->player.planeX_save;
	mlx->player.planeY = mlx->player.planeY_save;
	mlx->player.dirX = mlx->player.dirX_save;
	mlx->player.dirY = mlx->player.dirY_save;

	mlx->player.inside = 0;
	mlx->player.using = 0;

	free_map(mlx, mlx->map);
	mlx->map = create_map(mlx);
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

		//printf("\e[1A\e[2Ki:%d\n", i);
		if (i >= 0 && i <= 50)
			put_img_transp(mlx, mlx->hand, WIN_W / 2 - 228, WIN_H - 118);
		else
			put_img_transp(mlx, mlx->hand2, WIN_W / 2 + 70, WIN_H - 118);
		if (i++ == 100)
			i = 0;
	}

	// DISPLAY THE IMG
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->display.img, 0, 0);

	// MESSAGES
	if (mlx->player.biking == -1
	&& mlx->player.posX - mlx->tmax.x <= 0.25 && mlx->player.posX - mlx->tmax.x >= -0.25 
	&& mlx->player.posY - mlx->tmax.y <= 0.25 && mlx->player.posY - mlx->tmax.y >= -0.25)
	{
		// Message
		printf("\e[1A\e[2KT-MAX A PROXIMITÉ\n");
		
		mlx->message = "Press F to get on the TMAX";
		if (mlx->player.using == 1)
		{
			mlx->tmax.x = 0;
			mlx->tmax.y = 0;
			mlx->player.biking = 1;
		}
	}
	if (mlx->message)
	{
		mlx_string_put(mlx->mlx, mlx->win, WIN_W / 2 - 12, WIN_H - 70, 0xffffff, mlx->message);
		mlx->message = NULL;
	}
	
	return (0);
}

int	exit_hook(t_mlx *mlx)
{
	exit_game(mlx);
	return (0);
}

int	mouse_hook(int key, t_mlx *mlx)
{
	(void)mlx;
	//printf("key:%d\n", key);
	if (key == 1)
		printf("\e[2APAN                            \n                                \n");
	return (0);
}

void	ft_parsing(t_mlx *mlx)
{
	check_map_ext(mlx);
	mlx->map = create_map(mlx);
	place_player_on_map(mlx, mlx->map);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	mlx->display.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->display.addr = mlx_get_data_addr(mlx->display.img, &mlx->display.bits_per_pixel,
			&mlx->display.line_length, &mlx->display.endian);


	// GET SPRITES
	mlx->in_wall.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/in_wall.xpm", &mlx->in_wall.tex_width, &mlx->in_wall.tex_height);
	mlx->in_wall.addr = mlx_get_data_addr(mlx->in_wall.img, &mlx->in_wall.bits_per_pixel, &mlx->in_wall.line_length, &mlx->in_wall.endian);
	
	mlx->in_wall2.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/in_wall2.xpm", &mlx->in_wall2.tex_width, &mlx->in_wall2.tex_height);
	mlx->in_wall2.addr = mlx_get_data_addr(mlx->in_wall2.img, &mlx->in_wall2.bits_per_pixel, &mlx->in_wall2.line_length, &mlx->in_wall2.endian);

	mlx->in_door_tex.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/in_door.xpm", &mlx->in_door_tex.tex_width, &mlx->in_door_tex.tex_height);
	mlx->in_door_tex.addr = mlx_get_data_addr(mlx->in_door_tex.img, &mlx->in_door_tex.bits_per_pixel, &mlx->in_door_tex.line_length, &mlx->in_door_tex.endian);

	

	mlx->bat_tex.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/out_wall.xpm", &mlx->bat_tex.tex_width, &mlx->bat_tex.tex_height);
	mlx->bat_tex.addr = mlx_get_data_addr(mlx->bat_tex.img, &mlx->bat_tex.bits_per_pixel, &mlx->bat_tex.line_length, &mlx->bat_tex.endian);

	mlx->bat2_tex.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/out_wall2.xpm", &mlx->bat2_tex.tex_width, &mlx->bat2_tex.tex_height);
	mlx->bat2_tex.addr = mlx_get_data_addr(mlx->bat2_tex.img, &mlx->bat2_tex.bits_per_pixel, &mlx->bat2_tex.line_length, &mlx->bat2_tex.endian);

	mlx->bat3_tex.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/out_wall3.xpm", &mlx->bat3_tex.tex_width, &mlx->bat3_tex.tex_height);
	mlx->bat3_tex.addr = mlx_get_data_addr(mlx->bat3_tex.img, &mlx->bat3_tex.bits_per_pixel, &mlx->bat3_tex.line_length, &mlx->bat3_tex.endian);

	mlx->door_tex.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/out_door.xpm", &mlx->door_tex.tex_width, &mlx->door_tex.tex_height);
	mlx->door_tex.addr = mlx_get_data_addr(mlx->door_tex.img, &mlx->door_tex.bits_per_pixel, &mlx->door_tex.line_length, &mlx->door_tex.endian);


	// JUL SPRITE
    mlx->jul.x = 5;
    mlx->jul.y = 25;
	mlx->jul.tex.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/jul.xpm", &mlx->jul.tex.tex_width, &mlx->jul.tex.tex_height);
	mlx->jul.tex.addr = mlx_get_data_addr(mlx->jul.tex.img, &mlx->jul.tex.bits_per_pixel, &mlx->jul.tex.line_length, &mlx->jul.tex.endian);
	
	// TMAX SPRITE
    mlx->tmax.x = TMAX_START_X;
    mlx->tmax.y = TMAX_START_Y;
	mlx->tmax.tex.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/tmax_onfoot.xpm", &mlx->tmax.tex.tex_width, &mlx->tmax.tex.tex_height);
	mlx->tmax.tex.addr = mlx_get_data_addr(mlx->tmax.tex.img, &mlx->tmax.tex.bits_per_pixel, &mlx->tmax.tex.line_length, &mlx->tmax.tex.endian);

	mlx->hand.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/hand.xpm", &mlx->hand.tex_width, &mlx->hand.tex_height);
	mlx->hand.addr = mlx_get_data_addr(mlx->hand.img, &mlx->hand.bits_per_pixel, &mlx->hand.line_length, &mlx->hand.endian);

	mlx->hand2.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/hand2.xpm", &mlx->hand2.tex_width, &mlx->hand2.tex_height);
	mlx->hand2.addr = mlx_get_data_addr(mlx->hand2.img, &mlx->hand2.bits_per_pixel, &mlx->hand2.line_length, &mlx->hand2.endian);
	



	mlx->bike.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/tmax.xpm", &mlx->bike.tex_width, &mlx->bike.tex_height);
	mlx->bike.addr = mlx_get_data_addr(mlx->bike.img, &mlx->bike.bits_per_pixel, &mlx->bike.line_length, &mlx->bike.endian);

	mlx->bike_wheel.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/tmax_wheel.xpm", &mlx->bike_wheel.tex_width, &mlx->bike_wheel.tex_height);
	mlx->bike_wheel.addr = mlx_get_data_addr(mlx->bike_wheel.img, &mlx->bike_wheel.bits_per_pixel, &mlx->bike_wheel.line_length, &mlx->bike_wheel.endian);


	mlx->crash.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/crash.xpm", &mlx->crash.tex_width, &mlx->crash.tex_height);

	mlx->startscreen.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/startscreen.xpm", &mlx->startscreen.tex_width, &mlx->startscreen.tex_height);

}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	mlx.player.planeX = 0;
	mlx.player.planeY = FOV;

	if (ac != 2)
		return (1);
	mlx.mapname = av[1];

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


	mlx.message = NULL;
	mlx.started = 0;
	mlx.crashed = 0;
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);

	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);
}

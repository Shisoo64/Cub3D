/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:47:59 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/24 17:56:56 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D_bonus.h"

void	init_structs(t_mlx *mlx)
{
	mlx->player.rot_r = 0;
	mlx->player.rot_l = 0;
	mlx->player.up = 0;
	mlx->player.down = 0;
	mlx->player.left = 0;
	mlx->player.right = 0;
	mlx->player.inside = 0;
	mlx->player.using = 0;
	mlx->player.speed = 0;
	mlx->player.use_phone = 0;
	mlx->player.biking = -1;
	mlx->tmaxkeys = 0;
	mlx->bag_status = 0;
	mlx->dialog = 1;
	mlx->wazing = -1;
	mlx->msg = NULL;
	mlx->started = 0;
	mlx->crashed = 0;
	mlx->player_nb = 0;
}

void	init_sprite(t_mlx *mlx, t_sprite *sprt, char *path, double coord[2])
{
	sprt->x = coord[0];
	sprt->y = coord[1];
	sprt->tex.img = mlx_xpm_file_to_image(mlx->mlx, path,
			&sprt->tex.tex_width, &sprt->tex.tex_height);
	sprt->tex.addr = mlx_get_data_addr(sprt->tex.img, &sprt->tex.bits_per_pixel,
			&sprt->tex.line_length, &sprt->tex.endian);
}

void	get_sprites(t_mlx *mlx)
{
	init_sprite(mlx, &mlx->jul, "./sprites/jul.xpm", (double []){4.2, 6.2});
	init_sprite(mlx, &mlx->sch, "./sprites/sch.xpm", (double []){12.3, 1.15});
	init_sprite(mlx, &mlx->bag, "./sprites/bag.xpm", (double []){4.6, 6.2});
	init_sprite(mlx, &mlx->tmax, "./sprites/tmax_onfoot.xpm",
		(double []){TMAX_START_X, TMAX_START_Y});
}

void	get_textures(t_mlx *mlx)
{
	init_tex(mlx, &mlx->in_wall, "./sprites/in_wall.xpm");
	init_tex(mlx, &mlx->in_wall2, "./sprites/in_wall2.xpm");
	init_tex(mlx, &mlx->in_door_tex, "./sprites/in_door.xpm");
	init_tex(mlx, &mlx->handbag, "./sprites/handbag.xpm");
	init_tex(mlx, &mlx->bat_tex, "./sprites/out_wall.xpm");
	init_tex(mlx, &mlx->bat2_tex, "./sprites/out_wall2.xpm");
	init_tex(mlx, &mlx->bat3_tex, "./sprites/out_wall3.xpm");
	init_tex(mlx, &mlx->door_tex, "./sprites/out_door.xpm");
	init_tex(mlx, &mlx->hand, "./sprites/hand.xpm");
	init_tex(mlx, &mlx->hand2, "./sprites/hand2.xpm");
	init_tex(mlx, &mlx->phone, "./sprites/phone.xpm");
	init_tex(mlx, &mlx->waze, "./sprites/phone_transp.xpm");
	init_tex(mlx, &mlx->bike, "./sprites/tmax.xpm");
	init_tex(mlx, &mlx->bike_wheel, "./sprites/tmax_wheel.xpm");
	init_tex(mlx, &mlx->crash, "./sprites/crash.xpm");
	init_tex(mlx, &mlx->startscreen, "./sprites/startscreen.xpm");
	get_sprites(mlx);
}

void	init_mlx(t_mlx *mlx, char **data)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
	{
		error_message("Mlx initialization failed.\n", NULL);
		exit_game_light(data);
	}
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	if (mlx->win == NULL)
	{
		error_message("Mlx initialization failed.\n", NULL);
		exit_game_light(data);
	}
	mlx->display.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	if (mlx->display.img == NULL)
	{
		error_message("Mlx initialization failed.\n", NULL);
		exit_game_light(data);
	}
	mlx->display.addr = mlx_get_data_addr(mlx->display.img,
			&mlx->display.bits_per_pixel,
			&mlx->display.line_length, &mlx->display.endian);
	mlx->no_tex.img = NULL;
	mlx->so_tex.img = NULL;
	mlx->we_tex.img = NULL;
	mlx->ea_tex.img = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 17:57:57 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3D_bonus.h"

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
		free_map(mlx->map);
		ft_change_map(mlx);
		place_player_on_map(mlx);
	}
	else
		mlx->msg = "Press F to open door";
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
		free_map(mlx->map);
		ft_change_map(mlx);
	}
	else
		mlx->msg = "Press F to open door";
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
		ft_dialog(mlx);
		if (mlx->player.biking == -1)
			ft_start_dialog(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->display.img, 0, 0);
		if (mlx->msg)
			mlx_string_put(mlx->mlx, mlx->win, 342, 717, 0xffffff, mlx->msg);
		mlx->msg = NULL;
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

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
	{
		error_message("Map argument is erroneous.\n", NULL);
		return (1);
	}
	mlx.mapname = av[1];
	ft_printf("Controls: \n"
		" WASD to move\n F to use\n M to take out your phone\n\n\n");
	mlx.player.plane_x = 0;
	mlx.player.plane_y = FOV;
	ft_parsing(&mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);
	mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}

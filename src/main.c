/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/28 18:19:19 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	frames(t_vars *vars)
{
	(void)vars;
	usleep(1000000 / 60);
	return (0);
}

int	inputs(int key, t_vars *vars)
{
	if (key == ESC)
		exit_game(vars);
	/*
	else if (key == KEY_UP)
		move_player(1, 0, vars);
	else if (key == KEY_LEFT)
		move_player(0, -1, vars);
	else if (key == KEY_DOWN)
		move_player(-1, 0, vars);
	else if (key == KEY_RIGHT)
		move_player(0, 1, vars);
		*/
	return (0);
}

int	exit_hook(t_vars *vars)
{
	exit_game(vars);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		return (1);
	vars.mapname = av[1];
	check_map_ext(&vars);
	create_map(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_W, WIN_H, "cub3d");
	mlx_key_hook(vars.win, inputs, &vars);
	mlx_loop_hook(vars.mlx, frames, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	mlx_loop(vars.mlx);
}

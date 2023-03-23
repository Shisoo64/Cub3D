/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/23 17:23:55 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	frames(t_mlx *mlx)
{
	ft_display(mlx);
	input_manager(mlx);
	// DISPLAY THE IMG
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->display.img, 0, 0);
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
	//mlx->map = create_map(mlx);
	ft_fill_map(mlx);
	place_player_on_map(mlx, mlx->map);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "cub3D");
	mlx->display.img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->display.addr = mlx_get_data_addr(mlx->display.img, &mlx->display.bits_per_pixel,
			&mlx->display.line_length, &mlx->display.endian);

	// GET SPRITES
	mlx->wall.img = mlx_xpm_file_to_image(mlx->mlx, "./sprites/in_wall.xpm", &mlx->wall.tex_width, &mlx->wall.tex_height);
	mlx->wall.addr = mlx_get_data_addr(mlx->wall.img, &mlx->wall.bits_per_pixel, &mlx->wall.line_length, &mlx->wall.endian);

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

	mlx_hook(mlx.win, 2, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.win, 3, 1L << 1, key_release, &mlx);

	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_loop_hook(mlx.mlx, frames, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_loop(mlx.mlx);
}

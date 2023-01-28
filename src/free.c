/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:52:00 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/29 00:37:24 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_game(t_vars *vars)
{
	//free_map(vars, vars->map);
	//free_img(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

/*
void	exit_game_light(t_vars *vars, int map)
{
	if (map)
		free_map(vars, vars->map);
	free_img(vars);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

void	free_map(t_vars *vars, char **map)
{
	int	y;

	y = 0;
	while (y < vars->map_y)
		free(map[y++]);
	free(map);
}
*/

//void	free_img(t_vars *v)
//{
//	mlx_destroy_image(v->mlx, v->sprites.w_u);
//}
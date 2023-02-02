/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:31 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/02 15:14:40 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_display *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	check_map_ext(t_mlx *v)
{
	int		i;
	char	*ext;

	i = 1;
	ext = ".cub";
	if (ft_strlen(v->mapname) < 5
		|| v->mapname[ft_strlen(v->mapname) - 5] == '/')
	{
		ft_printf("Error\nNo map name!\n");
		exit(1);
	}
	while (++i < 5)
		if (v->mapname[ft_strlen(v->mapname) - i] != ext[4 - i])
		{
			ft_printf("Error\nProblem with map extension.\n");
			exit (1);
		}
}

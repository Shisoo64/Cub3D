/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:31 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/28 18:12:49 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	check_map_ext(t_vars *v)
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

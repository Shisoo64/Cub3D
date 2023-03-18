/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/18 20:56:51 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

#include "cub3D.h"

typedef struct s_raycast {
	//what cardinal point the raycast hit is perpendicular to
	int		side;


	//what type of wall the ray has hit
	int		wall_type;

	//what direction to step in x or y-direction (either +1 or -1)
	int		stepX;
	int		stepY;

	double	raydirX;
	double	raydirY;

	//which box of the map we're in
	int		mapX;
	int		mapY;


	int		tex_x;

	//length of ray from current position to next x or y-side
	double	sideDistX;
	double	sideDistY;
	double	DeltaDistX;
	double	DeltaDistY;
}				t_raycast;


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/31 18:55:40 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

# define WIN_W 1024
# define WIN_H 768
# define MOVESPEED 0.25
# define ROTSPEED 0.25
# define FRAMETIME 30

# define VERTCOLOR 0xFFE7CC
# define HORIZCOLOR 0xFFFBEB
# define SKYCOLOR 0xECF9FF
# define FLOORCOLOR 0xF8CBA6

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars {
	void		*mlx;
	void		*win;
	t_data		img;
	char		**map;
	char		*mapname;
	int			map_y;
	int			map_x;

	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
}				t_vars;

enum e_keycode
{
	KEY_UP = 115,
	KEY_DOWN = 119,
	KEY_LEFT = 97,
	KEY_RIGHT = 100,
	ESC = 0xFF1B
};

void	exit_game(t_vars *vars);
char	**create_map(t_vars *vars);
int		frames(t_vars *vars);
void	check_map_ext(t_vars *v);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif

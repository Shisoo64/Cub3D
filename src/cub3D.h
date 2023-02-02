/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/02 20:05:39 by rlaforge         ###   ########.fr       */
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
# define MOVESPEED 0.1
# define ROTSPEED 0.15

# define YCOLOR 0xFFE7CC
# define XCOLOR 0xFFFBEB
# define SKYCOLOR 0xECF9FF
# define FLOORCOLOR 0xF8CBA6

typedef struct s_display {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_display;

typedef struct s_player {
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}				t_player;

typedef struct s_raycast {
	//what cardinal point the raycast hit is perpendicular to
	int	side;

	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;

	//calculate ray position and direction
	double cameraX;

	double raydirX;
	double raydirY;

	//which box of the map we're in
	int mapX;
	int mapY;

	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;
	double DeltaDistX;
	double DeltaDistY;
}				t_raycast;

typedef struct s_mlx {
	void		*mlx;
	void		*win;
	char		**map;
	char		*mapname;
	int			map_y;
	int			map_x;
	t_display	display;
	t_player	player;
}				t_mlx;

enum e_keycode
{
	KEY_UP = 115,
	KEY_DOWN = 119,
	KEY_LEFT = 97,
	KEY_RIGHT = 100,
	ESC = 0xFF1B
};

void	exit_game(t_mlx *mlx);
char	**create_map(t_mlx *mlx);
int		frames(t_mlx *mlx);
void	check_map_ext(t_mlx *v);
void	my_mlx_pixel_put(t_display *data, int x, int y, int color);

#endif

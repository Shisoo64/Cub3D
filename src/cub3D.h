/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/02/12 01:46:08 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

// Colors
# define YCOLOR 0xD84727
# define XCOLOR 0xEF7B45
# define SKYCOLOR 0x5EB1BF
# define FLOORCOLOR 0x000000//0xFFECD1


# define FOV 0.8
# define FPS 60

#define texWidth 64
#define texHeight 64

// Screen size
# define WIN_W 1024
# define WIN_H 768

// Movement
# define MOVESPEED 0.00001//0.05
# define ROTSPEED 0.000005



// NEW
# define CRASH_SPEED 750


//
//		STRUCTS
typedef struct s_raycast {
	//what cardinal point the raycast hit is perpendicular to
	int		side;

	//what direction to step in x or y-direction (either +1 or -1)
	int		stepX;
	int		stepY;

	double	raydirX;
	double	raydirY;

	//which box of the map we're in
	int		mapX;
	int		mapY;

	//length of ray from current position to next x or y-side
	double	sideDistX;
	double	sideDistY;
	double	DeltaDistX;
	double	DeltaDistY;
}				t_raycast;

typedef struct s_player {
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;



	int	rot_l;
	int rot_r;
	int left;
	int right;
	int up;
	int down;

}				t_player;

typedef struct s_display {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_display;

typedef struct s_mlx {
	void		*mlx;
	void		*win;
	char		**map;
	char		*mapname;
	int			map_y;
	int			map_x;
	t_display	display;
	t_player	player;


	t_display	*texture;
	t_display	*bike;
	t_display	*bike_wheel;

}				t_mlx;

//
//		PARSING
void	check_map_ext(t_mlx *v);
char	**create_map(t_mlx *mlx);
void	rotate_player(int multi, t_player *player);

//
//		MOVEMENT
int		inputs(int key, t_mlx *mlx);

int	key_press(int key, t_mlx *mlx);
int	key_release(int key, t_mlx *mlx);
int	input_manager(t_mlx *mlx);

enum e_keycode
{
	KEY_W = 115,
	KEY_S = 119,
	KEY_A = 97,
	KEY_D = 100,
	KEY_Q = 113,
	KEY_E = 101,
	KEY_ARROW_L = 65361,
	KEY_ARROW_R = 65363,
	ESC = 0xFF1B
};

//
//		RENDER
int		frames(t_mlx *mlx);
void	ft_display(t_mlx *mlx);

//
//		MLX
void	my_mlx_pixel_put(t_display *data, int x, int y, int color);
void	exit_game(t_mlx *mlx);


#endif

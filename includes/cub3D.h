/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/09 22:41:53 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include "player_settings.h"

//
//		STRUCTS
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
	int		tex_width;
	int		tex_height;
}				t_display;

typedef struct s_mlx {
	void		*mlx;
	void		*win;
	char		**map;
	char		*mapname;
	int			map_y;
	int			map_x;
	int			color_f;
	int			color_c;
	t_display	display;

	t_player	player;

	t_display	NO_tex;
	t_display	SO_tex;
	t_display	WE_tex;
	t_display	EA_tex;
}				t_mlx;

//
//		PARSING
void	ft_parsing(t_mlx *mlx);
void	check_map_ext(t_mlx *v);
void	ft_fill_map(t_mlx *mlx, char **data);
void	ft_map_height(t_mlx *mlx, char **data);
int		is_input(char *line);
void	place_player_on_map(t_mlx *mlx);
int		is_asset(char *line);
void	fetch_assets(t_mlx *mlx, char **data);
void	get_colors(t_mlx *mlx, char *line);
void	get_wall_textures(t_mlx *mlx, char *line);
void	draw_line(t_mlx *mlx, int beginX, int beginY, int endX, int endY, int color);


//
//		MOVEMENT
void	input_manager_foot(t_mlx *mlx);
void	rotate_player(int multi, t_player *player);

//
//		INPUTS
int		key_press(int key, t_mlx *mlx);
int		key_release(int key, t_mlx *mlx);
int		input_manager(t_mlx *mlx);

//
//		RENDER
int		frames(t_mlx *mlx);
void	ft_display(t_mlx *mlx);
void	ft_raycast(t_mlx *mlx, t_raycast *ray, int x);
void    draw_minimap(t_mlx *mlx, t_raycast *ray);

//
//		SCREENS
void	draw_backdrop(t_mlx *mlx);

//
//		FREE
void	free_map(t_mlx *mlx, char **map);

//
//		ERRORS
void	error_message(char *msg, char *line);
void	check_assets(t_mlx *mlx, char **data);

//
//		MLX
void	my_mlx_pixel_put(t_display *data, int x, int y, int color);
int		my_mlx_get_color(t_display *texture, int x, int y);
void	put_img_transp(t_mlx *mlx, t_display img, int pad_x, int pad_y);
void	exit_game(t_mlx *mlx);
void	exit_game_light(t_mlx *mlx);

int		ft_strcspn(char *s, const char *rejects);
int		ft_strspn(char *s, const char *accepts);
char	*ft_strtok(char *str, char *token);
void	print_map(char **map);

#endif

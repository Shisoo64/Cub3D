/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/14 19:00:28 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "../../mlx_linux/mlx.h"
# include "../../libft/libft.h"
# include "player_settings.h"

//
//		STRUCTS
typedef struct s_display {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		tex_width;
	int		tex_height;
}				t_display;

typedef struct s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	int		rot_l;
	int		rot_r;
	int		left;
	int		right;
	int		up;
	int		down;

}				t_player;

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

	t_display	no_tex;
	t_display	so_tex;
	t_display	we_tex;
	t_display	ea_tex;
}				t_mlx;

typedef struct s_raycast {
	int			side;
	int			wall_type;

	int			step_x;
	int			step_y;

	double		raydir_x;
	double		raydir_y;

	double		perpwalldists[WIN_W];
	int			lineheight;
	int			tex_x;

	int			map_x;
	int			map_y;

	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	t_display	*display;
}				t_raycast;

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
void	init_mlx(t_mlx *mlx);

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

//
//		SCREENS
void	draw_backdrop(t_mlx *mlx);

//
//		FREE
void	free_map(char **map);

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
void	exit_game_light(t_mlx *mlx, char **data);

int		ft_strcspn(char *s, const char *rejects);
int		ft_strspn(char *s, const char *accepts);
char	*ft_strtok(char *str, char *token);
void	print_map(char **map);

//
//		UTILS
void	error_message(char *msg, char *line);
int		is_input(char *line);
int		is_asset(char *line);

#endif

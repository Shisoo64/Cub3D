/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/19 15:23:18 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
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
	int			player_nb;
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
//		INITIALIZE
void		init_data(t_mlx *mlx);
void		init_mlx(t_mlx *mlx);

//
//		PARSING
void		ft_parsing(t_mlx *mlx);
void		check_map_ext(t_mlx *v);
void		ft_fill_map(t_mlx *mlx, char **data);
void		ft_map_height(t_mlx *mlx, char **data);
void		place_player_on_map(t_mlx *mlx);
void		fetch_assets(t_mlx *mlx, char **data);

//
//		ASSETS
void		fetch_assets(t_mlx *mlx, char **data);
void		get_wall_textures(t_mlx *mlx, char *line);
int			fill_color(char *line);
void		get_colors(t_mlx *mlx, char *line);

//
//		MOVEMENT
void		input_manager_foot(t_mlx *mlx);
void		rotate_player(int multi, t_player *player);

//
//		INPUTS
int			key_press(int key, t_mlx *mlx);
int			key_release(int key, t_mlx *mlx);
int			input_manager(t_mlx *mlx);

//
//		RENDER
void		ft_display(t_mlx *mlx);
void		ft_raycast(t_mlx *mlx, t_raycast *ray, int x);
void		draw_backdrop(t_mlx *mlx);

//
//		FREE
void		free_map(char **map);
void		exit_game(t_mlx *mlx);
void		exit_game_light(t_mlx *mlx, char **data);

//
//		ERRORS
void		error_message(char *msg, char *line);
void		check_assets(t_mlx *mlx, char **data);

//
//		MLX
void		my_mlx_pixel_put(t_display *data, int x, int y, int color);
int			my_mlx_get_color(t_display *texture, int x, int y);

//
//		UTILS_PARSING
int			is_mapline_ok(char *line);
int			is_asset(char *line);
int			is_colorline_ok(char *str);
int			get_next_color(char *line);

//
//		UTILS_MAP
void		check_map_borders(t_mlx *mlx, char **data);
int			check_surround_cells(char **test_map);

//
//		UTILS_RENDERING
void		draw_line_tex(t_display *tex, t_raycast *ray, int x,
				int draw_coord[2]);
void		get_tex_line(t_raycast *ray, t_mlx *mlx, int draw_coord[2], int x);
t_display	identify_wall(t_mlx *mlx, t_raycast *ray);
void		ft_sidedist_calc(t_mlx *mlx, t_raycast *ray);

#endif

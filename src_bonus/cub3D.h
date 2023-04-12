/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/12 15:24:33 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "player_settings.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

//
//		STRUCTS
typedef struct s_display
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			tex_width;
	int			tex_height;
}				t_display;

typedef struct s_raycast
{
	int			side;
	int			hit_type;

	int			step_x;
	int			step_y;

	double		raydir_x;
	double		raydir_y;

	int			map_x;
	int			map_y;

	int			tex_x;

	double		perpwalldists[WIN_W];
	int			lineheight;

	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	t_display	*display;
}				t_raycast;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;

	double		plane_x_save;
	double		plane_y_save;
	double		dir_x_save;
	double		dir_y_save;
	double		pos_x_save;
	double		pos_y_save;

	double		speed;
	int			inside;
	int			biking;
	int			use_phone;
	int			using;
	int			rot_l;
	int			rot_r;
	int			left;
	int			right;
	int			up;
	int			down;

}				t_player;

typedef struct s_sprite
{
	double		x;
	double		y;
	t_display	tex;
}				t_sprite;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	char		**map;
	char		*mapname;
	int			map_y;
	int			map_x;

	int			started;
	int			crashed;

	int			dialog;
	char		*message;
	int			wazing;

	int			tmaxkeys;
	int			bag_status;

	t_display	display;
	t_player	player;

	t_display	hand;
	t_display	hand2;
	t_display	phone;
	t_display	waze;

	t_sprite	jul;
	t_sprite	sch;
	t_sprite	bag;
	t_sprite	tmax;

	t_display	handbag;
	t_display	in_wall;
	t_display	in_wall2;
	t_display	bat_tex;
	t_display	bat2_tex;
	t_display	bat3_tex;
	t_display	door_tex;
	t_display	in_door_tex;
	t_display	startscreen;
	t_display	crash;
	t_display	bike;
	t_display	bike_wheel;

}				t_mlx;

//
//		PARSING
void			get_textures(t_mlx *mlx);
char			**create_map(t_mlx *mlx);
void			place_player_on_map(t_mlx *mlx, char **map);
void			ft_parsing(t_mlx *mlx);
void			free_map(t_mlx *mlx, char **map);

//
//		MOVEMENT
void			input_manager_foot(t_mlx *mlx);
void			input_manager_bike(t_mlx *mlx);
void			rotate_player(int multi, t_player *player);

//
//		INPUTS
int				key_press(int key, t_mlx *mlx);
int				key_release(int key, t_mlx *mlx);
int				input_manager(t_mlx *mlx);

//
//		TRUCS
void			open_door(t_mlx *mlx, char *mapname, int batnbr);
void			close_door(t_mlx *mlx);

//
//		RENDER
int				frames(t_mlx *mlx);
void			ft_rendering(t_mlx *mlx);
void			ft_raycast(t_mlx *mlx, t_raycast *ray, int x);
void			ft_render_sprite(t_raycast *ray, t_mlx *mlx, t_sprite texture);
void			ft_render_out_vline(t_raycast *ray, t_mlx *mlx, int x);
void			ft_render_in_vline(t_raycast *ray, t_mlx *mlx, int x);
void			draw_minimap(t_mlx *mlx, int pad_x, int pad_y);

//
//		SCREENS
void			start_screen(t_mlx *mlx);
void			crash_screen(t_mlx *mlx);
void			draw_backdrop(t_mlx *mlx);
void			ft_dialog(t_mlx *mlx);

//
//		MLX
void			my_mlx_pixel_put(t_display *data, int x, int y, int color);
int				my_mlx_get_color(t_display *texture, int x, int y);
void			put_img_transp(t_mlx *mlx, t_display img, int pad_x, int pad_y);
void			exit_game(t_mlx *mlx);

#endif

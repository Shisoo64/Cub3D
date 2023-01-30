/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/30 17:58:20 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

# define WIN_W 480
# define WIN_H 320


typedef struct	s_data {
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

#endif

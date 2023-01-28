/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/28 18:19:28 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

# define WIN_W 480
# define WIN_H 320

typedef struct s_vars {
	void		*mlx;
	void		*win;
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

void		exit_game(t_vars *vars);
char		**create_map(t_vars *vars);
int			get_map_height(t_vars *vars);
int			frames(t_vars *vars);

void		check_map_ext(t_vars *v);

#endif

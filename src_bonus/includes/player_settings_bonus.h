/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_settings_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2024/03/21 12:07:37 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_SETTINGS_BONUS_H
# define PLAYER_SETTINGS_BONUS_H

// Colors
# define SKYCOLOR 0x2faee0
# define FLOORCOLOR 0xFFECD1

# define CEILINGCOLOR 0xc7c7c7
# define IN_FLOORCOLOR 0xc4c4c4

# define FOV 0.8
# define FPS 60

// Screen size
# define WIN_W 1024
# define WIN_H 768

// Movement
# define MOVESPEED 0.00001//0.05
# define ROTSPEED 0.000005

# define CRASH_SPEED 750

//# define TMAX_START_X 8.65
//# define TMAX_START_Y 30.5
# define TMAX_START_X 9.2
# define TMAX_START_Y 33.2

enum e_keycode
{
	KEY_W = 115,
	KEY_S = 119,
	KEY_A = 97,
	KEY_D = 100,
	KEY_Q = 113,
	KEY_E = 101,
	KEY_F = 102,
	KEY_M = 109,
	KEY_ARROW_L = 65361,
	KEY_ARROW_R = 65363,
	ESC = 0xFF1B
};

#endif

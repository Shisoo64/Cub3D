/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_settings.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchabot <bchabot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:20:10 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/11 17:11:30 by bchabot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_SETTINGS_H
# define PLAYER_SETTINGS_H

# define FOV 0.66

// Screen size
# define WIN_W 1024
# define WIN_H 768

// Movement
# define MOVESPEED 0.0001
# define ROTSPEED 0.000005

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

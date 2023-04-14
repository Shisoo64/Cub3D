/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dialog.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:47:24 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/14 19:04:22 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_dialog(t_mlx *mlx)
{
	int	y;
	int	x;

	y = WIN_H - (WIN_H / 5);
	while (++y <= WIN_H)
	{
		x = -1;
		while (++x <= WIN_W)
			my_mlx_pixel_put(&mlx->display, x, y, 0);
	}
}

void	starting_dialog_ext(t_mlx *mlx)
{
	if (mlx->dialog == 2)
	{
		ft_playsound(1, "paplay ./ringtone.ogg &");
		mlx->message = "*sonnerie de telephone*";
	}
	else if (mlx->dialog == 3)
	{
		ft_playsound(0, NULL);
		mlx->message = "*decroche*";
	}
	else if (mlx->dialog == 4)
	{
		ft_playsound(1, "paplay ./dialog1.ogg &");
		put_img_transp(mlx, mlx->phone, WIN_W / 2 + 90, WIN_H - 320);
		mlx->message = "slt la famille c JuL";
	}
	else if (mlx->dialog == 5)
	{
		ft_playsound(1, "paplay ./dialog1.ogg &");
		put_img_transp(mlx, mlx->phone, WIN_W / 2 + 90, WIN_H - 320);
		mlx->message = "oe fodrai juste ke tu viene me voir vite fai";
	}
	else if (mlx->dialog == 6)
	{
		ft_playsound(1, "paplay ./dialog1.ogg &");
		put_img_transp(mlx, mlx->phone, WIN_W / 2 + 90, WIN_H - 320);
		mlx->message = "jui dan le bat tou seul o mileu tu pe pa louper";
	}
	else if (mlx->dialog == 7)
	{
		ft_playsound(1, "paplay ./dialog1.ogg &");
		put_img_transp(mlx, mlx->phone, WIN_W / 2 + 90, WIN_H - 320);
		mlx->message = "aller a tte";
	}
}

void	starting_dialog(t_mlx *mlx)
{
	starting_dialog_ext(mlx);
	if (mlx->dialog > 5)
	{
		mlx->dialog = 0;
		return ;
	}
	if (mlx->player.using == -1)
		mlx->dialog++;
}

void	jul_dialog(t_mlx *mlx)
{
	if (mlx->dialog == 10)
			mlx->message = NULL;
	else if (mlx->dialog == 11)
		mlx->message = "wsh mon sang sa va ou koi??";
	else if (mlx->dialog == 12)
		mlx->message = "oe g besoin ke tu maide sur un truk";
	else if (mlx->dialog == 13)
		mlx->message = "fodrai ke taille passer se sac au S dan la tour la ba";
	else if (mlx->dialog == 14)
		mlx->message = "c ok pr toi????";
	else if (mlx->dialog == 15)
		mlx->message = "Aler tien pren les cle du T-Max"
			" il et garer juste derier le bat";
	else if (mlx->dialog == 16)
		mlx->message = "*you've obtained the keys*";
	else
	{
		mlx->bag_status = 1;
		mlx->bag.x = 0;
		mlx->bag.y = 0;
		mlx->tmaxkeys = 1;
		mlx->dialog = 0;
	}
	if (mlx->player.using == -1)
		mlx->dialog++;
}

void	sch_dialog(t_mlx *mlx)
{
	if (mlx->dialog == 20)
			mlx->message = NULL;
	else if (mlx->dialog == 21)
		mlx->message = "Salut mon gate, comment va?";
	else if (mlx->dialog == 22)
		mlx->message = "La famille, les amis, la bonne mere";
	else if (mlx->dialog == 23)
		mlx->message = "Bon parfait alors";
	else if (mlx->dialog == 24)
		mlx->message = "Ca fait plaisir que t'ai pu nous depanner,"
			" tiens garde le t-max en cadeau";
	else if (mlx->dialog == 25)
		mlx->message = "Aller on se capte une autre fois";
	else
	{
		mlx->bag_status = 2;
		mlx->bag.x = 12.65;
		mlx->bag.y = 1.1;
		mlx->dialog = 0;
		return ;
	}
	if (mlx->player.using == -1)
		mlx->dialog++;
}

	#include <sys/types.h>
	#include <sys/wait.h>

void	ft_playsound(int play, char *param)
{
	static int	playing;

	if (play && !playing)
	{
		playing = 1;
		system(param);
	}
	else if (play == 0 && playing)
	{
		playing = 0;
		system("killall paplay");
	}
}

void	ft_dialog(t_mlx *mlx)
{
	if (mlx->dialog >= 1 && mlx->dialog < 10)
		starting_dialog(mlx);
	else if (mlx->dialog >= 10 && mlx->dialog < 20)
	{
		ft_playsound(1, "paplay ./dialog1.ogg &");
		jul_dialog(mlx);
	}
	else if (mlx->dialog >= 20 && mlx->dialog < 30)
		sch_dialog(mlx);
	draw_dialog(mlx);
}

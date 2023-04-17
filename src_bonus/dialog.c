/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dialog.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:47:24 by rlaforge          #+#    #+#             */
/*   Updated: 2023/04/17 15:09:23 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	starting_dialog_ext(t_mlx *mlx)
{
	if (mlx->dialog == 4)
	{
		ft_playsound(1, "paplay ./sounds/dialog1.ogg &");
		put_img_transp(mlx, mlx->phone, WIN_W / 2 + 90, WIN_H - 320);
		mlx->msg = "slt la famille c JuL";
	}
	else if (mlx->dialog == 5)
	{
		ft_playsound(1, "paplay ./sounds/dialog1.ogg &");
		put_img_transp(mlx, mlx->phone, WIN_W / 2 + 90, WIN_H - 320);
		mlx->msg = "oe fodrai juste ke tu viene me voir vite fai";
	}
	else if (mlx->dialog == 6)
	{
		ft_playsound(1, "paplay ./sounds/dialog1.ogg &");
		put_img_transp(mlx, mlx->phone, WIN_W / 2 + 90, WIN_H - 320);
		mlx->msg = "jui dan le bat tou seul o mileu tu pe pa louper";
	}
	else if (mlx->dialog == 7)
	{
		ft_playsound(1, "paplay ./sounds/dialog1.ogg &");
		put_img_transp(mlx, mlx->phone, WIN_W / 2 + 90, WIN_H - 320);
		mlx->msg = "aller a tte";
	}
}

void	starting_dialog(t_mlx *mlx)
{
	if (mlx->dialog == 2)
	{
		ft_playsound(1, "paplay ./sounds/ringtone.ogg &");
		mlx->msg = "*sonnerie de telephone*";
	}
	else if (mlx->dialog == 3)
	{
		ft_playsound(0, NULL);
		mlx->msg = "*decroche*";
	}
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
			mlx->msg = NULL;
	else if (mlx->dialog == 11)
		mlx->msg = "wsh mon sang sa va ou koi??";
	else if (mlx->dialog == 12)
		mlx->msg = "oe g besoin ke tu maide sur un truk";
	else if (mlx->dialog == 13)
		mlx->msg = "fodrai ke taille passer se sac au S dan la tour la ba";
	else if (mlx->dialog == 14)
		mlx->msg = "c ok pr toi????";
	else if (mlx->dialog == 15)
		mlx->msg = "Aler tien pren les cle du T-Max"
			" il et garer juste derier le bat";
	else if (mlx->dialog == 16)
		mlx->msg = "*you've obtained the keys*";
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
			mlx->msg = NULL;
	else if (mlx->dialog == 21)
		mlx->msg = "Salut mon gate, comment va?";
	else if (mlx->dialog == 22)
		mlx->msg = "La famille, les amis, la bonne mere";
	else if (mlx->dialog == 23)
		mlx->msg = "Bon parfait alors";
	else if (mlx->dialog == 24)
		mlx->msg = "Ca fait plaisir que t'ai pu nous depanner,"
			" tiens garde le t-max en cadeau";
	else if (mlx->dialog == 25)
		mlx->msg = "Aller on se capte une autre fois";
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

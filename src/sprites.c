/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:55:07 by rlaforge          #+#    #+#             */
/*   Updated: 2023/03/20 15:55:07 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

/*//arrays used to sort the sprites
int spriteOrder[numSprites];
double spriteDistance[numSprites];*/

void    draw_line_sprite(t_display *texture, t_display *display, int x, int lineHeight, int draw_start, int draw_end, int tex_x)
{
	double	step;
	double	tex_pos;
	int		color;
	int		tex_y;
	int		y;

	step = 1.0 * texture->tex_height / lineHeight;
	tex_pos = (draw_start - WIN_H / 2 + lineHeight / 2) * step;
	y = draw_start;
	tex_x = texture->tex_width - tex_x;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = my_mlx_get_color(texture, tex_x, tex_y);
		if (color != 0x00FF00)
    		my_mlx_pixel_put(display, x, y, color);
		y++;
	}
}

void	ft_render_sprite(t_raycast *ray, t_mlx *mlx, t_sprite texture)
{
    int stripe;

    /*for(int i = 0; i < numSprites; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded
    }
    sortSprites(spriteOrder, spriteDistance, numSprites);*/

    //after sorting the sprites, do the projection and draw them
    //for(int i = 0; i < 1; i++)
    //{
      //translate sprite position to relative to camera
      double spriteX = texture.x - mlx->player.posX;
      double spriteY = texture.y - mlx->player.posY;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (mlx->player.planeX * mlx->player.dirY - mlx->player.dirX * mlx->player.planeY); //required for correct matrix multiplication

      double transformX = invDet * (mlx->player.dirY * spriteX - mlx->player.dirX * spriteY);
      double transformY = invDet * (-mlx->player.planeY * spriteX + mlx->player.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = (int)((WIN_W / 2) * (1 + transformX / transformY));

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(WIN_H / 2 / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + WIN_H / 2;
      if (drawStartY < 0)
        drawStartY = 0;
      int drawEndY = spriteHeight / 2 + WIN_H / 2;
      if (drawEndY >= WIN_H)
        drawEndY = WIN_H - 1;

      //calculate width of the sprite
      int spriteWidth = abs((int)(WIN_H / 2 / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0)
        drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= WIN_W)
        drawEndX = WIN_W - 1;

      //loop through every vertical stripe of the sprite on screen
      stripe = drawStartX;
      while (stripe < drawEndX)
      {
        int tex_x = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) *  texture.tex.tex_width / spriteWidth) / 256;
        if(transformY > 0 && stripe > 0 && stripe < WIN_W && transformY - 0.6 < ray->ZBuffer[stripe])
          draw_line_sprite(&texture.tex, &mlx->display, stripe, spriteHeight, drawStartY, drawEndY, tex_x);
        stripe++;
    }
}

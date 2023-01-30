/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlaforge <rlaforge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:39:33 by rlaforge          #+#    #+#             */
/*   Updated: 2023/01/30 18:16:46 by rlaforge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


int	toto(t_vars *vars)
{
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	int	x;

	ft_printf("FRAME\n");
	x = -1;
	while (++x < WIN_W)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)WIN_W - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      //these are derived as:

      //which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
      //where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
      //unlike (dirX, dirY) is not 1, however this does not matter, only the
      //ratio between deltaDistX and deltaDistY matters, due to the way the DDA
      //stepping further below works. So the values can be computed as below.
      // Division through zero is prevented, even though technically that's not
      // needed in C++ with IEEE 754 floating point values.

	double DeltaDistX;
	double DeltaDistY;

	if(rayDirX == 0)
		DeltaDistX = 1000;
	else
		DeltaDistX = fabs(1 / rayDirX);
	//	DeltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));

	if(rayDirY == 0)
		DeltaDistY = 1000;
	else
		DeltaDistY = fabs(1 / rayDirY);
    //	DeltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * DeltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * DeltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * DeltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * DeltaDistY;
      }
      //perform DDA
      while(hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += DeltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += DeltaDistY;
          mapY += stepY;
          side = 1;
        }

        if(mapX > vars->map_x - 1)
			mapX = vars->map_x - 1;

		if(mapY > vars->map_y - 1)
			mapY = vars->map_y - 1;

        //Check if ray has hit a wall
        if(vars->map[mapY][mapX] && vars->map[mapY][mapX] == '1')
			hit = 1;
      }
      //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
      //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
      //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
      //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
      //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
      //steps, but we subtract deltaDist once because one step more into the wall was taken above.
      if(side == 0)
	  	perpWallDist = (sideDistX - DeltaDistX);
      else
	  	perpWallDist = (sideDistY - DeltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(WIN_H / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + WIN_H / 2;
      if(drawStart < 0)
	  	drawStart = 0;
      int drawEnd = lineHeight / 2 + WIN_H / 2;
      if(drawEnd >= WIN_H)
	  	drawEnd = WIN_H - 1;

      //draw the pixels of the stripe as a vertical line
	  while (drawStart < drawEnd)
		my_mlx_pixel_put(&vars->img, x, drawStart++, 0xffffff);
    }

	//redraw
	//mlx_clear_window(vars->mlx, vars->win);

	/* MOVEMENT

    //speed modifiers
    double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
    readKeys();
    //move forward if no wall in front of you
    if(keyDown(SDLK_UP))
    {
      if(vars->map[(int)(posX + dirX * moveSpeed)][(int)posY] == false)
	  	posX += dirX * moveSpeed;
      if(vars->map[(int)posX][(int)(posY + dirY * moveSpeed)] == false)
	  	posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if(keyDown(SDLK_DOWN))
    {
      if(vars->map[(int)(posX - dirX * moveSpeed)][(int)posY] == false)
	  	posX -= dirX * moveSpeed;
      if(vars->map[(int)posX][(int)(posY - dirY * moveSpeed)] == false)
	  	posY -= dirY * moveSpeed;
    }
    //rotate to the right
    if(keyDown(SDLK_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if(keyDown(SDLK_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    }

	*/

	return (0);
}


int	frames(t_vars *vars)
{
	(void)vars;
	return (0);
}

int	inputs(int key, t_vars *vars)
{
	if (key == ESC)
		exit_game(vars);
	/*
	else if (key == KEY_UP)
		move_player(1, 0, vars);
	else if (key == KEY_LEFT)
		move_player(0, -1, vars);
	else if (key == KEY_DOWN)
		move_player(-1, 0, vars);
	else if (key == KEY_RIGHT)
		move_player(0, 1, vars);
		*/
	return (0);
}

int	exit_hook(t_vars *vars)
{
	exit_game(vars);
	return (0);
}

void	print_map(t_vars *vars)
{
	int	y;
	int	x;

	y = -1;
	while (++y < vars->map_y)
	{
		x = -1;
		while (++x < vars->map_x && ft_isdigit(vars->map[y][x] + 48))
			ft_printf("%d", vars->map[y][x]);
		ft_printf("\n");
	}
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		return (1);
	vars.mapname = av[1];
	check_map_ext(&vars);
	vars.map = create_map(&vars);

/*
vars->map = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
*/

	print_map(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_W, WIN_H, "cub3d");

	vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel,
			&vars.img.line_length, &vars.img.endian);

	toto(&vars);

	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img, 0, 0);


	mlx_key_hook(vars.win, inputs, &vars);
	mlx_loop_hook(vars.mlx, frames, &vars);
	mlx_hook(vars.win, 17, 0, exit_hook, &vars);
	mlx_loop(vars.mlx);
}

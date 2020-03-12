/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:02:16 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/12 16:23:10 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

/*
BONUS LIST IDEA
 - menu de depart
 - minimap
 - editeur map dans minimap
 - pieces secretes
 - mini zelda : tu dois recuperer les trois triforces pour acceder à l'epee de legende
		mini puzzle (trois mecaniques differentes)
 - son musique
 - animation, particule
 - hud
 - petite histoire ?
*/

void	pixel(t_window *win, int x, int y, int color)
{
	if (x >= 0 && x < win->set.res_x && y >= 0 && y < win->set.res_y)
		(win->img.data)[y * win->set.res_x + x] = color;
}

int		rgb(int r, int g, int b, int t)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_line_ver(t_window *win, int x, int start, int end, int color)
{
	while (start < end)
	{
		pixel(win, x, start, color);
		start++;
	}
}

void	draw_square(t_window *win, int x, int y, int size, int color)
{
	int i = 0;
	while(i < size)
	{
		int j = 0;
		while (j < size)
		{
			pixel(win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	minimap(t_window *win)
{
	int px = (int)win->set.player_x;
	int py = (int)win->set.player_y;
	int x = 0;
	int offsetx = win->set.res_x - 300;
	while (win->set.map[x])
	{
		int y = 0;
		int offsety = win->set.res_y - 20;
		while (win->set.map[x][y])
		{
			
			if (win->set.map[x][y] == '1')
			{
				draw_square(win, y + offsety, x + offsetx, 5, RED);
			}
			if (win->set.map[x][y] == '0')
			{
				draw_square(win, y + offsety, x + offsetx, 5, WHITE);
			}
			if (win->set.map[x][y] == '2')
			{
				draw_square(win, y + offsety, x + offsetx, 5, YELLOW);
			}
			if (win->set.map[x][y] == 'N' || win->set.map[x][y] == 'W')
			{
				draw_square(win, y + offsety, x + offsetx, 5, BLUE);
			}
			if (x == px && y == py)
				draw_square(win, y + offsety, x + offsetx, 5, BLUE);
			y++;
			offsety += 5;
		}
		x++;
		offsetx += 5;
	}
}

int	raycasting(t_window *win)
{
	int x;
	x = 0;
	double posX = win->set.player_x;
	//posX += 0.5;
	double posY = win->set.player_y;
	//posY += 0.5;
	while (x < win->set.res_x)
	{
		//calculate rays pos and dir
		double cameraX = 2 * x / (double)win->set.res_x - 1;
		double rayDirX = win->set.player_dir_x + win->scene.plane_x * cameraX;
		double rayDirY = win->set.player_dir_y + win->scene.plane_y * cameraX;

		//index of the map based on player position
		int mapX = (int)posX;
		int mapY = (int)posY;
		//printf("%d %d player pos", mapX, mapY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //variable to know if wall hit
		int side; //variable to know what side of wall hit

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX- mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//digital differencial algorithm DDA
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (win->set.map[mapX][mapY] == '1' || win->set.map[mapX][mapY] == '2')
			{
				hit = 1;
				//printf("x = %d, hit %d %d\t", x, mapX, mapY);
			}
		}
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      	else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(win->set.res_y / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + win->set.res_y / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + win->set.res_y / 2;
		if(drawEnd >= win->set.res_y)
			drawEnd = win->set.res_y;
		
		draw_line_ver(win, x, 0, drawStart, win->set.ceil);
		draw_line_ver(win, x, drawEnd, win->set.res_y, win->set.floor);
		
		
		//PARTIE TEXTURE
		int color;

		double wallX;
		if (side == 0)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);
		
		//determiner quelle texture en fonction orientation
		t_img texture;
		if (win->set.map[mapX][mapY] == '1')
		{
			if (side == 0)
			{
				if (rayDirX < 0)
					texture = win->set.text_no; //N
				else
					texture = win->set.text_so; //S
			}
			else
			{
				if (rayDirY < 0)
					texture = win->set.text_we; //W
				else
					texture = win->set.text_ea; //E
			}
		}
		int texX = (int)(wallX * (double)texture.width);
		if (side == 0 && rayDirX > 0)
			texX = texture.width - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texture.width - texX - 1;
		
		double step = 1.0 * texture.height / lineHeight;
		double texPos = (drawStart - win->set.res_y / 2 + lineHeight / 2) * step;
		int y = drawStart;
		
		while (y < drawEnd)
		{
			int texY = (int)texPos & (texture.height - 1);
			texPos += step;
			if (win->set.map[mapX][mapY] == '1')
				color = texture.data[texture.height * texY + texX];
			else
				color = YELLOW;
			pixel(win, x, y, color);
			y++;
		}
		//PARTIE COLOR QUI MARCHE BIEN
		//int color;
		/*
		if (win->set.map[mapX][mapY] == '1')
		{
			if (side == 0)
			{
				if (rayDirX < 0)
					color = RED; //N
				else
					color = YELLOW; //S
			}
			else
			{
				if (rayDirY < 0)
					color = BLUE; //W
				else
					color = PURPLE; //E
			}
		}
		else if (win->set.map[mapX][mapY] == '2')
			color = YELLOW;
		else
			color = BLACK;
		draw_line_ver(win, x, drawStart, drawEnd, color);
		*/
		x++;
	}
	minimap(win);
	return(1);
}

int		render_next_frame(t_window *win)
{
	mlx_destroy_image(win->mlx_ptr, win->img.img_ptr);
	win->img.img_ptr = mlx_new_image(win->mlx_ptr, win->set.res_x, win->set.res_y);
	win->img.data = (int*)mlx_get_data_addr(win->img.img_ptr, \
		&win->img.bpp, &win->img.s_l, &win->img.endian);
	raycasting(win);
	minimap(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img_ptr, 0, 0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_window win;

	if (argc < 2 || argc > 3)
	{
		ft_putstr_fd(USAGE, 2);
		return (EXIT_FAILURE);
	}
	window_constructor(&win);
	window_set(&win, argv[1]);
	if (win.set.player_orientation == 'W')
	{
		win.scene.plane_x = -0.66;
		win.scene.plane_y = 0;
	}
	else if (win.set.player_orientation == 'E')
	{
		win.scene.plane_x = 0.66;
		win.scene.plane_y = 0;
	}
	else if (win.set.player_orientation == 'S')
	{
		win.scene.plane_x = 0;
		win.scene.plane_y = -0.66;
	}
	else if (win.set.player_orientation == 'N')
	{
		win.scene.plane_x = 0;
		win.scene.plane_y = 0.66;
	}
	mlx_loop_hook(win.mlx_ptr, render_next_frame, &win);
	hook_event(&win);
	mlx_loop(win.mlx_ptr);
	return (EXIT_SUCCESS);
}

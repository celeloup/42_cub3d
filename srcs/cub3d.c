/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celeloup <celeloup@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 11:02:16 by celeloup          #+#    #+#             */
/*   Updated: 2020/03/11 14:31:55 by celeloup         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

/*
BONUS LIST IDEA
 - minimap
 - editeur map dans minimap
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

int	raycasting(t_window *win)
{
	int x;
	x = 0;
	double posX = win->set.player_x;
	posX += 0.5;
	double posY = win->set.player_y;
	posY += 0.5;
	printf("pos player %f %f\n", posX, posY);
	printf("dir player %f %f\n", win->set.player_dir_x, win->set.player_dir_y);
	printf("plane %f %f\n", win->scene.plane_x, win->scene.plane_y);
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
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));;
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
			if (win->set.map[mapX][mapY] == '1')
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
			drawEnd = win->set.res_y - 1;
		
		int color;
		if (win->set.map[mapX][mapY] == '1')
		{
			color = RED;
		}
		else
			color = BLACK;
		if (side == 1)
			color = color /2;
		draw_line_ver(win, x, drawStart, drawEnd, color);
		x++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img_ptr, 0, 0);
	return(1);
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
			y++;
			offsety += 5;
		}
		x++;
		offsetx += 5;
	}
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
	// pixel(&win, 100, 100, win.set.ceil);
	// draw_line_ver(&win, 10, 50, 150, RED);
	//draw_square(&win, 100, 100, 40, YELLOW);
	//print_map(win.set.map);
	
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
	
	raycasting(&win);
	minimap(&win);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr, win.img.img_ptr, 0, 0);
	//mlx_loop_hook(win.mlx_ptr, raycasting, &win);
	hook_event(&win);
	mlx_loop(win.mlx_ptr);
	return (EXIT_SUCCESS);
}

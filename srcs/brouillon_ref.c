int		raycasting(t_window *win, double pos_x, double pos_y)
{
	int x;
	double z_buffer[win->set.res_x];

	x = 0;
	while (x < win->set.res_x)
	{
		//calculate rays pos and dir
		double camera_x = 2 * x / (double)win->set.res_x - 1;
		double ray_dir_x = win->set.player_dir_x + win->scene.plane_x * camera_x;
		double ray_dir_y = win->set.player_dir_y + win->scene.plane_y * camera_x;

		//index of the map based on player position
		int map_x = (int)pos_x;
		int map_y = (int)pos_y;
		//printf("%d %d player pos", map_x, map_y);

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		double delta_dist_x = (ray_dir_y == 0) ? 0 : ((ray_dir_x == 0) ? 1 : fabs(1 / ray_dir_x));
		double delta_dis_y = (ray_dir_x == 0) ? 0 : ((ray_dir_y == 0) ? 1 : fabs(1 / ray_dir_y));
		double perp_wall_dist;

		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;

		int hit = 0;//variable to know if wall hit
		int side;//variable to know what side of wall hit

		//calculate step and initial sideDist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (pos_y - map_y) * delta_dis_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - pos_y) * delta_dis_y;
		}
		//digital differencial algorithm DDA
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dis_y;
				map_y += step_y;
				side = 1;
			}
			if (win->set.map[map_x][map_y] == '1')
			{
				hit = 1;
				//printf("x = %d, hit %d %d\t", x, map_x, map_y);
			}
		}
		if (side == 0)
			perp_wall_dist = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;

		//Calculate height of line to draw on screen
		int line_height = (int)(win->set.res_y / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int draw_start = -line_height / 2 + win->set.res_y / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + win->set.res_y / 2;
		if (draw_end >= win->set.res_y)
			draw_end = win->set.res_y;

		draw_line_ver(win, x, 0, draw_start, win->set.ceil);
		draw_line_ver(win, x, draw_end, win->set.res_y, win->set.floor);

		//PARTIE TEXTURE
		int color;

		double wall_x;
		if (side == 0)
			wall_x = pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		//determiner quelle texture en fonction orientation
		t_img texture;
		if (win->set.map[map_x][map_y] == '1')
		{
			if (side == 0)
			{
				if (ray_dir_x < 0)
					texture = win->set.text_no; //N
				else
					texture = win->set.text_so; //S
			}
			else
			{
				if (ray_dir_y < 0)
					texture = win->set.text_we; //W
				else
					texture = win->set.text_ea; //E
			}
		}
		int wall_texture_x = (int)(wall_x * (double)texture.width);
		if (side == 0 && ray_dir_x > 0)
			wall_texture_x = texture.width - wall_texture_x - 1;
		if (side == 1 && ray_dir_y < 0)
			wall_texture_x = texture.width - wall_texture_x - 1;

		double step = 1.0 * texture.height / line_height;
		double texture_pos = (draw_start - win->set.res_y / 2 + line_height / 2) * step;
		int y = draw_start;

		while (y < draw_end)
		{
			int wall_texture_y = (int)texture_pos & (texture.height - 1);
			texture_pos += step;
			if (win->set.map[map_x][map_y] == '1')
				color = texture.data[texture.height * wall_texture_y + wall_texture_x];
			pixel(win, x, y, color);
			y++;
		}
		z_buffer[x] = perp_wall_dist;
		x++;
	}
	sprite_render(win, z_buffer);
	return (1);
}

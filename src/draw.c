/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khestia <khestia@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:01:01 by tune              #+#    #+#             */
/*   Updated: 2022/04/12 10:07:44 by khestia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Calculation of viewing angles for each column of pixels on the screen (ray)
static void	cub_ray(t_all *all)
{
	double	win_angle;
	double	ray_angle;

	win_angle = (WIN_ANGLE / 2) * M_PI / 180;
	ray_angle
		= ((double)all->ray.i - (WIN_WIDTH / 2)) * win_angle / (WIN_WIDTH / 2);
	all->ray.x = all->cam.dx * cos(ray_angle) - all->cam.dy * sin(ray_angle);
	all->ray.y = all->cam.dy * cos(ray_angle) + all->cam.dx * sin(ray_angle);
	all->ray.xceil = 0;
	if (all->ray.x >= 0)
		all->ray.xceil = 1;
	all->ray.yceil = 0;
	if (all->ray.y >= 0)
		all->ray.yceil = 1;
}

//Ray tracing to the nearest vertical wall
static void	cub_trc_verwall(t_all *all)
{
	double	x;
	double	y;
	int		tab_y;
	int		tab_x;

	x = floor(all->cam.px) + all->ray.xceil;
	y = all->cam.py + (x - all->cam.px) * (all->ray.y / all->ray.x);
	while ((int)y > 0 && (int)y < all->map.y)
	{
		tab_y = (int)y;
		tab_x = (int)(x - 1 + all->ray.xceil);
		if (tab_y >= 0 && tab_y < all->map.y && tab_x >= 0 && tab_x < all->map.x
			&& all->map.tab[tab_y][tab_x] == '1')
		{
			all->trc.x = x;
			all->trc.y = y;
			all->trc.d = hypot(x - all->cam.px, y - all->cam.py);
			return ;
		}
		x += (2 * all->ray.xceil - 1);
		y += (2 * all->ray.xceil - 1) * all->ray.y / all->ray.x;
	}
	all->trc.x = all->cam.px;
	all->trc.y = all->cam.py;
	all->trc.d = 1000000;
}

//Ray tracing to nearest horizontal wall (if closer than vertical)
static void	cub_trc_horwall(t_all *all)
{
	double	y;
	double	x;
	int		tab_y;
	int		tab_x;

	y = floor(all->cam.py) + all->ray.yceil;
	x = all->cam.px + (y - all->cam.py) * (all->ray.x / all->ray.y);
	while ((int)x > 0 && (int)x < all->map.x)
	{
		tab_y = (int)(y - 1 + all->ray.yceil);
		tab_x = (int)x;
		if (tab_y >= 0 && tab_y < all->map.y && tab_x >= 0 && tab_x < all->map.x
			&& all->map.tab[tab_y][tab_x] == '1')
		{
			if (all->trc.d > hypot(x - all->cam.px, y - all->cam.py))
			{
				all->trc.x = x;
				all->trc.y = y;
				all->trc.d = hypot(x - all->cam.px, y - all->cam.py);
			}
			return ;
		}
		y += (2 * all->ray.yceil - 1);
		x += (2 * all->ray.yceil - 1) * all->ray.x / all->ray.y;
	}
}

//Frame image rendering
static void	cub_draw_mlx(t_all *all)
{
	int		tmp[3];

	all->img.ptr = mlx_new_image(all->mlx.ptr, WIN_WIDTH, WIN_HEIGHT);
	all->img.adr
		= (UNINT *)mlx_get_data_addr(all->img.ptr, &tmp[0], &tmp[1], &tmp[2]);
	while (all->ray.i < WIN_WIDTH)
	{
		cub_ray(all);
		cub_trc_verwall(all);
		cub_trc_horwall(all);
		cub_draw_column(all, cub_wall_height(all));
		all->ray.i++;
	}
}

//Positioning the frame on the screen
void	cub_draw(t_all *all)
{
	t_ray	ray;
	t_trc	trc;

	ray.x = 0;
	ray.y = 0;
	ray.i = 0;
	ray.xceil = 0;
	ray.yceil = 0;
	trc.x = 0;
	trc.y = 0;
	trc.d = 0;
	all->ray = ray;
	all->trc = trc;
	cub_draw_mlx(all);
	mlx_put_image_to_window(all->mlx.ptr, all->win.ptr, all->img.ptr, 0, 0);
	free(all->img.ptr);
	free(all->img.adr);
}

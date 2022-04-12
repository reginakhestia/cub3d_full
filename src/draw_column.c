/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khestia <khestia@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:01:01 by tune              #+#    #+#             */
/*   Updated: 2022/04/12 12:06:35 by khestia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Finding a color in a texture to output a wall pixel
static UNINT	cub_pixel_from_texture(t_all *all, double i)
{
	int	index;

	if (floor(all->trc.y) == all->trc.y)
	{
		index = 64 * floor(64 * i) + 64 * (all->trc.x - floor(all->trc.x));
		if (all->ray.yceil == 1)
			return (all->tex.so[index]);
		else if (all->ray.yceil == 0)
			return (all->tex.no[index]);
	}
	else if (floor(all->trc.x) == all->trc.x)
	{
		index = 64 * floor(64 * i) + 64 * (all->trc.y - floor(all->trc.y));
		if (all->ray.xceil == 1)
			return (all->tex.ea[index]);
		else if (all->ray.xceil == 0)
			return (all->tex.we[index]);
	}
	return (0);
}

//Displaying pixel colors in a column from top to bottom
void	cub_draw_column(t_all *all, int wall_height)
{
	int		start;
	int		count;
	UNINT	color;
	int		pixel_i;

	start = WIN_WIDTH * (WIN_HEIGHT - wall_height) / 2;
	if (wall_height > WIN_HEIGHT)
		count = (wall_height - WIN_HEIGHT) / 2;
	else
		count = 0;
	color = all->tex.c;
	pixel_i = all->ray.i;
	while (pixel_i < WIN_WIDTH * WIN_HEIGHT)
	{
		if (pixel_i >= start && count < wall_height)
		{
			color = cub_pixel_from_texture(all, (double)count / wall_height);
			count++;
		}
		else if (count == wall_height)
			color = all->tex.f;
		all->img.adr[pixel_i] = mlx_get_color_value(all->mlx.ptr, color);
		pixel_i += WIN_WIDTH;
	}
}

/*Calculating the wall height for a column of pixels, 
			taking into account the fisheye*/
int	cub_wall_height(t_all *all)
{
	double	fisheye_coef;
	double	fisheye_angle;

	fisheye_coef = fabs((double)all->ray.i / (WIN_WIDTH / 2) - 1);
	fisheye_angle = fisheye_coef * (WIN_ANGLE / 2 - WIN_EYE) * M_PI / 180;
	return (round(WIN_HEIGHT / ((double)all->trc.d * cos(fisheye_angle))));
}

//chek for open walls and empty spaces inside the map
int	cub_walls_errors(t_all *all, int i, int j)
{
	if (i == 0 || j == 0)
		return (-1);
	else if (all->map.tab[i + 1][j] == '\0'
		|| all->map.tab[i][j + 1] == '\0')
		return (-1);
	else if (all->map.tab[i - 1][j] == '\0'
		|| all->map.tab[i][j - 1] == '\0')
		return (-1);
	else if (all->map.tab[i + 1] == NULL
		|| all->map.tab[i - 1] == NULL)
		return (-1);
	else if (all->map.tab[i + 1][j] == ' ' || all->map.tab[i][j + 1] == ' ')
		return (-1);
	else if (all->map.tab[i - 1][j] == ' ' || all->map.tab[i][j - 1] == ' ')
		return (-1);
	return (0);
}

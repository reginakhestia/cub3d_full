/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khestia <khestia@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:01:01 by hestia            #+#    #+#             */
/*   Updated: 2022/04/12 11:29:02 by khestia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Parsing one line of a map file
static int	cub_parse_line(t_all *all, char *line, int i)
{
	cub_spaces_skip(line, &i);
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		all->err.n = cub_texture(all, &all->tex.no, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		all->err.n = cub_texture(all, &all->tex.so, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		all->err.n = cub_texture(all, &all->tex.we, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		all->err.n = cub_texture(all, &all->tex.ea, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		all->err.n = cub_colors(&all->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		all->err.n = cub_colors(&all->tex.c, line, &i);
	else if ((line[i] == '0' || line[i] == '1' || all->err.m == 1)
		&& line[i] != '\0')
	{
		i = 0;
		all->err.n = cub_maptable(all, line, &i, -1);
	}
	cub_spaces_skip(line, &i);
	if (all->err.n == 0 && line[i] != '\0')
		return (cub_return_error(8));
	if (all->err.n != 0)
		return (cub_return_error(all->err.n));
	return (0);
}

//Starting position and camera direction on the map
static void	cub_start_position(t_all *all, char c, int i, int j)
{
	while (i < all->map.y)
	{
		j = 0;
		while (all->map.tab[i][j] != '\0')
		{
			c = all->map.tab[i][j];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
			{
				all->cam.py = (double)i + 0.5;
				all->cam.px = (double)j + 0.5;
				if (c == 'E')
					all->cam.dx = 1;
				else if (c == 'W')
					all->cam.dx = -1;
				if (c == 'S')
					all->cam.dy = 1;
				else if (c == 'N')
					all->cam.dy = -1;
				all->err.p++;
			}
			j++;
		}
		i++;
	}
}

//Checking map walls for errors
static int	cub_map_errors(t_all *all, int i, int j)
{
	while (i < all->map.y)
	{
		j = 0;
		while (all->map.tab[i][j] != '\0')
		{
			if (all->map.tab[i][j] == '0' || all->map.tab[i][j] == 'N'
				|| all->map.tab[i][j] == 'S' || all->map.tab[i][j] == 'W'
					|| all->map.tab[i][j] == 'E')
			{
				if (cub_walls_errors(all, i, j) == -1)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (1);
}

//Checking the map for errors
static int	cub_find_errors(t_all *all)
{
	if (all->tex.no == NULL || all->tex.so == NULL
		|| all->tex.we == NULL || all->tex.ea == NULL)
		return (cub_return_error(11));
	else if (all->tex.f == 0 || all->tex.c == 0)
		return (cub_return_error(12));
	else if (all->err.p == 0)
		return (cub_return_error(13));
	else if (all->err.p > 1)
		return (cub_return_error(14));
	else if (cub_map_errors(all, 0, 0) == -1)
		return (cub_return_error(15));
	return (1);
}

//Reading a map file
int	cub_parse(t_all *all, char *file)
{
	char	*line;
	int		fd;
	int		gnl_return;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (cub_return_error(1));
	gnl_return = 1;
	while (gnl_return == 1)
	{
		gnl_return = ft_gnl(fd, &line);
		if (cub_parse_line(all, line, 0) == -1)
		{
			close(fd);
			free(line);
			return (cub_return_error(0));
		}
		free(line);
	}
	close(fd);
	if (gnl_return == -1)
		return (cub_return_error(2));
	cub_start_position(all, 0, 0, 0);
	return (cub_find_errors(all));
}

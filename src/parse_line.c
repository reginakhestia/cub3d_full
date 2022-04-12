/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khestia <khestia@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:01:01 by hestia            #+#    #+#             */
/*   Updated: 2022/04/12 10:11:48 by khestia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Convert XPM texture file to image (sequence of numbers)
static int	cub_xpm_put_adr(t_all *all, UNINT **adr, char *file)
{
	int		fd;
	void	*img;
	int		xpm_w;
	int		xpm_h;
	int		tmp[3];

	if (cub_filename_ext(file, "xpm") == 0)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	close(fd);
	img = mlx_xpm_file_to_image(all->mlx.ptr, file, &xpm_w, &xpm_h);
	if (img == NULL || xpm_w != 64 || xpm_h != 64)
		return (-1);
	*adr = (UNINT *)mlx_get_data_addr(img, &tmp[0], &tmp[1], &tmp[2]);
	free(img);
	return (0);
}

//Reading a string with the address of a texture file
int	cub_texture(t_all *all, UNINT **adr, char *line, int *i)
{
	char	*file;
	int		j;

	if (*adr != NULL)
		return (5);
	(*i) += 2;
	cub_spaces_skip(line, i);
	j = *i;
	while (line[j] != '\0')
		j++;
	file = malloc(sizeof(char) * (j - *i + 1));
	if (file == NULL)
		return (6);
	j = 0;
	while (line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	j = cub_xpm_put_adr(all, adr, file);
	free(file);
	if (j == -1)
		return (7);
	return (0);
}

//Convert color string to color number
int	cub_colors(UNINT *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != 0)
		return (3);
	(*i)++;
	r = cub_custom_atoi(line, i);
	if (line[*i] != ',')
		return (4);
	(*i)++;
	g = cub_custom_atoi(line, i);
	if (line[*i] != ',')
		return (4);
	(*i)++;
	b = cub_custom_atoi(line, i);
	cub_spaces_skip(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (4);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}

//Saving a Map Line
static char	*cub_maptable_line(char *line, int *i)
{
	char	*map_line;
	int		j;

	map_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (map_line == NULL)
		return (NULL);
	j = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] == ' ' || line[*i] == '0' || line[*i] == '1'
			|| line[*i] == 'N' || line[*i] == 'S'
			|| line[*i] == 'W' || line[*i] == 'E')
		{
			map_line[j] = line[*i];
			j++;
		}
		else
		{
			free(map_line);
			return (NULL);
		}
		(*i)++;
	}
	map_line[j] = '\0';
	return (map_line);
}

//Accumulation of "all->map.tab" array by map lines
int	cub_maptable(t_all *all, char *line, int *i, int j)
{
	char	**tmp;

	all->err.m = 1;
	tmp = malloc(sizeof(char *) * (all->map.y + 2));
	if (tmp == NULL)
		return (9);
	while (++j < all->map.y)
		tmp[j] = all->map.tab[j];
	tmp[all->map.y] = cub_maptable_line(line, i);
	if (tmp[all->map.y] == NULL)
	{
		free(tmp);
		return (10);
	}
	tmp[all->map.y + 1] = NULL;
	if (all->map.y > 0)
		free(all->map.tab);
	all->map.tab = tmp;
	all->map.y++;
	if (ft_strlen(line) > all->map.x)
		all->map.x = ft_strlen(line);
	return (0);
}

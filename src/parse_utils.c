/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khestia <khestia@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:01:01 by hestia            #+#    #+#             */
/*   Updated: 2022/04/12 10:16:26 by khestia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//File Extension Check
int	cub_filename_ext(char *name, char *ext)
{
	int	i;

	i = 0;
	while (name[i] != '\0')
		i++;
	if (i > 4 && name[i - 1] == ext[2] && name[i - 2] == ext[1]
		&& name[i - 3] == ext[0] && name[i - 4] == '.')
		return (1);
	return (0);
}

//Skip all spaces in a string, changing the ending position in the string
int	cub_spaces_skip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
		|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

/*Translation of a string into a number (atoi)
	with a change in the final position in the string*/
int	cub_custom_atoi(char *line, int *i)
{
	int	num;

	num = 0;
	cub_spaces_skip(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (num);
}

//Error printout (continued)
static void	cub_return_error_two(int num)
{
	if (num == 9)
		write(2, "Error: No malloc (map table)\n", 29);
	if (num == 10)
		write(2, "Error: Invalid map table\n", 25);
	if (num == 11)
		write(2, "Error: Missing texture(s)\n", 26);
	if (num == 12)
		write(2, "Error: Missing floor/ceiling color\n", 35);
	if (num == 13)
		write(2, "Error: No start position\n", 25);
	if (num == 14)
		write(2, "Error: Double start position\n", 29);
	if (num == 15)
		write(2, "Error: Map isn't surrounded by walls/space inside map\n", 54);
}

//Print errors and return "-1"
int	cub_return_error(int num)
{
	if (num == 1)
		write(2, "Error: Couldn't open file (FD)\n", 31);
	if (num == 2)
		write(2, "Error: Couldn't parse file (GNL)\n", 33);
	if (num == 3)
		write(2, "Error: Double floor/ceiling\n", 28);
	if (num == 4)
		write(2, "Error: Invalid floor/ceiling\n", 29);
	if (num == 5)
		write(2, "Error: Double texture path\n", 27);
	if (num == 6)
		write(2, "Error: No malloc (texture path)\n", 32);
	if (num == 7)
		write(2, "Error: Invalid texture file\n", 28);
	if (num == 8)
		write(2, "Error: Invalid line in file\n", 28);
	cub_return_error_two(num);
	return (-1);
}

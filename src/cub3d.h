/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khestia <khestia@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 00:01:01 by tune              #+#    #+#             */
/*   Updated: 2022/04/12 10:04:50 by khestia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>

# define UNINT		unsigned int
# define WIN_WIDTH	1280
# define WIN_HEIGHT	693
# define WIN_ANGLE	90
# define WIN_EYE	12
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_ESC	53
# define MOVE_STEP	0.2
# define MOVE_TURN	0.05236

//MLX
typedef struct s_mlx
{
	void		*ptr;
}	t_mlx;

//Graphics window
typedef struct s_win
{
	void		*ptr;
}	t_win;

//Image in graphics window (full window)
typedef struct s_img
{
	void		*ptr;
	UNINT		*adr;
}	t_img;

//Map parsing errors
typedef struct s_err
{
	int			n;
	int			m;
	int			p;
}	t_err;

//Map
typedef struct s_map
{
	char		**tab;
	int			x;
	int			y;
}	t_map;

//Textures
typedef struct s_tex
{
	UNINT		*no;
	UNINT		*so;
	UNINT		*we;
	UNINT		*ea;
	UNINT		f;
	UNINT		c;
}	t_tex;

//Camera position and direction
typedef struct s_cam
{
	double		px;
	double		py;
	double		dx;
	double		dy;
}	t_cam;

//Column of pixels on the screen (ray in the field of view)
typedef struct s_ray
{
	double		x;
	double		y;
	int			i;
	bool		xceil;
	bool		yceil;
}	t_ray;

//Wall tracing in rays
typedef struct s_trc
{
	double		x;
	double		y;
	double		d;
}	t_trc;

//Structure of all structures
typedef struct s_all
{
	t_mlx		mlx;
	t_win		win;
	t_img		img;
	t_err		err;
	t_map		map;
	t_tex		tex;
	t_cam		cam;
	t_ray		ray;
	t_trc		trc;
}	t_all;

//Parsing the map file
int		cub_parse(t_all *all, char *file);
int		cub_texture(t_all *all, unsigned int **adr, char *line, int *i);
int		cub_colors(unsigned int *color, char *line, int *i);
int		cub_maptable(t_all *all, char *line, int *i, int j);
int		cub_filename_ext(char *fName, char *fExt);
int		cub_spaces_skip(char *line, int *i);
int		cub_custom_atoi(char *line, int *i);
int		cub_return_error(int num);
int		cub_walls_errors(t_all *all, int i, int j);

//moving
int		cub_keydown(int key, void *all);

//Drawing a frame on the screen
void	cub_draw(t_all *all);
void	cub_draw_column(t_all *all, int wall_height);
int		cub_wall_height(t_all *all);

//Closing the program
int		cub_close(t_all *all, int win_destroy);

#endif

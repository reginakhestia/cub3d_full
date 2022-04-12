/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ztune <ztune@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 0:01:01 by ztune              #+#    #+#             */
/*   Updated: 2022/04/08 0:02:02 by ztune             ###   ########.fr       */
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
	void		*ptr;	//Указатель на MLX
}	t_mlx;

//Графическое окно
typedef struct s_win
{
	void		*ptr;	//Указатель на окно в MLX
}	t_win;

//Изображение в графическом окне (во всё окно)
typedef struct s_img
{
	void		*ptr;	//Указатель на изображение
	UNINT		*adr;	//Массив указателей на пиксели внутри изображения
}	t_img;

//Ошибки парсинга карты
typedef struct s_err
{
	int			n;		//Код возникшей ошибки
	int			m;		//Если 1, то таблица карты начала считываться
	int			p;		//Количество стартовых позиций
}	t_err;

//Карта
typedef struct s_map
{
	char		**tab;	//Массив таблицы карты
	int			x;		//Количество столбцов
	int			y;		//Количество строк
}	t_map;

//Текстуры
typedef struct s_tex
{
	UNINT		*no;	//Северная
	UNINT		*so;	//Южная
	UNINT		*we;	//Западная
	UNINT		*ea;	//Восточная
	UNINT		f;		//Цвет пола
	UNINT		c;		//Цвет потолка
}	t_tex;

//Позиция и направление камеры
typedef struct s_cam
{
	double		px;		//Координата позиции X
	double		py;		//Координата позиции Y
	double		dx;		//Направление X ("1" - направо, "-1" - налево)
	double		dy;		//Направление Y ("1" - вниз, "-1" - вверх)
}	t_cam;

//Столбец пикселей на экране (луч в поле обзора)
typedef struct s_ray
{
	double		x;		//Направление X ("1" - направо, "-1" - налево)
	double		y;		//Направление Y ("1" - вниз, "-1" - вверх)
	int			i;		//Номер столбца пикселей
	bool		xceil;	//0 (если смотрим на запад) и 1 (если смотрим на восток) 
	bool		yceil;	//0 (если смотрим на север) и 1 (если смотрим на юг) 
}	t_ray;

//Трассировка стен в лучах
typedef struct s_trc
{
	double		x;		//Координата X стены в луче
	double		y;		//Координата Y стены в луче
	double		d;		//Расстояние до стены в луче
}	t_trc;

//Структура всех структур
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

//Парсинг файла карты
int		cub_parse(t_all *all, char *file);
int		cub_texture(t_all *all, unsigned int **adr, char *line, int *i);
int		cub_colors(unsigned int *color, char *line, int *i);
int		cub_maptable(t_all *all, char *line, int *i, int j);
int		cub_filename_ext(char *fName, char *fExt);
int		cub_spaces_skip(char *line, int *i);
int		cub_custom_atoi(char *line, int *i);
int		cub_return_error(int num);

//Перемещение
int		cub_keydown(int key, void *all);

//Отрисовка кадра на экране
void	cub_draw(t_all *all);
void	cub_draw_column(t_all *all, int wall_height);
int		cub_wall_height(t_all *all);

//Закрытие программы
int		cub_close(t_all *all, int win_destroy);

#endif

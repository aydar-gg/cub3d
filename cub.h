/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:21:47 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/22 15:42:35 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#define s_map 64
# define turn 0.05 //M_PI/12no

#include "minilibx/mlx.h"
#include "libft/libft.h"
#include "gnl/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>// printf
#include <stdlib.h>
#include <math.h>

typedef struct	s_p_n
{
	char	*north;
	int		width;
	int		hight;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_p_n;

typedef struct	s_p_s
{
	char	*south;
	int		width;
	int		hight;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_p_s;

typedef struct	s_p_w
{
	char	*west;
	int		width;
	int		hight;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_p_w;

typedef struct	s_p_e
{
	char	*east;
	int		width;
	int		hight;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_p_e;

typedef struct	s_p
{
	char	*sprit;
	int		width;
	int		hight;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_spr;

typedef struct	s_vars {
	char	**t_map;
	void	*mlx;
	void	*win;
	void	*img_ptr;
	char	*img_data;
	double	plr_x;
	double	plr_y;
	double	x_reycast;
	double	y_reycast;
	double	x_line;
	double	y_line;
	int		max_map_width;
	int		max_map_hight;
	int		width;
	int		hight;
	int		fd;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	double	overview;
	double	Hy_ray;
	double	Hx_ray;
	double	Ya;
	double	Xa;
	double	Vy_ray;
	double	Vx_ray;
	double	z;
	double	z_horizontlly;
	double	z_vertically;
	double	z_sprit_h;
	double	z_sprit_v;
	double	z_sprit;
	int		offset;
	int		offset_sprit;
	t_p_n	no;
	t_p_s	so;
	t_p_w	we;
	t_p_e	ea;
	t_spr	sp;
}				t_vars;

void	read_map(char **argv, t_vars *vars);
int		key_press(int keycode, t_vars *vars);
void	print_map_2d(t_vars *vars);
void	map_3d(t_vars *vars, int k);
double	check_over(double over);
void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void	print_sprit(t_vars *vars, int k);

#endif

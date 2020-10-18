/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:21:47 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/18 17:27:34 by psabreto         ###   ########.fr       */
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
	double	main_line;
	double	Hy_ray;
	double	Hx_ray;
	double	Ya;
	double	Xa;
	double	Vy_ray;
	double	Vx_ray;
	double	z;
	double	z_horizontlly;
	double	z_vertically;
}				t_vars;

void	read_map(char **argv, t_vars *vars);
int		key_press(int keycode, t_vars *vars);
void	print_map_2d(t_vars *vars);

#endif

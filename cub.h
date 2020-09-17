/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:21:47 by psabreto          #+#    #+#             */
/*   Updated: 2020/09/17 14:40:02 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

#define s_map 20
# define turn M_PI/12

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
	float	plr_x;
	float	plr_y;
	float	plr_view;
	float	x_reycast;
	float	y_reycast;
	float	x_line;
	float	y_line;
	int		max_map_width;
	int		max_map_hight;
	int		width;
	int		hight;
	int		fd;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	float	alpha;
	float	beta;
	float	dir;
}				t_vars;

#endif

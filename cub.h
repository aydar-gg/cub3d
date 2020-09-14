/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:21:47 by psabreto          #+#    #+#             */
/*   Updated: 2020/09/13 13:09:34 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

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
	int		plr_x;
	int		plr_y;
	int		max_map_width;
	int		max_map_hight;
	int		width;
	int		hight;
	int		fd;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_vars;

#endif

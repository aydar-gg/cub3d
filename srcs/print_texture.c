/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:41:29 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 16:51:15 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void			my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char *dst;

	dst = vars->img_data + (y * vars->line_length + x * (vars->bpp / 8));
	*(unsigned int*)dst = color;
}

int				my_mlx_pixel_get_color(t_p_n *data, int x, int y)
{
	int *dst;
	int color;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

static int		pix_color_v2(t_vars *vars, int x, int y, float line)
{
	int index;
	int *dst;

	dst = NULL;
	vars->is_wr_t = 0;
	if (check_over(vars->overview) > M_PI_2 && check_over(vars->overview)
	< 3 * M_PI_2 && vars->z_horizontlly > vars->z_vertically)
	{
		y = y * vars->ea.hight / line;
		index = (x + y * vars->ea.width);
		dst = vars->ea.addr + index;
		vars->is_wr_t = 1;
	}
	else if (((check_over(vars->overview) > 3 * M_PI_2 &&
	check_over(vars->overview) < 2 * M_PI) ||
	(check_over(vars->overview) > 0 && check_over(vars->overview) < M_PI_2)) &&
	vars->z_horizontlly > vars->z_vertically)
	{
		y = y * vars->we.hight / line;
		index = (x + y * vars->we.width);
		dst = vars->we.addr + index;
		vars->is_wr_t = 1;
	}
	return (*(unsigned int*)dst);
}

int				pix_color(t_vars *vars, int x, int y, float line)
{
	int index;
	int *dst;

	dst = NULL;
	if (check_over(vars->overview) > M_PI && check_over(vars->overview) <
	2 * M_PI
	&& vars->z_horizontlly <= vars->z_vertically)
	{
		y = y * vars->no.hight / line;
		index = (x + y * vars->no.width);
		dst = vars->no.addr + index;
	}
	else if (check_over(vars->overview) > 0 && check_over(vars->overview) < M_PI
	&& vars->z_horizontlly <= vars->z_vertically)
	{
		y = y * vars->so.hight / line;
		index = (x + y * vars->so.width);
		dst = vars->so.addr + index;
	}
	else if (pix_color_v2(vars, x, y, line) || vars->is_wr_t)
		return (pix_color_v2(vars, x, y, line));
	return (*(unsigned int*)dst);
}

void			map_3d(t_vars *vars, int k)
{
	int h;
	int i;
	int color;
	int copy_h;

	vars->z = (vars->z * cos(vars->overview - vars->x_reycast)) ?
	vars->z * cos(vars->overview - vars->x_reycast) : vars->z;
	check_z(vars, k);
	vars->arr_z[k] = vars->z;
	h = S_MAP * ((vars->hight / 2) / tan(M_PI / 6)) / vars->z;
	copy_h = (h > vars->hight * 2) ? h - vars->hight * 2 : 0;
	h = (h > vars->hight * 2) ? vars->hight * 2 : h;
	i = 0;
	while (i < (int)(h / 2))
	{
		color = pix_color(vars, vars->offset, i + copy_h / 4,
		h / 2 + copy_h / 2);
		my_mlx_pixel_put(vars, k, vars->hight / 2 - h / 4 + i, color);
		i++;
	}
}

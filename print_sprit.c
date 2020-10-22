/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:41:29 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/22 18:54:23 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int			my_mlx_pixel_get_color(t_p_n *data, int x, int y)
{
	int *dst;
	int color;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

static int		pix_color(t_vars *vars, int x, int y, float line)
{
	int		index;
	int		*dst;

	if (check_over(vars->overview) > M_PI && check_over(vars->overview) < 2 * M_PI
	&& (int)(vars->z_horizontlly * cos(vars->overview - vars->x_reycast)) == (int)vars->z)//north
	{
		//dst = vars->no.addr + (y * vars->no.line_length + x * (vars->no.bpp / 8));
		y = y * vars->no.hight / line;
		index = (x + y * vars->no.width);
		dst = vars->no.addr + index;
		//return (my_mlx_pixel_get_color(&vars->no, x, y));
	}
	else if (check_over(vars->overview) > 0 && check_over(vars->overview) < M_PI
	&& (int)(vars->z_horizontlly * cos(vars->overview - vars->x_reycast)) == (int)vars->z)//south
	{
		//dst = vars->so.addr + (y * vars->so.line_length + x * (vars->so.bpp / 8));
		y = y * vars->so.hight / line;
		index = (x + y * vars->so.width);
		dst = vars->so.addr + index;
	}
	else if (check_over(vars->overview) > M_PI_2 && check_over(vars->overview) < 3 * M_PI_2//east
	&& (int)(vars->z_vertically * cos(vars->overview - vars->x_reycast)) == (int)vars->z)
	{
		//dst = vars->we.addr + (y * vars->we.line_length + x * (vars->we.bpp / 8));
		y = y * vars->we.hight / line;
		index = (x + y * vars->we.width);
		dst = vars->we.addr + index;
	}
	else//west
	{
		//dst = vars->ea.addr + (y * vars->ea.line_length + x * (vars->ea.bpp / 8));
		y = y * vars->ea.hight / line;
		index = (x + y * vars->ea.width);
		dst = vars->ea.addr + index;
	}
	return (*(unsigned int*)dst);
}

void			map_3d(t_vars *vars, int k)
{
	int h;
	int i;
	int color;
	int copy_h;

	vars->z = (vars->z * cos(vars->overview - vars->x_reycast)) ? vars->z * cos(vars->overview - vars->x_reycast) : vars->z;
	h = s_map * ((vars->hight / 2) / tan(M_PI / 6)) / vars->z;
	copy_h = (h > vars->hight * 2) ? h - vars->hight * 2 : 0;
	h = (h > vars->hight * 2) ? vars->hight * 2 : h;
	i = 0;
	while (i < (int)(h / 2))
	{
		color = pix_color(vars, vars->offset, i + copy_h / 4, h / 2 + copy_h / 2);
		my_mlx_pixel_put(vars, k, vars->hight / 2 - h / 4 + i, color);
		i++;
	}
}

static int		pix_color_sprit(t_vars *vars, int x, int y, float line)
{
	int		index;
	int		*dst;

	y = y * vars->sp.hight / line;
	index = (x + y * vars->sp.width);
	dst = vars->sp.addr + index;

	return (*(unsigned int*)dst);
}

void			print_sprit(t_vars *vars, int k)
{
	int h;
	int i;
	int color;
	int copy_h;

	vars->z_sprit = (vars->z_sprit * cos(vars->overview - vars->x_reycast)) ? vars->z_sprit * cos(vars->overview - vars->x_reycast) : vars->z_sprit;
	h = s_map * ((vars->hight / 2) / tan(M_PI / 6)) / vars->z_sprit;
	copy_h = (h > vars->hight * 2) ? h - vars->hight * 2 : 0;
	h = (h > vars->hight * 2) ? vars->hight * 2 : h;
	i = 0;
	while (i < (int)(h / 2))
	{
		color = pix_color_sprit(vars, vars->offset, i, h / 2 + copy_h);
		my_mlx_pixel_put(vars, k, vars->hight / 2 - h / 4 + i, color);
		i++;
	}
}

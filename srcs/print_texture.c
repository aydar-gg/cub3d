/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 14:41:29 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 20:16:00 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void		my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char *dst;

	dst = vars->img_data + (y * vars->line_length + x * (vars->bpp / 8));
	*(unsigned int*)dst = color;
}


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

	dst = NULL;
	if (check_over(vars->overview) > M_PI && check_over(vars->overview) < 2 * M_PI
	&& vars->z_horizontlly <= vars->z_vertically)//north
	{
		y = y * vars->no.hight / line;
		index = (x + y * vars->no.width);
		dst = vars->no.addr + index;
	}
	else if (check_over(vars->overview) > 0 && check_over(vars->overview) < M_PI
	&& vars->z_horizontlly <= vars->z_vertically)//south
	{
		y = y * vars->so.hight / line;
		index = (x + y * vars->so.width);
		dst = vars->so.addr + index;
	}
	else if (check_over(vars->overview) > M_PI_2 && check_over(vars->overview) < 3 * M_PI_2//east //линии на стыках текстур
	&& vars->z_horizontlly > vars->z_vertically)
	{
		y = y * vars->ea.hight / line;
		index = (x + y * vars->ea.width);
		dst = vars->ea.addr + index;
	}
	else if (((check_over(vars->overview) > 3 * M_PI_2 && check_over(vars->overview) < 2 * M_PI) ||
	(check_over(vars->overview) > 0 && check_over(vars->overview) < M_PI_2)) && vars->z_horizontlly > vars->z_vertically)//west //линии на стыках текстур
	{
		y = y * vars->we.hight / line;
		index = (x + y * vars->we.width);
		dst = vars->we.addr + index;
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
	vars->arr_z[k] = vars->z;
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

static t_sprite		*sort_sprite(t_vars *vars)
{
	t_sprite	*copy_sp;
	t_sprite	*sp_max;

	copy_sp = vars->sprit;
	sp_max = vars->sprit;
	while (copy_sp != NULL)
	{
		if ((copy_sp->z_sp > sp_max->z_sp && copy_sp->flag == 1 &&
		sp_max->flag == 1) || (sp_max->flag != 1 && copy_sp->flag == 1))
			sp_max = copy_sp;
		copy_sp = copy_sp->next;
	}
	return (sp_max);
}

void			print_sprite(t_vars *vars)
{
	int i;

	i = 0;
	while (i != vars->count_sp)
	{
		print_sprite_v_2(vars, sort_sprite(vars));
		i++;
	}
}

static int		pix_color_sp(t_vars *vars, int x, int y, float line)
{
	int		index;
	int		*dst;

	x = x * vars->sp.width / line;
	y = y * vars->sp.hight / line;
	index = (x + y * vars->sp.width);
	dst = vars->sp.addr + index;
	return (*(unsigned int*)dst);
}

void			print_sprite_v_2(t_vars *vars, t_sprite *sp)
{
	int h;
	int h_offset;
	int v_offset;
	int i;
	int j;
	int color;

	i = -1;
	sp->flag = -1;
	sp->sp_dir = atan2(sp->y_3d - vars->plr_y, sp->x_3d - vars->plr_x);
	while (sp->sp_dir - vars->x_reycast > M_PI)
		sp->sp_dir -= 2 * M_PI;
	while (sp->sp_dir - vars->x_reycast < -M_PI)
		sp->sp_dir += 2 * M_PI;
	h = (s_map * vars->hight) / sp->z_sp;
	h_offset = (sp->sp_dir - vars->x_reycast) * ((vars->width) / (M_PI / 3)) + vars->width / 2 - h / 2;
	v_offset = vars->hight / 2 - h / 4;
	while (++i < h / 2)
	{
		if (h_offset + i < 0 || v_offset + i > vars->width)
			continue ;
		j = -1;
		while (++j < h / 2)
		{
			if (v_offset + j >= vars->hight)
				continue ;
			color = pix_color_sp(vars, i, j, h / 2);
			if (color != 9961608 && h_offset + i < vars->width &&
			vars->arr_z[h_offset + i] > sp->z_sp && sp->z_sp > 22)
				my_mlx_pixel_put(vars, h_offset + i, v_offset + j, color);
		}
	}
}

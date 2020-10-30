/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:30:37 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 16:51:15 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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

static int			pix_color_sp(t_vars *vars, int x, int y, float line)
{
	int		index;
	int		*dst;

	x = x * vars->sp.width / line;
	y = y * vars->sp.hight / line;
	index = (x + y * vars->sp.width);
	dst = vars->sp.addr + index;
	return (*(unsigned int*)dst);
}

static void			print_sp_v_2_2(t_vars *vars, t_sprite *sp, int i, int j)
{
	while (++i < vars->h_sp / 2)
	{
		if (vars->h_offset + i < 0 || vars->v_offset + i > vars->width)
			continue ;
		j = -1;
		while (++j < vars->h_sp / 2)
		{
			if (vars->v_offset + j >= vars->hight)
				continue ;
			vars->color = pix_color_sp(vars, i, j, vars->h_sp / 2);
			if (vars->color != 9961608 && vars->h_offset + i < vars->width &&
			vars->arr_z[vars->h_offset + i] > sp->z_sp && sp->z_sp > 22)
				my_mlx_pixel_put(vars, vars->h_offset + i, vars->v_offset + j,
				vars->color);
		}
	}
}

static void			print_sprite_v_2(t_vars *vars, t_sprite *sp)
{
	sp->flag = -1;
	sp->sp_dir = atan2(sp->y_3d - vars->plr_y, sp->x_3d - vars->plr_x);
	while (sp->sp_dir - vars->x_reycast > M_PI)
		sp->sp_dir -= 2 * M_PI;
	while (sp->sp_dir - vars->x_reycast < -M_PI)
		sp->sp_dir += 2 * M_PI;
	vars->h_sp = (S_MAP * vars->hight) / sp->z_sp;
	vars->h_offset = (sp->sp_dir - vars->x_reycast) * ((vars->width) /
	(M_PI / 3)) + vars->width / 2 - vars->h_sp / 2;
	vars->v_offset = vars->hight / 2 - vars->h_sp / 4;
	print_sp_v_2_2(vars, sp, -1, 0);
}

void				print_sprite(t_vars *vars)
{
	int i;

	i = 0;
	while (i != vars->count_sp)
	{
		print_sprite_v_2(vars, sort_sprite(vars));
		i++;
	}
}

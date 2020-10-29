/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculat_raycast_h.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:20:01 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 21:21:51 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	v_sp_h_2(t_vars *vars, t_sprite *copy_sp)
{
	if (((int)(vars->Hy_ray / s_map) == copy_sp->y &&
	(int)(vars->Hx_ray / s_map) == copy_sp->x) ||
	((int)(vars->plr_y / s_map) == copy_sp->y &&
	(int)(vars->plr_x / s_map) == copy_sp->x))
	{
		copy_sp->flag = 1;
		copy_sp->z_sp = sqrt(pow(vars->plr_x - copy_sp->x_3d, 2)
			+ pow(vars->plr_y - copy_sp->y_3d, 2));
		vars->is_sp_h = 1;
	}
}

void	visible_sp_h(t_vars *vars)
{
	t_sprite	*copy_sp;

	while (vars->Hx_ray < vars->max_map_width * s_map && vars->Hy_ray <
	vars->max_map_hight * s_map &&
	 vars->Hy_ray / s_map > 0 && vars->Hx_ray / s_map > 0)
	{
		if (vars->t_map[(int)(vars->Hy_ray / s_map)]
		[((int)vars->Hx_ray / s_map)] == '2' || vars->t_map[(int)(vars->plr_y
		/ s_map)][(int)(vars->plr_x / s_map)] == '2')
		{
			copy_sp = vars->sprit;
			while (copy_sp != NULL)
			{
				v_sp_h_2(vars, copy_sp);
				copy_sp = copy_sp->next;
			}
		}
		vars->Hx_ray += vars->Xa;
		vars->Hy_ray += vars->Ya;
	}
}

void			take_change_h(t_vars *vars)
{
	if (check_over(vars->overview) > M_PI && check_over(vars->overview) < 2 * M_PI)//начальное расстояние по у новый способ если луч идет вверх
	{
		vars->Hy_ray = (int)(vars->plr_y / s_map) * (s_map) - 0.001;
		vars->Ya = -s_map;
	}
	else//если луч идет вниз
	{
		vars->Hy_ray = ((int)vars->plr_y / s_map) * (s_map) + s_map;
		vars->Ya = s_map;
	}
	if (check_over(vars->overview) > M_PI_2 && check_over(vars->overview) < 3 * M_PI_2)//влево по горизонтали
	{
		vars->Hx_ray = vars->plr_x + fabs((vars->plr_y - vars->Hy_ray) / tan(vars->overview)) * (-1);
		vars->Xa = fabs(s_map / tan(vars->overview)) * (-1);
	}
	else//вправо по горизонтали
	{
		vars->Hx_ray = vars->plr_x + fabs((vars->plr_y - vars->Hy_ray) / tan(vars->overview));
		vars->Xa = fabs(s_map / tan(vars->overview));
	}
}

void		length_at_horizontlly(t_vars *vars)
{
	take_change_h(vars);
	visible_sp_h(vars);
	take_change_h(vars);
	while (vars->Hx_ray < vars->max_map_width * s_map && vars->Hy_ray < vars->max_map_hight * s_map &&
	 vars->Hy_ray / s_map > 0 && vars->Hx_ray / s_map > 0 &&
	 vars->t_map[(int)(vars->Hy_ray / s_map)][(int)(vars->Hx_ray / s_map)] != '1')
	{
		vars->Hx_ray += vars->Xa;
		vars->Hy_ray += vars->Ya;
	}
	vars->z_horizontlly = sqrt(pow(vars->plr_y - vars->Hy_ray, 2) + pow(vars->plr_x - vars->Hx_ray, 2));
}

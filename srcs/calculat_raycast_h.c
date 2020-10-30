/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculat_raycast_h.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 21:20:01 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 16:55:26 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void		v_sp_h_2(t_vars *vars, t_sprite *copy_sp)
{
	if (((int)(vars->hy_ray / S_MAP) == copy_sp->y &&
	(int)(vars->hx_ray / S_MAP) == copy_sp->x) ||
	((int)(vars->plr_y / S_MAP) == copy_sp->y &&
	(int)(vars->plr_x / S_MAP) == copy_sp->x))
	{
		copy_sp->flag = 1;
		copy_sp->z_sp = sqrt(pow(vars->plr_x - copy_sp->x_3d, 2)
			+ pow(vars->plr_y - copy_sp->y_3d, 2));
		vars->is_sp_h = 1;
	}
}

static void		visible_sp_h(t_vars *vars)
{
	t_sprite	*copy_sp;

	while (vars->hx_ray < vars->max_map_width * S_MAP && vars->hy_ray <
	vars->max_map_hight * S_MAP &&
	vars->hy_ray / S_MAP > 0 && vars->hx_ray / S_MAP > 0)
	{
		if (vars->t_map[(int)(vars->hy_ray / S_MAP)]
		[((int)vars->hx_ray / S_MAP)] == '2' || vars->t_map[(int)(vars->plr_y
		/ S_MAP)][(int)(vars->plr_x / S_MAP)] == '2')
		{
			copy_sp = vars->sprit;
			while (copy_sp != NULL)
			{
				v_sp_h_2(vars, copy_sp);
				copy_sp = copy_sp->next;
			}
		}
		vars->hx_ray += vars->xa;
		vars->hy_ray += vars->ya;
	}
}

static void		take_change_h(t_vars *vars)
{
	if (check_over(vars->overview) > M_PI && check_over(vars->overview) <
	2 * M_PI)
	{
		vars->hy_ray = (int)(vars->plr_y / S_MAP) * (S_MAP) - 0.001;
		vars->ya = -S_MAP;
	}
	else
	{
		vars->hy_ray = ((int)vars->plr_y / S_MAP) * (S_MAP) + S_MAP;
		vars->ya = S_MAP;
	}
	if (check_over(vars->overview) > M_PI_2 && check_over(vars->overview) <
	3 * M_PI_2)
	{
		vars->hx_ray = vars->plr_x + fabs((vars->plr_y - vars->hy_ray) /
		tan(vars->overview)) * (-1);
		vars->xa = fabs(S_MAP / tan(vars->overview)) * (-1);
	}
	else
	{
		vars->hx_ray = vars->plr_x + fabs((vars->plr_y - vars->hy_ray) /
		tan(vars->overview));
		vars->xa = fabs(S_MAP / tan(vars->overview));
	}
}

void			length_at_horizontlly(t_vars *vars)
{
	take_change_h(vars);
	visible_sp_h(vars);
	take_change_h(vars);
	while (vars->hx_ray < vars->max_map_width * S_MAP && vars->hy_ray <
	vars->max_map_hight * S_MAP &&
	vars->hy_ray / S_MAP > 0 && vars->hx_ray / S_MAP > 0 &&
	vars->t_map[(int)(vars->hy_ray / S_MAP)][(int)(vars->hx_ray / S_MAP)]
	!= '1')
	{
		vars->hx_ray += vars->xa;
		vars->hy_ray += vars->ya;
	}
	vars->z_horizontlly = sqrt(pow(vars->plr_y - vars->hy_ray, 2)
	+ pow(vars->plr_x - vars->hx_ray, 2));
}

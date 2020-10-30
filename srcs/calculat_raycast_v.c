/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculat_raycast_v.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:43:08 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 16:55:26 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void		v_sp_v_2(t_vars *vars, t_sprite *copy_sp)
{
	if (((int)(vars->vy_ray / S_MAP) == copy_sp->y &&
	(int)(vars->vx_ray / S_MAP) == copy_sp->x) ||
	((int)(vars->plr_y / S_MAP) == copy_sp->y &&
	(int)(vars->plr_x / S_MAP) == copy_sp->x))
	{
		copy_sp->flag = 1;
		copy_sp->z_sp = sqrt(pow(vars->plr_x - copy_sp->x_3d, 2)
		+ pow(vars->plr_y - copy_sp->y_3d, 2));
		vars->is_sp_v = 1;
	}
}

static void		visible_sp_v(t_vars *vars)
{
	t_sprite	*copy_sp;

	while (vars->vx_ray < vars->max_map_width * S_MAP &&
	vars->vy_ray < vars->max_map_hight * S_MAP
	&& vars->vy_ray / S_MAP > 0 && vars->vx_ray / S_MAP > 0)
	{
		if (vars->t_map[(int)(vars->vy_ray / S_MAP)][((int)vars->vx_ray
		/ S_MAP)] == '2' || vars->t_map[(int)(vars->plr_y / S_MAP)]
		[(int)(vars->plr_x / S_MAP)] == '2')
		{
			copy_sp = vars->sprit;
			while (copy_sp != NULL)
			{
				v_sp_v_2(vars, copy_sp);
				copy_sp = copy_sp->next;
			}
		}
		vars->vx_ray += vars->xa;
		vars->vy_ray += vars->ya;
	}
}

static void		take_change_v(t_vars *vars)
{
	if (check_over(vars->overview) > M_PI_2 && check_over(vars->overview)
	< 3 * M_PI_2)
	{
		vars->vx_ray = (int)(vars->plr_x / S_MAP) * S_MAP - 0.001;
		vars->xa = -S_MAP;
	}
	else
	{
		vars->vx_ray = (int)(vars->plr_x / S_MAP) * S_MAP + S_MAP;
		vars->xa = S_MAP;
	}
	if (check_over(vars->overview) > 0 && check_over(vars->overview) < M_PI)
	{
		vars->vy_ray = vars->plr_y + fabs((vars->plr_x - vars->vx_ray)
		* tan(vars->overview));
		vars->ya = fabs(S_MAP * tan(vars->overview));
	}
	else
	{
		vars->vy_ray = vars->plr_y + fabs((vars->plr_x - vars->vx_ray)
		* tan(vars->overview)) * (-1);
		vars->ya = fabs(S_MAP * tan(vars->overview)) * (-1);
	}
}

void			length_at_vertically(t_vars *vars)
{
	take_change_v(vars);
	visible_sp_v(vars);
	take_change_v(vars);
	while (vars->vx_ray < vars->max_map_width * S_MAP &&
	vars->vy_ray < vars->max_map_hight * S_MAP
	&& vars->vy_ray / S_MAP > 0 && vars->vx_ray / S_MAP > 0 &&
	vars->t_map[(int)(vars->vy_ray / S_MAP)]
	[(int)(vars->vx_ray / S_MAP)] != '1')
	{
		vars->vx_ray += vars->xa;
		vars->vy_ray += vars->ya;
	}
	vars->z_vertically = sqrt(pow(vars->plr_y - vars->vy_ray, 2)
	+ pow(vars->plr_x - vars->vx_ray, 2));
}

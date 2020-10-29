/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculat_raycast_v.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:43:08 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 21:20:44 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	v_sp_v_2(t_vars *vars, t_sprite *copy_sp)
{
	if (((int)(vars->Vy_ray / s_map) == copy_sp->y &&
	(int)(vars->Vx_ray / s_map) == copy_sp->x) ||
	((int)(vars->plr_y / s_map) == copy_sp->y &&
	(int)(vars->plr_x / s_map) == copy_sp->x))
	{
		copy_sp->flag = 1;
		copy_sp->z_sp = sqrt(pow(vars->plr_x - copy_sp->x_3d, 2)
		+ pow(vars->plr_y - copy_sp->y_3d, 2));
		vars->is_sp_v = 1;
	}
}

void	visible_sp_v(t_vars *vars)
{
	t_sprite	*copy_sp;

	while (vars->Vx_ray < vars->max_map_width * s_map &&
	vars->Vy_ray < vars->max_map_hight * s_map
	&& vars->Vy_ray / s_map > 0 && vars->Vx_ray / s_map > 0)
	{
		if (vars->t_map[(int)(vars->Vy_ray / s_map)][((int)vars->Vx_ray
		/ s_map)] == '2' || vars->t_map[(int)(vars->plr_y / s_map)]
		[(int)(vars->plr_x / s_map)] == '2')
		{
			copy_sp = vars->sprit;
			while (copy_sp!= NULL)
			{
				v_sp_v_2(vars, copy_sp);
				copy_sp = copy_sp->next;
			}
		}
		vars->Vx_ray += vars->Xa;
		vars->Vy_ray += vars->Ya;
	}
}

void			take_change_v(t_vars *vars)
{
	if (check_over(vars->overview) > M_PI_2 && check_over(vars->overview) < 3 * M_PI_2)//начальное расстояние по х новый способ если луч идет влево
	{
		vars->Vx_ray = (int)(vars->plr_x / s_map) * s_map - 0.001;
		vars->Xa = -s_map;
	}
	else//если луч идет вправо
	{
		vars->Vx_ray = (int)(vars->plr_x / s_map) * s_map + s_map;
		vars->Xa = s_map;
	}
	if (check_over(vars->overview) > 0 && check_over(vars->overview) < M_PI)// вниз по вертикали
	{
		vars->Vy_ray = vars->plr_y + fabs((vars->plr_x - vars->Vx_ray) * tan(vars->overview));
		vars->Ya = fabs(s_map * tan(vars->overview));
	}
	else//вверх по вертикали
	{
		vars->Vy_ray = vars->plr_y + fabs((vars->plr_x - vars->Vx_ray) * tan(vars->overview)) * (-1);
		vars->Ya = fabs(s_map * tan(vars->overview)) * (-1);
	}
}

void		length_at_vertically(t_vars *vars)
{
	take_change_v(vars);
	visible_sp_v(vars);
	take_change_v(vars);
	while (vars->Vx_ray < vars->max_map_width * s_map && vars->Vy_ray < vars->max_map_hight * s_map
	&& vars->Vy_ray / s_map > 0 && vars->Vx_ray / s_map > 0 && vars->t_map[(int)(vars->Vy_ray / s_map)][(int)(vars->Vx_ray / s_map)] != '1')
	{
		vars->Vx_ray += vars->Xa;
		vars->Vy_ray += vars->Ya;
	}
	vars->z_vertically = sqrt(pow(vars->plr_y - vars->Vy_ray, 2) + pow(vars->plr_x - vars->Vx_ray, 2));
}

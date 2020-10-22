/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:26:42 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/22 16:39:46 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int check_cell(t_vars *vars, double ch_c, double ch_s)
{
	int ret;
	int ret_x;
	int ret_y;

	ret = (vars->t_map[(int)((vars->plr_y + ch_s) / s_map)][(int)((vars->plr_x + ch_c) / s_map)] == '1') ? 0 : 1;
	ret_x = (vars->t_map[(int)((vars->plr_y) / s_map)][(int)((vars->plr_x + ch_c) / s_map)] == '1') ? 0 : 1;
	ret_y = (vars->t_map[(int)((vars->plr_y + ch_s) / s_map)][(int)((vars->plr_x) / s_map)] == '1') ? 0 : 1;
	return (ret && ret_x && ret_y);
}

int		key_press(int keycode, t_vars *vars)
{
	double ch_cos;
	double ch_sin;

	ch_cos = cos(vars->x_reycast);
	ch_sin = sin(vars->y_reycast);
	if (keycode == 13)//FORWARD
	{
		if (check_cell(vars, ch_cos, ch_sin))
		{
			vars->plr_x += cos(vars->x_reycast);
			vars->plr_y += sin(vars->y_reycast);
		}
	}
	if (keycode == 0)//LEFT
	{
		if (check_cell(vars, -cos(vars->x_reycast + M_PI_2), -sin(vars->y_reycast + M_PI_2)))
		{
			vars->plr_x -= cos(vars->x_reycast + M_PI_2);
			vars->plr_y -= sin(vars->y_reycast + M_PI_2);
		}
	}
	if (keycode == 1)//BACK
	{
		if (check_cell(vars, -ch_cos, -ch_sin))
		{
			vars->plr_x -= cos(vars->x_reycast);
			vars->plr_y -= sin(vars->y_reycast);
		}
	}
	if (keycode == 2)//RIGHT
	{
		if (check_cell(vars, cos(vars->x_reycast + M_PI_2), sin(vars->y_reycast + M_PI_2)))
		{
			vars->plr_x += cos(vars->x_reycast + M_PI_2);
			vars->plr_y += sin(vars->y_reycast + M_PI_2);
		}
	}
	if (keycode == 123)//turn right
	{
		vars->x_reycast -= turn;
		vars->y_reycast -= turn;
	}
	if (keycode == 124)//turn left
	{
		vars->x_reycast += turn;
		vars->y_reycast += turn;
	}
	mlx_clear_window(vars->mlx, vars->win);
	print_map_2d(vars);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:26:42 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 16:52:54 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int		check_cell(t_vars *vars, double ch_c, double ch_s)
{
	int ret;
	int ret_x;
	int ret_y;

	ret = (vars->t_map[(int)((vars->plr_y + ch_s) / S_MAP)]
	[(int)((vars->plr_x + ch_c) / S_MAP)] == '1') ? 0 : 1;
	ret_x = (vars->t_map[(int)((vars->plr_y) / S_MAP)]
	[(int)((vars->plr_x + ch_c) / S_MAP)] == '1') ? 0 : 1;
	ret_y = (vars->t_map[(int)((vars->plr_y + ch_s) / S_MAP)]
	[(int)((vars->plr_x) / S_MAP)] == '1') ? 0 : 1;
	return (ret && ret_x && ret_y);
}

static void		key_press_part_2(int keycode, t_vars *vars, double ch_cos,
double ch_sin)
{
	if (keycode == 13 || keycode == 126)
	{
		if (check_cell(vars, 16 * ch_cos, 16 * ch_sin))
		{
			vars->plr_x += 4 * cos(vars->x_reycast);
			vars->plr_y += 4 * sin(vars->y_reycast);
		}
	}
	if (keycode == 0)
	{
		if (check_cell(vars, 16 * -cos(vars->x_reycast + M_PI_2),
		16 * -sin(vars->y_reycast + M_PI_2)))
		{
			vars->plr_x -= 4 * cos(vars->x_reycast + M_PI_2);
			vars->plr_y -= 4 * sin(vars->y_reycast + M_PI_2);
		}
	}
}

static void		key_press_part_3(int keycode, t_vars *vars, double ch_cos,
double ch_sin)
{
	if (keycode == 1 || keycode == 125)
	{
		if (check_cell(vars, 16 * -ch_cos, 16 * -ch_sin))
		{
			vars->plr_x -= 4 * cos(vars->x_reycast);
			vars->plr_y -= 4 * sin(vars->y_reycast);
		}
	}
	if (keycode == 2)
	{
		if (check_cell(vars, 16 * cos(vars->x_reycast + M_PI_2),
		16 * sin(vars->y_reycast + M_PI_2)))
		{
			vars->plr_x += 4 * cos(vars->x_reycast + M_PI_2);
			vars->plr_y += 4 * sin(vars->y_reycast + M_PI_2);
		}
	}
}

int				key_press(int keycode, t_vars *vars)
{
	double ch_cos;
	double ch_sin;

	ch_cos = cos(vars->x_reycast);
	ch_sin = sin(vars->y_reycast);
	key_press_part_2(keycode, vars, ch_cos, ch_sin);
	key_press_part_3(keycode, vars, ch_cos, ch_sin);
	if (keycode == 123)
	{
		vars->x_reycast -= TURN;
		vars->y_reycast -= TURN;
	}
	if (keycode == 124)
	{
		vars->x_reycast += TURN;
		vars->y_reycast += TURN;
	}
	mlx_clear_window(vars->mlx, vars->win);
	print_map_2d(vars);
	return (0);
}

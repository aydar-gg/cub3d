/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plr_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:26:42 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/04 17:09:44 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		key_press(int keycode, t_vars *vars)
{
	if (keycode == 13)//FORWARD
	{
		vars->plr_x += cos(vars->x_reycast);
		vars->plr_y += sin(vars->y_reycast);
	}
	if (keycode == 0)//LEFT
	{
		vars->plr_x -= cos(vars->x_reycast + M_PI_2);
		vars->plr_y -= sin(vars->y_reycast + M_PI_2);
	}
	if (keycode == 1)//BACK
	{
		vars->plr_x -= cos(vars->x_reycast);
		vars->plr_y -= sin(vars->y_reycast);
	}
	if (keycode == 2)//RIGHT
	{
		vars->plr_x += cos(vars->x_reycast + M_PI/2);
		vars->plr_y += sin(vars->y_reycast + M_PI/2);
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

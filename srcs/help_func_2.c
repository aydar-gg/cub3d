/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:26:32 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 19:28:09 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		v_test_2(int keycode)
{
	if (keycode ==53)
		exit (0);
	return (0);
}

int		ft_exit(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(1);
	return (0);
}

void	inicial_vars(t_vars *vars)
{
	vars->r_mon = 0;
	vars->s_text = 0;
	vars->so_text = 0;
	vars->no_text = 0;
	vars->ea_text = 0;
	vars->we_text = 0;
	vars->f_count = 0;
	vars->c_count = 0;
	vars->width = -1;
	vars->hight = -1;
}

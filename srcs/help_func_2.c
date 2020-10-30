/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:26:32 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 16:51:15 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		v_test_2(int keycode)
{
	if (keycode == 53)
		exit(1);
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
	vars->is_wr_t = 0;
	vars->max_map_hight = 0;
	vars->max_map_width = 0;
}

void	check_z(t_vars *vars, int k)
{
	int h;
	int i;
	int color;
	int copy_h;

	if (vars->arr_z[k - 1] > vars->arr_z[k - 2])
	{
		if (vars->arr_z[k - 1] > vars->z)
		{
			vars->arr_z[k - 1] = vars->z;
			h = S_MAP * ((vars->hight / 2) / tan(M_PI / 6)) / vars->z;
			copy_h = (h > vars->hight * 2) ? h - vars->hight * 2 : 0;
			h = (h > vars->hight * 2) ? vars->hight * 2 : h;
			i = 0;
			while (i < (int)(h / 2))
			{
				color = pix_color(vars, vars->offset, i + copy_h / 4,
				h / 2 + copy_h / 2);
				my_mlx_pixel_put(vars, k - 1,
				vars->hight / 2 - h / 4 + i, color);
				i++;
			}
		}
	}
}

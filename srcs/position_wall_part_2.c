/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_wall_part_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:15:09 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 20:32:29 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	d2_map_part_3(char c, t_vars *vars, int k, int h)
{
	int k_2;
	int h_2;

	k_2 = k;
	while (k != k_2 + s_map / 4)
	{
		h_2 = h;
		while (h != h_2 + s_map / 4)
		{
			if (c == '1')
				my_mlx_pixel_put(vars, h, k, 0x000000FF);
			else if (c == '2' && h < h_2 + s_map / 8 && k < k_2 + s_map / 8)
				my_mlx_pixel_put(vars, h, k, 0x0000AAAA);
			h++;
		}
		h -= s_map / 4;
		k++;
	}
}

void	d2_map_part_2(t_vars *vars, int i, int k, int h)
{
	int k_2;
	int h_2;
	int l;

	l = 0;
	k_2 = 0;
	h_2 = 0;
	while (vars->t_map[i][l] != '\n' && vars->t_map[i][l] != '\0')
	{
		if (vars->t_map[i][l] != '0')
		{
			d2_map_part_3(vars->t_map[i][l], vars, k, h);
		}
		h += s_map / 4;
		l++;
	}
}

void	d2_map(t_vars *vars)
{
	int k;
	int h;
	int i;

	i = 0;
	k = 0;
	while(i != vars->max_map_hight)
	{
		h = 0;
		d2_map_part_2(vars, i, k, h);
		k += s_map / 4;
		i++;
	}
}

void	put_z(t_vars *vars)
{
	int c;

	c = 0;
	while (c != (int)(vars->z / 4))
	{
		my_mlx_pixel_put(vars, vars->plr_x / 4 + c * cos(vars->overview),
		vars->plr_y / 4 + c * sin(vars->overview), 0x00FF0000);
		c++;
	}
}

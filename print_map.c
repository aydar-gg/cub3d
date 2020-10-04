/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:28:49 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/04 16:29:57 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char *dst;

	dst = data->img_data + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void d2_map(t_vars *vars)
{
	int k, k_2;
	int h, h_2;
	int i;
	int l;
	float z;
	i = 0;
	k = 0;
	while(i != vars->max_map_hight)
	{
		l = 0;
		h = 0;
		while (vars->t_map[i][l] != '\n' && vars->t_map[i][l] != '\0')
		{
			if (vars->t_map[i][l] == '1')
			{
				k_2 = k;
				while (k != k_2 + s_map)
				{
					h_2 = h;
					while (h != h_2 + s_map)
					{
						my_mlx_pixel_put(vars, h, k, 0x00AAFF00);
						h++;
					}
					h -= s_map;
					k++;
				}
				k -= s_map;
			}
				h += s_map;
			l++;
		}
		k += s_map;
		i++;
	}
}
static void		map_3d(double z, t_vars *vars, float k)
{
	int h;
	int i;
	double test;
	double over;

	if (k  == 1000 || k == 900 || k == 500)
		i = 0;
	//if (vars->overview < vars->x_reycast)
	//	z = z * sin(M_PI_2 - (vars->x_reycast - vars->overview));//sin(vars->x_reycast - vars->overview);
	//else
	//	z = z * sin(M_PI_2 - (vars->overview - vars->x_reycast));//sin(vars->overview - vars->x_reycast);
	//over = ((int)(vars->overview - vars->x_reycast) == 0) ? vars->x_reycast : vars->overview;
	test = cos(vars->overview - vars->x_reycast);
	z = z * cos(vars->overview - vars->x_reycast);
	h = (vars->hight) / z;
	if (h > vars->hight * 2)
		h = vars->hight * 2;
	i = 0;
	while (i <= h / 2)
	{
		my_mlx_pixel_put(vars, k, vars->hight / 2 - h / 4 + i, 0x00AAFFAA);
		i += 1;
	}
}

static void find_main_line(t_vars *vars)
{
	double z;

	z = 0;
	vars->x_line = vars->plr_x;
	vars->y_line = vars->plr_y;
	while ((int)z != 40)
	{
		vars->x_line += cos(vars->x_reycast);
		vars->y_line += sin(vars->y_reycast);
		if (vars->t_map[(int)vars->y_line / s_map][(int)vars->x_line / s_map] == '1')
		{
			vars->main_line = sqrt(pow((vars->x_line - vars->plr_x), 2) + pow((vars->y_line - vars->plr_y), 2)) / s_map;
			break ;
		}
		z += 0.1;
	}
}

void	print_map_2d(t_vars *vars)	//быстрая рисовка линий
{
	int i;
	double z;

	i = 0;

	vars->img_ptr = mlx_new_image(vars->mlx, vars->width, vars->hight);
	vars->img_data = mlx_get_data_addr(vars->img_ptr, &vars->bpp, &vars->line_length, &vars->endian);
	find_main_line(vars);
	vars->overview = vars->x_reycast - M_PI / 6;
	d2_map(vars);
	while (vars->overview <= vars->x_reycast + M_PI / 6)//vars->x_reycast - M_PI / 6 + 2 * ((M_PI / 3) / vars->width))
	{
		vars->x_line = vars->plr_x;
		vars->y_line = vars->plr_y;
		z = 0;
		while ((int)z != 40)
		{
			vars->x_line += cos(vars->overview);
			vars->y_line += sin(vars->overview);
			if (vars->t_map[(int)(round(vars->y_line) / s_map)][(int)(round(vars->x_line) / s_map)] == '1')
			{
				map_3d(sqrt(pow((round(vars->x_line) - vars->plr_x), 2) + pow((round(vars->y_line) - vars->plr_y), 2)) / s_map, vars, i);
				i += 1;
				break ;
			}
			my_mlx_pixel_put(vars, vars->x_line, vars->y_line, 0x00FF0000);
			z += 0.1;
		}
		vars->overview += ((M_PI / 3) / vars->width);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ptr, 0, 0);
}

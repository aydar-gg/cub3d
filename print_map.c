/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:28:49 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/22 15:59:23 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	check_over(double over)
{
	while (over > 2 * M_PI)
		over -= 2 * M_PI;
	while (over < 0)
		over += 2 * M_PI;
	return (over);
}

void		my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char *dst;

	dst = vars->img_data + (y * vars->line_length + x * (vars->bpp / 8));
	*(unsigned int*)dst = color;
}

static void		d2_map(t_vars *vars)
{
	int k, k_2;
	int h, h_2;
	int i;
	int l;
	i = 0;
	k = 0;
	while(i != vars->max_map_hight)
	{
		l = 0;
		h = 0;
		while (vars->t_map[i][l] != '\n' && vars->t_map[i][l] != '\0')
		{
			if (vars->t_map[i][l] != '0')
			{
				k_2 = k;
				while (k != k_2 + s_map / 4)
				{
					h_2 = h;
					while (h != h_2 + s_map / 4)
					{
						if (vars->t_map[i][l] == '1')
							my_mlx_pixel_put(vars, h, k, 0x000000FF);
						else if (vars->t_map[i][l] == '2')
							my_mlx_pixel_put(vars, h, k, 0x0000AAAA);
						h++;
					}
					h -= s_map / 4;
					k++;
				}
				k -= s_map / 4;
			}
				h += s_map / 4;
			l++;
		}
		k += s_map / 4;
		i++;
	}
}

static void		length_at_horizontlly(t_vars *vars)
{
	if (check_over(vars->overview) > M_PI && check_over(vars->overview) < 2 * M_PI)//начальное расстояние по у новый способ если луч идет вверх
	{
		vars->Hy_ray = (int)(vars->plr_y / s_map) * (s_map) - 0.001;
		vars->Ya = -s_map;
	}
	else//если луч идет вниз
	{
		vars->Hy_ray = ((int)vars->plr_y / s_map) * (s_map) + s_map;
		vars->Ya = s_map;
	}
	if (check_over(vars->overview) > M_PI_2 && check_over(vars->overview) < 3 * M_PI_2)//влево по горизонтали
	{
		vars->Hx_ray = vars->plr_x + fabs((vars->plr_y - vars->Hy_ray) / tan(vars->overview)) * (-1);
		vars->Xa = fabs(s_map / tan(vars->overview)) * (-1);
	}
	else//вправо по горизонтали
	{
		vars->Hx_ray = vars->plr_x + fabs((vars->plr_y - vars->Hy_ray) / tan(vars->overview));
		vars->Xa = fabs(s_map / tan(vars->overview));
	}
	while (vars->Hx_ray < vars->max_map_width * s_map && vars->Hy_ray < vars->max_map_hight * s_map &&
	 vars->Hy_ray / s_map > 0 && vars->Hx_ray / s_map > 0 &&
	 vars->t_map[(int)(vars->Hy_ray / s_map)][(int)(vars->Hx_ray / s_map)] != '1')
	{
		if (vars->t_map[(int)(vars->Hy_ray / s_map)][(int)(vars->Hx_ray / s_map)] == '2')
			vars->z_sprit_h = sqrt(pow(vars->plr_y - vars->Hy_ray, 2) + pow(vars->plr_x - vars->Hx_ray, 2));
		vars->Hx_ray += vars->Xa;
		vars->Hy_ray += vars->Ya;
	}
	vars->z_horizontlly = sqrt(pow(vars->plr_y - vars->Hy_ray, 2) + pow(vars->plr_x - vars->Hx_ray, 2));
}

static void		length_at_vertically(t_vars *vars)
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
	while (vars->Vx_ray < vars->max_map_width * s_map && vars->Vy_ray < vars->max_map_hight * s_map
	&& vars->Vy_ray / s_map > 0 && vars->Vx_ray / s_map > 0 && vars->t_map[(int)(vars->Vy_ray / s_map)][(int)(vars->Vx_ray / s_map)] != '1')
	{
		if (vars->t_map[(int)(vars->Vy_ray / s_map)][(int)(vars->Vx_ray / s_map)] == '2')
			vars->z_sprit_v = sqrt(pow(vars->plr_y - vars->Vy_ray, 2) + pow(vars->plr_x - vars->Vx_ray, 2));
		vars->Vx_ray += vars->Xa;
		vars->Vy_ray += vars->Ya;
	}
	vars->z_vertically = sqrt(pow(vars->plr_y - vars->Vy_ray, 2) + pow(vars->plr_x - vars->Vx_ray, 2));
}

//static void right_left(t_vars *vars)
//{
//	vars->Vy_ray = vars->plr_y;
//	vars->Hy_ray = vars->plr_y;
//	if (check_over(vars->overview) > M_PI_2 && check_over(vars->overview) < 3 * M_PI_2)
//	{
//		vars->Vx_ray = (int)(vars->plr_x / s_map) * s_map - 0.001;
//		vars->Xa = -s_map;
//	}
//	else
//	{
//		vars->Vx_ray = (int)(vars->plr_x / s_map) * s_map + s_map;
//		vars->Xa = s_map;
//	}
//	while (vars->t_map[(int)(vars->Vy_ray / s_map)][(int)(vars->Vx_ray / s_map)] != '1')
//		vars->Vx_ray += vars->Xa;
//	vars->Hx_ray = vars->Vx_ray;
//	vars->z_horizontlly = fabs(vars->Vx_ray - vars->plr_x);
//	vars->z_vertically = fabs(vars->Vx_ray - vars->plr_x);
//}

//static void up_down(t_vars *vars)
//{
//	vars->Hx_ray = vars->plr_x;
//	vars->Vx_ray = vars->plr_x;
//	if (check_over(vars->overview) > M_PI && check_over(vars->overview) < 2 * M_PI)
//	{
//		vars->Hy_ray = (int)(vars->plr_y / s_map) * s_map - 0.001;
//		vars->Ya = -s_map;
//	}
//	else
//	{
//		vars->Hy_ray = (int)(vars->plr_y / s_map) * s_map + s_map;
//		vars->Ya = s_map;
//	}
//	while (vars->t_map[(int)(vars->Hy_ray / s_map)][(int)(vars->Hx_ray / s_map)] != '1')
//		vars->Hy_ray += vars->Ya;
//	vars->Vy_ray = vars->Hy_ray;
//	vars->z_horizontlly = fabs(vars->Hy_ray - vars->plr_y);
//	vars->z_vertically = fabs(vars->Hy_ray - vars->plr_y);
//}

static void		put_z(t_vars *vars)
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

static void		print_floor_ceiling(t_vars *vars)
{
	int i;
	int k;

	i = 0;
	while (i != vars->width)
	{
		k = vars->hight / 2;
		while (k != vars->hight)
		{
			my_mlx_pixel_put(vars, i, k, 600);
			k++;
		}
		i++;
	}
	i = 0;
	while (i != vars->width)
	{
		k = 0;
		while (k != vars->hight / 2)
		{
			my_mlx_pixel_put(vars, i, k, 14);
			k++;
		}
		i++;
	}
}

void			print_map_2d(t_vars *vars)	//быстрая рисовка линий
{
	int i;

	vars->img_ptr = mlx_new_image(vars->mlx, vars->width, vars->hight);
	vars->img_data = mlx_get_data_addr(vars->img_ptr, &vars->bpp, &vars->line_length, &vars->endian);
	vars->overview = vars->x_reycast - M_PI / 6;
	print_floor_ceiling(vars);
	i = 0;
	while (vars->overview <= vars->x_reycast + M_PI / 6)
	{
		//if ((int)(check_over(vars->overview) * 1000) == 0 || check_over(vars->overview) == 3.1415926535897962 ||
		//check_over(vars->overview) == 1.5707963267948641 || tan(vars->overview) == 0)
		//	right_left(vars);
		//else if (tan(vars->overview) == -2147483648 || (int)(check_over(vars->overview) * 1000) == 4712)
		//	up_down(vars);
		//else
		//{
		length_at_horizontlly(vars);
		length_at_vertically(vars);
		//}
		vars->z = (vars->z_vertically <= vars->z_horizontlly) ? vars->z_vertically : vars->z_horizontlly;
		vars->offset = (vars->z_vertically <= vars->z_horizontlly) ? (int)vars->Vy_ray % s_map : (int)vars->Hx_ray % s_map;
		map_3d(vars, i);
		if ((int)vars->z_sprit_h || (int)vars->z_sprit_v)
		{
			vars->z_sprit = (vars->z_sprit_v <= vars->z_sprit_h) ? vars->z_sprit_v : vars->z_sprit_h;
			vars->offset_sprit = (vars->z_sprit_v <= vars->z_sprit_h) ? (int)vars->z_sprit_v % s_map : (int)vars->z_sprit_h % s_map;
			print_sprit(vars, i);
			vars->z_sprit_h = 0;
			vars->z_sprit_v = 0;
		}
		put_z(vars);
		vars->overview += ((M_PI / 3) / vars->width);
		i++;
	}
	d2_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ptr, 0, 0);
}


//void    draw_column(t_vars *ap, int col_nmb, float step)
//{
//    ap->start = -1;
//    step = step * cos(ap->player_a - ap->angle);
//    ap->dist_to_pp = (ap->win_x / 2) / tan(M_PI / 6);
//    ap->wall_size = ap->block_h * ap->dist_to_pp / step;
//    ap->centre = ap->win_y / 2;
//    ap->y_h = ap->centre - (ap->wall_size / 2);
//    if (ap->wall_size > ap->win_y)
//    {
//        ap->y_h = 0;
//        ap->y2 = (ap->wall_size - ap->win_y) / 2;
//    }
//    else
//        ap->y2 = 0;
//    while (ap->y_h > ++ap->start)
//        my_mlx_pixel_put(ap, col_nmb, ap->start, ap->ceil);
//    while (ap->y2 < ap->wall_size && ap->y_h < ap->win_y - 1)
//        get_color_wall(ap, col_nmb);
//    while (ap->y_h < ap->win_y - 1)
//    {
//        my_mlx_pixel_put(ap, col_nmb, ap->y_h, ap->floor);
//        ap->y_h++;
//    }
//}

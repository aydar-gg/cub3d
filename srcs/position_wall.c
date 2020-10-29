/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 16:28:49 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 20:44:35 by psabreto         ###   ########.fr       */
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
			my_mlx_pixel_put(vars, i, k, vars->f_color);
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
			my_mlx_pixel_put(vars, i, k, vars->c_color);
			k++;
		}
		i++;
	}
}

void			print_map_2d_part_2(t_vars *vars, int i)
{
	while (vars->overview <= vars->x_reycast + M_PI / 6 && i < vars->width)
	{
		length_at_horizontlly(vars);
		length_at_vertically(vars);
		vars->z = (vars->z_vertically <= vars->z_horizontlly) ? vars->z_vertically : vars->z_horizontlly;
		vars->offset = (vars->z_vertically <= vars->z_horizontlly) ? (int)vars->Vy_ray % s_map : (int)vars->Hx_ray % s_map;
		map_3d(vars, i);
		if (s_map / 4 * vars->max_map_hight < vars->hight &&
	s_map / 4 * vars->max_map_width < vars->width)
			put_z(vars);
		vars->overview += ((M_PI / 3) / vars->width);
		i++;
	}
	if (vars->is_sp_h || vars->is_sp_v)
		print_sprite(vars);
	if (s_map / 4 * vars->max_map_hight < vars->hight &&
	s_map / 4 * vars->max_map_width < vars->width)
		d2_map(vars);
}

void			print_map_2d(t_vars *vars)
{
	vars->img_ptr = mlx_new_image(vars->mlx, vars->width, vars->hight);
	vars->img_data = mlx_get_data_addr(vars->img_ptr, &vars->bpp, &vars->line_length, &vars->endian);
	vars->overview = vars->x_reycast - M_PI / 6;
	print_floor_ceiling(vars);
	vars->is_sp_h = 0;
	vars->is_sp_v = 0;
	if (!(vars->arr_z = (int*)malloc(vars->width * sizeof(int))))
		ft_error(1, vars);
	print_map_2d_part_2(vars, 0);
	if (vars->argc == 3)
		get_scrin(vars);
	free(vars->arr_z);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ptr, 0, 0);
}

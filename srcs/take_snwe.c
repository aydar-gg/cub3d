/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_snwe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 22:08:12 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 16:28:56 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		read_map_part_no(t_vars *vars, char *line)
{
	if (ft_strnstr(line, "NO ", 4))
	{
		check_space(ft_strnstr(line, "NO ", 4) + 2, vars);
		if (!(vars->no.north = mlx_xpm_file_to_image(vars->mlx,
		ft_strchr(line, '.'), &vars->no.width, &vars->no.hight)))
			ft_error(2, vars);
		vars->no.addr = (int*)mlx_get_data_addr(vars->no.north,
		&(vars->no.bpp), &(vars->no.line_length), &(vars->no.endian));
		vars->no_text++;
		return (1);
	}
	return (0);
}

int		read_map_part_so(t_vars *vars, char *line)
{
	if (ft_strnstr(line, "SO ", 4))
	{
		check_space(ft_strnstr(line, "SO ", 4) + 2, vars);
		if (!(vars->so.south = mlx_xpm_file_to_image(vars->mlx,
		ft_strchr(line, '.'), &vars->so.width, &vars->so.hight)))
			ft_error(2, vars);
		vars->so.addr = (int*)mlx_get_data_addr(vars->so.south,
		&(vars->so.bpp), &(vars->so.line_length), &(vars->so.endian));
		vars->so_text++;
		return (1);
	}
	return (0);
}

int		read_map_part_ea(t_vars *vars, char *line)
{
	if (ft_strnstr(line, "EA ", 4))
	{
		check_space(ft_strnstr(line, "EA ", 4) + 2, vars);
		if (!(vars->ea.east = mlx_xpm_file_to_image(vars->mlx,
		ft_strchr(line, '.'), &vars->ea.width, &vars->ea.hight)))
			ft_error(2, vars);
		vars->ea.addr = (int*)mlx_get_data_addr(vars->ea.east,
		&(vars->ea.bpp), &(vars->ea.line_length), &(vars->ea.endian));
		vars->ea_text++;
		return (1);
	}
	return (0);
}

int		read_map_part_we(t_vars *vars, char *line)
{
	if (ft_strnstr(line, "WE ", 4))
	{
		check_space(ft_strnstr(line, "WE ", 4) + 2, vars);
		if (!(vars->we.west = mlx_xpm_file_to_image(vars->mlx,
		ft_strchr(line, '.'), &vars->we.width, &vars->we.hight)))
			ft_error(2, vars);
		vars->we.addr = (int*)mlx_get_data_addr(vars->we.west,
		&(vars->we.bpp), &(vars->we.line_length), &(vars->we.endian));
		vars->we_text++;
		return (1);
	}
	else if (read_map_part_ea(vars, line))
		return (1);
	else if (read_map_part_s(vars, line))
		return (1);
	return (0);
}

int		read_map_part_s(t_vars *vars, char *line)
{
	if (ft_strnstr(line, "S ", 3))
	{
		check_space(ft_strnstr(line, "S ", 3) + 1, vars);
		if (!(vars->sp.sprit = mlx_xpm_file_to_image(vars->mlx,
		ft_strchr(line, '.'), &vars->sp.width, &vars->sp.hight)))
			ft_error(2, vars);
		vars->sp.addr = (int*)mlx_get_data_addr(vars->sp.sprit,
		&(vars->sp.bpp), &(vars->sp.line_length), &(vars->sp.endian));
		vars->s_text++;
		return (1);
	}
	return (0);
}

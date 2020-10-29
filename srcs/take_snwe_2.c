/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_snwe_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 22:10:02 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 20:06:19 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		read_map_part_FC(t_vars *vars, char *line)
{
	if (ft_strnstr(line, "F ", 3))
	{
		vars->f_color = take_color(vars, ft_strchr(line, ' '), 0, 0);
		vars->f_count++;
		return (1);
	}
	else if (ft_strnstr(line, "C ", 3))
	{
		vars->c_color = take_color(vars, ft_strchr(line, ' '), 0, 0);
		vars->c_count++;
		return (1);
	}
	return (0);
}

int		read_map_part_R(t_vars *vars, char *line, int i)
{
	if (ft_strnstr(line, "R", 2))
	{
		while (line[++i] != '\0')
		{
			if (!ft_isdigit(line[i]) && line[i] != ' ')
				ft_error(2, vars);
		}
		i = 1;
		while (line[i] == ' ')
			i++;
		vars->width = (ft_isdigit(line[i])) ? ft_atoi(&line[i]) : -1;
		i += num_width(vars->width);
		while (line[i] == ' ')
			i++;
		vars->hight = (ft_isdigit(line[i])) ? ft_atoi(&line[i]) : -1;
		if (vars->width < 0 || vars->hight < 0)
			ft_error(2, vars);
		vars->r_mon++;
		return (1);
	}
	else if (read_map_part_no(vars, line))
		return (1);
	else if (read_map_part_so(vars, line))
		return (1);
	return (0);
}

int		count_of_map(t_vars *vars, char *line, t_list **str_map)
{
	if (ft_strchr(line, '1') && vars->r_mon && vars->s_text &&
	vars->so_text && vars->no_text && vars->ea_text && vars->we_text &&
	vars->f_count && vars->c_count)
	{
		if (vars->max_map_width < (int)ft_strlen(line))
			vars->max_map_width = (int)ft_strlen(line);
		ft_lstadd_back(str_map, ft_lstnew(line));
		vars->max_map_hight++;
		return (1);
	}
	return (0);
}


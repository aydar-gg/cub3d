/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 22:28:04 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 22:03:24 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int		create_rgb(t_vars *ap)
{
	return (ap->r << 16 | ap->g << 8 | ap->b);
}

void	check_r(t_vars *vars, int *i, int *rg, char *line)
{
	vars->r = ft_atoi(&line[*i]);
	(vars->r > 255 || vars->r < 0) ? ft_error(2, vars) : 0;
	*i += num_width(vars->r);
	while (line[*i] != ',')
	{
		if (ft_isdigit(line[*i]))
			ft_error(2, vars);
		if (line[*i] != ' ')
			ft_error(2, vars);
		i[0]++;
	}
	rg[0]++;
}

void	check_g(t_vars *vars, int *i, int *rg, char *line)
{
	vars->g = ft_atoi(&line[*i]);
	(vars->g > 255 || vars->g < 0) ? ft_error(2, vars) : 0;
	*i += num_width(vars->g);
	while (line[*i] != ',')
	{
		if (ft_isdigit(line[*i]))
			ft_error(2, vars);
		if (line[*i] != ' ')
			ft_error(2, vars);
		i[0]++;
	}
	rg[0]++;
}

void	check_b(t_vars *vars, int *i, int *b, char *line)
{
	vars->b = ft_atoi(&line[*i]);
	(vars->b > 255 || vars->b < 0) ? ft_error(2, vars) : 0;
	*i += num_width(vars->b);
	b[0]++;
}

int		take_color(t_vars *vars, char *line, int r, int g)
{
	int i;
	int b;

	i = -1;
	b = 0;
	while (line[++i] != '\0')
	{
		if (ft_isdigit(line[i]) && !r)
			check_r(vars, &i, &r, line);
		if (ft_isdigit(line[i]) && r && !g)
			check_g(vars, &i, &g, line);
		if (ft_isdigit(line[i]) && g && r)
			check_b(vars, &i, &b, line);
		if (line[i] == '\0')
			break ;
		if (((b || (!b && !r && !g)) && line[i] == ',') ||
		(!ft_isdigit(line[i]) && line[i] != ',' && line[i] != ' '))
			ft_error(2, vars);
	}
	if (r != 1 || g != 1 || b != 1)
		ft_error(2, vars);
	return (create_rgb(vars));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:29:22 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 16:28:14 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_zero_one_part_2(t_vars *vars, int k, int i)
{
	if (((vars->t_map[i][k + 1] == '0' || vars->t_map[i][k + 1] == '2' ||
	vars->t_map[i][k + 1] == 'E' || vars->t_map[i][k + 1] == 'W' ||
	vars->t_map[i][k + 1] == 'S' || vars->t_map[i][k + 1] == 'N') &&
	vars->t_map[i][k] != '1' &&
	vars->t_map[i][k] != '0' && vars->t_map[i][k] != 'W' &&
	vars->t_map[i][k] != 'E' && vars->t_map[i][k] != 'S' &&
	vars->t_map[i][k] != 'N' && vars->t_map[i][k] != '2'))
		ft_error(4, vars);
	if ((k != 0 && (vars->t_map[i][k - 1] == '0' ||
	vars->t_map[i][k - 1] == '2' || vars->t_map[i][k - 1] == 'E' ||
	vars->t_map[i][k - 1] == 'W' || vars->t_map[i][k - 1] == 'S' ||
	vars->t_map[i][k - 1] == 'N') && vars->t_map[i][k] != '1' &&
	vars->t_map[i][k] != '0' && vars->t_map[i][k] != 'W' &&
	vars->t_map[i][k] != 'E' && vars->t_map[i][k] != 'S' &&
	vars->t_map[i][k] != 'N' && vars->t_map[i][k] != '2'))
		ft_error(4, vars);
	if ((vars->t_map[i][k] == '0' || vars->t_map[i][k] == '2' ||
	vars->t_map[i][k] == 'E' || vars->t_map[i][k] == 'W' ||
	vars->t_map[i][k] == 'S' || vars->t_map[i][k] == 'N') &&
	vars->t_map[i + 1][k] != '1' &&
	vars->t_map[i + 1][k] != '0' && vars->t_map[i + 1][k] != 'W' &&
	vars->t_map[i + 1][k] != 'E' && vars->t_map[i + 1][k] != 'S' &&
	vars->t_map[i + 1][k] != 'N' && vars->t_map[i + 1][k] != '2')
		ft_error(4, vars);
}

void	check_zero_one(t_vars *vars, int k, int i)
{
	if (i != 0 && (vars->t_map[i][k] == '0' ||
	vars->t_map[i][k] == '2' || vars->t_map[i][k] == 'E' ||
	vars->t_map[i][k] == 'W' || vars->t_map[i][k] == 'S' ||
	vars->t_map[i][k] == 'N') && vars->t_map[i - 1][k] != '1' &&
	vars->t_map[i - 1][k] != '0' && vars->t_map[i - 1][k] != 'W' &&
	vars->t_map[i - 1][k] != 'E' && vars->t_map[i - 1][k] != 'S' &&
	vars->t_map[i - 1][k] != 'N' && vars->t_map[i - 1][k] != '2')
		ft_error(4, vars);
	if (((vars->t_map[i][k] == '0' || vars->t_map[i][k] == '2' ||
	vars->t_map[i][k] == 'E' || vars->t_map[i][k] == 'W' ||
	vars->t_map[i][k] == 'S' || vars->t_map[i][k] == 'N') &&
	vars->t_map[i][k + 1] != '1' &&
	vars->t_map[i][k + 1] != '0' && vars->t_map[i][k + 1] != 'W' &&
	vars->t_map[i][k + 1] != 'E' && vars->t_map[i][k + 1] != 'S' &&
	vars->t_map[i][k + 1] != 'N' && vars->t_map[i][k + 1] != '2'))
		ft_error(4, vars);
	if ((k == 0 || i == 0) &&
	vars->t_map[i][k] != '1' && vars->t_map[i][k] != ' ')
		ft_error(4, vars);
	check_zero_one_part_2(vars, k, i);
}

void	check_symbol(char c, int *wesn, t_vars *vars)
{
	if (c != '1' && c != '0' && c != '2' && c != 'W' && c != 'N'
	&& c != 'S' && c != 'E' && c != ' ')
		ft_error(4, vars);
	if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
		wesn[0]++;
}

void	check_map(t_vars *vars)
{
	int i;
	int k;
	int length;
	int wesn;

	i = -1;
	length = 0;
	wesn = 0;
	while (vars->t_map[++i])
	{
		k = -1;
		while (vars->t_map[i][++k])
		{
			length = (length > k && i == 0) ? length : k;
			check_zero_one(vars, k, i);
			check_symbol(vars->t_map[i][k], &wesn, vars);
		}
	}
	(wesn != 1) ? ft_error(4, vars) : 0;
}

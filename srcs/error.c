/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 22:09:42 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 15:35:09 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void		free_str(t_vars *vars)
{
	int i;

	i = 0;
	while (i != vars->max_map_hight)
	{
		free(vars->t_map[i]);
		i++;
	}
	free(vars->t_map);
}

void			ft_error(int num_mistake, t_vars *vars)
{
	if (num_mistake == 1)
	{
		ft_putstr_fd("Error!\nInvalid malloc.\n", 1);
		exit(1);
	}
	if (num_mistake == 2)
	{
		ft_putstr_fd("Error!\nInvalid parser.\n", 1);
		exit(1);
	}
	if (num_mistake == 3)
	{
		ft_putstr_fd("Error!\nInvalid arguments.\n", 1);
		exit(1);
	}
	if (num_mistake == 4)
	{
		free_str(vars);
		ft_putstr_fd("Error!\nInvalid map.\n", 1);
		exit(1);
	}
}

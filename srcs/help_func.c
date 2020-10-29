/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 22:12:45 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 19:51:54 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_space(char *line, t_vars *vars)
{
	int i;

	i = 0;
	while (line[i] != '.')
	{
		if (line[i] != ' ')
			ft_error(2, vars);
		i++;
	}
	return (1);
}

int		num_width(int num)
{
	int i = 0;

	if (num == 0)
		i++;
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int		read_map_part_space(char *line, t_vars *vars)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			ft_error(2, vars);
		i++;
	}
	return (1);
}

void	free_list(t_list **str_map)
{
	t_list *copy;
	t_list *copy_next;

	copy = *str_map;
	while (copy)
	{
		copy_next = copy->next;
		free(copy);
		copy = copy_next;
	}
	*str_map = NULL;
}

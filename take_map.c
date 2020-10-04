/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:11:22 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/04 17:15:38 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		where_plr(t_vars *vars, int i)
{
	(ft_strchr(vars->t_map[i], 'N')) ? (vars->x_reycast = M_PI_2) : 0;
	(ft_strchr(vars->t_map[i], 'S')) ? (vars->x_reycast = 3 * M_PI_2) : 0;
	(ft_strchr(vars->t_map[i], 'E')) ? (vars->x_reycast = M_PI) : 0;
	(ft_strchr(vars->t_map[i], 'W')) ? (vars->x_reycast = 0) : 0;
	(ft_strchr(vars->t_map[i], 'N')) ? (vars->y_reycast = M_PI_2) : 0;
	(ft_strchr(vars->t_map[i], 'S')) ? (vars->y_reycast = 3 * M_PI_2) : 0;
	(ft_strchr(vars->t_map[i], 'E')) ? (vars->y_reycast = M_PI) : 0;
	(ft_strchr(vars->t_map[i], 'W')) ? (vars->y_reycast = 0) : 0;
}

void	make_map(t_list **str_map, int size, t_vars *vars)
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = *str_map;
	vars->t_map = ft_calloc(size + 1, sizeof(char *));
	while (tmp)
	{
		vars->t_map[i] = (char *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (vars->t_map[i])//пычатает карту как 1, 0, 2 и ищет позицию игрока
	{
		if (ft_strchr(vars->t_map[i], 'N') || ft_strchr(vars->t_map[i], 'S') || \
		ft_strchr(vars->t_map[i], 'E') || ft_strchr(vars->t_map[i], 'W'))
		{
			vars->plr_y = i * s_map;
			vars->plr_x = (ft_strlen(vars->t_map[i]) - ft_strlen(ft_strchr(vars->t_map[i], 'N'))) * s_map;
			where_plr(vars, i);
		}
		i++;
	}
}

void	read_map(char **argv, t_vars *vars)
{
	char *line;
	t_list *str_map;
	vars->max_map_hight = 0;
	vars->max_map_width = 0;

	str_map = NULL;
	line = NULL;
	vars->fd = open(argv[1], O_RDONLY);
	while (get_next_line(vars->fd, &line) > 0)
	{
		if (vars->max_map_width < (int)ft_strlen(line))
			vars->max_map_width = (int)ft_strlen(line);
		ft_lstadd_back(&str_map, ft_lstnew(line));
		vars->max_map_hight++;
	}
	ft_lstadd_back(&str_map, ft_lstnew(line));
	make_map(&str_map, ft_lstsize(str_map), vars);
}

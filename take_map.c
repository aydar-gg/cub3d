/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:11:22 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/15 19:57:11 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		where_plr(t_vars *vars, int i)
{
	(ft_strchr(vars->t_map[i], 'N')) ? (vars->x_reycast = 3 * M_PI_2) : 0;
	(ft_strchr(vars->t_map[i], 'S')) ? (vars->x_reycast = M_PI_2) : 0;
	(ft_strchr(vars->t_map[i], 'E')) ? (vars->x_reycast = 0) : 0;
	(ft_strchr(vars->t_map[i], 'W')) ? (vars->x_reycast = M_PI) : 0;
	(ft_strchr(vars->t_map[i], 'N')) ? (vars->y_reycast = 3 * M_PI_2) : 0;
	(ft_strchr(vars->t_map[i], 'S')) ? (vars->y_reycast = M_PI_2) : 0;
	(ft_strchr(vars->t_map[i], 'E')) ? (vars->y_reycast = 0) : 0;
	(ft_strchr(vars->t_map[i], 'W')) ? (vars->y_reycast = M_PI) : 0;
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
			vars->plr_y = i * s_map + s_map / 2;
			vars->plr_x = (ft_strchr(vars->t_map[i], 'S')) ? (ft_strlen(vars->t_map[i]) - ft_strlen(ft_strchr(vars->t_map[i], 'S'))) * s_map + s_map / 2 : vars->plr_x;
			vars->plr_x = (ft_strchr(vars->t_map[i], 'N')) ? (ft_strlen(vars->t_map[i]) - ft_strlen(ft_strchr(vars->t_map[i], 'N'))) * s_map + s_map / 2 : vars->plr_x;
			vars->plr_x = (ft_strchr(vars->t_map[i], 'W')) ? (ft_strlen(vars->t_map[i]) - ft_strlen(ft_strchr(vars->t_map[i], 'W'))) * s_map + s_map / 2 : vars->plr_x;
			vars->plr_x = (ft_strchr(vars->t_map[i], 'E')) ? (ft_strlen(vars->t_map[i]) - ft_strlen(ft_strchr(vars->t_map[i], 'E'))) * s_map + s_map / 2 : vars->plr_x;
			where_plr(vars, i);
		}
		i++;
	}
}

static int num_width(int num)
{
	int i = 0;

	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
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
		if (ft_strnstr(line, "R", 2))
		{
			vars->width = ft_atoi(&line[2]);
			vars->hight = ft_atoi(&line[3 + num_width(vars->width)]);
			int R = 1;
		}
		else if (ft_strnstr(line, "NO .", 5))
		{
			int NO = 1;
		}
		else if (ft_strnstr(line, "SO .", 5))
		{
			int SO = 1;
		}
		else if (ft_strnstr(line, "WE .", 5))
		{
			int WE = 1;
		}
		else if (ft_strnstr(line, "EA .", 5))
		{
			int EA = 1;
		}
		else if (ft_strnstr(line, "S .", 4))
		{
			int S = 1;
		}
		else if (ft_strnstr(line, "F", 2))
		{
			int F = 1;
		}
		else if (ft_strnstr(line, "C", 2))
		{
			int C = 1;
		}
		else
		{
			if (vars->max_map_width < (int)ft_strlen(line))
				vars->max_map_width = (int)ft_strlen(line);
			ft_lstadd_back(&str_map, ft_lstnew(line));
			vars->max_map_hight++;
		}
	}
	ft_lstadd_back(&str_map, ft_lstnew(line));
	make_map(&str_map, ft_lstsize(str_map), vars);
}

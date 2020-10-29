/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:11:22 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/29 20:05:45 by psabreto         ###   ########.fr       */
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

void	take_coord_plr(t_vars *vars, int i)
{
	if (ft_strchr(vars->t_map[i], 'N') || ft_strchr(vars->t_map[i], 'S') || \
	ft_strchr(vars->t_map[i], 'E') || ft_strchr(vars->t_map[i], 'W'))
	{
		vars->plr_y = i * s_map + s_map / 2;
		vars->plr_x = (ft_strchr(vars->t_map[i], 'S')) ?
		(ft_strlen(vars->t_map[i]) - ft_strlen(ft_strchr(vars->t_map[i],
		'S'))) * s_map + s_map / 2 : vars->plr_x;
		vars->plr_x = (ft_strchr(vars->t_map[i], 'N')) ?
		(ft_strlen(vars->t_map[i]) - ft_strlen(ft_strchr(vars->t_map[i],
		'N'))) * s_map + s_map / 2 : vars->plr_x;
		vars->plr_x = (ft_strchr(vars->t_map[i], 'W')) ?
		(ft_strlen(vars->t_map[i]) - ft_strlen(ft_strchr(vars->t_map[i],
		'W'))) * s_map + s_map / 2 : vars->plr_x;
		vars->plr_x = (ft_strchr(vars->t_map[i], 'E')) ?
		(ft_strlen(vars->t_map[i]) - ft_strlen(ft_strchr(vars->t_map[i],
		'E'))) * s_map + s_map / 2 : vars->plr_x;
		where_plr(vars, i);
	}
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
	free_list(str_map);
	i = 0;
	while (vars->t_map[i])
	{
		take_coord_plr(vars, i);
		i++;
	}
	check_map(vars);
}

void	count_while(t_vars *vars, char *line, t_list *str_map)
{
	while (get_next_line(vars->fd, &line) > 0)
	{
		if (read_map_part_R(vars, line, 0))
			free(line);
		else if (read_map_part_we(vars, line))
			free(line);
		else if (read_map_part_FC(vars, line))
			free(line);
		else if (count_of_map(vars, line, &str_map))
			continue ;
		else if (read_map_part_space(line, vars))
			free(line);
		else
		{
			free(line);
			ft_error(2, vars);
		}
	}
	ft_lstadd_back(&str_map, ft_lstnew(line));
	make_map(&str_map, ft_lstsize(str_map), vars);
}

void	read_map(char **argv, t_vars *vars)
{
	char *line;
	t_list *str_map;
	vars->max_map_hight = 0;
	vars->max_map_width = 0;

	str_map = NULL;
	line = NULL;
	if ((vars->fd = open(argv[1], O_RDONLY)) == -1)
		ft_error(3, vars);
	count_while(vars, line, str_map);
	free(str_map);
	if (vars->r_mon != 1 || vars->s_text != 1 || vars->so_text != 1 ||
	vars->no_text != 1 || vars->ea_text != 1 || vars->we_text != 1 ||
	vars->f_count != 1 || vars->c_count != 1)
		ft_error(2, vars);
	take_map_sprit(vars);
}

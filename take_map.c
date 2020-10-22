/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 17:11:22 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/22 14:49:25 by psabreto         ###   ########.fr       */
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
	int bpp;
	int line_length;
	int endian;

	str_map = NULL;
	line = NULL;
	vars->fd = open(argv[1], O_RDONLY);
	while (get_next_line(vars->fd, &line) > 0)
	{
		if (ft_strnstr(line, "R", 2))
		{
			vars->width = ft_atoi(&line[2]);
			vars->hight = ft_atoi(&line[3 + num_width(vars->width)]);
		}
		else if (ft_strnstr(line, "NO .", 5))
		{
			vars->no.north = mlx_xpm_file_to_image(vars->mlx, ft_strchr(line, '.'), &vars->no.width, &vars->no.hight);
			vars->no.addr = (int*)mlx_get_data_addr(vars->no.north, &(bpp), &(line_length), &(endian));
		}
		else if (ft_strnstr(line, "SO .", 5))
		{
			vars->so.south = mlx_xpm_file_to_image(vars->mlx, ft_strchr(line, '.'), &vars->so.width, &vars->so.hight);
			vars->so.addr = (int*)mlx_get_data_addr(vars->so.south, &(vars->so.bpp), &(vars->so.line_length), &(vars->so.endian));
		}
		else if (ft_strnstr(line, "WE .", 5))
		{
			vars->we.west = mlx_xpm_file_to_image(vars->mlx, ft_strchr(line, '.'), &vars->we.width, &vars->we.hight);
			vars->we.addr = (int*)mlx_get_data_addr(vars->we.west, &(vars->we.bpp), &(vars->we.line_length), &(vars->we.endian));
		}
		else if (ft_strnstr(line, "EA .", 5))
		{
			vars->ea.east = mlx_xpm_file_to_image(vars->mlx, ft_strchr(line, '.'), &vars->ea.width, &vars->ea.hight);
			vars->ea.addr = (int*)mlx_get_data_addr(vars->ea.east, &(vars->ea.bpp), &(vars->ea.line_length), &(vars->ea.endian));
		}
		else if (ft_strnstr(line, "S .", 4))
		{
			vars->sp.sprit = mlx_xpm_file_to_image(vars->mlx, ft_strchr(line, '.'), &vars->sp.width, &vars->sp.hight);
			vars->sp.addr = (int*)mlx_get_data_addr(vars->sp.sprit, &(vars->sp.bpp), &(vars->sp.line_length), &(vars->sp.endian));
		}
		else if (ft_strnstr(line, "F", 2))
		{
		}
		else if (ft_strnstr(line, "C", 2))
		{
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

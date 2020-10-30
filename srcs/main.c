/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:52:00 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 16:11:10 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void		size(t_vars *vars)
{
	mlx_get_screen_size(vars->mlx, &vars->w_mon, &vars->h_mon);
	if (vars->h_mon < vars->hight)
		vars->hight = vars->h_mon;
	if (vars->w_mon < vars->width)
		vars->width = vars->w_mon;
	if (vars->hight < 50)
		vars->hight = 50;
	if (vars->width < 50)
		vars->width = 50;
}

static void		move_plr_make_window(t_vars *vars)
{
	size(vars);
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->hight, "Test");
	print_map_2d(vars);
	mlx_hook(vars->win, 3, 1L << 2, v_test_2, vars);
	mlx_hook(vars->win, 2, 0, key_press, vars);
	mlx_hook(vars->win, 17, 0L, ft_exit, vars);
}

static int		check_argv(char *argv)
{
	int i;

	i = ft_strlen(argv) - 4;
	if (ft_strnstr(&argv[i], ".cub", 5))
		return (1);
	return (0);
}

int				main(int argc, char **argv)
{
	t_vars vars;

	vars.argc = argc;
	inicial_vars(&vars);
	if (argc == 2 || (argc == 3 && ft_strnstr("--save", argv[2], 7) &&
	ft_strnstr(argv[2], "--save", 7)))
	{
		if (!check_argv(argv[1]))
			ft_error(3, &vars);
		vars.mlx = mlx_init();
		read_map(argv, &vars);
		move_plr_make_window(&vars);
		mlx_loop(vars.mlx);
	}
	else
		ft_error(3, &vars);
	return (0);
}

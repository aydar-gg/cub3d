#include "cub.h"

int		v_test_2(int keycode)
{
	if (keycode ==53)
		exit (0);
	return (0);
}

static void size(t_vars *vars) //определяет размер окна
{
	int i;
	int j;
	mlx_get_screen_size(vars->mlx, &i, &j);
	if (i < vars->hight)
		vars->hight = i;
	if (j < vars->width)
		vars->width = j;
	printf("%d:%d\n", i, j);
}


void	move_plr_make_window(t_vars *vars)
{
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->hight, "Test");

	size(vars);

	print_map_2d(vars);

	mlx_hook(vars->win, 3, 1L<<2, v_test_2, vars);

	mlx_hook(vars->win, 2, 0, key_press, vars);

}

int main(int argc, char **argv)
{
	t_vars vars;

	if (argc == 2)
	{
		vars.mlx = mlx_init();
		read_map(argv, &vars);
	}
	move_plr_make_window(&vars);
	mlx_loop(vars.mlx);
	return (0);
}

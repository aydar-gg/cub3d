#include "cub.h"

int		v_test_2(int keycode)
{
	//int x = 0;
	//int y = 0;
	//mlx_mouse_hide(); //прячет мышку при нажатии на игруn
	if (keycode ==53)
		exit (0);
	//mlx_mouse_get_pos(vars->win, &x, &y);
	//if (x >= 8 && x <= 20 && y >= 5 && y <= 16) //закрывает окно если мышку навести на крестик и нажать на клавишу
	//    exit (0);
	return (0);
	//если нажать по х (8-20), по у (5-16), окно закроется
}

//static void size(t_vars *vars) //определяет размер окна
//{
//	int i;
//	int j;
//	mlx_get_screen_size(vars->mlx, &i, &j);
//	printf("%d:%d\n", i, j);
//}


void	move_plr_make_window(t_vars *vars)
{
	vars->width = 1000;
	vars->hight = 1000;
	vars->mlx = mlx_init();
	//size(vars);
	//exit(0);
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->hight, "Test");

	print_map_2d(vars);

	mlx_hook(vars->win, 3, 1L<<2, v_test_2, vars);

	mlx_hook(vars->win, 2, 0, key_press, vars);

	mlx_loop(vars->mlx);
}

int main(int argc, char **argv)
{
	t_vars vars;

	if (argc == 2)
		read_map(argv, &vars);
	move_plr_make_window(&vars);
	return (0);
}

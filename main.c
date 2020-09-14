#include "minilibx/mlx.h"
#include "cub.h"

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
	while (vars->t_map[i])//пычатает карту как 1, 0, 2
	{
		ft_putendl_fd(vars->t_map[i], 1);
		i++;
	}
}

void	read_map(int argc, char **argv, t_vars *vars)
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
		if (vars->max_map_width < ft_strlen(line))
			vars->max_map_width = (int)ft_strlen(line);
		ft_lstadd_back(&str_map, ft_lstnew(line));
		vars->max_map_hight++;
	}
	ft_lstadd_back(&str_map, ft_lstnew(line));
	make_map(&str_map, ft_lstsize(str_map), vars);
}


int		v_test(int keycode, t_vars *vars)
{
	if (keycode == 53)// при нажатии esc окно закрывается
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	printf("%d\n", keycode);
	return (0);
}
int		v_test_2(int keycode, t_vars *vars)
{
	int x = 0;
	int y = 0;
	//printf("%s\n", vars->win);
	//mlx_mouse_hide(); //прячет мышку при нажатии на игруn
	if (keycode ==53)
		exit (0);
	//mlx_mouse_get_pos(vars->win, &x, &y);
	//if (x >= 8 && x <= 20 && y >= 5 && y <= 16) //закрывает окно если мышку навести на крестик и нажать на клавишу
	//    exit (0);
	return (0);
	//если нажать по х (8-20), по у (5-16), окно закроется
}

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char *dst;

	dst = data->img_data + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

//static void size(t_vars *vars) //определяет размер окна
//{
//	int i;
//	int j;
//	mlx_get_screen_size(vars->mlx, &i, &j);
//	printf("%d:%d\n", i, j);
//}

void	print_map_2d(t_vars *vars)
{
	int k, k_2;
	int h, h_2;
	int i;
	int l;

	i = 0;
	//быстрая рисовка линий

	vars->img_ptr = mlx_new_image(vars->mlx, vars->width, vars->hight);
	vars->img_data = mlx_get_data_addr(vars->img_ptr, &vars->bpp, &vars->line_length, &vars->endian);
	k = 0;
	while(i != vars->max_map_hight)
	{
		l = 0;
		h = 0;
		while (vars->t_map[i][l] != '\n' && vars->t_map[i][l] != '\0')
		{
			if (vars->t_map[i][l] == '1')
			{
				k_2 = k;
				while (k != k_2 + 10)
				{
					h_2 = h;
					while (h != h_2 + 10)
					{
						my_mlx_pixel_put(vars, h, k, 0x00AAFF00);
						//mlx_pixel_put(vars->mlx, vars->win, h, k, 0x00AA0000);
						h++;
					}
					h -= 10;
					k++;
				}
				k -= 10;
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ptr, 0, 0);
			}
				h += 10;
			l++;
		}
		k += 10;
		i++;
	}
}

int key_press(int keycode, t_vars *vars)
{
	//mlx_clear_window(vars.mlx, vars.win);
	//mlx_destroy_image(vars.mlx, vars.img_ptr);
	//vars.img_ptr = mlx_new_image(vars.mlx, 1000, 1000);
	if (keycode == 13)//UP
		vars->plr_y--;
	if (keycode == 0)//LEFT
		vars->plr_x--;
	if (keycode == 1)//DOWN
		vars->plr_y++;
	if (keycode == 2)//RIGHT
		vars->plr_x++;
	printf("position - %d %d\n", vars->plr_x, vars->plr_y);
	vars->img_ptr = mlx_new_image(vars->mlx, vars->width, vars->hight);
	vars->img_data = mlx_get_data_addr(vars->img_ptr, &vars->bpp, &vars->line_length, &vars->endian);
	//mlx_pixel_put(vars->mlx, vars->win, vars->plr_x, vars->plr_y, 0xFFFFFF);
	//mlx_pixel_put(vars->mlx, vars->win, vars->plr_x + 1, vars->plr_y + 1, 0xFFFFFF);
	//mlx_pixel_put(vars->mlx, vars->win, vars->plr_x + 1, vars->plr_y, 0xFFFFFF);
	//mlx_pixel_put(vars->mlx, vars->win, vars->plr_x, vars->plr_y + 1, 0xFFFFFF);
	my_mlx_pixel_put(vars, vars->plr_x, vars->plr_y, 0x00FF0000);
	my_mlx_pixel_put(vars, vars->plr_x + 1, vars->plr_y + 1, 0x00FF0000);
	my_mlx_pixel_put(vars, vars->plr_x + 1, vars->plr_y, 0x00FF0000);
	my_mlx_pixel_put(vars, vars->plr_x, vars->plr_y + 1, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ptr, 0, 0);
	return (0);
}

void	move_plr_make_window(t_vars *vars)
{
	vars->plr_x = 50;
	vars->plr_y = 50;
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
		read_map(argc, argv, &vars);
	move_plr_make_window(&vars);
	return (0);
}

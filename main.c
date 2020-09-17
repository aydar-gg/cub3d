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
	while (vars->t_map[i])//пычатает карту как 1, 0, 2 и ищет позицию игрока
	{
		if (ft_strchr(vars->t_map[i], 'N') || ft_strchr(vars->t_map[i], 'S') || \
		ft_strchr(vars->t_map[i], 'E') || ft_strchr(vars->t_map[i], 'W'))
		{
			vars->plr_y = i * s_map;
			vars->plr_x = (ft_strlen(vars->t_map[i]) - ft_strlen(ft_strchr(vars->t_map[i], 'N'))) * s_map;
		}
		//ft_putendl_fd(vars->t_map[i], 1);
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


//int		v_test(int keycode, t_vars *vars)
//{
//	if (keycode == 53)// при нажатии esc окно закрывается
//	{
//		mlx_destroy_window(vars->mlx, vars->win);
//		exit(0);
//	}
//	printf("%d\n", keycode);
//	return (0);
//}

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

void	print_map_2d(t_vars *vars)	//быстрая рисовка линий
{
	int k, k_2;
	int h, h_2;
	int i;
	int l;
	float z;

	i = 0;

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
				while (k != k_2 + s_map)
				{
					h_2 = h;
					while (h != h_2 + s_map)
					{
						my_mlx_pixel_put(vars, h, k, 0x00AAFF00);
						h++;
					}
					h -= s_map;
					k++;
				}
				k -= s_map;
			}
				h += s_map;
			l++;
		}
		k += s_map;
		i++;
	}

	//i = 0;
	//while (i != s_map)
	//{
	//	k = 0;
	//	while (k != s_map)
	//	{
	//		my_mlx_pixel_put(vars, vars->plr_x + k, vars->plr_y + i, 0x000000FF);
	//		k++;
	//	}
	//	i++;
	//}
	z = 0;
	vars->x_line = vars->plr_x;
	vars->y_line = vars->plr_y;
	//vars->plr_x += cos(vars->x_reycast);
	//vars->plr_y += sin(vars->y_reycast);
	while ((int)z != 40)
	{
		vars->x_line += cos(vars->x_reycast);
		vars->y_line += sin(vars->y_reycast);
		if (vars->t_map[(int)vars->y_line / s_map][(int)vars->x_line / s_map] != '0')
		{
			//vars->dir = sqrt(pow(vars->x_line / s_map - vars->plr_x, 2) + pow(vars->y_line / s_map - vars->plr_y, 2));
			//vars->alpha = vars->dir / (vars->x_line / s_map);
			//vars->beta = vars->dir / (vars->y_line / s_map);
			break ;
		}
		my_mlx_pixel_put(vars, vars->x_line, vars->y_line, 0x00FF0000);
		z += 0.1;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ptr, 0, 0);
}

int key_press(int keycode, t_vars *vars)
{
	if (keycode == 13)//FORWARD
	{
		vars->plr_x += cos(vars->x_reycast);
		vars->plr_y += sin(vars->y_reycast);
		//vars->plr_y--;
	}
	if (keycode == 0)//LEFT
	{
		vars->plr_x += cos(vars->x_reycast + M_PI/2);
		vars->plr_y += sin(vars->y_reycast + M_PI/2);
		//vars->plr_x--;
	}
	if (keycode == 1)//BACK
	{
		vars->plr_x -= cos(vars->x_reycast);
		vars->plr_y -= sin(vars->y_reycast);
		//vars->plr_y++;
	}
	if (keycode == 2)//RIGHT
	{
		vars->plr_x -= cos(vars->x_reycast + M_PI/2);
		vars->plr_y -= sin(vars->y_reycast + M_PI/2);
		//vars->plr_x++;
	}
	if (keycode == 123)//turn right
	{
		vars->x_reycast -= turn;
		vars->y_reycast -= turn;
	}
	if (keycode == 124)//turn left
	{
		vars->x_reycast += turn;
		vars->y_reycast += turn;
	}

	//printf("position - %f %f\n", vars->plr_x, vars->plr_y);
	mlx_clear_window(vars->mlx, vars->win);
	print_map_2d(vars);
	return (0);
}

void	move_plr_make_window(t_vars *vars)
{
	vars->width = 1000;
	vars->hight = 1000;
	vars->x_reycast = 0;
	vars->y_reycast = 0;
	vars->alpha = 0;
	vars->beta = 0;
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

// вывод изображение другой способ

// #include <mlx.h>

// typedef struct  s_data {
//     void        *img;
//     char        *addr;
//     int         bits_per_pixel;
//     int         line_length;
//     int         endian;
// }               t_data;

// void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
//     char    *dst;

//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

// int             main(void)
// {
//     void    *mlx;
//     void    *mlx_win;
//     t_data  img;

//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
//     img.img = mlx_new_image(mlx, 1920, 1080);
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
//     my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
//     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
//     mlx_loop(mlx);
// }

//любой клавишей закрываешь окно

// #include <mlx.h>

// typedef struct  s_vars {
//     void        *mlx;
//     void        *win;
// }               t_vars;

// int             close(int keycode, t_vars *vars)
// {
//     mlx_destroy_window(vars->mlx, vars->win);
// }

// int             main(void)
// {
//     t_vars      vars;

//     vars.mlx = mlx_init();
//     vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
// 	// mlx_mouse_hook(vars.win, close, &vars);
//     mlx_key_hook(vars.win, close, &vars);
//     mlx_loop(vars.mlx);
// }

// любой клавишей закрывать окно, способ №2

// #include <mlx.h>

// typedef struct  s_vars {
//         void    *mlx;
//         void    *win;
// }               t_vars;

// int             close(int keycode, t_vars *vars)
// {
//     mlx_destroy_window(vars->mlx, vars->win);
// }

// int             main(void)
// {
//     t_vars    vars;

//     vars.mlx = mlx_init();
//     vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
//     mlx_hook(vars.win, 2, 1L<<0, close, &vars);
//     mlx_loop(vars.mlx);
// }


// #include <mlx.h>

// int     render_next_frame(void *YourStruct);

// int     main(void)
// {
//     void    *mlx;
//     void    *YourStruct;

//     mlx = mlx_init();
//     mlx_loop_hook(mlx, render_next_frame, YourStruct);
//     mlx_loop(mlx);
// }

//тренировка

//int main()
//{
//    t_vars vars;
//    int x;
//    int y;


//    vars.mlx = mlx_init();
//    vars.win = mlx_new_window(vars.mlx, 1000, 1000, "Test");
//    //mlx_key_hook(vars.win, v_test, &vars);
//    //mlx_mouse_hook(vars.win, mlx_mouse_get_pos, &vars);
//    //mlx_mouse_get_pos(vars.mlx, &x, &y);
//    printf("%dx%d\n", x, y);
//    mlx_loop(vars.mlx);
//}

#include "minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

int v_test(int keycode, t_vars *vars)
{
    if (keycode == 53)// при нажатии esc окно закрывается
    {
        mlx_destroy_window(vars->mlx, vars->win);
        exit(0);
    }
    printf("%d\n", keycode);
    return (0);
}
int v_test_2(int keycode, t_vars *vars)
{
    int x = 0;
    int y = 0;
    //printf("%s\n", vars->win);
    //mlx_mouse_hide(); //прячет мышку при нажатии на игруn
    if (keycode ==53)
        exit (0);
    mlx_mouse_get_pos(vars->win, &x, &y);
    if (x >= 8 && x <= 20 && y >= 5 && y <= 16)
        exit (0);
    printf("%d %d\n", x, y);
    return (0);
    //если нажать по х (8-20), по у (5-16), окно закроется
}


int main()
{
    t_vars vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1000, 1000, "Test");
    //mlx_hook(vars.win, 3, 1L<<2, v_test_2, &vars);
    mlx_do_key_autorepeatoff(vars.mlx);
    mlx_hook(vars.win, 2, 0, mlx_mouse_get_pos, &vars);
    mlx_loop(vars.mlx);
}

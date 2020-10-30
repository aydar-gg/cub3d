/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psabreto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 19:21:47 by psabreto          #+#    #+#             */
/*   Updated: 2020/10/30 17:01:16 by psabreto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define S_MAP 64
# define TURN 0.1

# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

typedef struct		s_p_n
{
	char				*north;
	int					width;
	int					hight;
	int					*addr;
	int					bpp;
	int					line_length;
	int					endian;
}					t_p_n;

typedef struct		s_p_s
{
	char				*south;
	int					width;
	int					hight;
	int					*addr;
	int					bpp;
	int					line_length;
	int					endian;
}					t_p_s;

typedef struct		s_p_w
{
	char				*west;
	int					width;
	int					hight;
	int					*addr;
	int					bpp;
	int					line_length;
	int					endian;
}					t_p_w;

typedef struct		s_p_e
{
	char				*east;
	int					width;
	int					hight;
	int					*addr;
	int					bpp;
	int					line_length;
	int					endian;
}					t_p_e;

typedef struct		s_p
{
	char				*sprit;
	int					width;
	int					hight;
	int					*addr;
	int					bpp;
	int					line_length;
	int					endian;
}					t_spr;

typedef struct		s_sprite
{
	int					flag;
	int					x;
	int					y;
	double				x_3d;
	double				y_3d;
	double				z_sp_v;
	double				z_sp_h;
	double				z_sp;
	double				offset;
	double				sp_dir;
	struct s_sprite		*next;
}					t_sprite;

typedef struct		s_vars {
	char				**t_map;
	void				*mlx;
	void				*win;
	void				*img_ptr;
	char				*img_data;
	double				plr_x;
	double				plr_y;
	double				x_reycast;
	double				y_reycast;
	double				x_line;
	double				y_line;
	int					max_map_width;
	int					max_map_hight;
	int					width;
	int					hight;
	int					w_mon;
	int					h_mon;
	int					fd;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
	double				overview;
	double				hy_ray;
	double				hx_ray;
	double				ya;
	double				xa;
	double				vy_ray;
	double				vx_ray;
	double				z;
	double				z_horizontlly;
	double				z_vertically;
	int					offset;
	int					is_sp_v;
	int					is_sp_h;
	int					count_sp;
	double				*arr_z;
	int					f_color;
	int					c_color;
	int					r;
	int					g;
	int					b;
	int					r_mon;
	int					no_text;
	int					so_text;
	int					ea_text;
	int					we_text;
	int					s_text;
	int					f_count;
	int					c_count;
	int					argc;
	int					h_sp;
	int					h_offset;
	int					v_offset;
	int					color;
	int					is_wr_t;
	t_sprite			*sprit;
	t_p_n				no;
	t_p_s				so;
	t_p_w				we;
	t_p_e				ea;
	t_spr				sp;
}					t_vars;

void				read_map(char **argv, t_vars *vars);
int					key_press(int keycode, t_vars *vars);
void				print_map_2d(t_vars *vars);
void				map_3d(t_vars *vars, int k);
double				check_over(double over);
void				my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
void				print_texture(t_vars *vars, int k);
void				take_map_sprit(t_vars *vars);
void				sprite_3d(t_vars *vars);
void				print_sprite(t_vars *vars);
void				ft_error(int num_mistake, t_vars *vars);
int					check_space(char *line, t_vars *vars);
int					num_width(int num);
int					read_map_part_space(char *line, t_vars *vars);
int					take_color(t_vars *vars, char *line, int r, int g);
int					read_map_part_fc(t_vars *vars, char *line);
int					read_map_part_r(t_vars *vars, char *line, int i);
int					read_map_part_no(t_vars *vars, char *line);
int					read_map_part_so(t_vars *vars, char *line);
int					read_map_part_ea(t_vars *vars, char *line);
int					read_map_part_we(t_vars *vars, char *line);
int					read_map_part_s(t_vars *vars, char *line);
void				check_map(t_vars *vars);
void				free_list(t_list **str_map);
int					v_test_2(int keycode);
int					ft_exit(t_vars *vars);
void				inicial_vars(t_vars *vars);
int					count_of_map(t_vars *vars, char *line, t_list **str_map);
void				put_z(t_vars *vars);
void				d2_map(t_vars *vars);
void				get_scrin(t_vars *vars);
void				length_at_horizontlly(t_vars *vars);
void				length_at_vertically(t_vars *vars);
void				check_z(t_vars *vars, int i);
int					pix_color(t_vars *vars, int x, int y, float line);

#endif

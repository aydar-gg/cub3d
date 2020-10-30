# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psabreto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 21:32:11 by psabreto          #+#    #+#              #
#    Updated: 2020/10/30 17:25:13 by psabreto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

FUNC = srcs/main.c srcs/check_map.c srcs/error.c \
srcs/help_func_2.c srcs/help_func.c srcs/plr_control.c \
srcs/position_wall_part_2.c srcs/position_wall.c srcs/print_texture.c \
srcs/scrin_bmp.c srcs/take_color.c srcs/take_map.c srcs/take_pos_sprit.c \
srcs/take_snwe_2.c srcs/take_snwe.c srcs/print_sprite.c\
srcs/calculat_raycast_h.c srcs/calculat_raycast_v.c \
gnl/get_next_line.c gnl/get_next_line_utils.c

OBJS = $(FUNC:.c=.o)

HEADER = cub.h

CFLAGS = -Wall -Wextra -Werror#-Iminilibx/ -Ilibft/ -Llibft -lft

LIBS = -L minilibx -lmlx -framework OpenGL -framework AppKit

LIBFT = libft/libft.a

LIBMLX = libmlx.dylib

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) $(LIBFT) $(LIBMLX)
	gcc $(OBJS) ${LIBS} ${LIBFT} ${LIBMLX} -o ${NAME}

$(LIBFT): $(LIBMLX)
	@$(MAKE) -C libft

$(LIBMLX):
	@$(MAKE) -C minilibx
	cp minilibx/libmlx.dylib .

$(OBJS): %.o:%.c $(HEADER)
	gcc $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f libft/*.o
	rm -f minilibx/*.o

fclean: clean
	rm -f $(NAME) $(LIBFT) $(LIBMLX)

re: fclean all

bonus: all

.PHONY: all clean fclean re

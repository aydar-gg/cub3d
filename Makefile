# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psabreto <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 21:32:11 by psabreto          #+#    #+#              #
#    Updated: 2020/10/29 21:52:56 by psabreto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

FUNC = srcs/main.o srcs/check_map.o srcs/error.o \
srcs/help_func_2.o srcs/help_func.o srcs/plr_control.o \
srcs/position_wall_part_2.o srcs/position_wall.o srcs/print_texture.o \
srcs/scrin_bmp.o srcs/take_color.o srcs/take_map.o srcs/take_pos_sprit.o \
srcs/take_snwe_2.o srcs/take_snwe.o \
srcs/calculat_raycast_h.o srcs/calculat_raycast_v.o

CFLAGS = -Wall -Wextra -Werror -L minilibx -lmlx -framework OpenGL -framework AppKit

LIBFT = libft/libft.a

LIBMLX = minilibx/libmlx.dylib

all: $(NAME)

$(NAME): $(FUNC) $(LIBFT) $(LIBMLX)
	gcc &(CFLAGS) $^ $(NAME)

$(LIBFT):
	@$(MAKE) -C libft

$(LIBMLX):
	@$(MAKE) -C minilibx

clean:
	rm -f $(FUNC)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re

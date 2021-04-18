# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/06 15:29:03 by igomez-p          #+#    #+#              #
#    Updated: 2021/04/18 19:09:33 by igomez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = cub.c				\
	  src/read_cub.c	\
	  src/init.c		\
	  src/init_mlx.c	\
	  src/save_info.c	\
	  src/save_map.c	\
	  src/handler.c		\
	  src/move.c		\
	  src/raycaster.c	\
	  src/window.c		\
	  src/save_bmp.c	\
	  src/sprites.c		\
	  src/check_info.c	\

LIB = library/libft_$(OS).a \
	  minilibx-$(OS)/libmlx.a \

OS  = $(shell uname -s)

#ifeq MAC_SYSTEM
#MAC_SYSTEM=1
#endif

#ifeq LINUX_SYSTEM
#LINUX_SYSTEM=0
#endif

OBJ = $(SRC:.c=.o)

ifeq ($(OS), Darwin)
    MINILIB = -framework OpenGL -framework AppKit
else
    MINILIB = -lXext -lX11 -lz -lm
endif

%.o: %.c
	gcc -Wall -Werror -Wextra -g -I /usr/local/include -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		gcc -Wall -Werror -Wextra -g $(OBJ) -I /usr/local/include $(MINILIB) $(LIB) -o $(NAME)

clean:
		make -C minilibx-$(OS) clean
		rm -rf $(OBJ) libft.a libmlx.a

fclean: clean
		make -C minilibx-$(OS) clean
		rm -rf $(NAME)

re : fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/06 15:29:03 by igomez-p          #+#    #+#              #
#    Updated: 2021/01/31 19:48:04 by igomez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRC = cub.c				\
	  src/init.c		\
	  src/init_mlx.c	\
	  src/save_info.c	\
	  src/save_map.c	\
	  src/handler.c		\
	  src/check_info.c	\

LIB = library/libft.a \
	  library/libftprintf.a \
	  minilibx-linux/libmlx.a \
	  minilibx-linux/libmlx_Linux.a \


OBJ = $(SRC:.c=.o)

%.o: %.c
	gcc -Wall -Werror -Wextra -g -I /usr/local/include -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		gcc -Wall -Werror -Wextra -g $(OBJ) $(LIB) -I /usr/local/include -lm -lz -lXext -lX11 -L ./minilibx-linux -pthread -o $(NAME)

clean:
		make -C minilibx-linux clean
		rm -rf $(OBJ) libft.a libmlx.a

fclean: clean
		make -C minilibx-linux clean
		rm -rf $(NAME)

re : fclean all

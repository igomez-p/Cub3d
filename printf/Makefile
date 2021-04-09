# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: igomez-p <ire.go.pla@gmail.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/12 18:10:14 by igomez-p          #+#    #+#              #
#    Updated: 2020/01/16 18:56:45 by igomez-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	aux_functions.c \
		char_conversion.c \
		flags.c \
		ft_printf.c \
		hex_conversion.c \
		int_conversion.c \
		printfstruct.c \
		ptr_conversion.c \
		strings_conversion.c \
		

OBJ = ${SRC:.c=.o}

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

%.o:	%.c
		${CC} ${CFLAGS} -c $< -o $@


all:	$(NAME)

$(NAME): ${OBJ}
		make -C
		ar rc ${NAME} ${OBJ}

debug:
		$(CC) $(CFLAGS) -g $(SRC) libft.a

clean:
		rm -f ${OBJ}

fclean:	clean
		rm -f ${NAME} *.o

re:		fclean all
.PHONY:	all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbeaufil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 15:08:19 by nbeaufil          #+#    #+#              #
#    Updated: 2023/07/27 08:33:10 by nbeaufil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	readline/utils.c				\
			readline/funct.c				\
			readline/readline.c				\
			readline/read_history.c			\
			readline/auto_compl.c

CC		=	gcc
OBJS	=	${SRCS:.c=.o}
NAME	=	libreadline.a
FLAGS	=	#-Wall -Wextra -Werror
INCLUDE	=	-I readline
DEBUG	=

.c.o	:
	${CC} ${FLAGS} ${INCLUDE} ${DEBUG} -c $< -o ${<:.c=.o}

all	:	${NAME}

$(NAME)	:	${OBJS}
	ar -rcs ${NAME} ${OBJS}
	ranlib ${NAME}

test	:	$(NAME)
	${CC} ${FLAGS} ${INCLUDE} test.c -c -o test.o
	${CC} ${FLAGS} test.o -L. -lreadline ${INCLUDE} -o test

dclean	:
	rm -rf .rdlrc

clean	:
	rm -f ${OBJS}
	rm -f test.o

fclean	:	clean
	rm -f ${NAME}
	rm -f test

re	:	fclean all

.PHONY: all clean fclean re

.SILENT:

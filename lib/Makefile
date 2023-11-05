SRCS	=	utils.c				\
			funct.c				\
			readline.c				\
			read_history.c			\
			auto_compl.c

CC		=	gcc
OBJS	=	${SRCS:.c=.o}
NAME	=	readline.a
FLAGS	=	-Wall -Wextra -Werror
INCLUDE	=	-I readline
DEBUG	=

.c.o	:
	@${CC} ${FLAGS} ${INCLUDE} ${DEBUG} -c $< -o ${<:.c=.o}

all	:	${NAME}

$(NAME)	:	${OBJS}
	@ar -rcs ${NAME} ${OBJS}
	@ranlib ${NAME}


dclean	:
	@rm -rf .rdlrc

clean	:
	@rm -f ${OBJS}
	@rm -f test.o

fclean	: dclean clean
	@rm -f ${NAME}
	@rm -f test

re	:	fclean all

.PHONY: all clean fclean re dclean


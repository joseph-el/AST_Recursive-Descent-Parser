# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel-idr <yoel-idr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/01 11:31:53 by yoel-idr          #+#    #+#              #
#    Updated: 2023/02/14 18:31:09 by yoel-idr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	 			:= minishell

FLAGS 				:= -Wall -Wextra -Werror -fsanitize=address -g

SRCS 				:= srcs/
CC 					:= cc
RM					:= rm -f
INCLUDES			:= includes/
HEADERS 			:= environment.h executor.h expander.h lexer.h minishell.h
HEADERS 			:= $(addprefix $(INCLUDES), $(HEADERS))

RED    				:= \033[1;00m
GREEN  				:= \033[1;32m
YELLOW 				:= \033[1;33m
BLUE   				:= \033[0;34m
RESET  				:= \033[0m
COM_COLOR   		:= \033[0;34m
OBJ_COLOR   		:= \033[0;36m
OK_COLOR    		:= \033[0;32m
NO_COLOR    		:= \033[m

OK_STRING    		:= "[OK]"
COM_STRING  	    := "Compiling"
SHLEET    	 		:= "Shleet-minishell"
GARBAGE      		:= "gc_memory"
LIBT		 		:= "libtools"
DELETE       		:= "Deleting objects"


MINISHELL_FILE  	:=	minishell.c

UTILS_FILES 		:=  utils/g_error.c \
						utils/g_signel.c \
						utils/g_utils.c \
						utils/g_fd_utils.c \

LEXER_FILES 		:= 	lexer/lexer.c \
						lexer/lexer_helpful1.c \
						lexer/lexer_helpful2.c \
						lexer/list_construct.c \
						lexer/list_destroyer.c \

SYNTAX_FILES 		:=	lexer/syntax.c \

EXPANDER_FILES 		:=	expander/expander.c \
						expander/expander_helpful1.c \
						expander/expander_helpful2.c \
						expander/list_expansion.c \
						expander/list_construct.c \
						expander/wildcard.c \

EXECUTOR_FILES  	:=	executor/executor.c \
						executor/executor_utils.c \
						executor/ft_execve.c \


ENVIROMENT_FILES 	:= 	environment/environment.c \
						environment/environment_utils1.c \
						environment/environment_utils2.c \
						environment/environment_utils3.c \


BUILTINS_FILES  	:=  builtins/shleet_cd.c \
						builtins/shleet_echo.c \
						builtins/shleet_env.c \
						builtins/shleet_exit.c \
						builtins/shleet_export.c \
						builtins/shleet_pwd.c \
						builtins/shleet_unset.c \

FILES   			:= 	$(ENVIROMENT_FILES) \
						$(MINISHELL_FILE)   \
						$(EXECUTOR_FILES)   \
						$(EXPANDER_FILES)   \
						$(BUILTINS_FILES)   \
						$(SYNTAX_FILES)     \
						$(LEXER_FILES)      \
						$(UTILS_FILES)      \

FILES 				:= $(addprefix $(SRCS), $(FILES)) 
OBJS 				:= $(FILES:%.c=%.o)

GC_MEMORY_PATH		:= 	gc_memory/
LIBTOOLS_PATH		:= 	libtools/

GC_MEMORY 			:= $(addprefix $(GC_MEMORY_PATH), gc_memory.a)
LIBTOOLS 			:= $(addprefix $(LIBTOOLS_PATH), libtools.a)


s :
	echo "$(HEADERS)\n\n $(INCLUDES)"



all 				:	$(NAME)
							@printf "\n%b          %b" "$(GREEN) $(GARBAGE)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; 
							@printf "%b           %b" "$(GREEN) $(LIBT)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; 
							@printf "%b   %b" "$(GREEN) $(SHLEET)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; 

$(NAME) 			:  	$(GC_MEMORY) $(LIBTOOLS) $(OBJS)
							@$(CC) $(FLAGS) $^ -o $@ -lreadline

$(LIBTOOLS)			: 	$(addprefix $(LIBTOOLS_PATH), libtools.h)
							@make -C  $(LIBTOOLS_PATH) all 

$(GC_MEMORY)    	:  	$(addprefix $(GC_MEMORY_PATH), include/gc_memory.h)
							@make -C $(GC_MEMORY_PATH) all 

.c.o		 		:	$(HEADERS)
							@printf "%-100.900b\r" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@)$(NO_COLOR)\n";
							@$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDES) -I $(LIBTOOLS_PATH) -I $(addprefix $(GC_MEMORY_PATH), include)

clean   			:	
							@printf "   %b %b  %b" "$(BLUE) $(DELETE)" "$(GREEN) $(SHLEET)" "$(OK_COLOR) $(OK_STRING) \n$(RESET)" 
							@printf "%b %b  %-27b" "$(BLUE) $(DELETE)" "$(GREEN) $(GARBAGE)" "$(OK_COLOR) $(OK_STRING) \n$(RESET)" 
							@printf "%b %b  %-27b" "$(BLUE) $(DELETE)" "$(GREEN) $(LIBT)" "$(OK_COLOR) $(OK_STRING) \n$(RESET)" 
							@$(RM) $(OBJS)
							@make -C $(GC_MEMORY_PATH) clean
							@make -C $(LIBTOOLS_PATH) clean

fclean 				:  	clean
							@printf "\n\n   %b\t\t   %b\n" "$(BLUE) Deleting everything $(RESET)" "$(OK_COLOR)$(OK_STRING) $(RESET)"
							@make -C $(GC_MEMORY_PATH) fclean
							@make -C $(LIBTOOLS_PATH) fclean
							@$(RM) $(NAME)

re 					: 	fclean all

.PHONY 				: 	all clean fclean bonus re
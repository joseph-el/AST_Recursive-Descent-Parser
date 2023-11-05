NAME := rdb_exec #set to rdb

FLAGS := -std=c++17 -fsanitize=address -g3

SRCS := src/manageHeap.cpp src/tokenization.cpp src/rdb_main.cpp src/ast.cpp src/syntax.cpp src/equationResult.cpp src/print_ast.cpp

INC  := inc/
HDRS := rdb_main.hpp manageHeap.hpp tokenization.hpp ast.hpp syntax.hpp
HDRS := $(addprefix $(INC), $(HDRS))

OBJ := $(SRCS:%.cpp=%.o)

LIBPATH := 	lib/
LIB := $(addprefix $(LIBPATH), readline.a)


all : $(NAME)
		@echo "readline [✅]"
		@echo "rdb_exec [✅]"

$(NAME) : $(LIB) $(OBJ)	
		@c++ $(FLAGS) $^ -o $@

$(LIB) : $(addprefix $(LIBPATH), readline.h)
			@make -C  $(LIBPATH) re

%.o: %.cpp $(HDRS)
		@c++ $(FLAGS) -c $< -o $@ -I $(INC) -I $(LIBPATH)

clean :	$(OBJ) $(NAME)
		@make -C $(LIBPATH) clean
		@rm -f $^ 
		@echo "Clean [✅]"

re : clean all

.PHONY : clean all re

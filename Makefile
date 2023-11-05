NAME := rdb_exec #set to rdb

FLAGS := -std=c++17 -fsanitize=address -g3

SRCS := src/manageHeap.cpp src/tokenization.cpp src/rdb_main.cpp src/ast.cpp src/syntax.cpp src/equationResult.cpp src/print_ast.cpp

INC  := inc/
HDRS := rdb_main.hpp manageHeap.hpp tokenization.hpp ast.hpp syntax.hpp
HDRS := $(addprefix $(INC), $(HDRS))

OBJ := $(SRCS:%.cpp=%.o)


LIBPATH := $(addprefix $(shell pwd), /library/)
LIB     := $(addprefix $(LIBPATH),  libhistory.a  libreadline.a)

all : $(LIB) $(NAME)
		@echo "readline [✅]"
		@echo "rdb_exec [✅]"

$(NAME) : $(OBJ)
			cd $(addprefix $(shell pwd), /library) && bash configure
			make -C  $(LIBPATH) all
			c++ $(FLAGS) $^ -lreadline $(LIB) -o $@  

%.o: %.cpp $(HDRS)
		@c++ $(FLAGS) -c $< -o $@ -I $(INC)

clean :	$(OBJ) $(NAME)
		@make -C $(LIBPATH) clean
		@rm -f $^ 
		@echo "Clean [✅]"

re : clean all

.PHONY : clean all re

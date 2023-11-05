NAME := rdb_exec #set to rdb

FLAGS := -std=c++17 -fsanitize=address #-g3

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

$(NAME) : $(OBJ) $(LIB)
			@c++ $(FLAGS) -lreadline $^ -o $@ > /dev/null 2>&1

$(LIB) :
		@cd $(addprefix $(shell pwd), /library); echo "Generating library [⏳]"; bash configure > /dev/null 2>&1
		@make -C  $(LIBPATH) all > /dev/null 2>&1
	
%.o: %.cpp $(HDRS)
		@c++ $(FLAGS) -c $< -o $@ -I $(INC) > /dev/null 2>&1

clean :	
		@make -C $(LIBPATH) clean > /dev/null 2>&1
		@rm -f $(OBJ) $(NAME) > /dev/null 2>&1
		@echo "Clean [✅]"

re : clean all

.PHONY : clean all re

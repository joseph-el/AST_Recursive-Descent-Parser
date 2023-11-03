NAME := ast #set to rdb

FLAGS := -std=c++17 -fsanitize=address -g3
SRC := src/manageHeap.cpp src/tokenization.cpp src/main.cpp
HDR := inc/Calculator.hpp inc/manageHeap.hpp inc/tokenization.hpp

OBJ := $(SRC:%.cpp=%.o)

all : $(NAME)
		@echo "ast [✅]"

$(NAME) : $(OBJ)	
		@c++ $(FLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
		@c++ $(FLAGS) -c $< -o $@

clean :	$(OBJ) $(NAME)
		@rm -f $^ 
		@echo "Clean [✅]"

re : clean all

.PHONY : clean all re

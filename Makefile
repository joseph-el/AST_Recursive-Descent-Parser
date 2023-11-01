NAME := ast

all :
	c++ -std=c++11 Calculator.cpp manageHeap.cpp token.cpp && ./a.out
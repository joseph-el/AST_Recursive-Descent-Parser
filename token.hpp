# pragma once

#include <sstream>
#include <set>

extern "C" {
    #include <unistd.h>
    #include <stdalign.h>
    #include <stdlib.h>
    #include <stdnoreturn.h>
    #include <stdio.h>
}
#include "manageHeap.hpp"

enum Token {
    LPAR = (1<<1),
    RPAR = (1<<2),
    WSPACE = (1<<3),
    UNKNOWN = (1<<4),
    Division = (1<<5),
    Addition = (1<<6),
    Factorial = (1<<7),
    Subtraction = (1<<8),
    Multiplication = (1<<9),
    Exponentiation = (1<<10)
};

class tokenization : public deque< pair<int, Token> > {
    public:
        tokenization();
        void adding(pair<int, Token>&);
        Token getToken(const char &);
};

tokenization* lexer(stringstream &prompt);

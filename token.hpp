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

#define TOK (*token)
#define UNEXPECTED "syntax error near unexpected token "

enum Token {
    LPAR = (1<<1),
    RPAR = (1<<2),
    DIGIT = (1<<3),
    WSPACE = (1<<4),
    UNKNOWN = (1<<5),

    Division = (1<<6),
    Addition = (1<<7),
    Factorial = (1<<8),
    Modulation = (1<<9),
    Subtraction = (1<<10),
    Multiplication = (1<<11),
    Exponentiation = (1<<12),
    BEGIN          = (1<<13),
    END            = (1<<14)
};

class tokenization : public deque< pair<int, Token> > {
    public:
        
        tokenization() {
            push_back(make_pair(-1, BEGIN));
        }
        typedef deque< pair<int, Token>>::iterator Itr;
        void adding(pair<int, Token>&);
        Token getToken(const char &);
        int consumeNumbers(stringstream&, Token ret = DIGIT);
        void consumeWspace(stringstream&, Token ret = WSPACE);
        void getBack(stringstream&);
        bool unknownSyntax();
        int FindToken(Itr , bool);
        bool syntax();
        bool parenthesesSyntax(Itr &, bool);
        bool unarySyntax(Itr &);
        void error(const char *, const char );
        void printTokens();
};

tokenization* lexer(stringstream &prompt);

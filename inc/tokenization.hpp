# pragma once

#include <sstream>
#include <set>
#include <cmath>

#include "manageHeap.hpp"

#define UNEXPECTED "syntax error near unexpected token "
#define TOKEN_SIZE 14
#define TOK (*token)
#define GET_TOK *token[(int)log2((int)curr->second)]

enum Token {
    LPAR = (1<<1),
    RPAR = (1<<2),
    DIGIT = (1<<3),
    WSPACE = (1<<4),
    UNKNOWN = (1<<5),

    DIV = (1 << 6),
    ADD = (1 << 7),
    MOD = (1 << 8),
    SUB = (1 << 10),
    MUL = (1 << 11),
    POW = (1 << 12),
    FAC = (1 << 8),
    
    BEGIN          = (1<<13),
    END            = (1<<14),
};

                //  /     +      %     -     *     ^
#define BINARY_OPR (DIV | ADD | MOD | SUB | MUL | POW)

#define V_LPAR_LEFT (BEGIN | DIGIT | BINARY_OPR) // ( left
#define V_LPAR_RIGHT (DIGIT | LPAR) // ( right


#define V_RPAR_LEFT (RPAR | DIGIT | FAC) //  RPAR left
#define V_RPAR_RIGHT (BINARY_OPR | LPAR | FAC | DIGIT | END) // RPAR right

#define V_FAC_LEFT (RPAR | DIGIT) // ! left
#define V_FAC_RIGHT (BINARY_OPR | END | LPAR) // ! right

#define V_DIGIT_LEFT (BEGIN | BINARY_OPR | LPAR | RPAR) //  digit left
#define V_DIGIT_RIGHT (END | FAC | BINARY_OPR | LPAR | RPAR) // digit right

#define V_BINARY_LEFT (DIGIT | RPAR | FAC) // binary left
#define V_BINARY_RIGHT (LPAR | DIGIT) // binary right



class tokenization : public deque< pair<int, Token> > {
    public:
        
        tokenization() {
            push_back(make_pair(-1, BEGIN));
        }
        typedef deque< pair<int, Token>>::iterator Itr;
        void adding(pair<int, Token>&);
        Token getToken(const char &);
        int  consumeNumbers(stringstream&, Token ret = DIGIT);
        void consumeWspace(stringstream&, Token ret = WSPACE);
        void getBack(stringstream&);
        int FindToken(Itr , bool);

        bool syntax();

        bool unexpectedSyntax();
        bool parenthesesSyntax(Itr &);
        bool binarySyntax(Itr &);
        bool unarySyntax(Itr &);
    


        void error(const char *, const char );
        void printTokens();
};

tokenization* lexer(stringstream &prompt);

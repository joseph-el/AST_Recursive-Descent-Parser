#ifndef __TOK_H__
#define __TOK_H__

#include <sstream>
#include <set>
#include <cmath>

# include "rdb_main.hpp"

#define TOK (*token)
#define TOKEN_SIZE 14
#define GET_TOK *tokenType[(int)log2((int)curr->second) - 1]

enum Token : int {

    END     = (1<<1),
    BEGIN   = (1<<2),

    LPAR    = (1<<3),
    RPAR    = (1<<4),
    DIGIT   = (1<<5),
    WSPACE  = (1<<6),
    UNKNOWN = (1<<7),

    DIV = (1 << 8),
    ADD = (1 << 9),
    MOD = (1 << 10),
    SUB = (1 << 11),
    MUL = (1 << 12),
    POW = (1 << 13),
    FAC = (1 << 14)
};


typedef deque< pair<int, int>>::iterator Itr;

class tokenization : public deque< pair<int, int> > {
    public:
        
        tokenization() {
            push_back(make_pair(-1, BEGIN));
        }

        Token getToken(const char &);
        int  consumeNumbers(stringstream&, Token ret = DIGIT);
        void consumeWspace(stringstream&, Token ret = WSPACE);
        void getBack(stringstream&);
        void expander();
        int FindToken(Itr , bool);

        bool syntax();

        bool unexpectedSyntax();
        bool parenthesesSyntax(Itr &);
        bool binarySyntax(Itr &);
        bool unarySyntax(Itr &);
    
        void error(const char *, const char x = '?' );
        void printTokens();
};

extern const char* tokenType[TOKEN_SIZE];
tokenization* lexer(stringstream &prompt);

#endif
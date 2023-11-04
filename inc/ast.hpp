# pragma once

# include "tokenization.hpp"

struct ast {
    int           val;
    Token         token;
    struct s_ast* left;
    struct s_ast* right;
    ast() : val(-1) , token((Token)0), left(__null), right(__null) {}
};

class Parser {
    tokenization* token;
    Itr *it;

    public:
    Parser(tokenization*_tokens) : token(_tokens) {
        if (_tokens)
            it = &token->begin();
    }

    ast* parser();

    ast* expression() ;

    ast* term();

    ast* factor();

    ast* unary_expression();

    ast* primary();

    ast* number();

};


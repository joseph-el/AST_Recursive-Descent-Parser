# pragma once

# include "tokenization.hpp"

class ast {
    int           val;
    Token         token;
    struct s_ast* left;
    struct s_ast* right;

    
    /**
     *         Binary | ! | DIGIT | LPAR & RPAR 
    */
    ast() : val(-1) , token((Token)0), left(__null), right(__null) {}

};

typedef pair<int, Token> t_pair;


ast* parser(tokenization* );


ast* expression() ;

ast* term();

ast* factor();

ast* unary_expression();

ast* primary();

ast* number();
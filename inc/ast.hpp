# pragma once

# include "tokenization.hpp"

struct ast {
    double           val;
    Token         token;
    struct ast* left;
    struct ast* right;

//      <left> <right> <Token> <val>
    ast(ast* _left, ast* _right, Token _token, int _val) : 
        val(_val) , token(_token), left(_left), right(_right) {}
};

class Parser {
    tokenization* token;
    Itr it;

    public:
        Parser(tokenization*_tokens) : token(_tokens) {
            if (_tokens)
                it = token->begin();
            if (it->second == BEGIN) {
                // cout << "yes being found" << endl;
                it++;
                // cout << "tok after += : " << it->second  << endl; 
                // cout << "check num: " << it->first << endl;
            }


        }
        ast*   parser();
        void   scanToken();
        Token  currToken();

    private:
        ast* expression() ;
        ast* term();
        ast* factor();
        ast* unary_expression();
        ast* primary();
};

extern const char* tokenType[14];
#define heap Mgr.insertAddress


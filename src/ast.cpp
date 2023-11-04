# include "../inc/ast.hpp"

ast* Parser::parser() {
    ast* root = 0x0;

root = expression();
    if (!root or it->second &~ END)
        return 0x0;

    return root;
}


void Parser::scanToken() {
    it += (it != token->end());
}

Token Parser::currToken() {
    return it != token->end() ? (Token)it->second : END;
}

ast* Parser::expression() {

    ast* root;
    Token tok;

    root = term();

    while (true) {
        tok = currToken();
        if (tok & ADD | SUB) {


            root = 
        }

    }
    

    return nullptr; 
}

ast* Parser::term() {



    return nullptr; 
}

ast* Parser::factor() {
    return nullptr; 
}

ast* Parser::unary_expression() {
    return nullptr; 
}

ast* Parser::primary() {
    return nullptr; 
}

ast* Parser::number() {

    return nullptr; 
}
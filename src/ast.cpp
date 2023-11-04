# include "../inc/ast.hpp"

ast* Parser::parser() {
    ast* root = 0x0;

root = expression();
    if (!root or it->second &~ END)
        return 0x0;

    return root;
}


ast* Parser::expression() {

    ast* root;
    
    root = term();

    wh

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
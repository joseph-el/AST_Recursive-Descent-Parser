# include "../inc/ast.hpp"

ast* Parser::parser() {
    ast* root = 0x0;

    root = expression();
    // if (!root or it->second &~ END)
    //     return nullptr;

    return root;
}

void Parser::scanToken() {
    it += (it != token->end());
}

Token Parser::currToken() {
    return it != token->end() ? (Token)it->second : END;
}

// <expression> ::= <term> | <term> "+" <expression> | <term> "-" <expression>
ast* Parser::expression() {

    ast* root;
    Token tok;

    root = term();
    if (!root)
        return nullptr;
    while (true) {
        tok = currToken();
        if (tok & (ADD | SUB)) {
            scanToken();
            root = new ast(root,  term(), tok, -1);
            if (!root)
                return nullptr;       
        } else
            break; // case if just <term>
    }
    return root; 
}

// <term> ::= <factor> | <factor> "*" <term> | <factor> "/" <term> | <factor> "%" <term>
ast* Parser::term() {

    ast* root;
    Token tok;

    root = factor();
    if (!root)
        return nullptr;
    while (true) {
        tok = currToken();
        if (tok &  (MUL | MOD | DIV)) {
            scanToken();
            root = new ast(root, factor(), tok, -1);
            if (!root)
                return nullptr;
        } else
            break;
    }
    return root; 
}

// <factor> ::= <unary_expression> | <unary_expression> "^" <factor>
ast* Parser::factor() {
    ast* root;
    Token tok;

    root = unary_expression();
    if (!root)
        return nullptr;
    while (true) {
        tok = currToken();
        if (tok & POW) {
            scanToken();
            root = new ast(root, unary_expression(), tok, -1);
            if (!root)
                return nullptr;
        } else
            break;
    }
    return root; 
}

// <unary_expression> ::=  <primary> "!"
ast* Parser::unary_expression() {
    ast* root;
    Token tok;

    root = primary();
    tok  = currToken();
    if (!root)
        return nullptr;
    if (tok & FAC) {
        scanToken();
        root = new ast(root, nullptr, tok, -1);
        if (!root)
            return nullptr;
    }
    return root; 
}

// <primary> ::= "(" <expression> ")" | <number>
ast* Parser::primary() {
    ast* root;
    Token tok;

    tok = currToken();
    scanToken();
    switch (tok) {
        case LPAR:
            root = expression();
            scanToken(); // 100% the next is ) by the syntax 😀
            break;
        case DIGIT:
            root = new ast(nullptr, nullptr, tok, it->first);
            scanToken();
            break;
        default:
            break;
    }
    return root; 
}
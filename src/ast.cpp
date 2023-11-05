# include "../inc/ast.hpp"

const char* tokenType[TOKEN_SIZE] = {"END", "BEGIN",  "(", ")", "0", "WSPACE", "UNK", "/", "+", "%", "-", "*", "^", "!"};


ast* Parser::parser() {
    ast* root = 0x0;

    root = expression();

    if(!root)
        return 0x0;

    if (it->second &~ END) {
        cout << "last tok: " << it->second << endl;
        cout << "null because it &~ END" << endl;
        return 0x0;
    }

    return root;
}

void Parser::scanToken() {
    it ++;
}

Token Parser::currToken() {
    return it != token->end() ? (Token)it->second : END;
}

// <expression> ::= <term> | <term> "+" <expression> | <term> "-" <expression>
ast* Parser::expression() {

    ast* root;
    Token tok;

    // cout << "Expersion \n";

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

    // cout << "Term \n";

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

    // cout << "Factor \n";

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

    // cout << "Unary_expression \n";


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

    // cout << "Primary \n";
    
    tok = currToken();

    switch (tok) {
        case LPAR:
            scanToken(); // skip the LPAR
            root = expression();
            scanToken(); // 100% the next is ) by the syntax 😀
            break;
        case DIGIT:
            root = new ast(nullptr, nullptr, tok, it->first);
            scanToken();
            // cout << "after creat : " << it->first << endl;
            break;
        default:
            cout << "other in primary switch \n";
            break;
    }
    return root; 
}
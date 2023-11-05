# include "../inc/Calculator.hpp"

# define PARSER parser->parser()

std::string tokenToString(Token token) {
    switch (token) {
    case END: return "END";
    case BEGIN: return "BEGIN";
    case LPAR: return "LPAR";
    case RPAR: return "RPAR";
    case DIGIT: return "DIGIT";
    case WSPACE: return "WSPACE";
    case UNKNOWN: return "UNKNOWN";
    case DIV: return "DIV";
    case ADD: return "ADD";
    case SUB: return "SUB";
    case MUL: return "MUL";
    case MOD: return "MOD";
    case POW: return "POW";
    case FAC: return "FAC";
    default: return "UNKNOWN";
    }
}

void print_tree(ast* root, int indent) {
    if (root == nullptr) {
        return;
    }

    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }
    if (root->token == DIGIT) {
        std::cout << root->val << std::endl;
    } else {
        std::cout << tokenToString(root->token) << std::endl;
    }

    // Recursively print the left and right subtrees
    print_tree(root->left, indent + 1);
    print_tree(root->right, indent + 1);
}




int calculator(__unused int argc, __unused char *argv[] ) {
    tokenization* tokens = __null;
    ast* root;
    string prompt;

    while (true) {
        _gnl("equation :> ", prompt);

        stringstream ss(prompt);
        tokens = lexer(ss);
        if (tokens and tokens->syntax()) {
            tokens->expander();
            tokens->printTokens();
        } else {
            continue;
        }


        Parser *parser = new Parser(tokens);
        root = PARSER;
        if (!root) {
            cout << "null: " << endl;
            exit(12);
        }

        print_tree(root, 0);

        // equationResult(root);

         Mgr.clearHeap();
         tokens = __null;
    }

}
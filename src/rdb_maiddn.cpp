# include "../inc/Calculator.hpp"

# define PARSER parser->parser()

void print_tree(ast* root, int indent) {
    if (root == nullptr) {
        return;
    }

    for (int i = 0; i < indent; ++i) {
        cout << "  ";
    }
    if (root->token == DIGIT) {
        cout << root->val << endl;
    } else {
        cout << tokenType[(int)log2((int)root->token) - 1] << endl;
    }

    print_tree(root->left,  indent + 1);
    print_tree(root->right, indent + 1);
}







void printBT(const ast* node)
{
    printBT("", node, false);    
}



typedef long long result_t;

void equationResult(ast* root) {
    if (!root)
        return ;

    equationResult(root->right);
    equationResult(root->left);

    switch (root->token) {
        case ADD:
            root->val = root->left->val + root->right->val;
            break;
        case SUB:
            root->val = root->left->val - root->right->val;
            break;
        

        case MOD:
            root->val = (int)root->left->val % (int)root->right->val;
            break;
        case DIV:
            root->val = root->left->val / root->right->val;
            break;
        case MUL:
            root->val = root->left->val * root->right->val;
            break;

        case POW:
            root->val = pow(root->left->val, root->right->val);
            break;
        
        case FAC:
            root->val = factorial(root->left->val);
            break;


        default:
            break;
    }
}

int calculator(__unused int argc, __unused char *argv[] ) {
    tokenization* tokens = __null;
    ast*    root;
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

            // print_tree(root, 0);
            cout << endl;
            printBT(root);

            equationResult(root);
            
        cout << "Val : " << root->val << endl;
            Mgr.clearHeap();
            tokens = __null;
    }

}
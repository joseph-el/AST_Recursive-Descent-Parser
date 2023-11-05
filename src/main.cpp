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

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */



void printBT(const string& prefix, const ast* node, bool isLeft)
{
    if( node != nullptr )
    {
        cout << GREEN << prefix;

        cout << (isLeft ? "├──" : "└──" );

        cout << WHITE;
        if (node->token & DIGIT) {
            cout << " " <<  node->val << endl;
        } else {
            cout << " " <<  tokenType[(int)log2((int)node->token) - 1] << endl;
        }

        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void printBT(const ast* node)
{
    printBT("", node, false);    
}

int factorial(int n) {
  if(n > 1)
    return n * factorial(n - 1);
  else
    return 1;
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
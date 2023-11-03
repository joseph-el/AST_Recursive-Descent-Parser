# include "../inc/Calculator.hpp"

int calculator(__unused int argc, __unused char *argv[] ) {
    tokenization* tokens = __null;
    // ast* root;
    string prompt;

    while (true) {
        _gnl("equation :> ", prompt);

        stringstream ss(prompt);
        tokens = lexer(ss);
        // root = parser(tokens);
        // print_tree(root, 0);
        // equationResult(root);
        
        if (tokens and tokens->syntax()) {
            tokens->expander();
            tokens->printTokens();
        }

        Mgr.clearHeap();
        tokens = __null;
    }

}
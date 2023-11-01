# include "../inc/Calculator.hpp"

int calculator(__unused int argc,__unused char *argv[] ) {
    tokenization* tokens = nullptr;
    stringstream ss;
    // ast* root;
    string prompt;

    while (true) {
        _gnl("equation :> ", prompt);

        ss.str(prompt);
        tokens = lexer(ss);
        // root = parser(tokens);
        // print_tree(root, 0);
        // equationResult(root);
        // tokens->printTokens();

        Mgr.clearHeap();
    }

}
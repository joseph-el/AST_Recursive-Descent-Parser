# include "../inc/RDB.hpp"

int rdb_main(__unused int argc, __unused char *argv[] ) {
    tokenization* tokens;
    Parser*       parser;
    char*         prompt;  
    ast*          root;

    while (true) {
		prompt = readline(GREEN "equation> " WHITE);
        stringstream ss(prompt);
        tokens = lexer(ss);
        if (!tokens || !tokens->syntax())
            goto clearHeap;
        parser = new Parser(tokens);
        if (!parser || (root = pa)) {
            tokens->error("", "");
            goto clearHeap;
        }

        // print tree
        print_ast()

        clearHeap:

    }
}
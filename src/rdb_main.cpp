# include "rdb_main.hpp"

int rdb_main(__unused int argc, __unused char *argv[] ) {
    tokenization* tokens;
    Parser*       parser;
    char*         prompt;  
    ast*          root;

    while (true) {
		prompt = readline(GREEN "equation:> " WHITE);
        if (!prompt)
            break;
        add_history(prompt), gc_insert(prompt);
        stringstream ss(prompt);
        tokens = lexer(ss);
        if (!tokens || !tokens->syntax())
            goto done;
        parser = (Parser *)gc_insert(new Parser(tokens));
        if (!parser || !(root = parser->parser())) {
            tokens->error(UNEXPECTED);
            goto done;
        }
        print_ast("", root, false);
        eval(root);
        equationResult(tokens, root);
        done:
            clearHeap;
    }
    clearHeap;
    exit(EXIT_SUCCESS);
}